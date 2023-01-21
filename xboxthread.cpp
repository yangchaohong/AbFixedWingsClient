#include "xboxthread.h"
extern "C" {
#include <hidapi.h>
}

void XboxThread::run() {
    if (hid_init()) //初始化
        return;
    int res;
    unsigned char buf[64];
    hid_device *handle;
    // Open the device using the VID, PID,
    // and optionally the Serial number.
    handle = hid_open(0x045e, 0x028e, NULL);
    if (handle == NULL) {
        return;
    }
    hid_set_nonblocking(handle, 1);
    while (isRunning) {
        //qDebug() << "xbox360 gamepad thread runing!";
        res = hid_read(handle, buf, 64);
        if (res != 0) {
            //oldp=p;
            p.buttonUp = buf[11] & 0x01;
            p.buttonDown = (buf[11] >> 1) & 0x01;
            p.buttonLeft = (buf[11] >> 2) & 0x01;
            p.buttonRight = (buf[11] >> 3) & 0x01;
            p.buttonStart = (buf[10] >> 4) & 0x01;
            p.buttonBack = (buf[10] >> 5) & 0x01;
            p.buttonLS = (buf[11] >> 6) & 0x01;
            p.buttonRS = (buf[11] >> 7) & 0x01;

            p.buttonLB = buf[10] & 0x01; //第二组按键
            p.buttonRB = (buf[10] >> 1) & 0x01;
            p.buttonXBox = (buf[10] >> 2) & 0x01;
            p.buttonA = (buf[10] >> 4) & 0x01;
            p.buttonB = (buf[10] >> 5) & 0x01;
            p.buttonX = (buf[10] >> 6) & 0x01;
            p.buttonY = (buf[10] >> 7) & 0x01;

            p.SLValue = buf[8]; //滑杆
            p.SRValue = buf[9];

            p.LSXValue = buf[1]-124;
            p.LSYValue = buf[3]-132;

            p.RSXValue = buf[5]-128;
            p.RSYValue = buf[7]-126;
            //qDebug()<<"buf[0]:"<<buf[0]<<' '<<"buf[1]:"<<buf[1]<<' '<<"buf[2]:"<<buf[2]<<' '<<"buf[3]:"<<buf[3]<<' '<<"buf[4]:"<<buf[4]<<' '<<"buf[5]:"<<buf[5]<<' '<<"buf[6]:"<<buf[6]<<' '<<"buf[7]:"<<buf[7]<<' '<<"buf[8]:"<<buf[8]<<' '<<"buf[9]:"<<buf[9]<<' '<<"buf[10]:"<<buf[10]<<' '<<"buf[11]:"<<buf[11]<<' '<<"buf[12]:"<<buf[12]<<' '<<"buf[13]:"<<buf[13]<<' ';
            emit  resultReady();
        }
        /*if(p.SLValue!=oldp.SLValue||p.SRValue!=oldp.SRValue||p.LSXValue!=oldp.LSXValue||p.LSYValue!=oldp.LSYValue||p.RSXValue!=oldp.RSXValue
                ||p.buttonUp!=oldp.buttonUp||p.buttonDown!=oldp.buttonDown||p.buttonLeft!=oldp.buttonLeft||p.buttonRight!=oldp.buttonRight||p.buttonStart!=oldp.buttonStart
                ||p.buttonBack!=oldp.buttonBack||p.buttonLS!=oldp.buttonLS||p.buttonRS!=oldp.buttonRS||p.buttonLB!=oldp.buttonLB
                ||p.buttonA!=oldp.buttonA||p.buttonB!=oldp.buttonB||p.buttonX!=oldp.buttonX||p.buttonY!=oldp.buttonY)
        */
    }

    hid_close(handle);

    /* Free static HIDAPI objects. */
    hid_exit();
}

void XboxThread::setrun(bool set) { isRunning = set; }
