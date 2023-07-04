#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "joystick.h"
//#include <QtGamepad/QGamepad>
using namespace std;
//QGamepad *m_gamepad;

float pitchNeed,rollNeed,Yaw;
float imageRotate,imageY;
int thro;
QString skyip;
int skyport,tuchuanport;
joystick *joy;
PTR *ptr;
bool connected;
void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap horizon("horizon.png");
    QPainter painter(this);
    //imageRotate=30;

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(870,-150);

    /*painter.translate(200,650);
    painter.rotate(imageRotate);
    painter.translate(-200,-650);*/
    //painter.translate(-1300,-250);

    QMatrix matrix;
    matrix.rotate(imageRotate);
    /* 画图操作 */
    horizon=horizon.transformed(matrix);
    painter.drawPixmap(0,0+imageY,500,800,horizon);

    //painter.end();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_sender=new QUdpSocket(this);

    joy=new joystick(this);
    joy->xbox =new XboxThread(this);
    joy->isRunning=1;
    joy->start();
    connect(joy,SIGNAL(resultReady()),this,SLOT(move()));

    QPixmap background("background.png");
    //background.scaled(280,240);
    ui->label_2->setPixmap(background);

    UdpServer = new QUdpSocket(this);
    //UdpServer->bind(1354);
    connect(UdpServer, &QUdpSocket::readyRead, this, &MainWindow::readyData);

}

MainWindow::~MainWindow()
{
    joy->isRunning=0;
    joy->deleteLater();
    joy->wait();
    ptr->isRunning=0;
    ptr->mSocket->abort();
    ptr->deleteLater();
    ptr->wait();
    delete ui;
    delete joy;
    delete ptr;
}

void MainWindow::tuchuan()
{

    //qDebug()<<picBuffer.toStdString().c_str();

}
float pitch_old,roll_old;
int thro_old;
void MainWindow::move()
{
    pitch_old=pitchNeed;
    roll_old=rollNeed;
    thro_old=thro;
    pitchNeed=joy->pitchNeed;
    rollNeed=joy->rollNeed;
    if(joy->xbox->p.buttonY)
        thro+=2;
    if(joy->xbox->p.buttonX)
        thro-=2;
    if(thro>100)
        thro=100;
    if(thro<0)
        thro=0;
    ui->verticalSlider->setValue(thro);
    ui->pitch->setText(QString::number(pitchNeed));
    ui->roll->setText(QString::number(rollNeed));
    if(connected)
    {
        QByteArray dataGram="Hello";
        UdpServer->writeDatagram(dataGram.data(),
                                 dataGram.size(),
                                 QHostAddress( skyip ),    //udp广播地址
                                 skyport);

        QByteArray a;

        if(pitchNeed!=pitch_old)
        {
            a='P'+QString::number(pitchNeed).toUtf8()+'\n';
            UdpServer->writeDatagram(a,QHostAddress( skyip ),skyport);
        }
        if(rollNeed!=roll_old)
        {
            a='R'+QString::number(rollNeed).toUtf8()+'\n';
            UdpServer->writeDatagram(a,QHostAddress( skyip ),skyport);
        }
        if(thro!=thro_old)
        {
            a='T'+QString::number(thro).toUtf8()+'\n';
            UdpServer->writeDatagram(a,QHostAddress( skyip ),skyport);
        }
    }
}

void MainWindow::on_MainWindow_destroyed()
{

}

void MainWindow::on_pushButton_clicked()
{
    skyip=ui->lineEdit->text();
    skyport=ui->lineEdit_2->text().toInt();
    QByteArray dataGram="Hello";
    //UdpServer->bind(1354);
    UdpServer->writeDatagram(dataGram.data(),
                             dataGram.size(),
                             QHostAddress( skyip ),    //udp广播地址
                             skyport);
    UdpServer->connectToHost(QHostAddress( skyip ),skyport,QIODevice::ReadWrite);
    connected=1;
    /*————————————————
    版权声明：本文为CSDN博主「喝水怪~」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/qq_43686329/article/details/120352026*/
}
void MainWindow::showPicture(QByteArray picBuffer)
{

    qDebug()<<"准备图像";
    QByteArray tmp=QByteArray::fromBase64(picBuffer);
    tmp=qUncompress(tmp);
    QBuffer buffer(&tmp);
    buffer.open(QIODevice::ReadOnly);
    QImageReader reader(&buffer);
    QImage img = reader.read();
    ui->label->setPixmap(QPixmap::fromImage(img));
    //充满label
    ui->label->setScaledContents(true);
    //img.save("test.png","PNG");
    /*————————————————
    版权声明：本文为CSDN博主「aspiretop」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/ljjjjjjjjjjj/article/details/126043966*/
}
QByteArray recbuf;
void MainWindow::readyData()
{
    qDebug()<<"HAHAHA"<<UdpServer->bytesAvailable();
    QByteArray arr;
    arr.resize(UdpServer->bytesAvailable());
    UdpServer->readDatagram(arr.data(),arr.size());
    //qDebug()<<arr<<endl;
    if(arr[0]=='R')
    {
        string tmp=arr.toStdString();
        imageRotate=stof(tmp.substr(1,tmp.size()-1));
        qDebug()<<'R'<<imageRotate<<endl;
        update();
    }
    if(arr[0]=='P')
    {
        string tmp=arr.toStdString();
        imageY=stof(tmp.substr(1,tmp.size()-1));
        qDebug()<<'Y'<<imageY<<endl;
        update();
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    joy->reset();
}

void MainWindow::on_pushButton_3_clicked()
{

    ptr=new PTR(this);
    ptr->skyip=ui->lineEdit->text();
    ptr->tuchuanport=ui->lineEdit_3->text().toInt();
    connect(ptr,&PTR::picture,this,&MainWindow::showPicture);
    //connect(ptr->mSocket,&QTcpSocket::readyRead,ptr,&PTR::readyData);
    ptr->start();
    //QByteArray dataGram="Hello111\n";
    //ptr->mSocket->write(dataGram.data(),dataGram.size());
}
