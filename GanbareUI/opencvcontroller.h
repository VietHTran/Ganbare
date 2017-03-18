#ifndef OPENCVCONTROLLER_H
#define OPENCVCONTROLLER_H
#include <QObject>
#include "qtserver.h"

class OpenCVController : public QObject {
    Q_OBJECT

public:
    explicit OpenCVController();
    ~OpenCVController();
    bool is_off;

public slots:
    void runOpenCV();

signals:
    void onStateChanged(QString message);

};

#endif // OPENCVCONTROLLER_H
