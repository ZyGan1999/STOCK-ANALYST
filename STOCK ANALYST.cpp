#include"solution.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#ifndef threshold
#define threshold 1
#endif

int main()
{
	std::ios::sync_with_stdio(false);
	std::string FileName;
	solution* solu = new solution;
	std::cout << "欢迎使用股票自助查询系统!\n";
	chongxinshuru:
	std::cout << "请确保股票数据文件放在本程序统一目录下，请输入文件名（例如“stock.csv”）\n";
	std::cin >> FileName;
	std::ifstream cache(FileName.c_str());
	//time_t t1 = clock();
	if (cache.is_open()) {
		std::cout << "请耐心等待\n";
		
		solu->LoadStockData(FileName.c_str());
		std::cout << "\b\b\b" << "100%";
		std::cout << std::endl;
		std::cout << "读取成功！你想要做什么？\a\n";
		solu-> MENU();
	}
	else {
		std::cout << "读取失败，请检查后重试。\n";
		//system("pause");
		//system("cls");
		goto chongxinshuru;

	}
	chongxinxuanze:
	char _choice;
	_choice = std::cin.get();
	int Choice = _choice - '0';
	switch (Choice) {
	case 1: {
		std::cout << "请按格式输入一个指令 例如-C 000001.SZ -h -d 2017-01-03\n"
			<< "请注意，一定要包含股票名与查询日期\n" << "o:开盘价，c：收盘价，a：调整后收盘价，h：最高价，l：最低价\n";
		std::string instruct;
		std::getline(std::cin, instruct);
		std::getline(std::cin, instruct);
		if (solu->Query(instruct.c_str())) {
			std::cout << "没有找到相关信息！\n" << "您是否是要查询以下股票？\n";
			solu->FuzzyMatch(solu->tellStockID(instruct.c_str()).c_str(), threshold);
			system("pause");
			system("cls");
			solu->MENU();
			
			goto chongxinxuanze;
		}
		else {
			std::cout << "以上是您的查询结果,您还想要做什么？\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		}
	case 2: {
		std::cout << "请按格式输入需要查询的日期,如“2017-01-03”\n";
		std::string date;
		std::cin >> date;
		std::cout << "请输入排序的依据，可选择的有“Volume”、“Range”、“AdjClose”\n";
		std::string data;
		std::cin >> data;
		std::cout << "请输入一个数字k，代表你想要获取的前k项内容\n";
		int k;
		std::cin >> k;
		std::cout << "请输入一个数字0或1,0代表查询前k项，1代表查询后k项\n";
		int desc;
		std::cin >> desc;
		if (solu->TopK(date.c_str(), data.c_str(), k, desc)<0) {
			std::cout << "没有找到相关信息！\n" << "请再次核对您的查询信息！\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		else {
			std::cout << "以上是您的查询结果,您还想要做什么？\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
	}
	case 3: {
		std::string instruct;
		std::cout << "请按格式输入一个指令,例如-C 000001.SZ -d 2017-01-03 -d 2017-01-04 -o -v\n";
		std::cout << "必须包括股票名、开始日期、结束日期、计算目标、平均值（v）或标准差（s）\n";
		std::getline(std::cin,instruct);
		std::getline(std::cin, instruct);
		double result;
		if ((result=(solu->Calculate(instruct.c_str()))) < 0) {
			std::cout<< "没有找到相关信息！\n" << "您是否是要查询以下股票？\n";
			solu->FuzzyMatch(solu->tellStockID(instruct.c_str()).c_str(), threshold);
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		else {
			std::cout << result<<std::endl;
			std::cout << "以上是您的查询结果,您还想要做什么？\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
	}
	case 4: {
		std::cout << "请输入股票代码\n";
		std::string code;
		std::cin>>code;
		if (solu->FindCode(code.c_str()) < 0) {
			std::cout << "未能找到相应股票，您可能想查找以下股票？\n";
			solu->FuzzyMatch(code.c_str(), threshold);
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		std::cout << "请按格式输入开始日期,如“2017-01-03”\n";
		std::string start_date;
	    std::cin>>start_date;
		std::cout << "请按格式输入结束日期，如“2017-01-04”\n";
		std::string end_date;
		std::cin>>end_date;
		solu->CalcMacd(code.c_str(), start_date.c_str(), end_date.c_str());
		std::cout << "以上是您的查询结果,您还想要做什么？\n";
		system("pause");
		system("cls");
		solu->MENU();
		goto chongxinxuanze;
	}
	case 5:{
		std::cout << "请按格式输入开始日期,如“2017-01-03”\n";
		std::string start_date;
	    std::cin>>start_date;
		std::cout << "请按格式输入结束日期，如“2017-01-04”\n";
		std::string end_date;
		std::cin>>end_date;
		std::cout << "请输入一个数字k，代表你想要获取前k项内容\n";
		int k;
		std::cin >> k;
		if (solu->MACDTopK(start_date.c_str(), end_date.c_str(), k) > 0) {
			std::cout << "以上是您的查询结果,您还想要做什么？\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		else {
			std::cout << "没有找到符合条件的结果，请核对您的查询信息！\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
	}
	case 6: {
		std::string date;
		std::string code;
		std::cout << "请输入您想预测的前一天的日期,格式如2017-01-03\n请确保它存在，否则会查询失败^_^\n";
		std::cin >> date;
		std::cout << "请输入您想预测的股票的代码\n";
		std::cin >> code;
		int flag = solu->predictStock(code, date.c_str());
		if (flag == 0) {
			std::cout << "没有找到相应股票，您是否想预测以下股票？\n";
			solu->FuzzyMatch(code.c_str(), threshold);
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		else if (flag == -1) {
			std::cout << "没有找到相应的日期，请核实后重新输入\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		
		std::cout << "以上是您的涨跌预测结果,1代表涨，-1代表跌\n您还想要做什么？\n";
		system("pause");
		system("cls");
		solu->MENU();
		goto chongxinxuanze;
	}
	case 7: {
		std::cout << "谢谢使用，下次再见！（本程序将在3s后关闭）";
		Sleep(3000);
		return 0;
	}
	/*case 8: {
		std::string code;
		std::cout << std::endl;
		std::cin >> code;
		solu->FuzzyMatch(code.c_str(), 1);
	}
	用于测试模糊匹配*/
	default:
		goto chongxinxuanze;
	}
//	std::cout << clock() - t1;
    return 0;
}


/*int* test() {
	int a;
	int* b = new int;
	return b;
	delete b;
}*/
