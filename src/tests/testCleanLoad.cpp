#include "testCleanLoad.h"
#include "../mqttWrapper.h"
#include "../clientHandler.h"
#include <unistd.h>


TestCleanLoad::TestCleanLoad()
{    
}

void TestCleanLoad::run_test()
{
    OutputHandler *output = new OutputHandler("output/cleanLoadTest.csv");
   
    MqttWrapper *mqtt;
    mqtt = new MqttWrapper("output", HOSTADDRESS,2000,true,LOOP_START);
    mqtt->set_output(output);     
    output->output_write_to_file("clients,",true);
    output->output_write_to_file("heap",false);
    mqtt->set_head_topic(std::string("$SYS/broker/clients/active"));
    mqtt->mqtt_subscribe(NULL,"$SYS/broker/clients/active",0);
    mqtt->mqtt_subscribe(NULL,"$SYS/broker/heap/current",0);
    ClientHandler *clients = new ClientHandler("clean",HOSTADDRESS,2000);
    clients->clients_create_subscribers(300,"/clean",0,false);
    while(!clients->is_sub_empty()){
        clients->clients_disconnect_subs(10);
        sleep(2);
    }
}
