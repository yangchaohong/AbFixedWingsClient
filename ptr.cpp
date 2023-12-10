#include "ptr.h"

PTR::PTR()
{

}

QByteArray picBuffer;
void PTR::run()
{
    mSocket=new QTcpSocket(this);
    mSocket->connectToHost(tuchuanip,tuchuanport);
    mSocket->waitForConnected();
    //connect(mSocket,&QTcpSocket::readyRead,this,&PTR::readyData);
    mSocket->setReadBufferSize(1048576);
    qDebug()<<"Pictures Transmission Receiver thread!";
ac:
    mSocket->waitForReadyRead();
    QByteArray temp=mSocket->readLine();
    if(temp=="start\n")
    {
        //qDebug()<<"Start";
        while(1)
        {
            mSocket->waitForReadyRead();
            temp=mSocket->readLine();
            //if(temp.isEmpty())
            //    continue;
            if(temp=="end\n")
            {
                //qDebug()<<"end";
                break;
            }
            picBuffer+=temp;
        }


        emit picture(picBuffer);
        picBuffer.clear();
    }
    if(isRunning==1)
        goto ac;
}

void PTR::readyData()
{

}
