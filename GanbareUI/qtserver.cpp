#include "qtserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>
#include <stdio.h>
#include <iostream>

QT_USE_NAMESPACE

using namespace std;

QtServer::QtServer(quint16 port, QObject *parent) :
    QObject(parent), server(Q_NULLPTR){
    is_connected=false;
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
    if (is_connected) {
        cout << "Connection is currently busy" << endl;
        return;
    }
    cout << "connected" << endl;
    is_connected=true;
    client = server->nextPendingConnection();
    connect(client,&QWebSocket::disconnected,this,&QtServer::socketDisconnected);
    connect(client,&QWebSocket::textFrameReceived,this,&QtServer::processMessage);
}

void QtServer::socketDisconnected() {
    delete client;
    is_connected=false;
}

void QtServer::sendMessage(QString message) {
    if (!is_connected) {
        cout << "Error: Client not connected" << endl;
        return;
    }
    client->sendTextMessage(message);
}

void QtServer::processMessage(QString message) {
    printf("Message received %s",message.toUtf8().constData());
}
