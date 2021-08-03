#pragma once
#include "Data.h"

//单元流域汇流，包括坡地汇流和河网汇流，都采用线性水库法
class Confluence
{
public:
	void SetParmameter(const Parameter* parameter);   //设置参数

	void SetState(const State* state);   //设置状态

	void UpdateState(State* state);    //更新状态

	void calculate();   //坡地汇流和河网汇流

	Confluence(double cs = 0.1, double ci = 0.6, double cg = 0.95, double cr = 0.2, double im = 0.01,
		double qs = 0.0, double qi = 0.0, double qg = 0.0, double qt = 0.0, double qu = 0.0,
		double rs = 0.0, double ri = 0.0, double rg = 0.0, double rim = 0.0,
		double qi0 = 0.0, double qg0 = 0.0, double qu0 = 0.0, double f = 0.0,
		double u = 0.0, double m = 0.0, double csd = 0.0, 
		double cid = 0.0, double cgd = 0.0, double crd = 0.0, double dt_ = 24);

	~Confluence();
protected:
private:
	//========模型参数========//

	double CS;   //地面径流消退系数，敏感

	double CI;   //壤中流消退系数，敏感

	double CG;   //地下水消退系数，敏感

	double CR;   //河网蓄水消退系数，敏感

	double IM;   //不透水面积占全流域面积的比例，不敏感

	//========模型状态========//

	double QS;   //单元流域地面径流，m3/s

	double QI;   //单元流域壤中流，m3/s

	double QG;   //单元流域地下径流，m3/s

	double QT;   //单元流域河网总入流
				 //（进入单元面积的地面径流、壤中流和地下径流之和），m3/s

	double QU;   //单元流域出口流量，m3/s

	double RS;   //地面径流量，mm

	double RI;   //壤中流径流量，mm

	double RG;   //地下径流量，mm

	double RIM;   //不透水面积上的产流量，mm

	double QI0;  //QI(t-1)，前一时刻壤中流，m3/s

	double QG0;  //QG(t-1)，前一时刻地下径流，m3/s

	double QU0;  //QU(t-1)，前一时刻单元流域出口流量，m3/s

	double F;   //单元流域面积，km2

	double U;   //单位转换系数

	double M;   //一天划分的计算时段数

	double CSD;   //计算时段内地面径流蓄水库的消退系数

	double CID;   //计算时段内壤中流蓄水库的消退系数

	double CGD;   //计算时段内地下水蓄水库的消退系数

	double CRD;   //计算时段内河网蓄水消退系数

	double dt;   //模型计算时段长,h
};