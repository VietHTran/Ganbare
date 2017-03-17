#ifndef QTSERVER_H
#define QTSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

class QtServer : public QObject {
    Q_OBJECT
public:
    explicit QtServer(quint16 port, QObject *parent = Q_NULLPTR);
    virtual ~QtServer();
    void sendMessage(QString message);
private Q_SLOTS:
    void onNewConnection();
    void socketDisconnected();
private:
    bool is_connected;
    QWebSocketServer* server;
    QWebSocket* client;
};

#endif // QTSERVER_H
