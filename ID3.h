#pragma once
#ifndef ID3_H
#define ID3_H

#include<iostream>
#include<map>
#include<vector>
#include<deque>
#include<iomanip>

#define ID3_PRINTRESULT_ROOT -1//�����ԣ���ȫ������

#define ID3_MODE_SIMPLY 0
#define ID3_MODE_COMPILCATE 1

typedef std::map<int, int> item;//ÿһ��������Ŀ�����������Դ��뼰����ֵ����


typedef struct deque_node_struct {//���нڵ㣬������ʹ�õķ������Լ�����ʹ�õķ������Է���õ���������Ŀ���
	std::vector<int> dealing_line;
	std::vector<int> itempos;
}deque_node;



class ID3 {
public:
	//dataset inital
	ID3();

	void setDataSet(std::map<int,std::map<std::string,std::string>> dataset, std::string keyword);//������ݼ�
	void setMaxSortdepth(int maxdepth);//���������������������Ա�ǩ���������ֵ��Ĭ��Ϊ���ݼ�����֮��
	void setDataSetkey(std::string keyword);//����Ԥ��ֵ
	//final function
	void start();//��ʼ����
	void printresult();//���շ������Դ�ӡ���
	void printresultlist();//���շ������Ե�ֵ��ӡ���

	std::vector<deque_node> getresult();//ֱ�ӷ��ؽ��
	void setmode(int mode);
private:
			
	//basic function
	double Ent(std::vector<int> itempos);//Ent�㷨������itempos����
	double Gain(std::vector<int> itempos, int checkelement);//Gain�㷨����itempos�а���checkelement���Լ���õ�����Ϣ����
	
	bool samejudge(std::vector<int> itempos);//�ж�itempos���Ƿ������ͬ
	void add_result(deque_node income_result);//��ӷ�����ɾ�����ͬ��itempos������б���

	std::string transformnumbertostring(int symbol);//���ַ�������תΪ�ַ���

	//high-level function
	int getbestelementbyGain(std::vector<int> itempos,bool forceplaymodesimply);//��itempos�б���ѡȡ��Ϣ������������,forceplaymodesimplyΪ��ʹ�ü�ʹ��ID3_MODE_COMPILCATE�����Ҳֻ��һ��Gain����������ʹ��getdividedvectorbyGainӰ����Ч��
	std::map<int, std::vector<int>> getdividedvectorbyGain(std::vector<int> itempos);//������Ϣ�����������Ի����µ�itempos�б�
	

	
	//varieties
	std::map<int,item> items;//����ת����ֻ�����ַ������ŵ����ݼ���items->firstΪ������Ŀ���
	
	std::vector<deque_node> final_result;//���շ�������ÿһ�����һ��deque_node,���а���һ��ʹ�ù��ķ�������������һ���������ͬ���߽ڵ������
	int digging_maxlevel;// ��������������

	std::map<std::string, int> datasetstringsymbol;//�ַ���������Ŷ�Ӧ��ϵ�ʵ�
	std::map<std::string, int> datasetlabelsymbol;//�����ַ���������Ŷ�Ӧ��ϵ�ʵ�
	int keysymbol;//�����ַ�������

	int playmode;

};

#endif