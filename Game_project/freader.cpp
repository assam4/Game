#include "freader.hpp"

// CeaserCipher methods 
static const char sistem_chars = 32;
static const char max_limit = 126;


char CaesarCipher::chardecipher(char ciphered)
{
    int cp = ciphered + decipher_key;
    char decipher = (cp > max_limit) ? cp - max_limit : cp;
    if (cp < sistem_chars) return ' ';
    else  return decipher;
}

char CaesarCipher::charcipher(char letter)
{
    int cp = letter - decipher_key;
    char ccipher = (cp < (int)NULL) ? cp + max_limit : cp;
    return ccipher;
};

string CaesarCipher::decipher(string text)
    {
        string dc;
        for (auto simbhol : text) dc += chardecipher(simbhol);
        return dc;
    }

string CaesarCipher::cipher(string text)
    {
        string cp;
        for (auto simbhol : text) cp += charcipher(simbhol);
        return cp;

    }

CaesarCipher decoder;

// Abstract input methods
bool AbstractInput::open_file(const string filename)
{
    m_input.open(filename);
    return  (m_input.is_open()) ? true : false;
}

bool AbstractInput::eofbit()
{
    return m_input.eof();
}

// methods jsoninput 
InputJSON::~InputJSON() { m_input.close(); }
const int ignore_count = 100 ;
string InputJSON::read()
{
    m_input.ignore(ignore_count, '"');
    if (m_input.eof()) throw 0;
    string ciphered_text;
    getline(m_input, ciphered_text, '"');
    m_input.ignore(ignore_count, ':');
    string deciphered_text = decoder.decipher(ciphered_text);
    return deciphered_text;
}

// Abstract output methods
bool AbstractOutput::open_file(const string filename)
{

    m_output.open(filename);
    return  (m_output.is_open()) ? true : false;
}

// methods jsonoutput

bool OutputJSON::write(string q, string a1, string a2)
{
    if (m_output.good()) {
        m_output << '{' << '"' << "Question" << '"' << ": " << '"' << decoder.cipher(q) << '"' << ", " <<
            '"' << "Answer1" << '"' << ": " << '"' << decoder.cipher(a1) << '"' << ", " << '"' <<
            "Answer2" << '"' << ": " << '"' << decoder.cipher(a2) << '"' << '}' << endl;
        return true;
    }
    else return false;
}

OutputJSON::~OutputJSON()
{
    m_output.close();
}

// Question/Answer class methods

bool Question_Answers::datainit(AbstractInput* input)
{
    if (input->eofbit()) return false;
    m_question = input->read();
    m_ranswer = input->read();
    if (m_ranswer[0] == '*')
    {
        m_ranswer = m_ranswer.substr(1);
        m_wanswer = input->read();
    }
    else {
        m_wanswer = m_ranswer;
        m_ranswer = input->read().substr(1);
    }
    if (m_question.empty() || m_ranswer.empty() || m_wanswer.empty()) return false;
    return true;
};


void Question_Answers::show_question() noexcept
{
    cout << m_question << "?." << endl;
};

void Question_Answers::show_answers() noexcept
{
    cout << "[1]" << m_ranswer << "[2]" << m_wanswer << endl;
}

bool Question_Answers::check_answer() noexcept
{
    int index;
    cout << "Choose one of this variants ." << endl;
    cin >> index;
    while (index < 0 || index > 2)
    {
        cout << "There is no such option";
        cin.clear();
        cin >> index;
    }

    return (index == 1) ? true : false;

}

// Game methods

bool Game::QuestionsInit(AbstractInput* input)
{
    std::cout << "Loading ..." << endl;
    while (!(input->eofbit()))
    {
        Question_Answers temp;
        if (temp.datainit(input)) m_qa.push_back(temp);
        else return false;
    };
    return true;
};

bool Game::is_empty() noexcept
{
    return m_qa.empty();
}

bool Game::gameprocess()
{

    for (auto& var : m_qa)
    {
        var.show_question();
        var.show_answers();
        if (var.check_answer()) ++m_correct_answers;
    }

    cout << "Game Over ." << '\n' <<
        m_qa.size() << "questions :" << m_correct_answers <<
        " correct answers" << endl;
    return true;
}
