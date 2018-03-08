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


const char app_version[] = "1.0.1";
const char app_name[] = "mqtt_client";
const char config_filename[] = "mqtt_client.json";

 int main(int argc, char const *argv[]) {

     
     //MaxLoad::run_message_load(400);
    // TestSubsLoad::run_sub_load(900,1);
    //TestCleanLoad::run_test();
    //TestSubsLoad::run_topics(1000);
   /*   MqttWrapper *mqtt = new MqttWrapper("disc", "localhost",2000,true);
     mqtt->mqtt_subscribe(NULL,"/hej",1);

    MqttWrapper *mqtt2 = new MqttWrapper("pub", "localhost",2000,true);
    TestPublisher::publisher_publish_messages(mqtt2, "/hej", 100, 1000, 1);
 */

    /*// mqtt->mqtt_subscribe(NULL,"$SYS/broker/retained messages/#",0);
     sleep(2);
     ClientHandler *clients = new ClientHandler("test3","localhost",2000);
     for(int i=0; i<30; i++){
        clients->clients_create_subscribers(10,"/hej",0,true);
        sleep(2);
        //output->output_separation_line();
     } */
    


     //ca 80 mb per körning//
     //test->test_publish_messages("/hej",100,10000,1);
    //test->test_write_to_file("output/test","testing \ntesting");


    //output->output_system_to_file("");
    //output->output_separation_line();



//delete clients;
//delete mqtt;
//delete output;
     return 0;
}
