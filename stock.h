#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <cmath>
#include <vector>

class stock {
public:
	stock(const std::string&, const std::vector<stock>& stockArray);//表示引用，防止空间和时间的浪费，const防止函数中过程对这个string造成改变
	stock() {};
	//stock(const stock& rhs);
	int getYear() const ;
	int getMonth() const;
	int getDay() const;

	double getOpenPrice() const;
	double getHighPrice() const;
	double getLowPrice() const;
	double getClosePrice() const;
	double getAdjClosePrice() const;

	double getVolume() const;
	double getRange() const;
	std::string getId() const;

	double getChange() const;
	double getPct_Change() const;

	void debug() const;
	double getDelta() const;

private:
	int DateYear, DateMonth, DateDay; //date
	double openPrice, highPrice, lowPrice, closePrice, adjClosePrice; //price
	double Volume; //volume
	std::string id; //stockid
	double Change, Pct_Change; //change
};

double readDouble(std::istream&);
std::string readID(std::istream& input);
