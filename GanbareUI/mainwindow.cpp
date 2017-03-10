#include "mainwindow.h"
#include "mainwindow.h"
#include <QtWidgets>
#include <QtWebEngineWidgets>

MainWindow::MainWindow(const QUrl& url) {
    view = new QWebEngineView(this);
    view->load(url);
    setCentralWidget(view);
}

MainWindow::~MainWindow() {
    delete view;
}
