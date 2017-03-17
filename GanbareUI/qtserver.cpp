#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

#include <iostream>

#include "qtserver.h"

using namespace std;

QtServer::QtServer(quint16 port, QObject *parent) :
    QObject(parent), server(Q_NULLPTR){
    server= new QWebSocketServer("server",QWebSocketServer::NonSecureMode, this);
    client = Q_NULLPTR;
    if (server->listen(QHostAddress::Any),port) {
        cout << "Listeniing to port " << port << endl;
        connect(server,&QWebSocketServer::newConnection,this,&QtServer::onNewConnection);
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
    is_connected=true;
    client = server->nextPendingConnection();
    connect(client,&QWebSocket::disconnected,this,&QtServer::socketDisconnected);
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
