#include <stdlib.h>
#include <stdio.h>
#include "mqttWrapper.h"
#include "testPublisher.h"
#include "outputHandler.h"
#include "clientHandler.h"

const char app_version[] = "1.0.1";
const char app_name[] = "mqtt_client";
const char config_filename[] = "mqtt_client.json";

 int main(int argc, char const *argv[]) {

     OutputHandler *output = new OutputHandler("output/file");
     MqttWrapper *mqtt;
     mqtt = new MqttWrapper("testclient", "localhost",2000,true,LOOP_START);
     mqtt->set_output(output);
     mqtt->mqtt_subscribe(NULL,"$SYS/broker/messages/stored",0);
     mqtt->mqtt_subscribe(NULL,"$SYS/broker/heap/#",0);
     mqtt->mqtt_subscribe(NULL,"$SYS/broker/retained messages/#",0);
     mqtt->mqtt_subscribe(NULL,"$SYS/broker/clients/#",0);


     ClientHandler *clients = new ClientHandler("subs","localhost",2000);
     //clients->create_subscribers(50,"/hej");
     clients->create_clients(100);
     //mqtt->mqtt_disconnect();


     /*MqttWrapper *mqtt2;
     mqtt2 = new MqttWrapper("test2","localhost",2000,true,LOOP_WRITE);
     mqtt2->mqtt_max_inflight(0);
     TestPublisher *test;
     test = new TestPublisher(mqtt2);


     //ca 80 mb per körning//
     //test->test_publish_messages("/hej",100,10000,1);
    //test->test_write_to_file("output/test","testing \ntesting");


    //output->output_system_to_file("");
    //output->output_separation_line();


*/
//delete output;
delete clients;
delete mqtt;
delete output;
     return 0;
}
