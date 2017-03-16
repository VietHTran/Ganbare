#ifndef OPENCVCONTROLLER_H
#define OPENCVCONTROLLER_H
#include <QObject>

class OpenCVController : public QObject {
    Q_OBJECT

public:
    explicit OpenCVController();
    ~OpenCVController();
    bool is_off;

public slots:
    void runOpenCV();
};

#endif // OPENCVCONTROLLER_H
