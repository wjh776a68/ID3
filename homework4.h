#pragma once
#ifndef HOMEWORK4_H
#define HOMEWORK4_H
#include "ID3.h"
#include <iostream>
using namespace std;

void insertitem(std::map<int, std::map<std::string, std::string>>& dataset, int code, string ischoiceable, string ishungry, string price, string type, string popular, string waitingtime, string mind);
void insertitem_v2(std::map<int, std::map<std::string, std::string>>& dataset, int code, string a, string b, string c, string d, string e, string f, string g);




#endif HOMEWORK4_H