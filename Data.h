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
    //���ݳ�Ա
    double Uc0;// ���ݳ�ʼ��ѹ
    double h;// ����
    double tp[10] = { 0 };// �����ź�
    int tpLength;// �����������������źŸ�����

    double UcData;// ��������ѹ �������������Ե����������
    double IcData;// ����������
    vector<double> IData = {};// �������
    vector<double> UoData;// ��˵�ѹ

    double DicData;// �����������仯��
    double IcabData;// ���ε�������еĵ���

    vector<double> aData = {};// ���ٶ�
    vector<double> vData = {};// �ٶ�
    vector<double> xData = {};// λ��

    double Felec = 0;// �����
        // Fp = 0 % ��������
    double Ff = 0;// ����Ħ����

    double Ur = 0;// �����ѹ
    double Uf = 0;//
    double Ua = 0;// �����ѹ

    double C = 15e-3;// ��Դģ�����ֵ

    // ��������
    double rbr = 1.1;// ��ǰ����������
    double pkqmd0 = 1.29;// ��ǰ�����ĳ�ʼ�ܶ�
    double cf1 = 0.004;// �������ڹܱڵ�ճ��Ħ��ϵ��
    double Fp = 0;// ��ǰ��������

    // ������
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



