//创建时间：2021/5/14
//编程目标：以OOP方式实现三水源新安江模型
//模型结构：流域分单元，蒸散发分层次，产流分水源，汇流分阶段
//参考文献：[1]赵人俊.流域水文模型——新安江模型与陕北模型。北京：水利电力出版社，1983.
//         [2]包为民.水文预报，第5版，北京：中国水利水电出版社，2017
//         [3]李致家.现代水文模拟与预报技术，南京：河海大学出版社，2010
//         [4]翟家瑞.常用水文预报算法和计算程序，郑州：黄河水利出版社，1995


#include <string>

#include "Data.h"
#include "Watershed.h"
#include "Evapotranspiration.h"
#include "Runoff.h"
#include "Source.h"
#include "Confluence.h"
#include "Muskingum.h"


//主函数
int main(int argc, char* argv[])
{
	std::string Path = argv[0];  //获取可执行文件所在路径
	Path = Path.substr(0, Path.rfind("\\") + 1);   //获取可执行文件所在目录

	Parameter parameter;   //流域参数
	parameter.ReadFromFile(Path);   //读取参数文件

	IO io;      //流域输入与输出
	io.ReadFromFile(Path);   //从文本中导入降雨和蒸发数据，输出流量过程到文本中

	Watershed watershed;  //流域分单元
	watershed.ReadFromFile(Path);   //读取流域分块信息
	watershed.calculate(&io);    //计算各单元流域各时段降雨和水面蒸发量

	State * state = new State[watershed.GetnW()];   //每个单元流域的状态
	for (int nw = 0; nw < watershed.GetnW(); nw++)
	{
		state[nw].ReadFromFile(Path);   //读取模型计算时段长，h
	}

	Evapotranspiration evapotranspiration;  //流域蒸散发
	evapotranspiration.SetParmameter(&parameter);  //设置参数

	Runoff runoff;   //流域产流
	runoff.SetParmameter(&parameter);  //设置参数

	Source source;   //流域分水源
	source.SetParmameter(&parameter);  //设置参数

	Confluence confluence;   //呈村流域汇流
	confluence.SetParmameter(&parameter);  //设置参数

	Muskingum muskingum;    //呈村流域河道汇流
	muskingum.SetParmameter(&parameter);  //设置参数

	//逐时段逐单元流域计算
	int nT = io.nrows;   //nT表示时段数
	int nW = watershed.GetnW();   //nW为单元流域个数

	io.m_Q = new double[nT];   //创建动态一维数组存储流域出口断面流量过程

	for (int nt = 0; nt < nT; nt++)
	{
			state[0].m_Q = 0.0;;   //m_Q置为0

		for (int nw = 0; nw < nW; nw++)
		{
			state[nw].SetInput(nt, nw, &watershed);

			evapotranspiration.SetState(&state[nw]);
			evapotranspiration.calculate();
			evapotranspiration.UpdateState(&state[nw]);

			runoff.SetState(&state[nw]);
			runoff.calculate();
			runoff.UpdateState(&state[nw]);

			source.SetState(&state[nw]);
			source.calculate();   
			source.UpdateState(&state[nw]);

			confluence.SetState(&state[nw]);
			confluence.calculate();
			confluence.UpdateState(&state[nw]);

			muskingum.SetState(&state[nw]);
			muskingum.calculate();
			muskingum.UpdateState(&state[nw]);

			state[0].m_Q += state[nw].m_O2;
		}

		io.m_Q[nt] = state[0].m_Q;
	}
	
	//输出流域出口断面流量过程到文本Q.txt中
	io.WriteToFile(Path);

	delete[] state;

	return 0;
}

