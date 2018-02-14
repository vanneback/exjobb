#include "testPublisher.h"
#include "mqttWrapper.h"
#include <string.h>
#include <stdio.h>
// basic file operations
#include <iostream>
#include <fstream>



TestPublisher::TestPublisher(MqttWrapper *mqtt)
{
    this->mqtt = mqtt;
    file_name = NULL;
}

TestPublisher::~TestPublisher(){

}

void TestPublisher::test_publish_messages(const char* topic, int message_size, int number_of_messages, int qos)
{
    unsigned long int byte_size = message_size * 1000;
    if(byte_size > MAX_BYTE_SIZE){
        byte_size = MAX_BYTE_SIZE;
    }
    unsigned char message[byte_size];
    printf("%d Kb/message x %d messages = %lu kilobytes\n",
    message_size,number_of_messages, (byte_size*number_of_messages)/1000);
    for(int i=0; i<number_of_messages; i++){
        mqtt->mqtt_publish(byte_size,topic, &message, qos);
    }
}

int TestPublisher::test_write_to_file(const char* buffer)
{
    if(file_name == NULL){
        printf("ERROR: set file_name first\n");
        return -1;
    } else {

        std::ofstream file;
        file.open(file_name, std::ofstream::out | std::ofstream::app);
        file.write(buffer, strlen(buffer));
        file.close();
    }
        return 0;
}

int TestPublisher::test_separation_line()
{
    if(file_name == NULL){
        printf("ERROR: set file_name first\n");
        return -1;
    } else {
        std::ofstream file;
        file.open(file_name, std::ofstream::out | std::ofstream::app);
        file << "\n-----------------------------------------------------------------------------\n";
        file.close();
    }
    return 0;
}

int TestPublisher::test_system_to_file(const char* command)
{
    FILE *infile;
    int bufsize = 1000;
    char inbuf[bufsize];
    std::string outbuf;

    if(file_name == NULL){
        printf("ERROR: set file_name first\n");
        return -1;
    } else {
        infile = popen(command,"r");
        while(fgets(inbuf,bufsize,infile) != NULL){
            outbuf.append(inbuf);
        }
        pclose(infile);
        test_write_to_file(outbuf.data());
    }
    return 0;
}

void TestPublisher::set_file_name(const char* name)
{
    file_name = name;
}

const char* TestPublisher::get_file_name()
{
    return file_name;
}
