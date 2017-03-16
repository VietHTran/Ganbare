#include <QtWidgets>
#include <QtWebEngineWidgets>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
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

    is_run=false;
    start_btn=ui->start_btn;
    connect(start_btn, SIGNAL (released()), this, SLOT (handleButton()));

    controller= new OpenCVController;
    controller->moveToThread(&scanner);
    connect(this,SIGNAL(operateController()),controller,SLOT(runOpenCV()));
    scanner.start();
}
MainWindow::~MainWindow() {
    delete ui;
    delete start_btn;
    delete controller;
    scanner.quit();
    delete &scanner;
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
