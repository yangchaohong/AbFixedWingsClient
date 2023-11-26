#include "joystick.h"
#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <unistd.h>
    #define Sleep sleep
#endif
void joystick::run()
{
    pitchNeed=rollNeed=0;

    while (isRunning)
    {
        double x=m_gamepad->axisLeftY(),y=m_gamepad->axisLeftX(),z=m_gamepad->buttonR2()-m_gamepad->buttonL2();
        //if(x!=0.0||y!=0.0||z!=0.0)
        //{
            pitchNeed+=x*0.5;
            //qDebug()<<"PitchNeed:"<<pitchNeed<<' '<<(int)xbox->p.LSYValue;
            rollNeed+=y*0.5;
            //qDebug()<<"RollNeed:"<<rollNeed<<' '<<(int)xbox->p.LSXValue;
            if(pitchNeed<=-15)
                pitchNeed=-15;
            if(rollNeed>=56)
                rollNeed=56;
            if(rollNeed<=-56)
                rollNeed=-56;
            Yaw=z*48;
            emit resultReady();
        //}
        Sleep(10);
    }
    delete m_gamepad;
}
void joystick::reset()
{
    pitchNeed=0;
    rollNeed=0;
}
