#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "common.h"

using namespace std;

class Server {
public:
    Server();
    void                    waitForClient(); //wait until client connect to proceed
    void                    closeConnection(); //close connection 
    void                    sendToClient(char * buffer); //send message to client with setup buffer
    void                    sendToClientCLI(); //send message to client with text input from command line
    void                    getClientMessage(char *buff); //receive message sent from client and store in buff
private:
    bool                    isConnect; //Only accept one client
    char                    buff[BUFF_SIZE];
    int                     listener;
    int                     connection;
    int                     status;
    pid_t                   child_id; 
    socklen_t               client_len;
    struct sockaddr_in      client_address; 
    struct sockaddr_in      server_address;
};