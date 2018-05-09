#include "maxLoad.h"
#include "../mqttWrapper.h"
#include "../clientHandler.h"
#include "../publisher.h"
#include <unistd.h>
#include <chrono>
#include <thread>
#include <string>

MaxLoad::MaxLoad()
{
}

void MaxLoad::run_message_load(int mb)
{
    //MqttWrapper *sub = new MqttWrapper("subscriber", HOSTADDRESS, PORT_DEFAULT, false,LOOP_START);
    MqttWrapper *pub = new MqttWrapper("publisher", HOSTADDRESS, PORT_DEFAULT, true, LOOP_WRITE);
    pub->mqtt_max_inflight(0);
    Publisher::publish_messages(pub, "/load", mb, 1000, 1);
    printf("Cleaned\n");
    delete pub;

}

void MaxLoad::run_consistent_load(int kb, int no_messages, int subs,int duration, int qos)
{
    ClientHandler *clients = new ClientHandler("client",LAPTOPADDRESS,PORT_DEFAULT);
    if(subs>0){
        clients->clients_create_subscribers(subs,"test/+/",qos);
    } else{
        clients->clients_create_subscribers(1,"/delay",qos);
    }

    MqttWrapper *pub = new MqttWrapper("publish", HOSTADDRESS,PORT_DEFAULT, true, 1);
    
    unsigned long int byte_size = kb * 1000;
    if(byte_size > MAX_BYTE_SIZE){
        printf("\nmax reached!!!\n\n");
        byte_size = MAX_BYTE_SIZE;
    }
    unsigned char message[byte_size];

    int count =1;
    std::string temp_id;
    for(int j =0; j<duration; j++){
        for(int i=0; i<no_messages; i++){  
            temp_id=std::string("test/");
            temp_id.append(std::to_string(count));
            temp_id.append("/");
            pub->mqtt_publish(byte_size,temp_id.data(),&message,qos);
            printf("%s\n",temp_id.data());
            if(count%100==0){
                count=0;
            }
            count++;

            std::this_thread::sleep_for(std::chrono::microseconds(1000000/no_messages));            
        }
    

        if(subs<1){
                pub->mqtt_publish(byte_size,"load/",&message,qos);
        }
    }
}