#include "testPublisher.h"
#include "mqttWrapper.h"

TestPublisher::TestPublisher(MqttWrapper *mqtt)
{
    this->mqtt = mqtt;
}

TestPublisher::~TestPublisher(){

}

void TestPublisher::test_publish_messages(const char* topic, int message_size, int number_of_messages, int qos)
{
    char message [message_size];

    for(int i=0; i<number_of_messages; i++){
        mqtt->mqtt_publish(topic, message, qos);
    }

}
