#include "mqttWrapper.h"
#include <mosquittopp.h>
#include <mosquitto.h>
#include <stdio.h>
#include <string.h>



MqttWrapper::MqttWrapper(const char *id, const char *host, int port):
mosquittopp(id)
{
    this->id = id;
    this->port = port;
    this->host = host;
    mosqpp::lib_init();
    keepalive=120; //seconds
    connect_async(host,port,keepalive);    //connects to broker
    loop_start();
}

MqttWrapper::~MqttWrapper(){
    loop_stop();
    mosqpp::lib_cleanup();
}

bool MqttWrapper::mqtt_publish(const char * topic, const char* message, int qos)
{
    int ret = publish(NULL,topic,strlen(message), message,qos,false);
    return(ret == MOSQ_ERR_SUCCESS);
}

bool MqttWrapper::mqtt_subscribe(int *mid, const char* topic, int qos)
{
    int ret = subscribe(mid,topic,qos);

    if(!ret){
        printf("sub to >> %s << succeeded\n",topic);
        return true;
    } else {
        printf("sub to >> %s << failed\n",topic );
        return false;
    }
}

bool MqttWrapper::mqtt_unsubscribe(int *mid, const char* topic){
    int ret;
    if(!ret == unsubscribe(mid, topic)){
        printf("unsub to >> %s << succeeded \n", topic);
        return true;
    } else {
        printf("unsub to >> %s << failed \n", topic);
        return false;
    }
}


void MqttWrapper::on_connect(int rc)
{
    printf("Conneted with code %d. \n", rc);

    if(rc==0){
        //subscribe(NULL,"/hej");
    } else{
        printf("Could not connect : %d\n",rc );
    }
}

void MqttWrapper::on_disconnect(int rc)
{
    printf("Disconneted with code %d. \n", rc);
}

void MqttWrapper::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    printf("Subscription succeeded. \n");

}

void MqttWrapper::on_message(const struct mosquitto_message *message)
{
    char buf[100];
    memset(buf,0,50*sizeof(char));
    memcpy(buf,message->payload,50*sizeof(char));
    printf("message -> %s \n",buf);

}

void MqttWrapper::on_unsubscribe(int mid){
    printf("unsubscribed sucessfull \n");
}

void MqttWrapper::on_log(int level, const char *str){
    if(level == MOSQ_LOG_WARNING){
        printf("log: %s \n",str);
    }

}

void MqttWrapper::on_error(){
    printf("Error \n");
}

void MqttWrapper::on_publish(int mid)
{
    printf("publish succeeded. >> %d <<\n",mid);
}
