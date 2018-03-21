#include <stdlib.h>
#include <stdio.h>
#include "mqttWrapper.h"
#include "publisher.h"
#include "outputHandler.h"
#include "clientHandler.h"
#include "tests/testSubsLoad.h"
#include "tests/testCleanLoad.h"
#include "tests/maxLoad.h"
#include <unistd.h>
#include <string>
#include <map>


const char app_version[] = "1.0.1";
const char app_name[] = "mqtt_client";
const char config_filename[] = "mqtt_client.json";

 int main(int argc, char const *argv[]) {


    //ClientHandler *clients = new ClientHandler("test3", HOSTADDRESS, PORT_DEFAULT);
    //clients->clients_random_subscriptions(10000);
    MaxLoad::run_consistent_load(1,1,1,INT32_MAX,0);
     //MaxLoad::run_message_load(200);
     //TestSubsLoad::run_sub_load(900,1);
    //TestCleanLoad::run_test();
    //TestSubsLoad::run_topics(1000);
   /*   MqttWrapper *mqtt = new MqttWrapper("disc", HOSTADDRESS,2000,true);
     mqtt->mqtt_subscribe(NULL,"/hej",1);

    MqttWrapper *mqtt2 = new MqttWrapper("pub", HOSTADDRESS,2000,true);
    TestPublisher::publisher_publish_messages(mqtt2, "/hej", 100, 1000, 1);
    */



//delete clients;
//delete mqtt;
//delete output;
     return 0;
}
