#pragma once
#include<vector>
#include<fstream>
#include<string>
#include"stock.h"
#include <stack>
#include <iomanip>
#include <cmath>
#include <string.h>

class solution {
public:
	solution();
	~solution();

	int LoadStockData(const char* fileName);
	void MENU();
	int file_size(const char* filename);
	inline int min_of_three(int x, int y, int z);
	int edit_distance(const char *a, const char *b);
	int FindCode(const char *codename);
	inline int Atoi(char* s, char* t);
	std::string tellStockID(const char *instruct);
    int predictStock(const std::string& stockID, const char* Date);
	int Query(const char * para_str);
	int TopK(const char *date, const char *data, int k, int desc);
	double Calculate(const char *para_str);
	void CalcMacd(const char *code, const char *start_date, const char *end_date);
	int MACDTopK(const char *start_date, const char *end_date, int k);
	int FuzzyMatch(const char *query, int threshold);
	int Atoi(const char* s, const char* t);
private:
	std::vector<stock>* stocks;
	long readedCharNum, totalCharNum;
};

