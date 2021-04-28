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

#include <iomanip>       //C++输出精度控制需要
#include <string>

#include <armadillo>
#include "Data.h"


using namespace std;
using namespace arma;
class my_f
{
public:
	void static vc_out(vector<double> vc);//输出vector内数据
	double static vc_max(vector<double> vc);//返回vector内最大值
	void static get_data(string filename, vector<vector<double>>& c_data, int D);//从文本获得数据
};
double gaussrand();//标准正态分布
double gaussrand_u_sigma(double u, double sigma);//生成特定u,sigma正态分布
vector<vector<double>> sample_norm(int N, int M);//正态抽样
vector<vector<double>> sample_uniform(int N, int M);//均匀抽样
vector<vector<double>> sample_uniform_bounds(int N, vector<vector<double>> bounds); //输入区间，生成区间内均匀分布

string showTime();//输出本地时间

double sim_model(vector<double> xin, vector<double> cin, int choice); //模型：输入为时序脉冲和电压X，不确定参数C，输出项选择choice

