#include "joystick.h"
#include <windows.h>
void joystick::run()
{
    pitchNeed=rollNeed=0;
    xbox->setrun(1);
    //xbox->moveToThread(xbox);
    xbox->start();
    Sleep(10);
    while (isRunning)
    {
        short x=xbox->p.LSYValue,y=xbox->p.LSXValue;
        pitchNeed+=x*0.001;
        //qDebug()<<"PitchNeed:"<<pitchNeed<<' '<<(int)xbox->p.LSYValue;
        rollNeed+=y*0.001;
        //qDebug()<<"RollNeed:"<<rollNeed<<' '<<(int)xbox->p.LSXValue;
        if(pitchNeed<=-15)
            pitchNeed=-15;
        if(rollNeed>=56)
            rollNeed=56;
        if(rollNeed<=-56)
            rollNeed=-56;
        emit resultReady();
        Sleep(1);
    }
    xbox->setrun(0);
    xbox->deleteLater();
    xbox->wait();
}
void joystick::reset()
{
    pitchNeed=0;
    rollNeed=0;
}
