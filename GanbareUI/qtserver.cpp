#include <QtCore/QDebug>
#include <iostream>

#include "qtserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"

QT_USE_NAMESPACE

using namespace std;

QtServer::QtServer(quint16 port, QObject *parent) :
    QObject(parent), server(Q_NULLPTR){
    server= new QWebSocketServer(QStringLiteral("Server"),
                                 QWebSocketServer::NonSecureMode,
                                 this);
    client = Q_NULLPTR;
    if (server->listen(QHostAddress::Any,port)) {
        cout << "Listening to port " << port << endl;
        connect(server,&QWebSocketServer::newConnection,
                this,&QtServer::onNewConnection);
    }
}

QtServer::~QtServer() {
    server->close();
    if (client!=Q_NULLPTR) {
        delete client;
    }
}

void QtServer::onNewConnection() {
    if (client!=Q_NULLPTR) {
        cout << "Connection is currently busy" << endl;
        return;
    }
    cout << "connected" << endl;
    client = server->nextPendingConnection();
    connect(client,&QWebSocket::disconnected,this,&QtServer::socketDisconnected);
    connect(client,&QWebSocket::textFrameReceived,this,&QtServer::processMessage);
}

void QtServer::socketDisconnected() {
    delete client;
}

void QtServer::sendMessage(QString message) {
    if (client==Q_NULLPTR) {
        cout << "Error: No connected client found" << endl;
        return;
    }
    client->sendTextMessage(message);
}

void QtServer::processMessage(QString message) {
    cout << "message received "<<message.toUtf8().constData()<<endl;
}
