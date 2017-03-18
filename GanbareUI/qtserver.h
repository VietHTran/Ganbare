#ifndef QTSERVER_H
#define QTSERVER_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>


QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class QtServer : public QObject {
    Q_OBJECT
public:
    explicit QtServer(quint16 port, QObject *parent = Q_NULLPTR);
    virtual ~QtServer();
    void sendMessage(QString message);
private Q_SLOTS:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();
private:
    QWebSocketServer* server;
    QWebSocket* client;
};

#endif // QTSERVER_H
