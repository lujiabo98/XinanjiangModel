#include "Muskingum.h"

void Muskingum::SetParmameter(const Parameter* parameter)
{
	KE = parameter->m_KE;

	XE = parameter->m_XE;
}

void Muskingum::SetState(const State* state)
{
	I1 = state->m_QU0;

	I2 = state->m_QU;

	O = state->m_O;

	dt = state->m_dt;
}

void Muskingum::UpdateState(State* state)
{
	state->m_O = O;

	state->m_O2 = O2;
}

void Muskingum::calculate()
{
	KL = dt;   //为了保证马斯京根法的两个线性条件，每个单元河取 KL = ∆t

	N = int(KE / KL);    //单元河段数

	XL = 0.5 - N * (1 - 2 * XE) / 2;    //计算单元河段XL

	double denominator = 0.5 * dt + KL - KL * XL;   //计算分母

	C0 = (0.5 * dt - KL * XL) / denominator;

	C1 = (0.5 * dt + KL * XL) / denominator;

	C2 = (-0.5 * dt + KL - KL * XL) / denominator;

	if (!O)
	{
		O = new double[N];  //创建存储单元流域在子河段出口断面的出流量的动态数组
		
		for (int n = 0; n < N; n++)
		{
			O[n] = 0.0;    //单元流域在子河段出口断面的出流量为0
		}
	}
	
	for (int n = 0; n < N; n++)
	{
		O1 = O[n];   //子河段时段初出流量

		O2 = C0 * I2 + C1 * I1 + C2 * O1;   //计算时段末单元流域在子河段出口断面的出流量，m3/s

		O[n] = O2;   //更新子河段时段初出流量

		I1 = O1;    //上一河段时段初出流为下一河段时段初入流

		I2 = O2;    //上一河段时段末出流为下一河段时段末入流
	}
}

Muskingum::Muskingum(double ke, double xe, double kl, double xl, 
	int n, double c0, double c1, double c2,
	double i1, double i2, double o1, 
	double o2, double* o, double dt_)
{
	KE = ke;

	XE = xe;

	KL = kl;

	XL = xl;

	N = n;

	C0 = c0;

	C1 = c1;

	C2 = c2;

	I1 = i1;

	I2 = i2;

	O1 = o1;

	O2 = o2;

	O = o;

	dt = dt_;
}

Muskingum::~Muskingum()
{

}