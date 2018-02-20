#ifndef TESTPUBLISHER_H
#define TESTPUBLISHER_H

#include "mqttWrapper.h"

class TestPublisher {
public:
    TestPublisher();
    ~TestPublisher();

    static void publisher_publish_messages(MqttWrapper *mqtt ,const char* topic,
                    int message_size,int number_of_messages, int qos);



private:
    MqttWrapper *mqtt;
};
#endif
