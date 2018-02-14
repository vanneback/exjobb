#include "mqttWrapper.h"

class TestPublisher {
public:
    TestPublisher(MqttWrapper *mqtt);
    ~TestPublisher();

    void test_publish_messages(const char* topic,int message_size,
         int number_of_messages, int qos);



private:
    MqttWrapper *mqtt;
};
