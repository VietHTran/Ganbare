#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QThread>

#include "opencvcontroller.h"
#include "qtserver.h"

class QWebEngineView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void sendMessage(QString message);

private slots:
    void handleButton();
    void loadPage();

private:
    Ui::MainWindow* ui;
    QPushButton* start_btn;
    QPushButton* load_btn;
    QLineEdit* ytkey_box;
    OpenCVController* controller;
    QThread scanner;
    QtServer* server;
    bool is_run;

signals:
    void operateController();

};
#endif // MAINWINDOW_H
