#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H
class OutputHandler{
public:
    OutputHandler(const char* file_name);
    ~OutputHandler();
    int output_write_to_file(const char* buffer,bool line);

    int output_system_to_file(const char* command);

    int output_separation_line();

    void set_file_name(const char* name);
    const char * get_file_name(void);

private:
    const char* file_name;


};
#endif
