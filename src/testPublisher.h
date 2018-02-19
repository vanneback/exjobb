#ifndef TESTPUBLISHER_H
#define TESTPUBLISHER_H

#include "mqttWrapper.h"

class TestPublisher {
public:
    TestPublisher(MqttWrapper *mqtt);
    ~TestPublisher();

    void publisher_publish_messages(const char* topic,int message_size,
         int number_of_messages, int qos);



private:
    MqttWrapper *mqtt;
};
#endif
