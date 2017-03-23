#include <QtWidgets>
#include <QtWebEngineWidgets>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencvcontroller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QUrl url= QUrl("qrc:///web/video.html");
    ui->video->load(url);

    server= new QtServer(1234);

    is_run=false;
    start_btn=ui->start_btn;
    connect(start_btn, SIGNAL (released()), this, SLOT (handleButton()));

    controller= new OpenCVController;
    controller->moveToThread(&scanner);
    connect(this,SIGNAL(operateController()),controller,SLOT(runOpenCV()));
    connect(controller,SIGNAL(onStateChanged(QString)),this,SLOT(sendMessage(QString)));
    scanner.start();

    load_btn=ui->load_btn;
    ytkey_box=ui->ytkey_box;
    connect(load_btn,SIGNAL(released()),this,SLOT(loadPage()));
}

void MainWindow::sendMessage(QString message) {
    server->sendMessage(message);
}

MainWindow::~MainWindow() {
    delete ui;
    delete start_btn;
    delete controller;
    delete load_btn;
    delete ytkey_box;
    scanner.quit();
    delete &scanner;
    delete server;
}

void MainWindow::handleButton() {
    controller->is_off=is_run;
    if (is_run) {
        start_btn->setText("Start");
        is_run=false;
    } else {
        start_btn->setText("Stop");
        is_run=true;
        emit operateController();
    }
}

void MainWindow::loadPage() {
    std::string key=ytkey_box->text().toUtf8().toStdString();
    if (!key.empty()) {
        server->sendMessage("2");
        key="qrc:///web/video.html?key="+key;
        QString url_str{key.c_str()};
        QUrl url{url_str};
        ui->video->load(url);
    }
}
