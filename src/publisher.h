#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "mqttWrapper.h"

class Publisher
{
  public:
    Publisher();
    ~Publisher();

  /*
    * function: publish_messages
    * 
    * Publishes alot of messages at once
    *
    * Parameters:
    *   mqtt-    Mqttwrapper *. The mqtt instance to publish from.
    *   topic-           char*. The topic to publish on.
    *   message_size-      int. The size of each message. In Kilobytes.
    *   number_of_messages int. The number of messages. Each messages is of size from
    *                           message_size.
    *   qos-               int. The qos level.                          
    */
    static void publish_messages(MqttWrapper *mqtt ,const char* topic,
                    int message_size,int number_of_messages, int qos);



private:
    MqttWrapper *mqtt;
};
#endif
