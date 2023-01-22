# AbFixedWings图传遥控一体化网络无人机项目_客户端

AbFixedWings是一套以4G/WiFi等TCP/IP网络实现的固定翼无人机，以实现更好的图传画质和更远的遥控距离。

AbFixedWings需要一台电脑、一台树莓派和一块Arduino（例程适用于STM32F103C6T6）。树莓派作为天空端，Arduino作为飞控，两者用串口通信；电脑作为地面站，以游戏手柄遥控。图传使用TCP协议，遥控使用UDP协议。

其余的硬件还有MPU6050，舵机，电子调速器，电机，摄像头。

AbFixedWings前卫地支持了树莓派船新的LibCamera库。

为了简化设计，我们将复刻空客电传飞控的常规法则。

天空端：https://github.com/yangchaohong/AbFixedWingsSky

飞控端：https://github.com/yangchaohong/AbFixedWingsArduino
