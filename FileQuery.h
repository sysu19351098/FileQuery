#ifndef FILEQUERY_H
#define FILEQUERY_H

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>

class FileQuery
{
private:
    using sentence_no = std::vector<std::string>::size_type;
    std::vector<std::string> sentences_;
    std::map<std::string, std::shared_ptr<std::set<sentence_no>>> wsm; //每个单词与所在句子顺序的映射
    std::map<std::string, int> wnm;                                    //每个单词与其出现次数的映射
    std::string text_;//用于保存txt文本内容
    std::string filename_;//文本名
public:
    FileQuery(std::string filename);
    ~FileQuery();
    void PrintSentencesOrdered()const;
    void PrintSentencesFiltered(const std::string & str)const;
    void PrintWordCount()const;
    void ReplaceWord(const std::string &oldword, const std::string &newword);
};

#endif