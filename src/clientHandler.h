#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include "mqttWrapper.h"
#include <string.h>
#include <fstream>
#include <vector>

class ClientHandler{
public:
    ClientHandler(const char *id, const char *host, int port);
    ~ClientHandler();

    int create_subscribers(int number_of_subs, char* topic, int qos=0,
                            bool clean_session=true);

    int create_clients(int number_of_clients, bool clean_session=true);

private:
    std::string id;
    const char* host;
    int port;
    std::vector<MqttWrapper*> sub_list;
    std::vector<MqttWrapper*> client_list;



};
#endif
