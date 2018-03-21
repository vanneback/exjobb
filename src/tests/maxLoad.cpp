#include "maxLoad.h"
#include "../mqttWrapper.h"
#include "../clientHandler.h"
#include "../publisher.h"
#include <unistd.h>
#include <chrono>
#include <thread>

MaxLoad::MaxLoad()
{
}

void MaxLoad::run_message_load(int mb)
{
    MqttWrapper *sub = new MqttWrapper("subscriber", HOSTADDRESS, PORT_DEFAULT, false);
    MqttWrapper *pub = new MqttWrapper("publisher", HOSTADDRESS, PORT_DEFAULT, true, false);

    sub->mqtt_subscribe(NULL, "/hej", 1);
    sub->mqtt_disconnect();
    pub->mqtt_max_inflight(0);

    OutputHandler* output;
    MqttWrapper *mqtt;
    output= new OutputHandler("output/maxload.csv");
    mqtt = new MqttWrapper("output", HOSTADDRESS, PORT_DEFAULT, true, LOOP_START);
    mqtt->set_output(output);

    mqtt->set_head_topic(std::string("$SYS/broker/messages/stored"));
    mqtt->mqtt_subscribe(NULL, "$SYS/broker/messages/stored", 0);
    output->output_write_to_file("storedmsg", true);

    mqtt->add_topic(std::string("$SYS/broker/heap/current"));
    mqtt->subscribe(NULL, "$SYS/broker/heap/current", 0);
    output->output_write_to_file(",Heap", false);

    output->output_write_to_file(",cs,us,sy,id,wa,st", false);
    mqtt->add_topic(std::string("/vmstat"));
    mqtt->subscribe(NULL, "/vmstat", 0);

    /*for(int i =0; i<20; i++){
        Publisher::publish_messages(pub, "/hej", mb, 1000/20, 1);
        sleep(3);
    }*/
    Publisher::publish_messages(pub, "/hej", mb, 1000, 1);

    //MqttWrapper *clean = new MqttWrapper("subscriber",HOSTADDRESS,PORT_DEFAULT,true);
    printf("Cleaned\n");
}

void MaxLoad::run_consistent_load(int kb, int no_messages, int subs,int duration, int qos)
{
    ClientHandler *clients = new ClientHandler("cons",HOSTADDRESS,PORT_DEFAULT);
    if(subs>0){
        clients->clients_create_subscribers(subs,"/load",qos);
    } else{
        clients->clients_create_subscribers(1,"/delay",qos);
    }

    MqttWrapper *pub = new MqttWrapper("publisher", HOSTADDRESS, PORT_DEFAULT, true, 1);

    unsigned long int byte_size = kb * 1000;
    if(byte_size > MAX_BYTE_SIZE){
        printf("\nmax reached!!!\n\n");
        byte_size = MAX_BYTE_SIZE;
    }
    unsigned char message[byte_size];
    
    for(int j =0; j<duration; j++){
        for(int i=0; i<no_messages; i++){
            pub->mqtt_publish(byte_size,"/load", &message, qos);
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/no_messages));
            
            printf("msg:%d + size:%d\n",i+1*j+1,byte_size);
            
        }
        if(subs<1){
                pub->mqtt_publish(byte_size,"/delay",&message,qos);
        }
    }
}