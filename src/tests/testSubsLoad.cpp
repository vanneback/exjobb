#include "testSubsLoad.h"
#include "../mqttWrapper.h"
#include "../outputHandler.h"
#include "../clientHandler.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cmath>

TestSubsLoad::TestSubsLoad()
{
}

void TestSubsLoad::create_subs(int id, OutputHandler *out, bool clean_session, int qos)
{
    ClientHandler *clients = new ClientHandler(std::to_string(id).data(), HOSTADDRESS, PORT_DEFAULT);
    for (int i = 0; i < 30; i++)
    {
        clients->clients_create_subscribers(10, "/hej", qos, clean_session);
        sleep(1);
    }
    delete clients;
}

void TestSubsLoad::create_clients(int id)
{
    ClientHandler *clients = new ClientHandler(std::to_string(id).data(), HOSTADDRESS, PORT_DEFAULT);
    for (int i = 0; i < 30; i++)
    {
        clients->clients_create_clients(10, true);
        sleep(1);
    }
    delete clients;
}

void TestSubsLoad::run_topics(int topics)
{
    OutputHandler *output = new OutputHandler("output/topicsTest.csv");

    MqttWrapper *mqtt;
    mqtt = new MqttWrapper("test", HOSTADDRESS, PORT_DEFAULT, true, LOOP_START);
    mqtt->set_output(output);
    mqtt->set_head_topic(std::string("$SYS/broker/subscriptions/count"));
    mqtt->mqtt_subscribe(NULL, "$SYS/broker/subscriptions/count", 0);
    output->output_write_to_file("topics,", true);

    mqtt->mqtt_subscribe(NULL, "$SYS/broker/heap/current", 0);
    output->output_write_to_file("heap", false);
    mqtt->add_topic(std::string("$SYS/broker/heap/current"));

    mqtt->add_topic(std::string("/vmstat"));
    mqtt->subscribe(NULL, "/vmstat", 0);
    output->output_write_to_file(",cs,us,sy,id,wa,st", false);
    ClientHandler *clients = new ClientHandler("test3", HOSTADDRESS, PORT_DEFAULT);
    clients->clients_random_subscriptions(topics);
}
void TestSubsLoad::run_sub_load(int subs, int type)
{
    OutputHandler *output;
    if (type == 1)
    {
        output = new OutputHandler("output/testSubsLoad.csv");
    }
    else if (type == 2)
    {
        output = new OutputHandler("output/testClientLoad.csv");
    }
    else
    {
        printf("invalid type\n");
        return;
    }
    MqttWrapper *mqtt;
    mqtt = new MqttWrapper("output", HOSTADDRESS, PORT_DEFAULT, true, LOOP_START);
    mqtt->set_output(output);

    mqtt->set_head_topic(std::string("$SYS/broker/clients/active"));
    mqtt->mqtt_subscribe(NULL, "$SYS/broker/clients/active", 0);
    output->output_write_to_file("clients", true);

    mqtt->add_topic(std::string("$SYS/broker/heap/current"));
    mqtt->subscribe(NULL, "$SYS/broker/heap/current", 0);
    output->output_write_to_file(",Heap", false);

    output->output_write_to_file(",cs,us,sy,id,wa,st", false);
    mqtt->add_topic(std::string("/vmstat"));
    mqtt->subscribe(NULL, "/vmstat", 0);

    int n = ceil(subs / 300);
    printf("n = %d\n", n);
    sleep(1);


    pid_t pid_array[n];
    pid_t pid;
    pid_t parent;
    int status = 0;
    for (int i = 0; i < n; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            printf("error in fork\n");
            exit(-1);
        }
        else if (pid == 0)
        {
            if (type == 1)
            {
                create_subs(i, output);
            }
            else if (type == 2)
            {
                create_clients(i);
            }
            exit(0);
        }
    }
    while (parent = wait(&status));

    delete mqtt;
    delete output;
}