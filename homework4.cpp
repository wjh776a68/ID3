#include "homework4.h"

#define debug 0

int main()
{
    ID3 id3core;
	std::map<int, std::map<std::string, std::string>> dataset;
#if debug == 0
	insertitem(dataset, 1,	"是", "是", "$$$",	"法式",		"有人", "0~10",		"是");
	insertitem(dataset, 2,	"是", "是", "$",		"中餐",		"客满", "30~60",		"否");
	insertitem(dataset, 3,	"否", "否", "$",		"快餐",		"有人", "0~10",		"是");
	insertitem(dataset, 4,	"是", "是", "$",		"中餐",		"客满", "10~30",		"是");
	insertitem(dataset, 5,	"是", "否", "$$$",	"法式",		"客满", ">60",		"否");
	insertitem(dataset, 6,	"否", "是", "$$",	"意大利式",	"有人", "0~10",		"是");
	insertitem(dataset, 7,	"否", "否", "$",		"快餐",		"无人", "0~10",		"否");
	insertitem(dataset, 8,	"否", "是", "$$",	"中餐",		"有人", "0~10",		"是");
	insertitem(dataset, 9,	"否", "否", "$",		"快餐",		"客满", ">60",		"否");
	insertitem(dataset, 10, "是", "是", "$$$",	"意大利式",	"客满", "10~30",		"否");
	insertitem(dataset, 11, "是", "否", "$",		"中餐",		"无人", "0~10",		"否");
	insertitem(dataset, 12, "否", "是", "$",		"快餐",		"客满", "30~60",		"是");
	id3core.setDataSet(dataset, "决策");
#else
	insertitem_v2(dataset, 1, "青绿", "蜷缩", "混响", "清晰", "凹陷", "硬滑", "是");
	insertitem_v2(dataset, 2, "乌黑", "蜷缩", "沉闷", "清晰", "凹陷", "硬滑", "是");
	insertitem_v2(dataset, 3, "乌黑", "蜷缩", "混响", "清晰", "凹陷", "硬滑", "是");
	insertitem_v2(dataset, 4, "青绿", "蜷缩", "沉闷", "清晰", "凹陷", "硬滑", "是");
	insertitem_v2(dataset, 5, "浅白", "蜷缩", "混响", "清晰", "凹陷", "硬滑", "是");
	insertitem_v2(dataset, 6, "青绿", "稍蜷", "混响", "清晰", "稍凹", "软粘", "是");
	insertitem_v2(dataset, 7, "青绿", "稍蜷", "混响", "稍糊", "稍凹", "软粘", "是");
	insertitem_v2(dataset, 8, "青绿", "稍蜷", "混响", "清晰", "稍凹", "硬滑", "是");

	insertitem_v2(dataset, 9, "青绿", "稍蜷", "沉闷", "稍糊", "稍凹", "硬滑", "否");
	insertitem_v2(dataset, 10, "青绿", "硬挺", "清脆", "清晰", "平坦", "软粘", "否");
	insertitem_v2(dataset, 11, "浅白", "硬挺", "清脆", "模糊", "平坦", "硬滑", "否");
	insertitem_v2(dataset, 12, "浅白", "蜷缩", "混响", "模糊", "平坦", "软粘", "否");
	insertitem_v2(dataset, 13, "青绿", "稍蜷", "混响", "稍糊", "凹陷", "硬滑", "否");
	insertitem_v2(dataset, 14, "浅白", "稍蜷", "沉闷", "稍糊", "凹陷", "硬滑", "否");
	insertitem_v2(dataset, 15, "乌黑", "稍蜷", "混响", "清晰", "稍凹", "软粘", "否");
	insertitem_v2(dataset, 16, "浅白", "蜷缩", "混响", "模糊", "平坦", "硬滑", "否");
	insertitem_v2(dataset, 17, "青绿", "蜷缩", "沉闷", "稍糊", "稍凹", "硬滑", "否");
	id3core.setDataSet(dataset, "好瓜");
#endif
	id3core.setmode(ID3_MODE_COMPILCATE);
    id3core.start();

	std::cout << std::endl;

    id3core.printresultlist();
    return 0;
}

void insertitem_v2(std::map<int, std::map<std::string, std::string>>& dataset, int code, string a, string b, string c, string d, string e, string f, string g) {
	std::map<string, string> newitem;
	newitem.insert(std::pair<string, string>("色泽", a));
	newitem.insert(std::pair<string, string>("根蒂", b));
	newitem.insert(std::pair<string, string>("敲声", c));
	newitem.insert(std::pair<string, string>("纹理", d));
	newitem.insert(std::pair<string, string>("脐部", e));
	newitem.insert(std::pair<string, string>("触感", f));
	newitem.insert(std::pair<string, string>("好瓜", g));

	dataset[code] = newitem;
}


void insertitem(std::map<int, std::map<std::string, std::string>> &dataset, int code, string ischoiceable, string ishungry, string price, string type, string popular, string waitingtime, string mind) {
	std::map<string,string> newitem;
	
	newitem.insert(std::pair<string, string>("是否有其他选择", ischoiceable));
	newitem.insert(std::pair<string, string>("饿否", ishungry));
	newitem.insert(std::pair<string, string>("价格", price));
	newitem.insert(std::pair<string, string>("餐馆类型", type));
	newitem.insert(std::pair<string, string>("餐馆顾客人数", popular));
	newitem.insert(std::pair<string, string>("等待时间", waitingtime));
	newitem.insert(std::pair<string, string>("决策", mind));
	
	dataset[code] = newitem;

}
