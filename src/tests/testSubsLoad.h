#ifndef TESTSUBSLOAD_H
#define TESTSUBSLOAD_H
#include "../outputHandler.h"

class TestSubsLoad
{
public:
    TestSubsLoad();

    /**
     * Function: run_sub_load
     * 
     * Function will test the load each subscriber causes to the broker.
     * The results will be saved in a file at output/testSubsLoad.csv or
     * output/testClientLoad.csv. The result will be number of subs/clients
     * against current heap memory of the broker.
     * 
     * Parameters:
     *  int subs -  The total number of subscribers tested.
     *  int type -  If type = 1. The test tests clients WITH subscriptions.
     *              If type = 2. The test tests clients WITHOUT subscriptions.
     **/
    static void run_sub_load(int subs, int type);

    /**
     * Function: run_topics
     * 
     * Funciton will test the load of each added topic. The result will be saved
     * at output/topicsTest.csv and store each topic against heap memory of broker.
     * 
     * Parameters:
     *  int topics - The total number of topics tested.
     * */
    static void run_topics(int topics);

private:
    static void create_clients(int id);    
    static void create_subs(int id,OutputHandler *output,bool clean_session=true, int qos=0);



};
#endif