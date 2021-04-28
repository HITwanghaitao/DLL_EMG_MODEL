#pragma once
#ifndef _AP_H
#define _AP_H

#include <cmath>
class AP
{
public:
    // �������
    double ma0 = 0.04;// ����ĳ�ʼ����
    double da = 0.03;// ���೤�ȣ����ڹ�����
    double ucdla0 = 12.566 * 1e-7;// ����������´ŵ���
    double pdzla0 = 2.655 * 1e-8;// ����������µ�����

    double Ba = 3.6 * 1e-16;// ����������˲̬�������õ��ĳ���(��.m2 / A)
    double ha = 0.025;// �����ȣ����ڹ�����

    double Aa = 7 * 1e-4;// ����ĺ�����
    double ua0 = 200;// �������˵�ѹ

    // ���³�ʼ��ʱδ��ֵ
    double Ft = 0;// ����Ե��������
    double ma = 0.04;// �����˲ʱ����

    double Ua = 0;// �������˵ĵ�ѹ

    double Rgrad = 0;//�������ĵ���ݶ�
    double Ra = 0;// �����˲ʱ����
    //double a = 0;// ��������˲ʱ����
    //double v = 0;// ���������ٶ�
    //double x = 0;// ��������λ��
    // �������
    double v0 = 0;// ������ٶȳ�ֵ
    double x0 = 0;// �����λ�ó�ֵ

    double mp0 = 0;// ���������ĳ�ʼֵ
    double Cp = 120 * 1e-3;// ����Ľ����ܳ�
    double Ap = 900 * 1e-6;// ����ĺ�����
    double mp = 0; //��������
    AP(void);
    //����
    double static Ragra_f(AP armature, double i, double t);
    double static Ra_f(AP armature, double x);
    double static Ua_f(double Ra, double i);

    // ��������
    double rbr = 1.1;// ��ǰ����������
    double pkqmd0 = 1.2;// ��ǰ�����ĳ�ʼ�ܶ� 
    double cf1 = 0.004;// �������ڹܱڵ�ճ��Ħ��ϵ��
    double Fp = 0;// ��ǰ��������
};
#endif // !_AP_H