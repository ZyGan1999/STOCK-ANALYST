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
	std::cout << "��ӭʹ�ù�Ʊ������ѯϵͳ!\n";
	chongxinshuru:
	std::cout << "��ȷ����Ʊ�����ļ����ڱ�����ͳһĿ¼�£��������ļ��������硰stock.csv����\n";
	std::cin >> FileName;
	std::ifstream cache(FileName.c_str());
	//time_t t1 = clock();
	if (cache.is_open()) {
		std::cout << "�����ĵȴ�\n";
		
		solu->LoadStockData(FileName.c_str());
		std::cout << "\b\b\b" << "100%";
		std::cout << std::endl;
		std::cout << "��ȡ�ɹ�������Ҫ��ʲô��\a\n";
		solu-> MENU();
	}
	else {
		std::cout << "��ȡʧ�ܣ���������ԡ�\n";
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
		std::cout << "�밴��ʽ����һ��ָ�� ����-C 000001.SZ -h -d 2017-01-03\n"
			<< "��ע�⣬һ��Ҫ������Ʊ�����ѯ����\n" << "o:���̼ۣ�c�����̼ۣ�a�����������̼ۣ�h����߼ۣ�l����ͼ�\n";
		std::string instruct;
		std::getline(std::cin, instruct);
		std::getline(std::cin, instruct);
		if (solu->Query(instruct.c_str())) {
			std::cout << "û���ҵ������Ϣ��\n" << "���Ƿ���Ҫ��ѯ���¹�Ʊ��\n";
			solu->FuzzyMatch(solu->tellStockID(instruct.c_str()).c_str(), threshold);
			system("pause");
			system("cls");
			solu->MENU();
			
			goto chongxinxuanze;
		}
		else {
			std::cout << "���������Ĳ�ѯ���,������Ҫ��ʲô��\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		}
	case 2: {
		std::cout << "�밴��ʽ������Ҫ��ѯ������,�硰2017-01-03��\n";
		std::string date;
		std::cin >> date;
		std::cout << "��������������ݣ���ѡ����С�Volume������Range������AdjClose��\n";
		std::string data;
		std::cin >> data;
		std::cout << "������һ������k����������Ҫ��ȡ��ǰk������\n";
		int k;
		std::cin >> k;
		std::cout << "������һ������0��1,0�����ѯǰk�1�����ѯ��k��\n";
		int desc;
		std::cin >> desc;
		if (solu->TopK(date.c_str(), data.c_str(), k, desc)<0) {
			std::cout << "û���ҵ������Ϣ��\n" << "���ٴκ˶����Ĳ�ѯ��Ϣ��\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		else {
			std::cout << "���������Ĳ�ѯ���,������Ҫ��ʲô��\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
	}
	case 3: {
		std::string instruct;
		std::cout << "�밴��ʽ����һ��ָ��,����-C 000001.SZ -d 2017-01-03 -d 2017-01-04 -o -v\n";
		std::cout << "���������Ʊ������ʼ���ڡ��������ڡ�����Ŀ�ꡢƽ��ֵ��v�����׼�s��\n";
		std::getline(std::cin,instruct);
		std::getline(std::cin, instruct);
		double result;
		if ((result=(solu->Calculate(instruct.c_str()))) < 0) {
			std::cout<< "û���ҵ������Ϣ��\n" << "���Ƿ���Ҫ��ѯ���¹�Ʊ��\n";
			solu->FuzzyMatch(solu->tellStockID(instruct.c_str()).c_str(), threshold);
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		else {
			std::cout << result<<std::endl;
			std::cout << "���������Ĳ�ѯ���,������Ҫ��ʲô��\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
	}
	case 4: {
		std::cout << "�������Ʊ����\n";
		std::string code;
		std::cin>>code;
		if (solu->FindCode(code.c_str()) < 0) {
			std::cout << "δ���ҵ���Ӧ��Ʊ����������������¹�Ʊ��\n";
			solu->FuzzyMatch(code.c_str(), threshold);
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		std::cout << "�밴��ʽ���뿪ʼ����,�硰2017-01-03��\n";
		std::string start_date;
	    std::cin>>start_date;
		std::cout << "�밴��ʽ����������ڣ��硰2017-01-04��\n";
		std::string end_date;
		std::cin>>end_date;
		solu->CalcMacd(code.c_str(), start_date.c_str(), end_date.c_str());
		std::cout << "���������Ĳ�ѯ���,������Ҫ��ʲô��\n";
		system("pause");
		system("cls");
		solu->MENU();
		goto chongxinxuanze;
	}
	case 5:{
		std::cout << "�밴��ʽ���뿪ʼ����,�硰2017-01-03��\n";
		std::string start_date;
	    std::cin>>start_date;
		std::cout << "�밴��ʽ����������ڣ��硰2017-01-04��\n";
		std::string end_date;
		std::cin>>end_date;
		std::cout << "������һ������k����������Ҫ��ȡǰk������\n";
		int k;
		std::cin >> k;
		if (solu->MACDTopK(start_date.c_str(), end_date.c_str(), k) > 0) {
			std::cout << "���������Ĳ�ѯ���,������Ҫ��ʲô��\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		else {
			std::cout << "û���ҵ����������Ľ������˶����Ĳ�ѯ��Ϣ��\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
	}
	case 6: {
		std::string date;
		std::string code;
		std::cout << "����������Ԥ���ǰһ�������,��ʽ��2017-01-03\n��ȷ�������ڣ�������ѯʧ��^_^\n";
		std::cin >> date;
		std::cout << "����������Ԥ��Ĺ�Ʊ�Ĵ���\n";
		std::cin >> code;
		int flag = solu->predictStock(code, date.c_str());
		if (flag == 0) {
			std::cout << "û���ҵ���Ӧ��Ʊ�����Ƿ���Ԥ�����¹�Ʊ��\n";
			solu->FuzzyMatch(code.c_str(), threshold);
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		else if (flag == -1) {
			std::cout << "û���ҵ���Ӧ�����ڣ����ʵ����������\n";
			system("pause");
			system("cls");
			solu->MENU();
			goto chongxinxuanze;
		}
		
		std::cout << "�����������ǵ�Ԥ����,1�����ǣ�-1�����\n������Ҫ��ʲô��\n";
		system("pause");
		system("cls");
		solu->MENU();
		goto chongxinxuanze;
	}
	case 7: {
		std::cout << "ллʹ�ã��´��ټ�������������3s��رգ�";
		Sleep(3000);
		return 0;
	}
	/*case 8: {
		std::string code;
		std::cout << std::endl;
		std::cin >> code;
		solu->FuzzyMatch(code.c_str(), 1);
	}
	���ڲ���ģ��ƥ��*/
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
