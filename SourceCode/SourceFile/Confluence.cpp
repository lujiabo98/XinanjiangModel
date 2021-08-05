#include "Confluence.h"

void Confluence::SetParmameter(const Parameter* parameter)
{
	CS = parameter->m_CS;

	CI = parameter->m_CI;

	CG = parameter->m_CG;

	CR = parameter->m_CR;

	IM = parameter->m_IM;
}

void Confluence::SetState(const State* state)
{
	RIM = state->m_RIM;

	RS = state->m_RS;

	RI = state->m_RI;

	RG = state->m_RG;

	QS = state->m_QS;

	QI = state->m_QI;

	QG = state->m_QG;

	QU0 = state->m_QU;

	F = state->m_F;

	dt = state->m_dt;
}

void Confluence::UpdateState(State* state)
{
	state->m_QS = QS;

	state->m_QI = QI;

	state->m_QG = QG;

	state->m_QU = QU;

	state->m_QU0 = QU0;
}

void Confluence::calculate()
{
	//把透水面积上的产流量均摊到单元流域上

	RS = RS * (1 - IM);

	RI = RI * (1 - IM);

	RG = RG * (1 - IM);

	//出流系数换算

	M = 24.0 / dt;   //一天划分的计算时段数

	CSD = pow(CS, 1.0 / M);   //计算时段内地面径流蓄水库的消退系数

	CID = pow(CI, 1.0 / M);   //计算时段内壤中流蓄水库的消退系数

	CGD = pow(CG, 1.0 / M);   //计算时段内地下水蓄水库的消退系数

	CRD = pow(CR, 1.0 / M);   //计算时段内河网蓄水消退系数

	//坡地汇流
	U = F / 3.6 / 24;   //单位转换系数

	QS = CSD * QS + (1 - CSD) * (RS + RIM) * U;   //地面径流流入地面径流水库，
	                                              //经过消退(CSD)，成为地面径流对河网的总入流QS

	QI = CID * QI + (1 - CID) * RI * U;    //壤中流流入壤中流水库，
										   //经过消退(CID)，成为壤中流对河网的总入流QI

	QG = CGD * QG + (1 - CGD) * RG * U;    //地下径流进入地下水蓄水库，经过地下水
										   //蓄水库的消退(CGD)，成为地下水对河网的总入流QG

	QT = QS + QI + QG;

	//河网汇流，采用线性水库法，且仅当单元流域面积大于200km2时才计算河网汇流
	if (F < 200)
	{
		QU = QT;   //单元流域面积不大且河道较短，对水流运动的调蓄作用通常较小
		           //将这种调蓄作用合并在地面径流和地下径流中一起考虑所带来的误差通常可以忽略
	}
	else
	{
		QU = CRD * QU + (1 - CRD) * QT;   //线性水库法
		                                  //只有在单元流域面积较大或流域坡面汇流极其复杂时
		                                  //才考虑单元面积内的河网汇流
	}
}

Confluence::Confluence(double cs, double ci, double cg, double cr, double im,
	double qs, double qi, double qg, double qt, double qu,
	double rs, double ri, double rg, double rim,
	double qi0, double qg0, double qu0, double f,
	double u, double m, double csd, double cid, double cgd, double crd, double dt_)
{
	CS = cs;

	CI = ci;

	CG = cg;
	
	CR = cr;

	IM = im;

	QS = qs;

	QI = qi;

	QG = qg;

	QT = qt;

	QU = qu;

	RS = rs;

	RI = ri;

	RG = rg;

	RIM = rim;

	QI0 = qi0;

	QG0 = qg0;

	QU0 = qu0;

	F = f;

	U = u;

	M = m;

	CSD = csd;

	CID = cid;

	CGD = cgd;

	CRD = crd;

	dt = dt_;
}

Confluence::~Confluence()
{

}