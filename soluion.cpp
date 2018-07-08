#include "solution.h"
#include <ctime>

solution::solution() {
	stocks = new std::vector<stock>;
	stocks->reserve(1000000);
}

solution::~solution() {
	if (stocks != NULL) delete stocks;
}
std::string solution::tellStockID(const char *instruct) {
	int i = 0;
	std::string ID="";
	for (i = 0; instruct[i] != 'C';i++) {
		;
	}
	for (i+=2; instruct[i] != ' '; i++) {
		ID += instruct[i];
	}
	return ID;
}

int solution::predictStock(const std::string & stockID, const char* Date)
{

	std::vector<stock>::iterator p;
	int Y =Atoi(Date,Date+4), M =Atoi(Date+5,Date+7), D =Atoi(Date+8,Date+10) ;
	for (p = stocks->begin(); p != stocks->end(); ++p) {
		if ((*p).getId() == stockID) break;

	}
	if (p == stocks->end()) return 0;//failed
	for (; p != stocks->end(); ++p) {
		if ((*p).getId() != stockID) return -1;
		if ((*p).getYear() == Y && (*p).getMonth() == M && (*p).getDay() == D) break;
	}
	if (p == stocks->end()) return -1;
	double exp = 1.0, res = 0.0; const double exp_ = 0.60;
	for (; (*p).getId() == stockID; --p) {
		res += exp * (*p).getDelta();
		exp *= exp_;
	}
	std::cout <<  (res >= 0.0 ? 1 : -1) << std::endl;
	return 1;
}

int solution::LoadStockData(const char * fileName)
{
	std::ifstream inFile(fileName);
	inFile.sync_with_stdio(false);
	if (!inFile) return -1;
	std::string str_cache;
	int pre = 0;
	int now = 0;
	totalCharNum = file_size(fileName)/100;
	readedCharNum = 0;
	std::getline(inFile, str_cache);
	//std::cout << "\n";

	time_t t1 = clock();
	while (!inFile.eof()) {
	//点点点
	//	if (clock() - t1 > 500) {
	//		std::cout << '.';
	//		t1 = clock();
	//	}
	//点点点
		std::getline(inFile, str_cache);
		readedCharNum += str_cache.size() * sizeof(char);
		now = readedCharNum / totalCharNum;
		//std::cout << readedCharNum << std::endl;
		if(now>pre)
		std::cout << "\b\b\b" << now << "%",pre=now;
	//	std::cout << str_cache << '\n';
		if (str_cache == "" || str_cache == ",,,,,,,,,") continue;
		stocks->push_back(stock(str_cache, *stocks));
	}
	return stocks->size();
	inFile.close();
}
void solution::MENU() {
	std::cout<< "1、查询某支股票关键信息\n"
		<< "2、按价格信息与日期查询TOP K\n"
		<< "3、计算平均值或标准偏差\n"
		<< "4、计算MACD指数\n"
		<< "5、按MACD查询TOP K\n"
		<< "6、股票涨跌预测\n"
		<< "7、退出\n"
		<< "请输入一个序号\n";
}

int solution::file_size(const char* filename)
{
	FILE *fp = fopen(filename, "r");
	if (!fp) return -1;
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fclose(fp);

	return size;
}

inline int solution::min_of_three(int x, int y, int z) {
	int min;
	min = x;
	min = min<y ? min : y;
	min = min<z ? min : z;
	return min;
}

int solution::edit_distance(const char *a, const char *b) {
	int lena = strlen(a);
	int lenb = strlen(b);
	int d[50];
	int i, j, old, temp;

	for (j = 0; j <= lenb; j++) {
		d[j] = j;
	}

	for (i = 1; i <= lena; i++) {
		old = i - 1;
		d[0] = i;
		for (j = 1; j <= lenb; j++) {
			temp = d[j];
			if (a[i - 1] == b[j - 1]) {
				d[j] = old;
			}
			else {
				d[j] = min_of_three(d[j] + 1, d[j - 1] + 1, old + 1);
			}
			old = temp;
		}
	}

	return d[lenb];
}

int solution::FindCode(const char *codename) {
	for (unsigned int i = 0; i < stocks->size(); i++) {
		if (!strcmp(codename,(*stocks)[i].getId().c_str()))
			return i;
	}
	return -1;
}

inline int solution::Atoi(const char* s, const char* t)
{
	int Ret = 0;
	for (int i = 0; s+i != t; i++) Ret = Ret * 10 + *(s+i) - '0';
	return Ret;
}

int solution::Query(const char* para_str)
{
	int l = strlen(para_str);
	int Year = 0, Month = 0, Day = 0;
	char Name[27];

	const char* i = strchr(para_str, '-'); //查找首个'-'字符 
									 //每当在上一个'-'的后面仍然查找到'-' 
	while (i != NULL)
	{
		//根据'-'的后一个字符判断应该作何操作
		const char* pos = strchr(i + 3, ' ');
		switch (*(i + 1))
		{
		case 'C':
//			char* pos = strchr(i + 3, ' ');
			if (pos == NULL) pos = para_str + l;
			strncpy(Name, i + 3, pos - (i + 3));
			break;
		case 'd':
			Year = Atoi(i + 3, i + 7); Month = Atoi(i + 8, i + 10); Day = Atoi(i + 11, i + 13);
//			i += 13;
			break;
			//i直接向后移动13位到下一个空格处，防止查找到的'-'在日期中，这会造成干扰 
		}
		//查找下一个'-' 
		//值得一提的是，如果i+1 >= para_str+l，此时使用strchr(i+1, '-')会越界，此时需要特殊处理 
		i = i - para_str + 1 < l ? strchr(i + 1, '-') : NULL;
	}

	int n = stocks->size();
	for (int i = 0; i < n; i++)
	{
		stock p = (*stocks)[i]; //这样写可以避免每次都打stocks[i]，省时美观 
		if (p.getYear() != Year) continue;
		if (p.getMonth() != Month) continue;
		if (p.getDay() != Day) continue;
		if (strcmp(p.getId().c_str(), Name)) continue;
		//不符合条件，则continue
		//把名称的比较放在最后，以尽可能减少strcmp的次数，因为strcmp比较慢 

		std::cout << Name << ' ' << Year << '-' << Month << '-' << Day;
		int j = strchr(para_str, '-') - para_str;
		while (j >= 0)
		{
			//值得一提的是，最后一种情况不能写成default，因为'-'可能出现在日期中，这会造成干扰，此时不应该进行操作 
			switch (para_str[j + 1])
			{
			case 'o': std::cout << " -o " << p.getOpenPrice(); break;
			case 'c': std::cout << " -c " << p.getClosePrice(); break;
			case 'a': std::cout << " -a " << p.getAdjClosePrice(); break;
			case 'h': std::cout << " -h " << p.getHighPrice(); break;
			case 'l': std::cout << " -l " << p.getLowPrice(); break;
			}
			j = j + 1 < l ? strchr(j + para_str + 1, '-') - para_str : -1;
		}

		std::cout << std::endl;
		return 0;
	}

	return -1;
}


//int solution::Query(const char * para_str) {
	/*
	for (int i = 0; i < stocks->size(); i++) {
		double a = (*stocks)[i].getAdjClosePrice;
	}
	*/
	//return 1;
//}
int solution::TopK(const char* date, const char* data, const int k, int desc)
{
	int n = stocks->size();
	std::vector<stock> v;

	const int Y = Atoi(date, date + 4), M = Atoi(date + 5, date + 7), D = Atoi(date + 8, date + 10);
	for (int i = 0; i < n; i++)
	{
		stock p = (*stocks)[i];
		if (p.getYear() != Y) continue;
		if (p.getMonth() != M) continue;
		if (p.getDay() != D) continue;

		if (desc == 0) desc = -1;
		//desc ==  1: 后k项 p < v[s-1] 
		//desc == -1: 前k项 p > v[s-1] 
		const char* A[3] = { "Volume", "AdjClose", "Range" };
		int s = v.size();
		if (strcmp(A[0], data) == 0)
		{
			if (s == 0 || (s > 0 && ((p.getVolume() - v[s - 1].getVolume()) * desc < 0 ||
				(p.getVolume() == v[s - 1].getVolume() && p.getId() < v[s - 1].getId()))))
			{
				int j;
				for (j = s - 1; j >= 0; j--)
					if (((p.getVolume() - v[j].getVolume()) * desc > 0) ||
						(p.getVolume() == v[j].getVolume() && p.getId() > v[j].getId())) break;
				std::vector<stock>::iterator I = v.begin();
				for (int l = 0; l < j + 1; l++) I++;
				v.insert(I, p);
				if (s == k) v.resize(k);
			}
		}
		else if (strcmp(A[1], data) == 0)
		{
			if (s == 0 || (s > 0 && ((p.getAdjClosePrice() - v[s - 1].getAdjClosePrice()) * desc < 0 ||
				(p.getAdjClosePrice() == v[s - 1].getAdjClosePrice() && p.getId() < v[s - 1].getId()))))
			{
				int j;
				for (j = s - 1; j >= 0; j--)
					if (((p.getAdjClosePrice() - v[j].getAdjClosePrice()) * desc > 0) ||
						(p.getAdjClosePrice() == v[j].getAdjClosePrice() && p.getId() > v[j].getId())) break;
				std::vector<stock>::iterator I = v.begin();
				for (int l = 0; l < j + 1; l++) I++;
				v.insert(I, p);
				if (s == k) v.resize(k);
				s = v.size();
			}
		}
		else {
			if (s == 0 || (s > 0 && ((p.getRange() - v[s - 1].getRange()) * desc < 0 ||
				(p.getRange() == v[s - 1].getRange() && p.getId() < v[s - 1].getId()))))
			{
				int j;
				for (j = s - 1; j >= 0; j--)
					if (((p.getRange() - v[j].getRange()) * desc > 0) ||
						(p.getRange() == v[j].getRange() && p.getId() > v[j].getId())) break;
				std::vector<stock>::iterator I = v.begin();
				for (int l = 0; l < j + 1; l++) I++;
				v.insert(I, p);
				if (s == k) v.resize(k);
				s = v.size();
			}
		}
	}
	std:: cout << v.size();
		if (v.size() < k) return -1;
		for (int i = 0; i < k; i++)
			std::cout << std::setiosflags(std::ios::fixed) <<
			v[i].getId() << ' ' << v[i].getYear() << '-' << v[i].getMonth() << '-' << v[i].getDay() << ' ' <<
			std::setprecision(6) << v[i].getOpenPrice() << ' ' <<
			std::setprecision(2) << v[i].getClosePrice() << ' ' << v[i].getAdjClosePrice() << ' ' <<
			v[i].getRange() << ' ' << v[i].getVolume() << std::endl;
		return k;
}

#include <algorithm>

#define DIFFDEA 1  //last diff bigger than last dea
#define DEADIFF 2  //last dea bigger than last diff
//as the statistic is double-type, I assume dea can't equal diff

// you can encapsulate DIFF/DEA into stock class
struct macd_stock {
	int gold_cross;
	int dead_cross;
	stock stk;
};

static bool stock_cmp(const macd_stock &a, const macd_stock &b);

int solution::MACDTopK(const char *start_date, const char *end_date, int k)
{
	std::vector<macd_stock> ms;
	macd_stock temp;
	std::string start = start_date;  //you can also write a class for date
	std::string end = end_date;
	int n = stocks->size();
	const int SY = Atoi(start_date, start_date + 4),
		SM = Atoi(start_date + 5, start_date + 7),
		SD = Atoi(start_date + 8, start_date + 10),
		EY = Atoi(end_date, end_date + 4),
		EM = Atoi(end_date + 5, end_date + 7),
		ED = Atoi(end_date + 8, end_date + 10);
	
	int flag, gdcrs, ddcrs;
	double EMA_12, EMA_26, DIF, DEA, MACD;
	for (int j = 0; j < n; j++)
	{
		stock i = (*stocks)[j];
		//一只股票数据输入开始 
		if (j == 0 || i.getId() != (*stocks)[j-1].getId())
		{
			flag = gdcrs = ddcrs = 0; 
			DIF = DEA = MACD = 0;
			EMA_12 = EMA_26 = i.getClosePrice();
			continue;
		}

		EMA_12 = i.getClosePrice() * 2 / 13.0 + EMA_12 * 11 / 13.0;
		EMA_26 = i.getClosePrice() * 2 / 27.0 + EMA_26 * 25 / 27.0;
		DIF = EMA_12 + EMA_26;
		DEA = 0.8 * DEA + 0.2 * DIF;
		MACD = 2 * (DIF - DEA);
		if (i.getYear() > EY || i.getYear() < SY) continue;
		if ((i.getYear() == SY && i.getMonth() < SM) || (i.getYear() == EY && i.getMonth() > EM)) continue;
		if ((i.getYear() == SY && i.getMonth() == SM && i.getDay() < SD) ||
			(i.getYear() == EY && i.getMonth() == EM && i.getDay() > ED)) continue;
		if (DIF > DEA)
		{
			if (flag == DEADIFF)
				++gdcrs;
			flag = DIFFDEA;
		}
		else {
			if (flag == DIFFDEA)
				++ddcrs;
			flag = DEADIFF;
		}

		//一只股票数据输入结束 
		if (j == n-1 || i.getId() != (*stocks)[j+1].getId())
		{
			temp.stk = i;
			temp.dead_cross = ddcrs;
			temp.gold_cross = gdcrs;
			ms.push_back(temp);
		}
	}
	sort(ms.begin(), ms.end(), stock_cmp);
	int count;
	for (count = 0; count < k&&count < ms.size(); count++)
		std::cout << ms[count].stk.getId() << " "
		<< start_date << " "
		<< end_date << " "
		<< ms[count].gold_cross << " "
		<< ms[count].dead_cross << " " << std::endl;
	return count + 1;
}

static bool stock_cmp(const macd_stock &a, const macd_stock &b)
{
	if (a.gold_cross != b.gold_cross)
		return a.gold_cross > b.gold_cross;
	if (a.dead_cross != b.dead_cross)
		return a.dead_cross < b.dead_cross;
	return a.stk.getId() < b.stk.getId();
}

int solution::FuzzyMatch(const char *query, int threshold) {//模糊匹配函数
	std::string old="";
	int ret = 0;
	for (int i = 0; i < stocks->size(); i++) {
		std::string cache = (*stocks)[i].getId();
		if (cache != old) {
			old = cache;
			if (edit_distance(query, cache.c_str()) <= threshold) {
				std::cout << cache << std::endl;
				ret++;
			}
		}
		else continue;
	}
	return ret;
}

void solution::CalcMacd(const char* code, const char* start_date, const char* end_date)
{
	int n = stocks->size();
	const int SY = Atoi(start_date, start_date + 4),
		SM = Atoi(start_date + 5, start_date + 7),
		SD = Atoi(start_date + 8, start_date + 10),
		EY = Atoi(end_date, end_date + 4),
		EM = Atoi(end_date + 5, end_date + 7),
		ED = Atoi(end_date + 8, end_date + 10);

	double EMA_12 = 0, EMA_26 = 0, DIF = 0, DEA = 0, MACD = 0;
	bool First = 1;
	for (int i = 0; i < n; i++)
	{
		stock p = (*stocks)[i];
		if (strcmp(code, p.getId().c_str()) != 0) continue;

		if (First) { First = 0; EMA_12 = EMA_26 = p.getClosePrice(); }
		else {
			EMA_12 = p.getClosePrice() * 2 / 13.0 + EMA_12 * 11 / 13.0;
			EMA_26 = p.getClosePrice() * 2 / 27.0 + EMA_26 * 25 / 27.0;
			DIF = EMA_12 + EMA_26;
			DEA = 0.8 * DEA + 0.2 * DIF;
			MACD = 2 * (DIF - DEA);
		}

		if (p.getYear() > EY || p.getYear() < SY) continue;
		if ((p.getYear() == SY && p.getMonth() < SM) || (p.getYear() == EY && p.getMonth() > EM)) continue;
		if ((p.getYear() == SY && p.getMonth() == SM && p.getDay() < SD) ||
			(p.getYear() == EY && p.getMonth() == EM && p.getDay() > ED)) continue;
		std::cout << p.getId() << ' ' << p.getYear() << '-' << p.getMonth() << '-' << p.getDay() <<
			std::setiosflags(std::ios::fixed) << std::setprecision(2) << ' ' << p.getClosePrice() << ' ' <<
			std::setprecision(0) << p.getVolume() << std::setprecision(4) << ' ' << EMA_12 << ' ' << EMA_26 << ' ' <<
			DIF << ' ' << DEA << ' ' << MACD << std::endl;
	}

}


double solution::Calculate(const char* para_str) {
	int l = strlen(para_str);
	//find stock ID
	std::string cacheID = "";
	int C_pos;
	for (C_pos = 0; C_pos < l && para_str[C_pos] != 'C'; C_pos++);
	if (para_str[++C_pos] != ' ') return -1.0;
	for (++C_pos; para_str[C_pos] != ' '; ++C_pos)
		cacheID += para_str[C_pos];
	//find date
	int D1_pos, D2_pos;
	for (D1_pos = 0; D1_pos < l && para_str[D1_pos] != 'd'; D1_pos++);
	for (D2_pos = D1_pos + 1; D2_pos < l && para_str[D2_pos] != 'd'; D2_pos++);
	if (para_str[++D1_pos] != ' ' || para_str[++D2_pos] != ' ') return -1.0;
	int Y1 = Atoi(para_str + D1_pos + 1, para_str + D1_pos + 5),
		Y2 = Atoi(para_str + D2_pos + 1, para_str + D2_pos + 5),
		M1 = Atoi(para_str + D1_pos + 6, para_str + D1_pos + 8),
		M2 = Atoi(para_str + D2_pos + 6, para_str + D2_pos + 8),
		D1 = Atoi(para_str + D1_pos + 9, para_str + D1_pos + 11),
		D2 = Atoi(para_str + D2_pos + 9, para_str + D2_pos + 11);
	int qType = 0; bool isNotAverage = true;
	for (int i = 0; i < l; i++) {
		if (para_str[i] == 'o') qType = 1;
		if (para_str[i] == 'c') qType = 2;
		if (para_str[i] == 'h') qType = 3;
		if (para_str[i] == 'l') qType = 4;
		if (para_str[i] == 'v') isNotAverage = false;
		if (para_str[i] == 's') isNotAverage = true;
	}
	std::vector<double> data;
	double average = 0.0; bool flag = false, found = false;

	for (std::vector<stock>::iterator I = stocks->begin(); I != stocks->end(); ++I) {
		stock p = *I;
		if (p.getId() == cacheID && p.getDay() == D1 && p.getMonth() == M1 && p.getYear() == Y1) flag = true, found = true;
		if (flag) {
			double cache = 0;
			switch (qType) {
			case 1: cache = p.getOpenPrice(); break;
			case 2: cache = p.getClosePrice(); break;
			case 3: cache = p.getHighPrice(); break;
			case 4: cache = p.getLowPrice(); break;
			default: break;
			}
			data.push_back(cache); average += cache;
		}
		if (p.getDay() == D2 && p.getMonth() == M2 && p.getYear() == Y2 && p.getId() == cacheID) {
			flag = false; break;
		}
	}

	if (!found) return -1.0;
	if (flag) return -1.0;
	int s = data.size(); average /= s;
	double rtn = average;
	if (isNotAverage) {
		rtn = 0.0;
		for (int i = 0; i < s; i++)
			rtn += pow((data[i] - average), 2);
		rtn /= s;
		rtn = sqrt(rtn);
	}
	return rtn;
}

