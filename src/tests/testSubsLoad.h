#ifndef TESTSUBSLOAD_H
#define TESTSUBSLOAD_H

class TestSubsLoad
{
public:
    TestSubsLoad();

    //Type 1 = subs
    //Type 2 = clients
    static void run_sub_load(int subs, int type);
    static void run_topics(int subs);

private:
    static void create_clients(int id);    
    static void create_subs(int id,bool clean_session=true, int qos=0);



};
#endif