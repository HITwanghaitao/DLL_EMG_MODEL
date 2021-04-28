#pragma once
#ifndef _RAIL_H
#define _RAIL_H


#include <cmath>
#include "AP.h"
class Rail
{
public:
	double Rr0 = 0;// 轨道初始电阻
	double Lr0 = 0;// 轨道初始电感
	double Lgrad = 0.403 * 1e-6;// 轨道电感梯度

	double ucdlr0 = 12.566 * 1e-7;// 轨道金属初始磁导率
	double pdzlr0 = 1.69 * 1e-8;// 轨道金属初始电阻率

	double Br = 3.6 * 1e-16;// 电阻率随电流变化系数(Ω.m2 / A)
	double hr = 0.04;//轨道高度

	double Fnvp = 60;// 弹丸对轨道的初始正压力
	double k1p = 0.025;// 弹丸轴向应力引起的径向应力与轴向应力的比率
	double Scp = 900 * 1e-6;// 弹丸与轨道接触的表面积
	double vpc = 2000;// 控制弹丸 - 轨道间摩擦系数切换的速度
	double upc = 0.34;// 速度小于切换速度时的弹丸 - 轨道间摩擦系数，即常值摩擦系数
	double up1 = 0.34;// 弹丸与轨道的静摩擦系数
	double up2 = 0.23;// 弹丸与钢质材料的静摩擦系数

	double Fnva = 60;// 电枢对轨道的初始正压力
	double k1a = 0.025;// 电枢轴向应力引起的径向应力与轴向应力的比率
	double Sca = 900 * 1e-6;// 电枢与轨道接触的表面积
	double vac = 2000;// 控制电枢 - 轨道间摩擦系数切换的速度
	double uac = 0.34;// 速度小于切换速度时的电枢 - 轨道间摩擦系数，即常值摩擦系数
	double ua1 = 0.34;// 电枢与轨道的静摩擦系数
	double ua2 = 0.23;// 电枢与钢质材料的静摩擦系数

	double cf2 = 0.003;// 等离子电枢与轨道间的粘滞摩擦系数
	double d = 0.03;// 轨道间距
	double l = 3.5;// 轨道长度

	// 以下初始化时未赋值
	double umcxsfp = 0;// 轨道 - 弹丸间的摩擦系数
	double Rgrad = 0;// 轨道电阻梯度

	double F = 0;// 电磁力
	double Fd = 0;// 轨道 - 等离子体间粘滞力
	double Ffp = 0;// 轨道 - 弹丸间摩擦力

	double Rr = 0;// 轨道的瞬时电阻
	double Lr = 0;// 轨道的瞬时电感
	double Ur = 0;// 轨道的瞬时电压

	double Pdzlr = 0;// 轨道金属瞬时电阻率
	Rail(void);
	//类函数
	//计算
	double static F_f(Rail rail, double i_sum);
	double static Fd_f(Rail rail, double ma, double v);
	double static Fp_f(AP environment, double a, double v, double x, double A, double P);
	double static Umcxsfp_f(Rail rail, double v);
	double static Ffp_f(Rail rail, double umcxsfp, double Ft, double Fp, double Ap);
	double static Dv_f(double F, double Ffp, double Fp, double Fd, double mp, double ma);
	double static RailRgrad_f(Rail rail, double i, double t);
	double static Rr_f(Rail rail, double x);
	double static Lr_f(Rail rail, double x);
	double static Ur_f(Rail rail, double Rr, double Lr, double i, double di, double v);
};

#endif // !_RAIL_H
