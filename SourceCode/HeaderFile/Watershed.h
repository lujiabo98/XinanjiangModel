#pragma once
#include <string>
#include <vector>

class IO    //从文本中导入降雨和蒸发数据，输出流量过程到文本中
{
public:

	void ReadFromFile(std::string StrPath = "");   //从文本中导入流域降雨或蒸发数据

	void WriteToFile(std::string StrPath = "");    //输出流域出口断面流量过程到文本中

	IO();

	~IO();

public:

	std::vector< std::vector<double> > m_P;  //各雨量站逐时段降雨量，mm

	std::vector< std::vector<double> > m_EM;  //各蒸发站逐时段水面蒸发量，mm

	double* m_Q;    //流域出口断面流量过程，m3/s

	int nrows;     //数据行数

	int ncols;     //数据列数

};

//流域分块
class Watershed
{
public:
	void ReadFromFile(std::string StrPath = "");
	
	void SetValues(std::string name, double area, 
		int numRainfallStation, int numEvaporationStation, int numSubWatershed,
		double* areaSubWatershed, std::vector< std::vector<double> > rateRainfallStation,
		std::vector< std::vector<double> > rateEvaporationStation,
		std::string* nameRainfallStation, std::string* nameEvaporationStation,
		std::vector< std::vector<double> > P, std::vector< std::vector<double> > EM);

	void calculate(const IO * io);   //计算各单元流域降雨量和水面蒸发量

	double GetP(int nt, int nw);   //得到nt时刻，第nw单元流域的降雨量，mm

	double GetEM(int nt, int nw);   //得到nt时刻，第nw单元流域的水面蒸发量，mm

	double GetF(int nw);    //得到第nw单元流域的面积，km2

	int GetnW();   //得到单元流域个数

	Watershed();

	~Watershed();

protected:
private:
	std::string m_name;	//流域名称

	double m_area;	//流域控制面积，km2

	int m_numRainfallStation;		//雨量站个数

	int m_numEvaporationStation;    //蒸发站个数

	int m_numSubWatershed;	//单元流域个数

	double* m_areaSubWatershed;	//单元流域面积，km2

	std::vector< std::vector<double> > m_rateRainfallStation;  //各单元流域对应各雨量站比例，按泰森多边形分配

	std::vector< std::vector<double> > m_rateEvaporationStation;  //各单元流域对应各蒸发站比例，按泰森多边形分配

	std::string* m_nameRainfallStation;	//雨量站点名称

	std::string* m_nameEvaporationStation;  //蒸发站点名称

	std::vector< std::vector<double> > m_P;  //各单元流域逐时段降雨量，mm

	std::vector< std::vector<double> > m_EM;  //各单元流域逐时段水面蒸发量，mm

};

