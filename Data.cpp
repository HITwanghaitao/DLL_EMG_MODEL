#include "Data.h"
#include "pch.h"
using namespace std;

Data::Data(vector<double> xin, vector<double> cin)
{
	tp[0] = 0;
	for (int j = 1; j < 10; j++)
	{
		tp[j] = xin[j - 1] * 1e-3;
	}
	Uc0 = xin[9] * 1000;
	tpLength = 10;

	for (int j = 0; j < 10; j++)
	{
		power[j] = Power(j, tp[j], Uc0, 0, 0);
		//Power::power_out(power[j]);
	}
	rail.Lgrad = cin[0] * 1e-6; //0.403
		//1 校准电感梯度Lgrad，Lgrad的真值为0.403*1e-6,波动范围选择[0.2,0.6]
	for (int j = 0; j < 10; j++)
	{
		power[j].C = cin[0] * 1e-3; //1 真值为15e-3，波动范围选择[12,18]
		power[j].Lind = cin[1] * 1e-6;// 2波形调整电感 21 * 1e-6; [15 25]
	}
	rail.Lgrad = cin[2] * 1e-6; // 3 0.403*1e-6 [0.2 0.6]
	rail.vpc = cin[3] * 1000;//4 2000 [1500 2500]
	rail.hr = cin[4]; //5 0.04 [0.03 0.05]

	ap.ma = cin[5]; // 6 40*1e-3 [20 50]
	ap.pkqmd0 = cin[6]; //7 1.2 [1.0 1.3]

	IData.push_back(0);
	UoData.push_back(0);
	aData.push_back(0);
	vData.push_back(0);
	xData.push_back(0);
}

/*
Data::Data(vector<double> xin, vector<double> cin)
{
	//cout << "size1=" << xin.size() << endl;
	//cout << "size2=" << cin.size() << endl;
	tp[0] = 0;
	for (int j = 1; j < 10; j++)
	{
		tp[j] = xin[j - 1]*1e-3;
	}
	Uc0 = xin[9]*1000;
	tpLength = 10;

	for (int j = 0; j < 10; j++)
	{
		power[j] = Power(j, tp[j], Uc0, 0, 0);
		//Power::power_out(power[j]);
	}
	//改动参数，（数量9 + 5个，分别为轨道类参数9个，电枢弹丸类参数5个），生成数据
		pm为mat类数据，大小为1*9
		数据依次为：
		轨道类参数9个：1.轨道电感梯度Lgrad， 2.初始磁导率miu0(ucdlr0),  3初始电阻率pdzlr0(rour0)，
		4 与轨道材料相关的常数beta（Br），
		5 miuc, 6 miu1,7 miu2,
		8 vc,9 k1
		电枢弹丸类参数5个：10 空气与炮管壁的粘滞阻力系数cf1，11 弹前空气的初始密度rou0（pkqmd0）,
		12 空气比热率gamma(rbr),
		13 电枢材料的磁导率miua0(ucdla0),14 电枢的初始电阻率roua0 (pdzla0)

	rail.Lgrad = cin[0] * 1e-6; //0.403
		//1 校准电感梯度Lgrad，Lgrad的真值为0.403*1e-6,波动范围选择[0.2,0.6]

	rail.ucdlr0 = cin[1] * 1e-7; //12.566
	//2 初始磁导率ucdlr0(miu0)= 12.566*1e-7

	rail.pdzlr0 = cin[2] * 1e-8; //1.69
	//3 初始电阻率pdzlr0(rour0) = 1.69*1e-8

	rail.Br = cin[3] * 1e-16; //3.6
	//4 与轨道材料相关的常数Br(beta)= 3.6*1e-16

	rail.upc = cin[4]; //0.34
	//5 速度小于切换速度时的弹丸 - 轨道间摩擦系数，即常值摩擦系数  miuc=0.34

	rail.up1 = cin[5]; //0.34
	//6 弹丸与轨道的静摩擦系数,miu1=0.34

	rail.up2 = cin[6]; //0.23
	//7 弹丸与钢质材料的静摩擦系数,miu2=0.23

	rail.vpc = cin[7]; //2000
	//8 控制弹丸 - 轨道间摩擦系数切换的速度,vc=2000

	rail.k1p = cin[8]; //0.025
	//9 弹丸轴向应力引起的径向应力与轴向应力的比率,k1=0.025

	ap.cf1 = cin[9] * 1e-3; //4
	//10 空气与炮管壁的粘滞阻力系数Cf1，真值为4*1e-3,波动范围选择[2,6]

	ap.pkqmd0 = cin[10]; //1.29
	//11 弹前空气的初始密度，真值为1.29，波动范围[1, 1.5]

	ap.rbr = cin[11]; //1.1
	//12 空气比热率gamma(rbr)=1.1

	ap.ucdla0 = cin[12] * 1e-7; //12.5666
	//13 电枢金属常温磁导率miua0(ucdla0)=12.566 * 1e-7

	ap.pdzla0 = cin[13] * 1e-8; //2.655
	//14 电枢的初始电阻率roua0 (pdzla0) = 2.655*1e-8
	IData.push_back(0);
	UoData.push_back(0);
	aData.push_back(0);
	vData.push_back(0);
	xData.push_back(0);
}
*/

void Data::staticDo(Data& data)
{
	double t = 0;
	int k = 0;
	data.h = 1e-5;
	double h = 1e-5;
	double dv = 1;
	double di_sum = 0;
	double Isum = data.IData[k];
	double x = data.xData[k];
	while ((Isum >= 0) && (dv > 0) && (x < 3.5) && (k < 1000))
	{
		Isum = data.IData[k];
		//cout << "第" << k << "次,Isum=" << Isum << endl;
		double a = data.aData[k];
		double v = data.vData[k];
		x = data.xData[k];

		double F = Rail::F_f(data.rail, Isum);
		data.rail.F = F;
		double Fd = Rail::Fd_f(data.rail, data.ap.ma, v) * 0;
		data.rail.Fd = Fd;
		double Fp = Rail::Fp_f(data.ap, a, v, x, data.ap.Ap, data.ap.Cp);
		data.Fp = Fp;
		double umcxsfp = Rail::Umcxsfp_f(data.rail, v);
		data.rail.umcxsfp = umcxsfp;
		double Ffp = Rail::Ffp_f(data.rail, umcxsfp, F, Fp, data.ap.Ap);
		data.rail.Ffp = Ffp;

		double a_ini = Rail::Dv_f(F, Ffp, Fp, Fd, data.ap.mp, data.ap.ma);

		if ((a_ini <= 0) && (v == 0))
		{
			a = 0;
			v = 0;
			x = 0;
			data.aData.push_back(a);
			data.vData.push_back(v);
			data.xData.push_back(x);
		}
		else
		{
			a = a_ini;
			v = v + a * h;
			x = x + v * h;
			data.aData.push_back(a);
			data.vData.push_back(v);
			data.xData.push_back(x);
			if (k == 0)
				dv = v;
			else
				dv = data.vData[k + 1] - data.vData[k];
		}

		double RailRgrad = Rail::RailRgrad_f(data.rail, Isum, t);
		data.rail.Rgrad = RailRgrad;
		double Rr = Rail::Rr_f(data.rail, x);
		data.rail.Rr = Rr;
		double Lr = Rail::Lr_f(data.rail, x);
		data.rail.Lr = Lr;
		double Ur = Rail::Ur_f(data.rail, Rr, Lr, Isum, di_sum, v);
		data.rail.Ur = Ur;

		double ArRgrad = AP::Ragra_f(data.ap, Isum, t);
		data.ap.Rgrad = ArRgrad;
		double Ra = AP::Ra_f(data.ap, data.ap.da);
		data.ap.Ra = Ra;
		double Ua = AP::Ua_f(Ra, Isum);
		data.ap.Ua = Ua;
		double Uao = Ua + Ur;

		double Inew_sum = 0;
		di_sum = 0;

		for (int j = 0; j < data.tpLength; j++)
		{
			Power::discharge(data.power, j, t, h, Uao);
			//cout << "data.power["<< j <<"].Id0=" << data.power[j].Id0 << endl;
			Inew_sum = Inew_sum + data.power[j].Id0;
			di_sum = di_sum + data.power[j].di;
		}
		data.IData.push_back(Inew_sum);
		//my_f::vc_out(data.IData);
		k = k + 1;
		t = t + h;
		//cout << "k = " << k << endl;
	}
	//my_f::vc_out(data.IData);
}


double Data::GetMaxI(Data data)
{
	return my_f::vc_max(data.IData);
}

double Data::GetMaxV(Data data)
{
	return my_f::vc_max(data.vData);
}

double Data::GetEff(Data data)
{
	double m = 0.04;
	double Vmax = my_f::vc_max(data.vData);
	int n = data.tpLength;
	double C = data.C;
	double U0 = data.Uc0;
	double y = m * pow(Vmax, 2) / (n * C * pow(U0, 2));
	return y;
}

double Data::GetHot(Data data)
{
	double h = data.h;
	vector<double> I = data.IData;
	double tlength = I.size();
	double miu = 1;
	double tho = 1;
	double Hot = 0;
	double t = 0;
	double theta = 0;
	for (int j = 0; j < tlength; j++)
	{
		theta = sqrt(3.1415926 * t / (miu * tho));
		Hot = Hot + pow(I[j], 2) * h;
		t = t + h;
	}
	return Hot;
}

mat  Data::GetOut(Data data)
{
	double y1 = Data::GetMaxI(data);
	double y2 = Data::GetMaxV(data);
	double y3 = Data::GetEff(data);
	double y4 = Data::GetHot(data);
	mat temp = { y1,y2,y3,y4 };
	//cout << temp << endl;
	return temp;
}
