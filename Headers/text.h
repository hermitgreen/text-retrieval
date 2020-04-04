#ifndef TEXT_H
#define TEXT_H

#include "result.h"

class Result;

class Text
{
public:
    using lineNumber = std::vector<std::string>::size_type;

    Text(std::ifstream&);

    Result query(const std::string&) const;

    std::shared_ptr<std::vector<std::string>> file;
    //string到所在行号的集合的映射
    std::map<std::string,
             std::shared_ptr<std::set<lineNumber>>
                > map;
};

#endif // TEXT_H
