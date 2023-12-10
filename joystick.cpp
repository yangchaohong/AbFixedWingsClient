#include "joystick.h"
#ifdef _WIN32
#include <windows.h>
#define sleep(sec)   Sleep(sec * 1000)
#define msleep(msec) Sleep(msec)

static void usleep(unsigned long usec)
{
    HANDLE timer;
    LARGE_INTEGER interval;
    interval.QuadPart = -(10 * usec);

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &interval, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}
#else
#include <unistd.h>
#define msleep(msec) usleep(msec * 1000)
#endif
extern "C"
{
#include <openJoystick.h>
}
void joystick::run()
{
    int a[25];
    int count;
    count=listJoysticks(a);
    qDebug()<<count;
    for(int i=0;i<count;i++)
        qDebug()<<a[i];

    pitchNeed=rollNeed=0;
    while (isRunning)
    {
        short x=getAxisLX(a[0]),y=getAxisLY(a[0]),z=getAxisRT(a[0])-getAxisLT(a[0]);
        bx=isButtonX(a[0]),by=isButtonY(a[0]),ba=isButtonA(a[0]),bb=isButtonB(a[0]);
        //qDebug()<<bx<<by;
        //if(x!=0.0||y!=0.0||z!=0.0)
        //{
        pitchNeed+=-y*0.000007;
        //qDebug()<<"PitchNeed:"<<pitchNeed<<' '<<(int)xbox->p.LSYValue;
        rollNeed+=x*0.000007;
        //qDebug()<<"RollNeed:"<<rollNeed<<' '<<(int)xbox->p.LSXValue;
        if(pitchNeed<=-15)
            pitchNeed=-15;
        if(rollNeed>=56)
            rollNeed=56;
        if(rollNeed<=-56)
            rollNeed=-56;
        Yaw=z/6;
        emit resultReady();
        usleep(1);
    }
}
void joystick::reset()
{
    pitchNeed=0;
    rollNeed=0;
}
