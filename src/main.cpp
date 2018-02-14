#include <stdlib.h>
#include <stdio.h>
#include "mqttWrapper.h"
#include "testPublisher.h"

const char app_version[] = "1.0.1";
const char app_name[] = "mqtt_client";
const char config_filename[] = "mqtt_client.json";

 int main(int argc, char const *argv[]) {


    /* MqttWrapper *mqtt;
     mqtt = new MqttWrapper("testclient", "localhost",2000,false);
     mqtt->mqtt_subscribe(NULL,"/hej",1);
     mqtt->mqtt_disconnect();*/


     MqttWrapper *mqtt2;
     mqtt2 = new MqttWrapper("test2","localhost",2000,true,LOOP_WRITE);
     mqtt2->mqtt_max_inflight(0);
     TestPublisher *test;
     test = new TestPublisher(mqtt2);
     test->set_file_name("/home/emil/miips/mosquitto_client/src/output/file");

     //ca 80 mb per körning//
     //test->test_publish_messages("/hej",100,10000,1);
    //test->test_write_to_file("output/test","testing \ntesting");
    test->test_system_to_file("free -m");
    test->test_separation_line();


     //delete mqtt;

     delete test;
     delete mqtt2;

     return 0;
}
