#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Lexer
{
private:
    string reserveWord_file;
    string operator_file;

    vector<string> ReserveWord;
    vector<string> Operator;

    int inputReserveWord(string file_name ,vector<string> &word);
    int inputOperator(string file_name ,vector<string> &oper);

    

};

int Lexer::inputReserveWord(string file_name ,vector<string> &word)
{
    ifstream fin;
    fin.open(file_name,ios::in);
    if(!fin.is_open())
    {
        cerr<<"can't find"<<file_name<<endl;
        return -1;
    }
    string temp;
    while(fin>>temp)
        word.push_back(temp);
    
    return 0;
}

int Lexer::inputOperator(string file_name ,vector<string> &oper)
{
    ifstream fin;
    fin.open(file_name,ios::in);
    if(!fin.is_open())
    {
        cerr<<"can't find"<<file_name<<endl;
        return -1;
    }
    string temp;
    while(fin>>temp)
        oper.push_back(temp);
    
    return 0;
}

