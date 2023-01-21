#ifndef XBOXTHREAD_H
#define XBOXTHREAD_H

#include <QByteArray>
#include <QDebug>
#include <QThread>
#include <QtGui>
class XboxThread : public QThread {
    Q_OBJECT

public:
    explicit XboxThread(QObject *parent = nullptr) : QThread(parent) {
        qDebug() << "xbox360 gamepad thread!";
        isRunning = true;
    }
    void setrun(bool);

    struct position { //键位定义

        bool buttonA; //按键A
        bool buttonB; //按键B
        bool buttonX; //按键X
        bool buttonY; //按键Y

        bool buttonBack;  // back按键
        bool buttonStart; // start按键
        bool buttonXBox;  // xbox键

        bool buttonLB; //按键LB
        bool buttonRB; //按键RB

        bool buttonUp;    //上
        bool buttonDown;  //下
        bool buttonLeft;  //左
        bool buttonRight; //右

        bool buttonRS; //右摇杆按键
        bool buttonLS; //左摇杆按键

        unsigned char SRValue; //右滑杆
        unsigned char SLValue; //左滑杆

        short LSXValue; //左摇杆X方向
        short LSYValue; //左摇杆Y方向
        short RSXValue; //右摇杆X方向
        short RSYValue; //右摇杆Y方向
    };
    position p;
protected:
    virtual void run() Q_DECL_OVERRIDE;

signals:
    void resultReady();
public slots:
private:
    bool isRunning;

};

Q_DECLARE_METATYPE(XboxThread::position)

#endif // XBOXTHREAD_H
