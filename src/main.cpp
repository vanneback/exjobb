#include <stdlib.h>
#include <stdio.h>
#include "mqttWrapper.h"
#include "testPublisher.h"
#include "outputHandler.h"
#include "clientHandler.h"
#include "testSubsLoad.h"
#include <unistd.h>
#include <string>


const char app_version[] = "1.0.1";
const char app_name[] = "mqtt_client";
const char config_filename[] = "mqtt_client.json";

 int main(int argc, char const *argv[]) {

     TestSubsLoad::run_test();
     /* OutputHandler *output = new OutputHandler("output/test");
   
     MqttWrapper *mqtt;
     mqtt = new MqttWrapper("testclient3", "localhost",2000,true,LOOP_START);
     mqtt->set_output(output);
     //mqtt->mqtt_subscribe(NULL,"$SYS/broker/messages/stored",0);
     mqtt->set_head_topic(std::string("$SYS/broker/clients/active"));
     mqtt->mqtt_subscribe(NULL,"$SYS/broker/clients/active",0);
     mqtt->mqtt_subscribe(NULL,"$SYS/broker/messages/sent",0);
     mqtt->mqtt_subscribe(NULL,"$SYS/broker/heap/current",0);
    // mqtt->mqtt_subscribe(NULL,"$SYS/broker/retained messages/#",0);
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
