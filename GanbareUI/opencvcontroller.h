#ifndef OPENCVCONTROLLER_H
#define OPENCVCONTROLLER_H
#include <QObject>
#include "qtserver.h"
#include "chatserver.h"

class OpenCVController : public QObject {
    Q_OBJECT

public:
    explicit OpenCVController();
    ~OpenCVController();
    bool is_off;

public slots:
    void runOpenCV();

private:
    QtServer* server;
};

#endif // OPENCVCONTROLLER_H
