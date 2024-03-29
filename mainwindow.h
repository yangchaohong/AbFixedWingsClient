#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bits/stdc++.h>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <bits/stdc++.h>
#include <QHostInfo>
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

    void lookUpHostInfo(const QHostInfo &host);
    void lookUpHostInfo_2(const QHostInfo &host);

private:
    Ui::MainWindow *ui;
    QUdpSocket* m_sender;
    QUdpSocket *UdpServer;

};
#endif // MAINWINDOW_H
