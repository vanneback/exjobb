#include "mqttWrapper.h"

class TestPublisher {
public:
    TestPublisher(MqttWrapper *mqtt);
    ~TestPublisher();

    void test_publish_messages(const char* topic,int message_size,
         int number_of_messages, int qos);

    int test_write_to_file(const char* buffer);

    int test_system_to_file(const char* command);

    int test_separation_line();

    void set_file_name(const char* name);
    const char * get_file_name(void);

private:
    MqttWrapper *mqtt;
    const char* file_name;
};
