#include "mqttWrapper.h"
#include "outputHandler.h"
#include <mosquittopp.h>
#include <mosquitto.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>


MqttWrapper::MqttWrapper(void) 
{

}

MqttWrapper::MqttWrapper(const MqttWrapper &obj)
{
    id = obj.id;
    host = obj.host;
    port = obj.port;
    keepalive = obj.keepalive;
    output = obj.output;
    type = obj.type;
    clean_session = obj.clean_session;
}

MqttWrapper::MqttWrapper(const char *id, const char *host, int port, bool clean_session, int type):
    mosquittopp(id,clean_session),
    id(id),
    port(port),
    host(host),
    output(NULL),
    type(type)

{
    mosqpp::lib_init();
    connect(host,port,keepalive);

    if(type == LOOP_START){
        loop_start();
    } else if(type == LOOP_WRITE){
        loop_write();
    } else if(type == LOOP_READ){
        loop_read();
    } else if (type==NO_LOOP){
        
    }
}


MqttWrapper::~MqttWrapper(){
    loop_stop();
    mosqpp::lib_cleanup();
}


bool MqttWrapper::mqtt_publish(int message_size, const char * topic, const void* message, int qos)
{
    int ret = publish(NULL,topic,message_size, message,qos,false);
    return(ret == MOSQ_ERR_SUCCESS);
}

bool MqttWrapper::mqtt_subscribe(int *mid, const char* topic, int qos)
{
    int ret = subscribe(mid,topic,qos);

    if(!ret){
        printf("[%s] sub to >> %s << succeeded\n",id,topic);
        return true;
    } else {
        printf("[%s] sub to >> %s << failed\n",id,topic );
        return false;
    }
}

bool MqttWrapper::mqtt_unsubscribe(int *mid, const char* topic){
    int ret = unsubscribe(mid, topic);
    if(!ret){
        printf("[%s] unsub to >> %s << succeeded \n", id,topic);
        return true;
    } else {
        printf("[%s] unsub to >> %s << failed \n", id, topic);
        return false;
    }
}

int MqttWrapper::mqtt_max_inflight(unsigned int max)
{
    return max_inflight_messages_set(max);
}

int MqttWrapper::mqtt_disconnect()
{
    return disconnect();
}

int MqttWrapper::mqtt_reconnect()
{
    return reconnect();
}

void MqttWrapper::on_message(const struct mosquitto_message *message)
{
    char buf[100];
    std::string out_message = std::string();
    std::string topic = std::string(message->topic);
    memset(buf,0,50*sizeof(char));
    memcpy(buf,message->payload,50*sizeof(char));
    if(output){
        out_message.append(buf);
        out_message.append(",");
        if(head_topic.compare(topic)==0){
           output->output_write_to_file(out_message.data(),true);
           for (auto& element: topics) {
                element.second = true;
            }    
        } else {
            if(topics.at(topic)==true){
                output->output_write_to_file(out_message.data(),false);
                topics.at(topic) = false;
            }
        }

    } else {
    printf("%s \n",buf);
    }
}

void MqttWrapper::on_connect(int rc)
{
    printf("[%s] Conneted with code %d. \n",id, rc);

    if(rc==0){

    } else{
        printf("[%s] Could not connect : %d\n",id ,rc );
    }
}

void MqttWrapper::on_disconnect(int rc)
{
    printf("[%s] Disconneted with code %d. \n",id, rc);
    disconnect();
   // loop_stop();
   // mosqpp::lib_cleanup();

}

void MqttWrapper::on_subscribe(int mid, int qos_count, const int *granted_qos)
{

}

void MqttWrapper::on_unsubscribe(int mid){
    printf("unsubscribed sucessfull \n");
}

void MqttWrapper::on_log(int level, const char *str){
    if(level == MOSQ_LOG_WARNING){
        printf("log: %s \n",str);
    } else if(level == MOSQ_LOG_DEBUG){

    }


}

void MqttWrapper::on_error(){
    printf("Error \n");
}

void MqttWrapper::on_publish(int mid)
{
    printf("publish succeeded. id[%d]\n",mid);
}

void MqttWrapper::set_output(OutputHandler *output)
{
    this->output = output;
}

OutputHandler* MqttWrapper::get_output()
{
    return output;
}

const char* MqttWrapper::get_id()
{
    return id;
}

void MqttWrapper::set_id(const char* id)
{
    this->id = id;
}

bool MqttWrapper::get_clean_session(void)
{
    return clean_session;
}

void MqttWrapper::set_clean_session(bool clean_session){
    this->clean_session = clean_session;
}

const char* MqttWrapper::get_host()
{
    return host;
}

int MqttWrapper::get_port()
{
    return port;
}

void MqttWrapper::set_head_topic(std::string topic)
{
    this->head_topic = topic;
}

void MqttWrapper::add_topic(std::string topic){
    topics.insert(std::pair<std::string,bool>(topic,true));
}


