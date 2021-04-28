#pragma once
#ifndef _AP_H
#define _AP_H

#include <cmath>
class AP
{
public:
    // 电枢参数
    double ma0 = 0.04;// 电枢的初始质量
    double da = 0.03;// 电枢长度，等于轨道间距
    double ucdla0 = 12.566 * 1e-7;// 电枢金属常温磁导率
    double pdzla0 = 2.655 * 1e-8;// 电枢金属常温电阻率

    double Ba = 3.6 * 1e-16;// 计算电枢金属瞬态电阻率用到的常数(Ω.m2 / A)
    double ha = 0.025;// 电枢厚度，等于轨道厚度

    double Aa = 7 * 1e-4;// 电枢的横截面积
    double ua0 = 200;// 电枢两端电压

    // 以下初始化时未赋值
    double Ft = 0;// 电枢对弹丸的推力
    double ma = 0.04;// 电枢的瞬时质量

    double Ua = 0;// 电枢两端的电压

    double Rgrad = 0;//电枢电阻的电感梯度
    double Ra = 0;// 电枢的瞬时电阻
    //double a = 0;// 固体电枢的瞬时电阻
    //double v = 0;// 固体电枢的速度
    //double x = 0;// 固体电枢的位置
    // 弹丸参数
    double v0 = 0;// 弹丸的速度初值
    double x0 = 0;// 弹丸的位置初值

    double mp0 = 0;// 弹丸质量的初始值
    double Cp = 120 * 1e-3;// 弹丸的截面周长
    double Ap = 900 * 1e-6;// 弹丸的横截面积
    double mp = 0; //弹丸质量
    AP(void);
    //计算
    double static Ragra_f(AP armature, double i, double t);
    double static Ra_f(AP armature, double x);
    double static Ua_f(double Ra, double i);

    // 环境参数
    double rbr = 1.1;// 弹前空气比热率
    double pkqmd0 = 1.2;// 弹前空气的初始密度 
    double cf1 = 0.004;// 空气与炮管壁的粘滞摩擦系数
    double Fp = 0;// 弹前空气阻力
};
#endif // !_AP_H