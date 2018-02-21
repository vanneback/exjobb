#ifndef MAXLOAD_H
#define MAXLOAD_H

/**
 * Class to max load on server
**/
class MaxLoad 
{
public:
    MaxLoad();

    /*
    * function: run_message_load
    * 
    * Connects user with clean_flag as false. Then disconnects user.
    * Then sends a lot of messages on the disconnecteds users topic
    * Forcing broker to store messages.
    *
    * Parameters:
    *   mb-     int. The total size of saved messages in megabytes.
    */
    static void run_message_load(int mb);

};
#endif