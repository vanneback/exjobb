#include "maxLoad.h"
#include "../mqttWrapper.h"
#include "../clientHandler.h"
#include "../publisher.h"
#include <unistd.h>


MaxLoad::MaxLoad()
{    
}

void MaxLoad::run_message_load(int mb)
{
    MqttWrapper *sub = new MqttWrapper("subscriber","localhost",2000,false);
    MqttWrapper *pub = new MqttWrapper("publisher","localhost",2000,true,false);

    sub->mqtt_subscribe(NULL,"/hej",1);
    sub->mqtt_disconnect();
    pub->mqtt_max_inflight(0);
    
    Publisher::publish_messages(pub,"/hej",mb,1000,1);
    sleep(5);
    MqttWrapper *clean = new MqttWrapper("subscriber","localhost",2000,true);



}