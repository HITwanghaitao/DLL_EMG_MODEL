#pragma once
#ifndef _POWER_H
#define _POWER_H

#include <armadillo>


using namespace arma;
class Power
{
public:
    double Rcap = 41 * 1e-6; // ����������
    double Rscr = 6.7 * 1e-6; // ��բ�ܵ���
    double Rind = 20 * 1e-6; // ���������
    double Rcab = 20 * 1e-6; // �����ߵ���
    double Rdio = 18 * 1e-3; //��Ч�����ܵĵ������

    double Lind = 21 * 1e-6; // ���ε������
    double Lcab = 45 * 1e-9; // �����ߵĵ��

    double C = 15e-3; // ��Դģ�����ֵ


    double tp; //����ʱ��
    double UcData;
    double IcData;
    double DiData;

    double Ucd0 = 0;
    double Id0 = 0; //�������ŵ�ʱ�ĳ�ʼ����
    int flag;
    double td;

    // ���³�ʼ��ʱδ��ֵ
    double Ucc; // ���������ʱ��˲ʱ��ѹ
    double Ucd; //�������ŵ�ʱ��˲ʱ��ѹ
    double Ucf; //����������ʱ��˲ʱ��ѹ
    double tcc; //�������ĳ��ʱ��
    double tcd; //�������ķŵ�ʱ��
    double tcf; //������������ʱ��

    double di = 0;// �������ŵ�ʱ�ĳ�ʼ�����ı仯��

    Power(int _flag = 0, double _tp = 0, double _Uc = 0, double _Ic = 0, double _Di = 0);

    void static discharge(Power* _power, int _flag, double _t0, double _step, double _uao);

    double static* rlc_d(double t, mat _x, Power* _power, int _flag, double _uao);
    mat static rlc(double t, mat _x, Power* _power, int _flag, double _uao);

    double static rl(double t, double _x, Power* _power, int _flag, double _uao);
    void static power_out(Power power);
};

#endif // !_POWER_H

