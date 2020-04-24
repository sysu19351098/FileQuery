#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "FileQuery.h"

using namespace std;

FileQuery::FileQuery(string filename) : filename_(filename)
{
    ifstream infile(filename_);
    if(!infile.is_open())
    {
        cout<<"The "<<filename<< " is fail to open.";
    }
    else
{
    stringstream ss;
    ss << infile.rdbuf();   //获取txt文本内容
    string text = ss.str(); //获取ss内的字符串
    text_ = text;
    string dele = "\n-"; //用于滤掉回车以及其它影响单词识别的字符

    //滤除dele里的字符
    string::size_type dele_startpos = text.find_first_of(dele);
    while (dele_startpos != string::npos)
    {
        string::size_type dele_endpos = text.find_first_not_of(dele, dele_startpos);
        text.erase(dele_startpos, dele_endpos - dele_startpos);
        dele_startpos = text.find_first_of(dele, dele_endpos);
    }

    //将整个文本提取出一条条句子
    string separate = ",."; //句子分隔符
    string::size_type sentence_startpos = text.find_first_not_of(separate);
    while (sentence_startpos != string::npos)
    {
        string::size_type sentence_endpos = text.find_first_of(separate, sentence_startpos);
        string s(text, sentence_startpos, sentence_endpos - sentence_startpos); //提取句子

        //把各个句子前的空格剔除掉，便于后面按字典排序
        string::size_type blank_end_pos = s.find_first_not_of(' ');
        s.erase(0, blank_end_pos);

        sentences_.push_back(s);   //把一个个处理好的句子放入sentence_这个向量中
        istringstream sentence(s); // 将句子分割成一个个单词

        //将每个单词与出现次数以及所在句子相关联
        string word;
        while (sentence >> word)
        {
            int n = sentences_.size() - 1;
            string lower_word = word;
            transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower); //将单词统统转化为小写
            if (!wnm[lower_word])
            {
                wnm[lower_word] = 0;
            }

            wnm[lower_word]++; //出现次数加1

            if (!wsm[word])
            {
                wsm[word].reset(new set<sentence_no>);
            }
            wsm[word]->insert(n);
        }
        sentence_startpos = text.find_first_not_of(separate, sentence_endpos);
    }
    infile.close();
}
}

FileQuery::~FileQuery()
{
}

void FileQuery::PrintSentencesOrdered() const
{
    vector<string> sentence(sentences_);
    sort(sentence.begin(), sentence.end());
    cout << endl
         << "The sentences are sorted in sictionary order :" << endl;
    for (auto i : sentence)
    {
        cout << i << endl;
    }
}

void FileQuery::PrintSentencesFiltered(const std::string &str) const
{
    vector<string> wordvec; //用于保存一个个单词
    set<sentence_no> s_no;  //用于保存查询单词所在的句子编号
    string seperator = " ,;()";

    string::size_type wordstartpos = str.find_first_not_of(seperator);

    while (wordstartpos != string::npos)
    {
        string::size_type wordendpos = str.find_first_of(seperator, wordstartpos);
        string word(str, wordstartpos, wordendpos - wordstartpos);
        wordvec.push_back(word);
        wordstartpos = str.find_first_not_of(seperator, wordendpos);
    }

    for (auto w : wordvec)
    {

        if (wsm.count(w)) //若wsm里的key里存在单词w
        {
            shared_ptr<set<sentence_no>> w_s = wsm.find(w)->second;

            for (auto i : *w_s) //把单词所在的句子编号循环放入s_no中，便于不重复输出句子
            {
                s_no.insert(i);
            }
        }
    }

    if (!s_no.empty()) //若s_no中不存在元素，即不存在所给单词
    {
        cout << endl
             << "The senteces exist any word of \"" << str << "\" : " << endl;
        for (auto i : s_no)
        {
            cout << sentences_[i] << endl;
        }
    }

    else
    {
        cout << "The text do not exist any word of \"" << str << "\" : " << endl;
    }
}

void FileQuery::PrintWordCount() const //输出各单词出现次数
{
    cout << endl
         << "The number of occurrences of each word is as follows :" << endl;

    for (auto i : wnm)
    {
        cout << i.first << " : " << i.second << endl;
    }
}

void FileQuery::ReplaceWord(const std::string &oldword, const std::string &newword) //替换单词
{
    bool judege = false; //用于判断是否存在所给的oldword.
    string seperator = " ,;()";
    string::size_type wordstartpos = text_.find_first_not_of(seperator);
    while (wordstartpos != string::npos) //查询单词并作替换处理
    {
        string::size_type wordendpos = text_.find_first_of(seperator, wordstartpos);
        string word(text_, wordstartpos, wordendpos - wordstartpos);
        if (word == oldword)
        {
            text_.replace(wordstartpos, oldword.length(), newword);
            judege = true; //查询到了oldword
        }

        wordstartpos = text_.find_first_not_of(seperator, wordendpos);
    }

    if (judege)
    {
        cout << "Replace " << oldword << " with " << newword << " successfuly." << endl;
    }
    else
    {
        cout << "There is no such word as " << oldword <<"."<< endl;
    }

    ofstream outfile(filename_);//以可写模式打开一个文件，并清空内容
    if(outfile.is_open())
    {
        outfile << text_;//将替换好的文本输入到原文件中
        outfile.close();
        FileQuery new_f(filename_);
        *this=new_f;//更新整个类的数据成员
    }
    else{
        cout<<"The "<<filename_<<" is fail to open."<<endl;
    }
}
