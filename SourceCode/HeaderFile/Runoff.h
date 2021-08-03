#pragma once
#include "Data.h"

//蓄满产流模型
class Runoff
{
public:

	void SetParmameter(const Parameter* parameter);   //设置参数

	void SetState(const State* state);   //设置状态

	void UpdateState(State* state);    //更新状态

	void calculate();	//产流计算并更新土壤含水量

	Runoff(double wm = 120.0, double b = 0.2, double im = 0.01, 
		double wum = 20.0, double wlm = 80.0, double wdm = 20.0,
		double r = 0.0, double rim = 0.0, double w = 0.0, 
		double wu = 10.0, double wl = 30.0, double wd = 20.0,
		double wmm = 0.0, double a = 0.0, 
		double eu = 0.0, double el = 0.0, double ed = 0.0,
		double ep = 0.0, double pe =0.0, double p =0.0);

	~Runoff();

protected:
private:
	//========模型参数========//

	double WM;   //流域平均张力水容量/mm，不敏感，120~200

	double B;    //张力水蓄水容量曲线方次，不敏感，0.1~0.4

	double IM;   //不透水面积占全流域面积的比例，不敏感

	double WUM;   //上层张力水容量/mm，敏感，10~50

	double WLM;   //下层张力水容量/mm，敏感，60~90

	double WDM;   //深层张力水容量/mm，等于WM - WUM - WLM，不属于参数

	//========模型状态========//

	double R;	//总径流量，mm

	double RIM;   //不透水面积上的产流量，mm

	double W;	//流域平均初始土壤含水量，mm

	double WU;   //上层张力水蓄量，mm

	double WL;   //下层张力水蓄量，mm

	double WD;   //深层张力水蓄量，mm

	double WMM;   //包气带蓄水容量最大值，mm

	double A;    //初始土壤含水量最大值，mm

	double EU;   //上层蒸散发量，mm

	double EL;   //下层蒸散发量，mm

	double ED;   //深层蒸散发量，mm

	double EP;   //流域蒸发能力，mm

	double PE;	//净雨量，mm


	//========外部输入========//

	double P;    //降雨量，mm

};