#include "outputHandler.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <limits.h>

OutputHandler::OutputHandler(const char* file_name):
    file_name(file_name)
{
}

OutputHandler::~OutputHandler()
{
    if(file_name != NULL){
        std::ofstream file;
        file.open(file_name, std::ofstream::out | std::ofstream::app);
        file << "\n-----------------------------------------------------------------------------\n";
        file.close();
    } 
}

int OutputHandler::output_write_to_file(const char* buffer, bool line)
{

    if(file_name == NULL){
        printf("ERROR: set file_name first\n");
        return -1;
    } else {

        std::ofstream file;
        file.open(file_name, std::ofstream::out | std::ofstream::app);
        if(line){
            file << " \n";
        }
        file.write(buffer, strlen(buffer));
        file.close();
    }
        return 0;
}

int OutputHandler::output_separation_line()
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

int OutputHandler::output_system_to_file(const char* command)
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
        output_write_to_file(outbuf.data(),true);
    }
    return 0;
}

void OutputHandler::set_file_name(const char* name)
{
    file_name = name;
}

const char* OutputHandler::get_file_name()
{
    return file_name;
}
