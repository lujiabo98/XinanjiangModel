#pragma once
#include "Data.h"

//河道汇流：马斯京根分段连续演算法（分段马法）
class Muskingum
{
public:
	void SetParmameter(const Parameter* parameter);   //设置参数

	void SetState(const State* state);   //设置状态

	void UpdateState(State* state);    //更新状态

	void calculate();

	Muskingum(double ke = 0.0, double xe = 0.0, 
		double kl = 0.0, double xl = 0.0, 
		int n = 1, double c0 = 0.0, 
		double c1 = 0.0, double c2 = 0.0,
		double i1 = 0.0, double i2 = 0.0, 
		double o1 = 0.0, double o2 = 0.0, double* o = nullptr, double dt_ = 24);

	~Muskingum();

protected:
private:
	//========模型参数========//

	double KE;   //马斯京根法演算参数，h，敏感，KE = N * ∆t

	double XE;   //马斯京根法演算参数，敏感，0.0~0.5

	//========模型状态========//

	double KL;   //子河段的马斯京根法演算参数/h

	double XL;   //子河段的马斯京根法演算参数

	int N;    //单元河段数，即分段数

	double C0;    //马斯京根流量演算公式I2系数

	double C1;    //马斯京根流量演算公式I1系数

	double C2;    //马斯京根流量演算公式O1系数

	double I1;    //时段初的河段入流量

	double I2;    //时段末的河段入流量

	double O1;    //时段初的河段出流量

	double O2;    //时段末的河段出流量

	double * O;   //各子河段出流量

	double dt;   //模型计算时段长,h

};