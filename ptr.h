#ifndef PTR_H
#define PTR_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTcpSocket>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QHostAddress>
#include <QImageReader>
class PTR : public QThread
{
    Q_OBJECT
public:
    explicit PTR(QObject *parent = nullptr) : QThread(parent) {
        qDebug() << "Pictures Transmission Receiver thread!";
        isRunning = true;
    }
    PTR();
    bool isRunning;
    QTcpSocket *mSocket;
    QHostAddress tuchuanip;
    int tuchuanport;
protected:
    virtual void run() Q_DECL_OVERRIDE;
signals:
    void picture(QByteArray picBuffer);
public slots:
    void readyData();
};

#endif // PTR_H
