#include "text.h"

Text::Text(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string text;
    while (getline(is, text)) {
        //保存
        file -> push_back(text);
		//map对应的标识
        int n = file->size()-1;
        std::istringstream line(text);
        std::string word;
        while (line >> word) {
            auto &lines = map[word];
            if(!lines){
                lines.reset(new std::set<lineNumber>);
            }
            lines->insert(n);
        }
    }
}

Result Text::query(const std::string &str) const{
	//未找到
	static std::shared_ptr<std::set<lineNumber>> nodata(new std::set<lineNumber>);

    auto loc = map.find(str);
	if (loc == map.end()) {
        return Result(str, nodata, file);
	} else {
        return Result(str, loc->second, file);
	}
}
