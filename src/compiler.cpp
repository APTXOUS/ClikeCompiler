#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <regex>

#define TAGWORD 100
#define CONSTANT 99

using namespace std;

struct ReWord
{
    string name;
    int syn;
};

struct ReOpera
{
    string name;
    int syn;
};

class Compiler
{
  public:
    string reserveWord_file;
    string operator_file;

    vector<ReWord> ReserveWord;
    vector<ReOpera> Operator;
    int OperatorMaxLen;
    string ProgramText;

  public:
    void inputText(string file_name, string &ProgramText);
    void preTreatText(string file_name, string &ProgramText);

    int inputReserveWord(string file_name, vector<ReWord> &word);
    int inputOperator(string file_name, vector<ReOpera> &oper);
    bool isDigit(char digit);
    bool isLetter(char letter);
    void lexScanner(int &syn,const char resourceText[], string &token, int &current);

    int searchReserve(vector<ReWord> reserverWord, string s);
    void lexScanner(int &syn, char resourceText[], string &token, int &current);
    int inOperator(vector<ReOpera> Opera, string s);
    void testLexScanner(string file_name);
};

int Compiler::inputReserveWord(string file_name, vector<ReWord> &word)
{
   ifstream fin;
    fin.open(file_name, ios::in);
    if (!fin.is_open())
    {
        cerr << "can't find" << file_name << endl;
        return -1;
    }
    string s;
    ReWord temp;
    this->OperatorMaxLen = 0;
    while (fin >> s)
    {
        temp.name=s.substr(s.find('<')+1,s.rfind(',')-s.find('<')-1);
        temp.syn=atoi(s.substr(s.rfind(',')+1,s.rfind('>')-s.rfind(',')).c_str());
        if (temp.name.length() > this->OperatorMaxLen)
            this->OperatorMaxLen = temp.name.length();
        word.push_back(temp);
    }

    return 0;
}

int Compiler::inputOperator(string file_name, vector<ReOpera> &oper)
{
    ifstream fin;
    fin.open(file_name, ios::in);
    if (!fin.is_open())
    {
        cerr << "can't find" << file_name << endl;
        return -1;
    }
    string s;
    ReOpera temp;
    this->OperatorMaxLen = 0;
    while (fin >> s)
    {
        temp.name=s.substr(s.find('<')+1,s.rfind(',')-s.find('<')-1);
        temp.syn=atoi(s.substr(s.rfind(',')+1,s.rfind('>')-s.rfind(',')).c_str());
        if (temp.name.length() > this->OperatorMaxLen)
            this->OperatorMaxLen = temp.name.length();
        oper.push_back(temp);
    }

    return 0;
}

void Compiler::inputText(string file_name, string &ProgramText)
{
    ifstream fin;
    fin.open(file_name, ios::in);
    if (!fin.is_open())
    {
        cerr << "can't find" << file_name << endl;
        return;
    }
    while (!fin.eof())
        ProgramText += fin.get();

    return;
}

void Compiler::preTreatText(string originText, string &ProgramText)
{
    int len = originText.length();

    for (int i = 0; i < len; i++)
    {
        if (originText[i] == '/' & originText[i + 1] == '/')
            while (originText[i] != '\n')
            {
                i++;
                if (i > len)
                    exit(-1);
            }
        if (originText[i] == '/' & originText[i + 1] == '*')
        {
            i += 2;
            while (originText[i] != '*' || originText[i + 1] != '/')
            {
                i++;
                if (i > len)
                    exit(-1);
            }
            i += 2;
        }
        if (originText[i] != '\n' && originText[i] != '\v' && originText[i] != '\r')
        {
            ProgramText += originText[i];
        }
    }
    replace(ProgramText.begin(), ProgramText.end(), '\t', ' ');
    return;
}

bool Compiler::isDigit(char digit)
{
    if (digit >= '0' && digit <= '9')
        return true;
    else
        return false;
}

bool Compiler::isLetter(char letter)
{
    if (letter >= 'a' && letter <= 'z' || letter >= 'A' & letter <= 'Z' || letter == '_')
        return true;
    else
        return false;
}

int Compiler::searchReserve(vector<ReWord> reserverWord, string s)
{
    vector<ReWord>::iterator t;
    for (t = reserverWord.begin(); t != reserverWord.end(); t++)
    {
        if ((*t).name == s)
            return (*t).syn;
    }
    return -1;
}
int Compiler::inOperator(vector<ReOpera> Opera, string s)
{
    vector<ReOpera>::iterator t;
    for (t = Opera.begin(); t != Opera.end(); t++)
    {
        if ((*t).name == s)
            return (*t).syn;
    }
    return -1;
}

void Compiler::lexScanner(int &syn,const char resourceText[], string &token, int &current)
{
    char now;
    int pointer;
    now = resourceText[current];
    while (now == ' ')
    {
        current++;
        now = resourceText[current];
    }
    token.clear();
    string tt;
    tt+=now;
    if (this->isLetter(resourceText[current]))
    {
        token += resourceText[current];
        current++;
        while (this->isLetter(resourceText[current]) || this->isDigit(resourceText[current]))
        {
            token += resourceText[current];
            current++;
        }
        syn = this->searchReserve(this->ReserveWord, token);
        if (syn == -1)
            syn = TAGWORD;
        return;
    }
    else if (this->isDigit(resourceText[current]))
    {
        while (this->isDigit(resourceText[current]))
        {
            token += resourceText[current];
            current++;
        }
        syn = CONSTANT;
    } //这边写的太丑陋了，应该全自适应词法规则
    //诶嘿嘿，改好了
    else if (this->inOperator(this->Operator,tt) != -1)
    {
        int i = 1;
        int last_syn = -1;
        while (i <= this->OperatorMaxLen)
        {
            last_syn = syn;
            token += resourceText[current];
            syn = this->inOperator(this->Operator, token);
            if (syn == -1)
            {
                token=token.substr(0, token.length() - 1);
                syn = last_syn;
                return;
            }
            current++;
            i++;
        }
        return;
    }
    else
    {
        cerr << "error:there is no exist" << int(now) << endl;
        exit(0);
    }
}

void Compiler::testLexScanner(string file_name)
{
    this->inputOperator("../conf/operator.in", this->Operator);
    this->inputReserveWord("../conf/reserveword.in", this->ReserveWord);
    string text;
    string pretext;
    this->inputText(file_name,text);
    this->preTreatText(text,pretext);
    int current=0;
    int syn;
    int length=pretext.length();
    string word;
    while(current<length-1)
    {
        word.clear();
        this->lexScanner(syn,pretext.c_str(),word,current);
        cout<<word<<" "<<syn<<endl;
    }

}

int main(int argc, char **argv)
{
    Compiler com;
    com.testLexScanner(argv[1]);
    return 0;
}