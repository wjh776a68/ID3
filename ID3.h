#pragma once
#ifndef ID3_H
#define ID3_H

#include<iostream>
#include<map>
#include<vector>
#include<deque>
#include<iomanip>

#define ID3_PRINTRESULT_ROOT -1//根属性，即全部属性

#define ID3_MODE_SIMPLY 0
#define ID3_MODE_COMPILCATE 1

typedef std::map<int, int> item;//每一项数据条目所包含的属性代码及属性值代码


typedef struct deque_node_struct {//队列节点，包含已使用的分类属性及经过使用的分类属性分类得到的数据条目序号
	std::vector<int> dealing_line;
	std::vector<int> itempos;
}deque_node;



class ID3 {
public:
	//dataset inital
	ID3();

	void setDataSet(std::map<int,std::map<std::string,std::string>> dataset, std::string keyword);//添加数据集
	void setMaxSortdepth(int maxdepth);//设置最大分类数量，即属性标签数量的最大值，默认为数据集属性之和
	void setDataSetkey(std::string keyword);//设置预测值
	//final function
	void start();//开始分类
	void printresult();//按照分类属性打印结果
	void printresultlist();//按照分类属性的值打印结果

	std::vector<deque_node> getresult();//直接返回结果
	void setmode(int mode);
private:
			
	//basic function
	double Ent(std::vector<int> itempos);//Ent算法，计算itempos的熵
	double Gain(std::vector<int> itempos, int checkelement);//Gain算法，对itempos中按照checkelement属性计算得到的信息增益
	
	bool samejudge(std::vector<int> itempos);//判断itempos中是否决策相同
	void add_result(deque_node income_result);//添加分类完成决策相同的itempos到结果列表中

	std::string transformnumbertostring(int symbol);//将字符串代码转为字符串

	//high-level function
	int getbestelementbyGain(std::vector<int> itempos,bool forceplaymodesimply);//从itempos列表中选取信息增益最大的属性,forceplaymodesimply为了使得即使在ID3_MODE_COMPILCATE情况下也只有一次Gain结果输出，即使得getdividedvectorbyGain影响无效。
	std::map<int, std::vector<int>> getdividedvectorbyGain(std::vector<int> itempos);//按照信息增益最大的属性划分新的itempos列表
	

	
	//varieties
	std::map<int,item> items;//经过转化后只包含字符串代号的数据集，items->first为数据条目序号
	
	std::vector<deque_node> final_result;//最终分类结果，每一项包含一个deque_node,其中包含一个使用过的分类属性向量和一个分类后相同决策节点的向量
	int digging_maxlevel;// 最大分类属性数量

	std::map<std::string, int> datasetstringsymbol;//字符串及其代号对应关系词典
	std::map<std::string, int> datasetlabelsymbol;//属性字符串及其代号对应关系词典
	int keysymbol;//决策字符串代码

	int playmode;

};

#endif