bool Compiler::isDigit(char digit)
{
    if (digit >= '0' && digit <= '9')
        return true;
    else
        return false;
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
