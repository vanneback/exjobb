#include "clientHandler.h"
#include "mqttWrapper.h"
#include "testPublisher.h"
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>


ClientHandler::ClientHandler(const char *id, const char *host, int port):
    host(host),
    port(port),
    id(std::string(id))
{
}

ClientHandler::~ClientHandler()
{
   for(int i=0;i<sub_list.size(); i++){
       delete sub_list.front();
       sub_list.pop_front();
   }
   for(int j=0;j<client_list.size(); j++){
       delete client_list.front();
       client_list.pop_front();
   }
   for(int k=0;k<disc_list.size(); k++){
       delete disc_list.front();
       disc_list.pop_front();
   }
}

int ClientHandler::clients_create_subscribers(int number_of_subs,const char* topic, int qos,
                                                       bool clean_session)
{
    int size = sub_list.size();
    for (int i=0; i<number_of_subs; i++){

        char *str = create_id("-sub-",i+size);
        MqttWrapper *temp_mqtt = new MqttWrapper(str,host,port,clean_session,LOOP_START);
        temp_mqtt->mqtt_subscribe(NULL,topic,qos);
        sub_list.push_back(temp_mqtt);
    }
    return 0;
}


int ClientHandler::clients_create_clients(int number_of_clients, bool clean_session)

{
    for (int i=0; i<number_of_clients; i++){
        char* str = create_id("-client-",i);
        MqttWrapper *temp_mqtt = new MqttWrapper(str,host,port,clean_session);
        client_list.push_back(temp_mqtt);
    }
    return 0;
}

int ClientHandler::clients_create_and_publish(int number_of_pubs, char* topic, int size,
     int messages, int qos, bool clean_session)
{
    for (int i=0; i<number_of_pubs; i++){
        char* str = create_id("-pub-",i);
        MqttWrapper *temp_mqtt = new MqttWrapper(
            str,host,port,clean_session,LOOP_WRITE);
        TestPublisher *temp_pub = new TestPublisher(temp_mqtt);
        temp_pub->publisher_publish_messages(topic,size,messages,qos);
    }
    return 0;
}

int ClientHandler::clients_disconnect_subs(int number_to_disc)
{
    if(number_to_disc==0){
        number_to_disc = sub_list.size();
    }
    for(int i =0; i<number_to_disc;i++){
        MqttWrapper *mqtt = sub_list.front();
        mqtt->mqtt_disconnect();
        disc_list.push_back(mqtt);
        sub_list.pop_front();
    }
    return 0;
}

int ClientHandler::clients_reconnect_subs(int number_to_reconnect, bool clean_session)
{
    if(number_to_reconnect == 0){
        number_to_reconnect=disc_list.size();
    }
    for(int i=0; i<number_to_reconnect; i++) {
        MqttWrapper *temp_mqtt = disc_list.front();
        if(clean_session && temp_mqtt->get_clean_session()==false){
            MqttWrapper *clean_mqtt = new MqttWrapper(temp_mqtt->get_id(),
                                                      temp_mqtt->get_host(),
                                                      temp_mqtt->get_port(),
                                                      clean_session);
            
            sub_list.push_back(clean_mqtt);
            disc_list.pop_front();
            delete temp_mqtt;
        }else {
            temp_mqtt->mqtt_reconnect();
            sub_list.push_back(temp_mqtt);
            disc_list.pop_front();
        }
    }
    return 0;
}

char* ClientHandler::create_id(const char* name, int num)
{
    std::string temp_id;
    temp_id.append(name);
    temp_id.append("[");
    temp_id.append(id);
    temp_id.append("-");
    temp_id.append(std::to_string(num));
    temp_id.append("]");
    char* str = (char*) malloc(temp_id.length()+1); 
    temp_id.copy(str,temp_id.length(),0);
    return str;

}

