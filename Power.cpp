#include "Power.h"
#include<iostream>
#include "pch.h"
using namespace std;
Power::Power(int _flag, double _tp, double _Uc, double _Ic, double _Di)
{
    flag = _flag;
    tp = _tp;
    td = _tp;

    UcData = _Uc;
    Ucd0 = _Uc;
    IcData = _Ic;
    DiData = _Di;
}



void Power::discharge(Power* _power, int _flag, double _t0, double _step, double _uao)
{
    double Icd, Ucd, Idio, Icab;
    double t = _t0;
    double h = _step;
    int flag = _flag;
    double uao = _uao;
    Power* power = _power;

    if (t > power[flag].td - _step + 0.1 * _step)
    {
        mat x = { power[flag].Id0, power[flag].Ucd0 };
        power[flag].Ucd = power[flag].Ucd0;
        double xI_end = power[flag].Id0;


        double x1 = 0;
        double x2 = 0;
        double x3 = 0;
        double xI = 0;
        if (power[flag].Ucd >= 0)
        {
            double x_rl = xI_end;
            //��������� ��ʼ  ����rl��·
            /*
            double k1 = h * Power::rl(t, x_rl, power, flag, uao);
            double k2 = h * Power::rl(t + h / 2, x_rl + 0.5 * k1, power, flag, uao);
            double k3 = h * Power::rl(t + h / 2, x_rl + 0.5 * k2, power, flag, uao);
            double k4 = h * Power::rl(t + h, x_rl + k3, power, flag, uao);
            x_rl = x_rl + (k1 + 2 * k2 + 2 * k3 + k4) / 6
            */
            mat k1(1, 2, fill::zeros);
            mat k2(1, 2, fill::zeros);
            mat k3(1, 2, fill::zeros);
            mat k4(1, 2, fill::zeros);
            mat dx(1, 2, fill::zeros);
            k1 = h * Power::rlc(t, x, power, flag, uao);
            k2 = h * Power::rlc(t + h / 2, x + 0.5 * k1, power, flag, uao);
            k3 = h * Power::rlc(t + h / 2, x + 0.5 * k2, power, flag, uao);
            k4 = h * Power::rlc(t + h / 1, x + 1.0 * k3, power, flag, uao);
            x = x + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            //cout << "k1(0,0)=" << k1(0, 0) << endl;
            // ��������� ����
            dx = Power::rlc(t + h, x, power, flag, uao);

            power[flag].Id0 = x(0, 0);
            power[flag].Ucd0 = x(0, 1);
            power[flag].di = dx(0, 0);

            x1 = x(0, 0);
            x2 = x(0, 1);
            x3 = 0;
            xI = x1;
        }
        if ((power[flag].Ucd < 0) && (xI_end > 0))
        {
            double x_rl = xI_end;
            // ��������� ��ʼ  ����rl��·
            double k1, k2, k3, k4;
            double dx_rl;

            k1 = h * Power::rl(t, x_rl, power, flag, uao);
            k2 = h * Power::rl(t + h / 2, x_rl + 0.5 * k1, power, flag, uao);
            k3 = h * Power::rl(t + h / 2, x_rl + 0.5 * k2, power, flag, uao);
            k4 = h * Power::rl(t + h, x_rl + k3, power, flag, uao);
            x_rl = x_rl + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

            // ��������� ����
            dx_rl = Power::rl(t + h, x_rl, power, flag, uao);

            power[flag].Id0 = x_rl; // ���ε�������еĵ���
            power[flag].di = dx_rl;

            x1 = 0; // �������еĵ���
            x2 = power[flag].Ucd0; // ���������˵ĵ�ѹ
            x3 = x_rl; // Ǯλ�������еĵ���
            xI = x_rl;
        }
        if ((power[flag].Ucd < 0) && (xI_end < 0))
        {
            power[flag].Id0 = -(1e-5);  // ���ε�������еĵ���Ϊ��ֵʱ����ֵԼΪ0
            power[flag].di = 0;

            x1 = 0; // �������еĵ���
            x2 = power[flag].Ucd0; // ���������˵ĵ�ѹ
            x3 = 0; // �������еĵ���
            xI = 0;
        }
        Icd = x1;// �������еĵ���
        Ucd = x2;// ���������˵ĵ�ѹ
        Idio = x3;// ǯλ�������еĵ���
        Icab = xI;//���ε�������еĵ���
    }
    else
    {
        Icd = power[flag].Id0;// �������еĵ���
        Ucd = power[flag].Ucd0;// ���������˵ĵ�ѹ
        Idio = 0;// ǯλ�������еĵ���
        Icab = power[flag].Id0;
    }
}


double* Power::rlc_d(double t, mat _x, Power* _power, int _flag, double _uao)
{
    /*
    mat y(1,2,fill::zeros);
    y(0,0) = (1 / (_power[_flag].Lind + _power[_flag].Lcab)) * (_x(0,1) - (_power[_flag].Rcap + _power[_flag].Rscr) * _x(0,0) - (_power[_flag].Rind + _power[_flag].Rcab) * _x(0,0) - _uao);
    y(0,1) = (-1 / _power[_flag].C)* _x(0,0);
    return y;
    */
    double y[2] = {};
    y[0] = (1 / (_power[_flag].Lind + _power[_flag].Lcab)) * (_x(0, 1) - (_power[_flag].Rcap + _power[_flag].Rscr) * _x(0, 0) - (_power[_flag].Rind + _power[_flag].Rcab) * _x(0, 0) - _uao);
    y[1] = (-1 / _power[_flag].C) * _x(0, 0);
    return y;

}
mat Power::rlc(double t, mat _x, Power* _power, int _flag, double _uao)
{

    mat y(1, 2, fill::zeros);
    y(0, 0) = (1 / (_power[_flag].Lind + _power[_flag].Lcab)) * (_x(0, 1) - (_power[_flag].Rcap + _power[_flag].Rscr) * _x(0, 0) - (_power[_flag].Rind + _power[_flag].Rcab) * _x(0, 0) - _uao);
    y(0, 1) = (-1 / _power[_flag].C) * _x(0, 0);
    //cout << "y(0,0)=" << y(0, 0) << endl;
    //cout << "y(0,1)=" << y(0, 1) << endl;
    return y;
}


double Power::rl(double t, double _x, Power* _power, int _flag, double _uao)
{
    double y;
    y = (-1 / (_power[_flag].Lind + _power[_flag].Lcab)) * ((_power[_flag].Rdio) * _x + (_power[_flag].Rind + _power[_flag].Rcab) * _x + _uao);
    return y;
}

void Power::power_out(Power power)
{
    // int _flag, double _tp, double _Uc, double _Ic, double _Di
    cout << "****��Power��ϢΪ****" << endl;
    cout << "power.flag=" << power.flag << endl;
    cout << "power.tp=" << power.tp << endl;
    cout << "power.Ucd0=" << power.Ucd0 << endl;
    cout << "          ***         " << endl;
}