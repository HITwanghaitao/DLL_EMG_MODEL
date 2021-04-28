#pragma once
#ifndef _DATA_H
#include "Power.h"
#include "Rail.h"
#include "AP.h"
#include "my_f.h"
#include <vector>
#include <armadillo>


using namespace arma;
using namespace std;

class Data
{
public:
    //数据成员
    double Uc0;// 电容初始电压
    double h;// 步长
    double tp[10] = { 0 };// 脉冲信号
    int tpLength;// 电容器个数（脉冲信号个数）

    double UcData;// 电容器电压 电容器个数乘以电容器组个数
    double IcData;// 电容器电流
    vector<double> IData = {};// 轨道电流
    vector<double> UoData;// 外端电压

    double DicData;// 电容器电流变化率
    double IcabData;// 波形调整电感中的电流

    vector<double> aData = {};// 加速度
    vector<double> vData = {};// 速度
    vector<double> xData = {};// 位移

    double Felec = 0;// 电磁力
        // Fp = 0 % 空气阻力
    double Ff = 0;// 滑动摩擦力

    double Ur = 0;// 轨道电压
    double Uf = 0;//
    double Ua = 0;// 电枢电压

    double C = 15e-3;// 电源模块电容值

    // 环境参数
    double rbr = 1.1;// 弹前空气比热率
    double pkqmd0 = 1.29;// 弹前空气的初始密度
    double cf1 = 0.004;// 空气与炮管壁的粘滞摩擦系数
    double Fp = 0;// 弹前空气阻力

    // 从属类
    Power power[10] = {};
    Rail rail = Rail();
    AP ap = AP();

    //Data(double _Uc, mat  _tp);
    Data(vector<double> xin, vector<double> cin);
    void static staticDo(Data& data);


    double static GetMaxI(Data data);
    double static GetMaxV(Data data);
    double static GetEff(Data data);
    double static GetHot(Data data);
    mat  static GetOut(Data data);
};
#define _DATA_H
#endif // !_DATA_H



