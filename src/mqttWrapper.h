#ifndef MQTTWRAPPER_H
#define MQTTWRAPPER_H
#include <mosquittopp.h>
#include <mosquitto.h>
#include <string>
#include <vector>

#include "outputHandler.h"

#define LOOP_START 1
#define LOOP_WRITE 2
#define LOOP_READ 3
#define NO_LOOP 4

#define MAX_BYTE_SIZE 10000

class MqttWrapper : public mosqpp::mosquittopp
{
public:
    MqttWrapper(void);
    MqttWrapper(const char *id, const char *host, int port, bool clean_session=true, int type=LOOP_START);
    MqttWrapper(const MqttWrapper &obj);  
    ~MqttWrapper();

    bool mqtt_publish(int message_size, const char* topic, const void* message, int qos);
    bool mqtt_subscribe(int *mid,const char* topic, int qos);
    bool mqtt_unsubscribe(int *mid, const char* topic);
    int mqtt_max_inflight(unsigned int max);
    int mqtt_disconnect();
    int mqtt_reconnect();
    virtual void on_connect(int rc);
    virtual void on_disconnect(int rc);
    virtual void on_subscribe(int mid, int qos_count, const int *qranted_qos);
    virtual void on_publish(int mid);
    virtual void on_message(const struct mosquitto_message *message);
    virtual void on_unsubscribe(int mid);
    virtual void on_log(int level, const char *str);
    virtual void on_error();

    void add_topic(char* topic);
    void set_output(OutputHandler *output);
    OutputHandler* get_output();
    const char* get_id();
    void set_id(const char* id);
    bool get_clean_session(void);
    void set_clean_session(bool);
    const char* get_host();
    int get_port();
    void set_head_topic(std::string topic);



private:
    bool clean_session;
    const char* host;
    const char* id;
    int port;
    int keepalive;
    int type;
    OutputHandler *output;
    std::string head_topic;
    std::vector<std::string> topics;

};

#endif
