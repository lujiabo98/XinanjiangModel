#pragma once
#include "Data.h"

//水源划分
class Source
{
public:

	void SetParmameter(const Parameter* parameter);   //设置参数

	void SetState(const State* state);   //设置状态

	void UpdateState(State* state);    //更新状态

	void calculate();   //划分三水源

	Source(double sm = 20.0, double ex = 1.5, double kg = 0.35, double ki = 0.35,
		double r = 0.0, double rs = 0.0, double ri = 0.0, double rg = 0.0,
		double pe = 0.0, double fr = 0.0, double s0 = 0.0, double s = 0.0,
		double m = 0.0, double kid = 0.0, double kgd = 0.0,
		double smm = 0.0, double smmf = 0.0, double smf = 0.0, double au = 0.0,
		double rsd = 0.0, double rid = 0.0, double rgd = 0.0, double fr0 = 0.0,
		int n = 1, double q = 0.0, double kidd = 0.0, double kgdd = 0.0, double dt_ = 0.0);

	~Source();

protected:
private:
	//========模型参数========//

	double SM;   //表层自由水蓄水容量/mm ，敏感

	double EX;   //表层自由水蓄水容量方次，不敏感，1.0~1.5

	double KG;   //表层自由水蓄水库对地下水的日出流系数，敏感

	double KI;   //表层自由水蓄水库对壤中流的日出流系数，敏感

	//========模型状态========//

	double R;	 //总径流量，mm

	double RS;   //地面径流，mm

	double RI;   //壤中流，mm

	double RG;   //地下径流，mm

	double PE;	 //净雨量，mm

	double FR;	 //本时段产流面积比例

	double S0;   //本时段初的自由水蓄量，mm

	double S;    //本时段的自由水蓄量，mm


	double M;    //一天划分的计算时段数

	double KID;   //表层自由水蓄水库对壤中流的计算时段出流系数，敏感

	double KGD;    //表层自由水蓄水库对地下水的计算时段出流系数，敏感

	double SMM;    //全流域单点最大的自由水蓄水容量，mm

	double SMMF;  //产流面积上最大一点的自由水蓄水容量，mm

	double SMF;   //产流面积上的平均自由水蓄水容量深，mm

	double AU;   //相应平均蓄水深的最大蓄水深，S0值对应的纵坐标，mm

	double RSD;  //计算步长地面径流，mm

	double RID;  //计算步长壤中流，mm

	double RGD;  //计算步长地下径流，mm

	double FR0;   //上一时段产流面积比例

	int N;       //N 为计算时段分段数，每一段为计算步长

	double Q;     //Q 是每个计算步长内的净雨量，mm

	double KIDD;   //表层自由水蓄水库对壤中流的计算步长出流系数，敏感

	double KGDD;   //表层自由水蓄水库对地下水的计算步长出流系数，敏感

	double dt;   //模型计算时段长,h
};