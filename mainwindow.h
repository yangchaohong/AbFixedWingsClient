#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>           //提供访问串口的功能
#include <QSerialPortInfo>    //提供系统中存在的串口的信息
#include <QtCharts>
#include <bits/stdc++.h>
#include <QUdpSocket>
#include "xboxthread.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <bits/stdc++.h>
//#include <opencv2/opencv.hpp>
#include "ptr.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//using namespace cv;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private slots:
    void move();
    void on_MainWindow_destroyed();
    void on_pushButton_clicked();
    void readyData();

    void on_pushButton_2_clicked();
    void tuchuan();

    void on_pushButton_3_clicked();
    void showPicture(QByteArray picBuffer);

private:
    Ui::MainWindow *ui;
    QUdpSocket* m_sender;
    QUdpSocket *UdpServer;

};
#endif // MAINWINDOW_H
