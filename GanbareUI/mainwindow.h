#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class QWebEngineView;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(const QUrl& url);
    ~MainWindow();
private:
    QWebEngineView* view;
};
#endif // MAINWINDOW_H
