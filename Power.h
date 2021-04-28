#pragma once
#ifndef _POWER_H
#define _POWER_H

#include <armadillo>


using namespace arma;
class Power
{
public:
    double Rcap = 41 * 1e-6; // 电容器电阻
    double Rscr = 6.7 * 1e-6; // 晶闸管电阻
    double Rind = 20 * 1e-6; // 电感器电阻
    double Rcab = 20 * 1e-6; // 连接线电阻
    double Rdio = 18 * 1e-3; //等效二极管的电阻电阻

    double Lind = 21 * 1e-6; // 波形调整电感
    double Lcab = 45 * 1e-9; // 连接线的电感

    double C = 15e-3; // 电源模块电容值


    double tp; //脉冲时间
    double UcData;
    double IcData;
    double DiData;

    double Ucd0 = 0;
    double Id0 = 0; //电容器放电时的初始电流
    int flag;
    double td;

    // 以下初始化时未赋值
    double Ucc; // 电容器充电时的瞬时电压
    double Ucd; //电容器放电时的瞬时电压
    double Ucf; //电容器馈电时的瞬时电压
    double tcc; //电容器的充电时间
    double tcd; //电容器的放电时间
    double tcf; //电容器的馈电时间

    double di = 0;// 电容器放电时的初始电流的变化率

    Power(int _flag = 0, double _tp = 0, double _Uc = 0, double _Ic = 0, double _Di = 0);

    void static discharge(Power* _power, int _flag, double _t0, double _step, double _uao);

    double static* rlc_d(double t, mat _x, Power* _power, int _flag, double _uao);
    mat static rlc(double t, mat _x, Power* _power, int _flag, double _uao);

    double static rl(double t, double _x, Power* _power, int _flag, double _uao);
    void static power_out(Power power);
};

#endif // !_POWER_H

