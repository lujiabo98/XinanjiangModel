#include "Data.h"
#include <fstream>

void Parameter::ReadFromFile(std::string StrPath)
{
	std::ifstream fin(StrPath + "parameter.txt");

	fin >> m_KC
		>> m_UM
		>> m_LM
		>> m_C

		>> m_WM
		>> m_B
		>> m_IM

		>> m_SM
		>> m_EX
		>> m_KG
		>> m_KI

		>> m_CS
		>> m_CI
		>> m_CG
		>> m_CR
		>> m_KE
		>> m_XE;

	fin.close();
}
void Parameter::SetValues(double KC, double UM, double LM, double C,
	double WM, double B, double IM,
	double SM, double EX, double KG, double KI,
	double CS, double CI, double CG, double CR, double KE, double XE)
{
	m_KC = KC;
	m_UM = UM;
	m_LM = LM;
	m_C = C;

	m_WM = WM;
	m_B = B;
	m_IM = IM;

	m_SM = SM;
	m_EX = EX;
	m_KG = KG;
	m_KI = KI;

	m_CS = CS;
	m_CI = CI;
	m_CG = CG;
	m_CR = CR;
	m_KE = KE;
	m_XE = XE;
}

Parameter::Parameter(double KC, double UM, double LM, double C,
	double WM, double B, double IM,
	double SM, double EX, double KG, double KI,
	double CS, double CI, double CG, double CR, double KE, double XE)
{
	m_KC = KC;
	m_UM = UM;
	m_LM = LM;
	m_C = C;

	m_WM = WM;
	m_B = B;
	m_IM = IM;

	m_SM = SM;
	m_EX = EX;
	m_KG = KG;
	m_KI = KI;

	m_CS = CS;
	m_CI = CI;
	m_CG = CG;
	m_CR = CR;
	m_KE = KE;
	m_XE = XE;
}

Parameter::~Parameter()
{

}


void State::SetInput(int nt, int nw, Watershed* watershed)
{
	m_P = watershed->GetP(nt, nw);

	m_EM = watershed->GetEM(nt, nw);

	m_F = watershed->GetF(nw);
}

void State::ReadFromFile(std::string StrPath)
{
	std::ifstream fin(StrPath + "time.txt");

	fin >> m_dt;  //读取模型计算时段长,h

	fin.close();
}

void State::SetValues(double P, double EM, double F, double dt, double S0, double FR,
	double EU, double EL, double ED, double E,
	double WU, double WL, double WD, double W,
	double RIM, double R, double RS, double RI, double RG,
	double PE, double QS, double QI, double QG, double QU,
	double QU0, double * O, double O2, double EP, double Q)
{
	m_P = P;
	m_EM = EM;
	m_F = F;
	m_dt = dt;

	m_S0 = S0;
	m_FR = FR;
	m_EU = EU;
	m_EL = EL;
	m_ED = ED;
	m_E = E;
	m_WU = WU;
	m_WL = WL;
	m_WD = WD;
	m_W = W;
	m_RIM = RIM;
	m_R = R;
	m_RS = RS;
	m_RI = RI;
	m_RG = RG;
	m_PE = PE;
	m_QS = QS;
	m_QI = QI;
	m_QG = QG;
	m_QU0 = QU0;
	m_O = O;
	m_O2 = O2;
	m_EP = EP;

	m_Q = Q;
}

State::State(double P, double EM, double F, double dt, double S0, double FR,
	double EU, double EL, double ED, double E,
	double WU, double WL, double WD, double W,
	double RIM, double R, double RS, double RI, double RG,
	double PE, double QS, double QI, double QG, double QU,
	double QU0, double * O, double O2, double EP, double Q)
{
	m_P = P;
	m_EM = EM;
	m_F = F;
	m_dt = dt;

	m_S0 = S0;
	m_FR = FR;
	m_EU = EU;
	m_EL = EL;
	m_ED = ED;
	m_E = E;
	m_WU = WU;
	m_WL = WL;
	m_WD = WD;
	m_W = W;
	m_RIM = RIM;
	m_R = R;
	m_RS = RS;
	m_RI = RI;
	m_RG = RG;
	m_PE = PE;
	m_QS = QS;
	m_QI = QI;
	m_QG = QG;
	m_QU = QU;
	m_QU0 = QU0;
	m_O = O;
	m_O2 = O2;
	m_EP = EP;

	m_Q = Q;
}

State::~State()
{
	delete[] m_O;
}
