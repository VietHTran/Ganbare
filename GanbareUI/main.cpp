#include <QApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "mainwindow.h"
#include "../headers/common.h"

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec(); //debug

    pid_t pID = fork();
    if (pID==0) {
        char* argv[] = {"Command-line",NULL};
        execvp("../ganbare",argv); //Need to sucessfully run Install.sh prior to execution
    }

    int sockfd,status;
    struct sockaddr_in server_address;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd<0) {
        cout << "Error initializing socket" <<endl;
        exit(1);
    }
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(1500);

    usleep(5000*1000); //Wait for exec to create the server

    do {
        status=connect(sockfd,(struct sockaddr *) &server_address, sizeof(server_address));
        checkError(status,"Error connecting server","Successfully connecting to server");
    } while (status==-1);
//    bool is_off=false;
//    while (!is_off) {
//        char buffer[BUFF_SIZE];
//        getMessage(sockfd,buffer);
//    }

//    cout << "Closing connection..." << endl;
//    close(sockfd);

    return a.exec();
}

