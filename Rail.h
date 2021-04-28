#pragma once
#ifndef _RAIL_H
#define _RAIL_H


#include <cmath>
#include "AP.h"
class Rail
{
public:
	double Rr0 = 0;// �����ʼ����
	double Lr0 = 0;// �����ʼ���
	double Lgrad = 0.403 * 1e-6;// �������ݶ�

	double ucdlr0 = 12.566 * 1e-7;// ���������ʼ�ŵ���
	double pdzlr0 = 1.69 * 1e-8;// ���������ʼ������

	double Br = 3.6 * 1e-16;// ������������仯ϵ��(��.m2 / A)
	double hr = 0.04;//����߶�

	double Fnvp = 60;// ����Թ���ĳ�ʼ��ѹ��
	double k1p = 0.025;// ��������Ӧ������ľ���Ӧ��������Ӧ���ı���
	double Scp = 900 * 1e-6;// ���������Ӵ��ı����
	double vpc = 2000;// ���Ƶ��� - �����Ħ��ϵ���л����ٶ�
	double upc = 0.34;// �ٶ�С���л��ٶ�ʱ�ĵ��� - �����Ħ��ϵ��������ֵĦ��ϵ��
	double up1 = 0.34;// ���������ľ�Ħ��ϵ��
	double up2 = 0.23;// ��������ʲ��ϵľ�Ħ��ϵ��

	double Fnva = 60;// ����Թ���ĳ�ʼ��ѹ��
	double k1a = 0.025;// ��������Ӧ������ľ���Ӧ��������Ӧ���ı���
	double Sca = 900 * 1e-6;// ���������Ӵ��ı����
	double vac = 2000;// ���Ƶ��� - �����Ħ��ϵ���л����ٶ�
	double uac = 0.34;// �ٶ�С���л��ٶ�ʱ�ĵ��� - �����Ħ��ϵ��������ֵĦ��ϵ��
	double ua1 = 0.34;// ���������ľ�Ħ��ϵ��
	double ua2 = 0.23;// ��������ʲ��ϵľ�Ħ��ϵ��

	double cf2 = 0.003;// �����ӵ����������ճ��Ħ��ϵ��
	double d = 0.03;// ������
	double l = 3.5;// �������

	// ���³�ʼ��ʱδ��ֵ
	double umcxsfp = 0;// ��� - ������Ħ��ϵ��
	double Rgrad = 0;// ��������ݶ�

	double F = 0;// �����
	double Fd = 0;// ��� - ���������ճ����
	double Ffp = 0;// ��� - �����Ħ����

	double Rr = 0;// �����˲ʱ����
	double Lr = 0;// �����˲ʱ���
	double Ur = 0;// �����˲ʱ��ѹ

	double Pdzlr = 0;// �������˲ʱ������
	Rail(void);
	//�ຯ��
	//����
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
