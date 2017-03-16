#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QThread>

#include "opencvcontroller.h"

class QWebEngineView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleButton();

private:
    Ui::MainWindow *ui;
    QPushButton *start_btn;
    OpenCVController* controller;
    QThread scanner;
    bool is_run;

signals:
    void operateController();

};
#endif // MAINWINDOW_H
