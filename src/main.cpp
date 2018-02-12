#include <stdlib.h>
#include <stdio.h>
#include "mqttWrapper.h"
#include "testPublisher.h"

const char app_version[] = "1.0.1";
const char app_name[] = "mqtt_client";
const char config_filename[] = "mqtt_client.json";

 int main(int argc, char const *argv[]) {


     MqttWrapper *mqtt;
     mqtt = new MqttWrapper("testclient", "localhost",2000);
     mqtt->mqtt_subscribe(NULL,"/hej",0);


     MqttWrapper *mqtt2;
     mqtt2 = new MqttWrapper("test2","localhost",2000);
     TestPublisher *test;
     test = new TestPublisher(mqtt2);
     test->test_publish_messages("/hej",100,10,0);
    // mqtt->mqtt_unsubscribe(NULL,"/hej");
    // mqtt->mqtt_subscribe("/hej",0);
     delete mqtt;

     return 0;
}
