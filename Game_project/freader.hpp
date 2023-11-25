#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class CaesarCipher {
public:
    CaesarCipher(char dk = 1):decipher_key(dk){}
public:
    string decipher(string text);
    string cipher(string text);
   
private:
    char chardecipher( char );
    char charcipher ( char );
    char decipher_key ;
};


class AbstractInput
{
public:
   
    virtual ~AbstractInput() {}
    virtual string read() = 0;
    bool open_file(const string);
    bool eofbit();


protected:
    std::ifstream m_input;

};


class InputJSON :public AbstractInput
{
public:
    ~InputJSON();
    string read() override;
};

class AbstractOutput
{
public:
    virtual ~AbstractOutput() {}
    bool    open_file(const string);
    virtual bool    write(string, string, string) = 0;

protected:
    std::ofstream m_output;

};

class OutputJSON :public AbstractOutput
{
public:
    ~OutputJSON();
    bool write(string, string, string) override;
};

class Question_Answers
{
public:
    bool datainit(AbstractInput*);
    bool check_answer() noexcept;
    void show_question() noexcept;
    void show_answers()  noexcept;

private:
    string m_question;
    string m_ranswer;
    string m_wanswer;

};


class Game
{
public:
    Game() :m_correct_answers(0) {}
    bool QuestionsInit(AbstractInput*);
    bool is_empty() noexcept;
    bool gameprocess();


private:
    vector <Question_Answers> m_qa;
    unsigned m_correct_answers;
};
















