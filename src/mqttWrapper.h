#ifndef MQTTWRAPPER_H
#define MQTTWRAPPER_H
#include <mosquittopp.h>
#include <mosquitto.h>

class MqttWrapper : public mosqpp::mosquittopp
{
public:
    MqttWrapper(const char *id, const char *host, int port);
    ~MqttWrapper();

    bool mqtt_publish(const char* topic, const char* message, int qos);
    bool mqtt_subscribe(int *mid,const char* topic, int qos);
    bool mqtt_unsubscribe(int *mid, const char* topic);
    virtual void on_connect(int rc);
    virtual void on_disconnect(int rc);
    virtual void on_subscribe(int mid, int qos_count, const int *qranted_qos);
    virtual void on_publish(int mid);
    virtual void on_message(const struct mosquitto_message *message);
    virtual void on_unsubscribe(int mid);
    virtual void on_log(int level, const char *str);
    virtual void on_error();



private:
    const char* host;
    const char* id;
    int port;
    int keepalive;


};

#endif
