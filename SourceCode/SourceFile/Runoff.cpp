#include "Runoff.h"

void Runoff::SetParmameter(const Parameter* parameter)
{
	WM = parameter->m_WM;

	B = parameter->m_B;

	IM = parameter->m_IM;

	WUM = parameter->m_UM;

	WLM = parameter->m_LM;

}

void Runoff::SetState(const State* state)
{
	WU = state->m_WU;

	WL = state->m_WL;

	WD = state->m_WD;

	W = state->m_W;

	P = state->m_P;

	EU = state->m_EU;

	EL = state->m_EL;

	ED = state->m_ED;

	EP = state->m_EP;
}

void Runoff::UpdateState(State* state)
{
	state->m_WU = WU;

	state->m_WL = WL;

	state->m_WD = WD;

	state->m_W = W;

	state->m_R = R;

	state->m_PE = PE;

	state->m_RIM = RIM;
}

void Runoff::calculate()
{
	//========计算产流========//
	WMM = (1 + B) / (1 - IM) * WM;   //包气带蓄水容量最大值，mm

	A = WMM * (1 - pow(1 - W / WM, 1 / (1 + B)));   //初始土壤含水量最大值，mm

	PE = P - EP;

	if (PE <= 1e-5)    //这里认为净雨量小于1e-5时即为小于等于0
	{
		R = 0.0;

		RIM = 0.0;   //计算不透水面积上的产流量
	}
	else
	{
		if (A + PE <= WMM)
		{
			R = PE + W - WM + WM * pow(1 - (A + PE) / WMM, B + 1);
		}
		else
		{
			R = PE - (WM - W);
		}

		RIM = PE * IM;   //计算不透水面积上的产流量
	}

	//========计算下一时段初土壤含水量========//
	WU = WU + P - EU - R;

	WL = WL - EL;

	WD = WD - ED;

	if (WD < 0)
	{
		WD = 0;   //防止深层张力水蓄量小于0
	}

	//放置张力水蓄量超上限
	if (WU > WUM)
	{
		WL = WL + WU - WUM;

		WU = WUM;
	}

	if (WL > WLM)
	{
		WD = WD + WL - WLM;

		WL = WLM;
	}

	WDM = WM - WUM - WLM;  //计算深层张力水容量

	if (WD > WDM)
	{
		WD = WDM;
	}

	//计算土壤含水量
	W = WU + WL + WD;
}


Runoff::Runoff(double wm, double b, double im, 
	double wum, double wlm, double wdm,
	double r, double rim, double w,
	double wu, double wl, double wd,
	double wmm, double a, 
	double eu, double el, double ed, 
	double ep, double pe, double p)
{
	WM = wm;
	B = b;
	IM = im;
	WUM = wum;
	WLM = wlm;
	WDM = wdm;

	R = r;
	RIM = rim;
	W = w;
	WU = wu;
	WL = wl;
	WD = wd;
	WMM = wmm;
	A = a;
	EU = eu;
	EL = el;
	ED = ed;
	EP = ep;
	PE = pe;

	P = p;

}

Runoff::~Runoff()
{

}