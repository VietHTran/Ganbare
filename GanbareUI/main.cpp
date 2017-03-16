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

    return a.exec();
}

