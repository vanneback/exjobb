#include "testSubsLoad.h"
#include "mqttWrapper.h"
#include "outputHandler.h"
#include "clientHandler.h"
#include <unistd.h>


TestSubsLoad::TestSubsLoad()
{

}

void TestSubsLoad::run_test(){
    OutputHandler *output = new OutputHandler("output/testSubsLoad.csv");
    MqttWrapper *mqtt;
    mqtt = new MqttWrapper("output", "localhost",2000,true,LOOP_START);
    mqtt->set_output(output);
    mqtt->set_head_topic(std::string("$SYS/broker/clients/active"));
    mqtt->mqtt_subscribe(NULL,"$SYS/broker/clients/active",0);
    output->output_write_to_file("clients",true);
    
    mqtt->subscribe(NULL,"$SYS/broker/heap/current",0);
    output->output_write_to_file(",Heap",false);

    sleep(1);
    pid_t pid = fork();
    if (pid == 0){
        ClientHandler *clients = new ClientHandler("parent","localhost",2000);
        for(int i=0; i<6; i++){
            clients->clients_create_subscribers(50,"/hej",0,true);
            sleep(2);
        }
        //delete clients;
    } else if(pid > 0){
        ClientHandler *clients2 = new ClientHandler("child","localhost",2000);
        for(int i=0; i<6; i++){
            clients2->clients_create_subscribers(50,"/hej",0,true);
            sleep(2);
        }
        //delete clients;
    } else {
        printf("fork failed\n");
    }

    delete mqtt;
    delete output;
}