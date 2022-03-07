#ifndef TRANSPORTER_H
#define TRANSPORTER_H
#include "QObject"
#include "constant.h"

class Transporter: public QObject
{
    Q_OBJECT
public:
    Transporter();
    static Transporter *getInstance();
signals:
    void sigCamera(int camera_type);
private:
    static Transporter *instance;
};

#endif // TRANSPORTER_H
