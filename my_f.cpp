#include "my_f.h"
#include "pch.h"
#pragma warning(disable:4996)
using namespace std;
using namespace arma;

void my_f::vc_out(vector<double> vc)
{
    cout << "vc.size()=" << vc.size() << endl;
    for (vector<double>::iterator it = vc.begin(); it < vc.end(); it++)
    {
        cout << *it << " ";

    }
    cout << endl;
}

double my_f::vc_max(vector<double> vc)
{
    sort(vc.begin(), vc.end());
    return *(vc.end() - 1);
}



void my_f::get_data(string filename, vector<vector<double>>& c_data, int D)
{

    ifstream data(filename);
    double d;
    vector<double> temp;

    int i = 0;
    while (data >> d)
        //V.push_back(d);//将数据压入堆栈。//
    {
        i = i + 1;
        temp.push_back(d);
        if (i == D)
        {
            c_data.push_back(temp);
            temp = {};
            i = 0;
        }
    }
    data.close();
}

double gaussrand()//标准正态分布
{
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X;
}

double gaussrand_u_sigma(double u, double sigma)
{
	return sigma * gaussrand() + u;
}

vector<vector<double>> sample_norm(int N, int M)
{
	vector<vector<double>> r;
	r.resize(N, vector<double>(M));
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < M; k++)
		{
			r[j][k] = gaussrand();
		}
	}
	return r;
}

vector<vector<double>> sample_uniform(int N, int M)
{
	vector<vector<double>> r;
	r.resize(N, vector<double>(M));
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < M; k++)
		{
			r[j][k] = (double)rand() / RAND_MAX;
		}
	}
	return r;
}
vector<vector<double>> sample_uniform_bounds(int N, vector<vector<double>> bounds)
{
	//bounds = {{1,2},{2,3},{3,5}},例子
	int M = bounds.size();
	vector<vector<double>> r0 = sample_uniform(N, M);
	vector<vector<double>> r;
	r.resize(N, vector<double>(M));
	for (int k = 0; k < M; k++)
	{
		for (int j = 0; j < N; j++)
		{
			r[j][k] = (bounds[k][1] - bounds[k][0]) * r0[j][k] + bounds[k][0];
		}
	}
	return r;
}

string showTime()
{
# define TIME_SIZE 40

	static char time_buffer[TIME_SIZE];
	const struct tm* tm;
	size_t len;
	time_t now;

	now = time(NULL);
	tm = localtime(&now);

	len = strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm);

	cout << time_buffer << "\n";
	string local_time(time_buffer);
	return local_time;
# undef TIME_SIZE
}

double sim_model(vector<double> xin, vector<double> cin, int choice)
{

    Data a = Data(xin, cin);
    Data::staticDo(a);
    double y[4] = { 0 };
    double standard[] = { 537993.627149521, 2204.83053828361, 0.0380720009900398, 506562517.872436 };
    //y[0]= Data::GetMaxI(a)/standard[0];
    y[0] = Data::GetMaxI(a);
    y[1] = Data::GetMaxV(a);
    y[2] = Data::GetEff(a);
    y[3] = Data::GetHot(a);
    return y[choice - 1];

}