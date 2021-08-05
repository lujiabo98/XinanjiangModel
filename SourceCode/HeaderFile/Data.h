#pragma once
#include <string>
#include <vector>
#include "Watershed.h"

//模型参数
class Parameter
{
public:
	void ReadFromFile(std::string StrPath = "");   //从文件中读取模型参数

	void SetValues(double KC, double UM, double LM, double C,
		double WM, double B, double IM,
		double SM, double EX, double KG, double KI,
		double CS, double CI, double CG, double CR, double KE, double XE);    //设置参数值

	Parameter(double KC = 0.8, double UM = 20.0, double LM = 80.0, double C = 0.15,
		double WM = 120.0, double B = 0.2, double IM = 0.01,
		double SM = 20.0, double EX = 1.5, double KG = 0.35, double KI = 0.35,
		double CS = 0.1, double CI = 0.6, double CG = 0.95, double CR = 0.2, double KE = 24.0, double XE = 0.4);  //默认构造函数
	
	~Parameter();    //析构函数

protected:
public:
	//========蒸散发计算========//

	double m_KC;   //流域蒸散发折算系数，敏感

	double m_UM;   //上层张力水容量/mm，敏感，10~50

	double m_LM;   //下层张力水容量/mm，敏感，60~90

	double m_C;    //深层蒸散发折算系数，不敏感，0.10~0.20

	//========产流计算========//

	double m_WM;   //流域平均张力水容量/mm，不敏感，120~200

	double m_B;    //张力水蓄水容量曲线方次，不敏感，0.1~0.4

	double m_IM;   //不透水面积占全流域面积的比例，不敏感

	//========水源划分========//

	double m_SM;   //表层自由水蓄水容量/mm ，敏感

	double m_EX;   //表层自由水蓄水容量方次，不敏感，1.0~1.5

	double m_KG;   //表层自由水蓄水库对地下水的日出流系数，敏感

	double m_KI;   //表层自由水蓄水库对壤中流的日出流系数，敏感

	//========汇流计算========//
	double m_CS;   //日模型地面径流消退系数，敏感

	double m_CI;   //日模型壤中流蓄水库的消退系数，敏感

	double m_CG;   //日模型地下水蓄水库的消退系数，敏感

	double m_CR;   //日模型河网蓄水消退系数，敏感

	double m_KE;   //马斯京根法演算参数/h，敏感，KE = N * ∆t，N为河道分段数

	double m_XE;   //马斯京根法演算参数，敏感，0.0~0.5
};

//单个单元流域状态
class State
{
public:

	void SetInput(int nt, int nw, Watershed * watershed);   //设置外部输入，包括nt时刻，第nw单元流域的降雨m_P、水面蒸发m_EM和面积m_F

	void ReadFromFile(std::string StrPath = "");    //从文件中读取模型计算时段长m_dt

	void SetValues(double P, double EM, double F, double dt, double S0, double FR, 
		double EU, double EL, double ED, double E,
		double WU, double WL, double WD, double W, 
		double RIM, double R, double RS, double RI, double RG,
		double PE, double QS, double QI, double QG, double QU, 
		double QU0, double * O, double O2, double EP, double Q);   //设置状态值

	State(double P = 0, double EM = 0, double F = 0, double dt = 24, 
		double S0 = 0, double FR = 0, 
		double EU = 0, double EL = 0, double ED = 0, double E = 0,
		double WU = 10, double WL = 30, double WD = 20, double W = 60, 
		double RIM = 0, double R = 0, double RS = 0, double RI = 0, 
		double RG = 0, double PE = 0, double QS = 0, double QI = 0,
		double QG = 0, double QU = 0, double QU0 = 0, double * O = nullptr, 
		double O2 = 0.0, double EP = 0, double Q = 0);    //默认构造函数

	~State();

protected:
public:
	//========外部输入========//
	double m_P;    //单元流域降雨量，mm

	double m_EM;   //单元流域水面蒸发量，mm

	double m_F;    //单元流域面积,km2

	double m_dt;   //模型计算时段长,h

	//========模型状态========//

	double m_S0;   //本时段初产流面积上的平均自由水深，mm

	double m_FR;   //本时段产流面积比例

	double m_EU;   //上层蒸散发量，mm

	double m_EL;   //下层蒸散发量，mm

	double m_ED;   //深层蒸散发量，mm

	double m_E;    //总的蒸散发量，mm

	double m_EP;   //流域蒸发能力，mm

	double m_WU;   //上层张力水蓄量，mm

	double m_WL;   //下层张力水蓄量，mm

	double m_WD;   //深层张力水蓄量，mm

	double m_W;    //总的张力水蓄量，mm

	double m_RIM;   //不透水面积上的产流量，mm

	double m_R;	    //总径流量，mm

	double m_RS;   //地面径流，mm

	double m_RI;   //壤中流，mm

	double m_RG;   //地下径流，mm

	double m_PE;   //净雨量，mm，PE = P - KC * EM

	double m_QS;   //地面径流汇流，m3/s

	double m_QI;   //壤中流汇流，m3/s

	double m_QG;   //地下径流汇流，m3/s

	double m_QU;   //本时段末单元流域出口流量，m3/s

	double m_QU0;   //上一时段末即本时段初的单元流域出口流量，m3/s

	double * m_O;    //单元流域在各子河段出口断面形成的出流，m3/s

	double m_O2;   //单元流域在全流域出口断面形成的出流，m3/s


	//========输出外部========//

	double m_Q;    //流域出口断面流量，m3/s

};

