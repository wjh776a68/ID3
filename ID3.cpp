#include "ID3.h"
ID3::ID3() {
	datasetstringsymbol["根"] = ID3_PRINTRESULT_ROOT;
	playmode = 0;

}

void ID3::setDataSetkey(std::string keyword) {
	if (datasetlabelsymbol.find(keyword) == datasetlabelsymbol.end()) {
		printf("Error in setDataSetKey, no definite keywords found");
	}
	else
		ID3::keysymbol = datasetlabelsymbol.find(keyword)->second;

}

void ID3::setDataSet(std::map<int,std::map<std::string, std::string>> dataset, std::string keyword) {
	
	for (std::map<int, std::map<std::string, std::string>>::iterator i = dataset.begin(); i != dataset.end(); i++) {
		std::map<std::string, std::string> thisdatasetitem = i->second;
		std::map<int, int> symboldatasetitem;
		for (std::map<std::string, std::string>::iterator thisdatasetitem_iter = thisdatasetitem.begin(); thisdatasetitem_iter != thisdatasetitem.end(); thisdatasetitem_iter++) {
			

			if (datasetstringsymbol.find(thisdatasetitem_iter->first) == datasetstringsymbol.end())
				datasetstringsymbol[thisdatasetitem_iter->first] = datasetstringsymbol.size();

			if (datasetstringsymbol.find(thisdatasetitem_iter->second) == datasetstringsymbol.end())
				datasetstringsymbol[thisdatasetitem_iter->second] = datasetstringsymbol.size();

			if (datasetlabelsymbol.find(thisdatasetitem_iter->first) == datasetlabelsymbol.end()) {
				datasetlabelsymbol[thisdatasetitem_iter->first] = datasetstringsymbol[thisdatasetitem_iter->first];
			}
				

			symboldatasetitem[datasetstringsymbol[thisdatasetitem_iter->first]] = datasetstringsymbol[thisdatasetitem_iter->second];
			
		}
		if (items.find(i->first) == items.end()) {
			items[i->first] = symboldatasetitem;
		}
		else {
			printf("Error in setDataset,find same index item, overwrite");
			items[i->first] = symboldatasetitem;
		}
		
	}

	ID3::setDataSetkey(keyword);//设置决策
	ID3::setMaxSortdepth(datasetlabelsymbol.size());//设置属性最大个数值
}

double ID3::Ent(std::vector<int> itempos) {
	std::map<int, int> elementvalue;
	int totalitem = itempos.size();
	double result = 0;
	for (int i = 0; i < itempos.size(); i++) {
		
		std::map<int,item>::iterator iter = items.find(itempos.at(i));
		if (iter == items.end()) {
			printf("Error occur in Ent");
			return -1;
		}

		item thisitem = iter->second;
		std::map<int, int>::iterator subiter = thisitem.find(keysymbol);//thisitem.find(checkelement);

		int thischeckelementvalue = subiter->second;
		
		if (elementvalue.find(thischeckelementvalue) != elementvalue.end()) {
			elementvalue[thischeckelementvalue]++;
		}
		else {
			elementvalue[thischeckelementvalue]=1;
			//elementvalue.insert(thischeckelementvalue, 1);
		}

	}
	
	for (std::map<int, int>::iterator i = elementvalue.begin(); i != elementvalue.end(); i++) {
		double fragment = (double)i->second / totalitem;
		result += -1 * fragment * log2(fragment);
	}
	
	return result;
}

//Gain(D,element) = Ent(D)-sum(element_number/D*Ent(element))
double ID3::Gain(std::vector<int> itempos, int checkelement) {
	double result = Ent(itempos);//Ent(D)

	std::map<int, std::vector<int>> elementvalue;

	for (int i = 0; i < itempos.size(); i++) {
		std::map<int, item>::iterator iter = items.find(itempos.at(i));
		if (iter == items.end()) {
			printf("Error occur in Gain");
			return -1;
		}

		item thisitem = iter->second;

		std::map<int, int>::iterator subiter = thisitem.find(checkelement);
		if (subiter == thisitem.end()) {
			printf("Error occur in Gain");
			return -1;
		}


		elementvalue[subiter->second].push_back(itempos.at(i));

	}

	for (std::map<int, std::vector<int>>::iterator i = elementvalue.begin(); i != elementvalue.end(); i++) {
		result -= ((double)i->second.size() / (double)itempos.size() * (double)Ent(i->second));//|D^v|/|D|*Ent(D^v)
	}

	

	return result;

}


int ID3::getbestelementbyGain(std::vector<int> itempos,bool forceplaymodesimply=false) {

	int biggestGainelement;
	double biggestGainelement_value;
	biggestGainelement = datasetlabelsymbol.begin()->second;
	biggestGainelement_value = Gain(itempos, datasetlabelsymbol.begin()->second);

	double tmp;

	for(std::map<std::string, int>::iterator datasetlabelsymbol_iter = (++datasetlabelsymbol.begin()); datasetlabelsymbol_iter != datasetlabelsymbol.end(); datasetlabelsymbol_iter++){
		if (datasetlabelsymbol_iter->second == keysymbol) {
			continue;//跳过决策属性代号
		}
		int testelement = datasetlabelsymbol_iter->second;
		tmp = Gain(itempos, testelement);

		if (ID3::playmode == ID3_MODE_COMPILCATE && forceplaymodesimply==false) {
			std::cout << "Gain((";
			for (int ii = 0; ii < itempos.size() - 1; ii++) {
				std::cout << itempos.at(ii) << ",";
			}
			std::cout << itempos.at(itempos.size() - 1);
			std::cout << "), " << ID3::transformnumbertostring(datasetlabelsymbol_iter->second) << ") = " << tmp << std::endl;
		}

		if (tmp > biggestGainelement_value) {
			biggestGainelement_value = tmp;
			biggestGainelement = testelement;
		}
	}

	return biggestGainelement;
}

std::map<int,std::vector<int>> ID3::getdividedvectorbyGain(std::vector<int> itempos) {
	std::map<int,std::vector<int>> result;
	int biggestGainelement = ID3::getbestelementbyGain(itempos,true);

	for (int i = 0; i < itempos.size(); i++) {
		std::map<int, item>::iterator iter = items.find(itempos.at(i));
		item thisitem = iter->second;

		std::map<int, int>::iterator element_iter = thisitem.find(biggestGainelement);

		result[element_iter->second].push_back(itempos.at(i));

	}

	return result;
}

void ID3::setmode(int mode) {
	ID3::playmode = mode;
}

void ID3::start() {
	std::deque<deque_node> deal_deque;//利用队列储存每一次得到的节点

	deque_node newdeque_node;
	//std::vector<int> itempos;
	for (std::map<int, item>::iterator i = items.begin(); i != items.end(); i++) {
		newdeque_node.itempos.push_back(i->first);
	}
	newdeque_node.dealing_line.push_back(ID3_PRINTRESULT_ROOT);
	deal_deque.push_back(newdeque_node);

	while (deal_deque.empty() == false) {

		deque_node thisdeque_node = deal_deque.front();
		deal_deque.pop_front();

		if (thisdeque_node.itempos.size() <= 1 || samejudge(thisdeque_node.itempos)==true || thisdeque_node.dealing_line.size()>=digging_maxlevel) {//end deque ignore
			add_result(thisdeque_node);
			continue;
		}

		int new_divideelement = getbestelementbyGain(thisdeque_node.itempos);
		std::map<int, std::vector<int>> newdeque_node = getdividedvectorbyGain(thisdeque_node.itempos);
		for (std::map<int, std::vector<int>>::iterator i = newdeque_node.begin(); i != newdeque_node.end(); i++) {
			deque_node subdeque_node;
			subdeque_node.dealing_line = thisdeque_node.dealing_line;
			subdeque_node.dealing_line.push_back(new_divideelement);

			subdeque_node.itempos = i->second;

			deal_deque.push_back(subdeque_node);

		}

	}

}

void ID3::add_result(deque_node income_result) {
	ID3::final_result.push_back(income_result);
}

void ID3::printresult() {
	for (int i = 0; i < final_result.size(); i++) {
		deque_node tmpstep = final_result.at(i);
		
		for (int j = 0; j < tmpstep.dealing_line.size()-1; j++) {
			std::cout<<transformnumbertostring(tmpstep.dealing_line.at(j))<<"->";
		}
		std::cout << transformnumbertostring(tmpstep.dealing_line.at(tmpstep.dealing_line.size() - 1)) << " : ";
		
		std::cout << "(";
		for (int j = 0; j < tmpstep.itempos.size()-1; j++) {
			std::cout << tmpstep.itempos.at(j) << ",";			
		}
		std::cout << tmpstep.itempos.at(tmpstep.itempos.size() - 1);

		std::cout << ")" << std::endl;
	}
}


std::string ID3::transformnumbertostring(int symbol) {
	for (std::map<std::string, int>::iterator i = ID3::datasetstringsymbol.begin(); i != ID3::datasetstringsymbol.end(); i++) {
		if (i->second == symbol) {
			return i->first;
		}
	}

	return "Error in transformnumbertostring";
}

bool ID3::samejudge(std::vector<int> itempos) {
	int tmp = 0;
	for (int i = 0; i < itempos.size(); i++) {
		item thisitem = ID3::items.find(itempos.at(i))->second;
		
		if (tmp == 0)
			tmp = thisitem.find(keysymbol)->second;
			//tmp = thisitem.find(MIND)->second;
		else
			//if (tmp != thisitem.find(MIND)->second) {
			if (tmp != thisitem.find(keysymbol)->second) {
				return false;
			}

		
	}

	return true;
}

void ID3::printresultlist() {
	std::cout << "----------  分类结果  ----------" << std::endl;
	std::cout << "分类属性 : " << "分类变量 : " << "预测结果" << std::endl;
	for (int i = 0; i < final_result.size(); i++) {
		deque_node tmpstep = final_result.at(i);

		for (int j = 0; j < tmpstep.dealing_line.size() - 1; j++) {
			if (tmpstep.dealing_line.at(j) == -1) {
				std::cout << "(";
				continue;
			}
			std::cout << transformnumbertostring((ID3::items.find(tmpstep.itempos.at(0))->second).find(tmpstep.dealing_line.at(j))->second) << ",";

			//printf_s("%5s,", transformnumbertostring((ID3::items.find(tmpstep.itempos.at(0))->second).find(tmpstep.dealing_line.at(j))->second));
		}
		std::cout << transformnumbertostring((ID3::items.find(tmpstep.itempos.at(0))->second).find(tmpstep.dealing_line.at(tmpstep.dealing_line.size() - 1))->second) << ") : ";


		std::cout << "(";
		for (int j = 0; j < tmpstep.itempos.size() - 1; j++) {
			std::cout << tmpstep.itempos.at(j) << ",";
			//printf_s("%2d,", tmpstep.itempos.at(j));
		}
		std::cout << tmpstep.itempos.at(tmpstep.itempos.size() - 1);

		std::cout << ")" ;

		std::cout << " : " << transformnumbertostring((ID3::items.find(tmpstep.itempos.at(0))->second).find(keysymbol)->second) << std::endl;
	}

}

void ID3::setMaxSortdepth(int maxdepth) {
	ID3::digging_maxlevel = maxdepth;
}

std::vector<deque_node> ID3::getresult() {
	return final_result;
}