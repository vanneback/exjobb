#include "testPublisher.h"
#include "mqttWrapper.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>



TestPublisher::TestPublisher(MqttWrapper *mqtt)
{
    this->mqtt = mqtt;
}

TestPublisher::~TestPublisher(){

}

void TestPublisher::test_publish_messages(const char* topic, int message_size, int number_of_messages, int qos)
{
    unsigned long int byte_size = message_size * 1000;
    if(byte_size > MAX_BYTE_SIZE){
        byte_size = MAX_BYTE_SIZE;
    }
    unsigned char message[byte_size];
    printf("%d Kb/message x %d messages = %lu kilobytes\n",
    message_size,number_of_messages, (byte_size*number_of_messages)/1000);
    for(int i=0; i<number_of_messages; i++){
        mqtt->mqtt_publish(byte_size,topic, &message, qos);
    }
}
