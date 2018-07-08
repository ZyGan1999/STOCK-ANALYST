#include "stock.h"

int readuInt(std::istream& input) {
	int ret = 0; 
	char cache; input >> cache;
	while (!isdigit(cache))input >> cache;
	while (isdigit(cache)) {
		ret = ret * 10 + cache - '0';
		input >> cache;
	}
	return ret;
}

double readDouble(std::istream& input) {
	double ret = 0.0;
	bool isnegative = 0;
	char cache; input >> cache;
	if (cache == '-') isnegative = 1;
	while (!isdigit(cache)) {
		input >> cache;
	}
	while (isdigit(cache)) {
		ret = ret * 10 + cache - '0';
		input >> cache;
	}
	if (cache == ',')return isnegative?-ret:ret;
	input >> cache;
	double retr = 0.0;
	int level = 0;
	while (isdigit(cache)) {
		retr = retr * 10 + cache - '0';
		level++;
		input >> cache;
	}
	retr /= pow(10, level);
	ret += retr;
	return isnegative?-ret:ret;
}

std::string readID(std::istream& input) {
	std::string ret;
	std::getline(input, ret, ',');
	return ret;
}


stock::stock(const std::string& str,const std::vector<stock>& stockArray){
	std::istringstream input(str + ",");
	input.sync_with_stdio(false);
	DateYear = readuInt(input);// std::cout << DateYear;
	DateMonth = readuInt(input);// std::cout << DateMonth;
	DateDay = readuInt(input);// std::cout << DateDay;
	if (input.peek() == ',') {
		openPrice = (*(stockArray.end()-1)).getOpenPrice();
		highPrice = (*(stockArray.end()-1)).getHighPrice();
		lowPrice = (*(stockArray.end()-1)).getLowPrice();
		closePrice = (*(stockArray.end()-1)).getClosePrice();
		adjClosePrice = (*(stockArray.end()-1)).getAdjClosePrice();
		id = (*(stockArray.end() - 1)).getId();
		Volume = 0;
		Change = 0;
		Pct_Change = 0;
		return;
		
	}
	openPrice = readDouble(input);// std::cout << openPrice;
	highPrice = readDouble(input); //std::cout << highPrice;
	lowPrice = readDouble(input); //std::cout << lowPrice;
	closePrice = readDouble(input); //std::cout << closePrice;
	adjClosePrice = readDouble(input);// std::cout << adjClosePrice;
	Volume = readDouble(input); //std::cout << Volume;
	id = readID(input); //std::cout << id;
	Change = closePrice-openPrice;// std::cout << Change;
	Pct_Change = Change/openPrice; //std::cout << Pct_Change<<"\n";

}

void stock::debug() const {
	std::cout << DateYear << ' ' << DateMonth << ' ' << DateDay << ' ' << openPrice << ' '
		<< highPrice << ' ' << lowPrice << ' ' << closePrice << ' ' << adjClosePrice << ' '
		<< (unsigned int)Volume << ' ' << id << ' ' << Change << ' ' << Pct_Change << std::endl;
}

int stock::getYear() const {
	return DateYear;
}

int stock::getMonth()const {
	return DateMonth;
}

int stock::getDay()const {
	return DateDay;
}

double stock::getOpenPrice()const {
	return openPrice;
}

double stock::getHighPrice()const {
	return highPrice;
}

double stock::getLowPrice()const {
	return lowPrice;
}

double stock::getClosePrice()const {
	return closePrice;
}

double stock::getAdjClosePrice()const {
	return adjClosePrice;
}

double stock::getVolume()const {
	return Volume;
}

std::string stock::getId()const {
	return id;
}

double stock::getChange()const {
	return Change;
}

double stock::getPct_Change()const {
	return Pct_Change;
}

double stock::getRange() const {
	return highPrice - lowPrice;
}

double stock::getDelta() const
{
	return closePrice - openPrice;
}

