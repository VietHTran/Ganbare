#include <string>

#define SERVER_PORT     1500//9877
#define MAX_QUEUE       1
#define MAX_LINE        4096
#define BUFF_SIZE       1024

using namespace std;

void checkError(int code, string message, string success);
void getMessage(int socketfd, void* buffer);
void sendMessageCLI(int socketfd);
void sendMessage(int socketfd, char* message);