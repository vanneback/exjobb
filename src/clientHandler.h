#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include "mqttWrapper.h"
#include <string.h>
#include <fstream>
#include <vector>
#include <list>

class ClientHandler{
public:
    /*
    * constructor: ClientHandler
    * 
    * sets variables used in the rest of the class
    * Parameters:
    *   id-     Char*. Used to set id of created clients.
    *   host-   Char*. Host adress to broker. Clients created connects to this adress.
    *   port-   int. Port number to connect to broker.
    */
    ClientHandler(const char *id, const char *host, int port);
    ~ClientHandler();

    /*
    * function: client_create_subscribers
    * 
    * Creates and connects subscribers to broker.
    *
    * Parameters:
    *   number_of_subs- int. Number of subscribers to connect.
    *   topic-          Char*. The topic to subscribe to.
    *   qos-            int. The qos of the subscription
    *   clean_session-  bool. If the subs should connect as a clean session or not.
    */
    int clients_create_subscribers(int number_of_subs, const char* topic, int qos=0,
                            bool clean_session=true);

    /*
    * function: client_create_clients
    * 
    * Creates and connects clients with no subscription.
    *
    * Parameters:
    *   number_of_clients-  int. Number of clients to connect.
    *   clean_session-      bool. If the clients should connect
    *                       as a clean session or not.
    */
    int clients_create_clients(int number_of_clients, bool clean_session=true);

    /*
    * function: client_create_and_publish
    * 
    * Creates and connects clients who publish messages.
    *
    * Parameters:
    *   number_of_pubs- int. Number of publishers to connect.
    *   topic-          Char*. The topic to publish to.
    *   size-           int. The size of each message.
    *   messages-       int. The number messages each publisher publish.
    *   qos-            int. The qos of the published messages.
    *   clean_session-  bool. If the publishers should connect as a 
    *                   clean session or not.
    */
    int clients_create_and_publish(int number_of_pubs, char* topic, int size,
         int messages, int qos=0, bool clean_session=true);


    /*
    * function: client_disconnect_subs,
    * 
    * Disconnects subscirbers from the broker.
    *
    * Parameters:
    *   number_to_disc- int. Number of subscribers to disconnect.
    *                   If 0 all subscribers will be disconnected.
    */
    int clients_disconnect_subs(int number_to_disc);

    /*
    * function: client_reconnect_subs,
    * 
    * Reconnects disconnected subscribers.
    *
    * Parameters:
    *   number_to_reconnect-    int. Number of subscribers to reconnect.
    *                           If 0 disconnected subscribers will be reconnected.
    *   clean_session-          bool. If true clients will be reconnected with
    *                           the clean_session flag as true. This flag only affects
    *                           Clients with the clean_session previously as false.
    */
    int clients_reconnect_subs(int number_to_reconnect=0, bool clean_session=true);

private:
    /*
    * function: create_id
    * 
    * Private function to create and id from a name and number.
    */
    char * create_id(const char *name, int num);

    std::string id;
    const char* host;
    int port;
    std::list<MqttWrapper*> sub_list;
    std::list<MqttWrapper*> client_list;
    std::list<MqttWrapper*> disc_list;



};
#endif
