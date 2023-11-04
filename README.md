# Xbox360GamePad_Qt
this is a qt demo project!
使用hidapi库编写了一个XBOX360手柄的线程库，可以读取手柄的信号然后进行其他动作
```
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

    char LSXValue; //左摇杆X方向
    char LSYValue; //左摇杆Y方向
    char RSXValue; //右摇杆X方向
    char RSYValue; //右摇杆Y方向
  };
```
<div align=center><img src="https://github.com/WanderROS/Xbox360GamePad_Qt/blob/master/demo.gif?raw=true"/></div>
