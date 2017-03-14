#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtWebEngineWidgets>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QUrl url= QUrl("qrc:///web/video.html");
    ui->video->load(url);
}
MainWindow::~MainWindow() {
    delete ui;
}
