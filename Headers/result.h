#ifndef RESULT_H
#define RESULT_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPalette"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <ostream>

class Result
{
public:
    using lineNumber = std::vector<std::string>::size_type;
	Result(std::string s, 
			std::shared_ptr<std::set<lineNumber>> p,
			std::shared_ptr<std::vector<std::string>> f):
	find(s),lines(p),file(f) { }

	std::string find; //单词
	std::shared_ptr<std::set<lineNumber>> lines; //行号
	std::shared_ptr<std::vector<std::string>> file; //输入文件
};

#endif // RESULT_H
