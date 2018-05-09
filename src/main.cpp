#include <stdlib.h>
#include <stdio.h>
#include "mqttWrapper.h"
#include "publisher.h"
#include "outputHandler.h"
#include "clientHandler.h"
#include "tests/testSubsLoad.h"
#include "tests/testCleanLoad.h"
#include "tests/maxLoad.h"
#include <unistd.h>
#include <string>
#include <map>


const char app_version[] = "1.0.1";
const char app_name[] = "mqtt_client";
const char config_filename[] = "mqtt_client.json";

 int main(int argc, char const *argv[]) {
   
    //  Testing storing messages to broker //
    MaxLoad::run_message_load(10);

    //  Test running a constant message load on broker //
    MaxLoad::run_consistent_load(1,500,1,120,0);
    
    //  Test running 900 subscribers //
    TestSubsLoad::run_sub_load(900,1);

    // Test running 1000 topics  //
    TestSubsLoad::run_topics(1000);
    
    return 0;
}
