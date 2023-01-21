#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "xboxthread.h"
#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QThread>
#include <QtGui>
class joystick : public QThread
{
    Q_OBJECT
public:
    bool isRunning;
    explicit joystick(QObject *parent = nullptr) : QThread(parent) {
        qDebug() << "joystick gamepad thread!";
        isRunning = true;
    }
    float pitchNeed,rollNeed,Yaw;
    XboxThread *xbox;
    void reset();
protected:
    virtual void run() Q_DECL_OVERRIDE;
signals:
    void resultReady();
};

#endif // JOYSTICK_H
