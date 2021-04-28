#include "Rail.h"
#include "pch.h"

Rail::Rail(void)
{

}

double Rail::F_f(Rail rail, double i_sum)
{
    return 0.5 * rail.Lgrad * i_sum * i_sum;
}

double Rail::Fd_f(Rail rail, double ma, double v)
{
    return 2 * rail.cf2 * ma * v * v / rail.d;
}

double Rail::Fp_f(AP environment, double a, double v, double x, double A, double P)
{
    return ((environment.rbr + 1) / 2) * environment.pkqmd0 * (A * v * v + A * x * a + 0.5 * environment.cf1 * P * v * v * x);
}

double Rail::Umcxsfp_f(Rail rail, double v)
{
    // 轨道--弹丸间摩擦系数
    double umcxsfp;
    if (v <= rail.vpc)
        umcxsfp = rail.upc;
    else
        umcxsfp = 4 * (rail.up1 / rail.up2) * pow(v, -0.4);
    return umcxsfp;
}

double Rail::Ffp_f(Rail rail, double umcxsfp, double Ft, double Fp, double Ap)
{
    return umcxsfp * (rail.Fnvp + rail.k1p * rail.Scp * (Ft + Fp) / (2 * Ap));
}

double Rail::Dv_f(double F, double Ffp, double Fp, double Fd, double mp, double ma)
{
    return (F - Ffp - Fp - Fd) / (ma + mp);
}

double Rail::RailRgrad_f(Rail rail, double i, double t)
{
    return 8 * sqrt(rail.ucdlr0) * sqrt(rail.pdzlr0 + rail.Br * i / rail.hr) * sqrt(3.1415926) / (3 * rail.hr * sqrt(2 * (t + 1 * 1e-8)));
}

double Rail::Rr_f(Rail rail, double x)
{
    return rail.Rr0 + rail.Rgrad * x;
}

double Rail::Lr_f(Rail rail, double x)
{
    return rail.Lr0 + rail.Lgrad * x;
}

double Rail::Ur_f(Rail rail, double Rr, double Lr, double i, double di, double v)
{
    return Rr * i + Lr * di + rail.Lgrad * v * i;
}