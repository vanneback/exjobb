#include "clientHandler.h"
#include "mqttWrapper.h"
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>

ClientHandler::ClientHandler(const char *id, const char *host, int port)
{
    this->host = host;
    this->port = port;
    this->id = std::string(id);
    sub_list = std::vector<MqttWrapper*> (0);
    client_list = std::vector<MqttWrapper*> (0);

}

ClientHandler::~ClientHandler()
{
    for(std::vector<MqttWrapper*>::iterator it = sub_list.begin(); it != sub_list.end(); ++it) {
        MqttWrapper *temp_mqtt = *it;
        delete temp_mqtt;
    }
}

int ClientHandler::create_subscribers(int number_of_subs, char* topic, int qos,
                                                        bool clean_session)
{
    for (int i=0; i<number_of_subs; i++){
        std::ostringstream temp_id;
        temp_id << "-sub-" << "[" << id << "]" << i;
        MqttWrapper *temp_mqtt = new MqttWrapper(temp_id.str().data(),host,port,clean_session);
        temp_mqtt->mqtt_subscribe(NULL,topic,qos);
        sub_list.push_back(temp_mqtt);
    }
    return 0;
}

int ClientHandler::create_clients(int number_of_clients, bool clean_session)
{
    for (int i=0; i<number_of_clients; i++){
        std::ostringstream temp_id;
        temp_id << "-client-" << "[" << id << i << "]";
        MqttWrapper *temp_mqtt = new MqttWrapper(temp_id.str().data(),host,port,clean_session);
        client_list.push_back(temp_mqtt);
    }
    return 0;
}
