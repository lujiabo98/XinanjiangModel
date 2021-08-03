#pragma once
#include "Data.h"

//三层蒸散发模型
class Evapotranspiration
{
public:
	void SetParmameter(const Parameter * parameter);   //设置参数

	void SetState(const State* state);   //设置状态

	void UpdateState(State* state);    //更新状态

	void calculate();    //计算三层蒸散发量

	Evapotranspiration(double kc = 0.8, double lm = 80.0, double c = 0.15,
		double wu = 10, double wl = 30, double ep = 0.0,
		double e = 0.0, double eu = 0.0, double el = 0.0, double ed = 0.0, 
		double p = 0.0, double em = 0.0);	//构造函数

	~Evapotranspiration();	 //析构函数

protected:
private:
	//========模型参数========//

	double KC;   //流域蒸散发折算系数，敏感

	double LM;   //下层张力水容量/mm，敏感，60~90

	double C;    //深层蒸散发折算系数，不敏感，0.10~0.20

	//========模型状态========//

	double WU;   //上层张力水蓄量，mm

	double WL;   //下层张力水蓄量，mm

	double EP;   //单元流域蒸发能力，mm

	double E;    //总的蒸散发量，mm

	double EU;   //上层蒸散发量，mm

	double EL;   //下层蒸散发量，mm

	double ED;   //深层蒸散发量，mm


	//========外部输入========//

	double P;    //降雨量，mm

	double EM;   //水面蒸发量，mm

};