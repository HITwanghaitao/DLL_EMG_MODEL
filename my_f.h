#pragma once
#pragma warning(disable:4996)
#include<vector>
#include<cmath>
#include<iostream>
#include <algorithm>
#include<vector>
#include<random>
#include<fstream>
# include <cstdlib>
# include <iomanip>
# include <ctime>
# include <cstring>

#include <iomanip>       //C++������ȿ�����Ҫ
#include <string>

#include <armadillo>
#include "Data.h"


using namespace std;
using namespace arma;
class my_f
{
public:
	void static vc_out(vector<double> vc);//���vector������
	double static vc_max(vector<double> vc);//����vector�����ֵ
	void static get_data(string filename, vector<vector<double>>& c_data, int D);//���ı��������
};
double gaussrand();//��׼��̬�ֲ�
double gaussrand_u_sigma(double u, double sigma);//�����ض�u,sigma��̬�ֲ�
vector<vector<double>> sample_norm(int N, int M);//��̬����
vector<vector<double>> sample_uniform(int N, int M);//���ȳ���
vector<vector<double>> sample_uniform_bounds(int N, vector<vector<double>> bounds); //�������䣬���������ھ��ȷֲ�

string showTime();//�������ʱ��

double sim_model(vector<double> xin, vector<double> cin, int choice); //ģ�ͣ�����Ϊʱ������͵�ѹX����ȷ������C�������ѡ��choice

