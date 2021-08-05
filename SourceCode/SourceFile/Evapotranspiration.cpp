#include "Evapotranspiration.h"

void Evapotranspiration::SetParmameter(const Parameter* parameter)
{
	KC = parameter->m_KC;

	LM = parameter->m_LM;

	C = parameter->m_C;
}

void Evapotranspiration::SetState(const State* state)
{
	WU = state->m_WU;

	WL = state->m_WL;


	P = state->m_P;

	EM = state->m_EM;

}

void Evapotranspiration::UpdateState(State* state)
{
	state->m_EP = EP;

	state->m_E = E;

	state->m_EU = EU;

	state->m_EL = EL;

	state->m_ED = ED;
}

void Evapotranspiration::calculate()
{
	//三层蒸散发计算
	EP = KC * EM;    //计算流域蒸发能力

	if (P + WU >= EP)
	{
		EU = EP;
		EL = 0;
		ED = 0;
	}
	else
	{
		EU = P + WU;

		if (WL >= C * LM)
		{
			EL = (EP - EU) * WL / LM;
			ED = 0;
		}
		else
		{
			if (WL >= C * (EP - EU))
			{
				EL = C * (EP - EU);
				ED = 0;
			}
			else
			{
				EL = WL;
				ED = C * (EP - EU) - EL;
			}
		}
	}

	//计算总的蒸散发量
	E = EU + EL + ED;
}


Evapotranspiration::Evapotranspiration(double kc, double lm, double c, 
	double wu, double wl, double ep,
	double e, double eu, double el, double ed, 
	double p, double em)
{
	KC = kc;

	LM = lm;

	C = c;


	WU = wu;

	WL = wl;

	EP = ep;

	E = e;

	EU = eu;

	EL = el;

	ED = ed;


	P = p;

	EM = em;
}

Evapotranspiration::~Evapotranspiration()
{

}