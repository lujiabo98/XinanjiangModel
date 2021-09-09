#include "Source.h"

void Source::SetParmameter(const Parameter* parameter)
{
	SM = parameter->m_SM;

	EX = parameter->m_EX;

	KG = parameter->m_KG;

	KI = parameter->m_KI;
}

void Source::SetState(const State* state)
{
	R = state->m_R;

	PE = state->m_PE;

	FR = state->m_FR;

	S0 = state->m_S0;

	dt = state->m_dt;
}

void Source::UpdateState(State* state)
{
	state->m_RS = RS;

	state->m_RI = RI;

	state->m_RG = RG;

	state->m_S0 = S;

	state->m_FR = FR;

}

void Source::calculate()
{
	//出流系数换算
	M = 24.0 / dt;   //一天划分的计算时段数

	KID = (1 - pow(1 - (KI + KG), 1.0 / M)) / (1 + KG / KI);   //表层自由水蓄水库对壤中流的计算时段出流系数，敏感

	KGD = KID * KG / KI;   //表层自由水蓄水库对地下水的计算时段出流系数，敏感

	//三分水源[4]
	if (PE <= 1e-5)
	{
		//净雨量小于等于0时,这里认为净雨量小于1e-5时即为小于等于0
		RS = 0;

		RI = KID * S0 * FR;   /*当净雨量小于等于0时，消耗自由水蓄水库中的水
							  产流面积比例仍为上一时段的比例不变*/
		RG = KGD * S0 * FR;

		S = S0 * (1 - KID - KGD);   //更新下一时段初的自由水蓄量

	}
	else
	{
		//净雨量大于0时
		SMM = SM * (1 + EX);   //全流域单点最大的自由水蓄水容量，mm

		FR0 = FR;   //上一时段产流面积比例

		FR = R / PE;   //计算本时段产流面积比例

		if (FR > 1)    //如果FR由于小数误差而计算出大于1的情况，则强制置为1
		{
			FR = 1;
		}

		S = S0 * FR0 / FR;

		N = int(PE / 5.0) + 1;   //N 为计算时段分段数，每一段为计算步长

		Q = PE / N;    //Q 是每个计算步长内的净雨量，mm
		                      //R 是总径流量，PE是单元流域降雨深度。
				              //把R按5mm分，实际操作就是把PE按5mm分，是为了减小产流面积变化的差分误差。
				              //自由水蓄水库只发生在产流面积上，其底宽为产流面积FR，显然FR是随时间变化的。
				              //产流量R进入水库即在产流面积上产生PE的径流深。
				              //FR = f / F = R / PE 

		KIDD = (1 - pow(1 - (KID + KGD), 1.0 / N)) / (1 + KGD / KID);  //表层自由水蓄水库对壤中流的计算步长出流系数，敏感

		KGDD = KIDD * KGD / KID;  //表层自由水蓄水库对地下水的计算步长出流系数，敏感

		//把该时段的RS、RI、RG置0，用于后续累加计算步长内的RSD、RID、RGD
		RS = 0.0;

		RI = 0.0;

		RG = 0.0;

		//计算产流面积上最大一点的自由水蓄水容量 SMMF
		if (EX == 0.0)
		{
			SMMF = SMM;   //EX等于0时，流域自由水蓄水容量分布均匀
		}
		else
		{
			//假定SMMF与产流面积FR及全流域上最大点的自由水蓄水容量SMM仍为抛物线分布
			//则SMMF应该用下式计算
			SMMF = (1 - pow(1 - FR, 1.0 / EX)) * SMM;
		}

		SMF = SMMF / (1.0 + EX);

		//将每个计算时段的入流量R分成N段，计算各个计算步长内的RSD、RID、RGD，再累加得到RS、RI、RG
		for (int i = 1; i <= N; i++)
		{
			if (S > SMF)
			{
				S = SMF;
			}

			AU = SMMF * (1 - pow(1 - S / SMF, 1.0 / (1 + EX)));

			if (Q + AU <= 0)
			{
				RSD = 0;

				RID = 0;

				RGD = 0;

				S = 0;
			}
			else
			{
				if (Q + AU >= SMMF)
				{
					//计算步长内的净雨量进入自由水蓄水库后，使得自由水蓄水深超过产流面积上最大单点自由水蓄水深
					RSD = (Q + S - SMF) * FR;

					RID = SMF * KIDD * FR;

					RGD = SMF * KGDD * FR;

					S = SMF * (1 - KIDD - KGDD);
				}
				else
				{
					//自由水蓄水深未超过产流面积上最大单点自由水蓄水深
					RSD = (S + Q - SMF + SMF * pow(1 - (Q + AU) / SMMF, 1 + EX)) * FR;

					RID = (S * FR + Q * FR - RSD) * KIDD;

					RGD = (S * FR + Q * FR - RSD) * KGDD;

					S = S + Q - (RSD + RID + RGD) / FR;
				}
			}

			//累加计算时段内的地面径流、壤中流和地下径流
			RS = RS + RSD;

			RI = RI + RID;

			RG = RG + RGD;
		}
	}
}


Source::Source(double sm, double ex, double kg, double ki,
	double r, double rs, double ri, double rg,
	double pe, double fr, double s0, double s,
	double m, double kid, double kgd,
	double smm, double smmf, double smf, double au,
	double rsd, double rid, double rgd, double fr0,
	int n, double q, double kidd, double kgdd, double dt_)
{
	SM = sm;

	EX = ex;

	KG = kg;

	KI = ki;

	R = r;

	RS = rs;

	RI = ri;

	RG = rg;

	PE = pe;

	FR = fr;

	S0 = s0;

	S = s;

	M = m;

	KID = kid;

	KGD = kgd;

	SMM = smm;

	SMMF = smmf;

	SMF = smf;

	AU = au;

	RSD = rsd;

	RID = rid;

	RGD = rgd;

	FR0 = fr0;

	N = n;

	Q = q;

	KIDD = kidd;

	KGDD = kgdd;

	dt = dt_;
}

Source::~Source()
{

}