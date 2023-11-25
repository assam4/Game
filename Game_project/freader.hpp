#pragma once

#include <iostream>
#include <string>

using namespace std;

static const char sistem_chars = 32;
static const char max_limit = 126;

class CaesarCipher {
public:
    CaesarCipher(char dk = 1):decipher_key(dk){}
    string decipher (string text)
    {
        string dc ; 
        for (auto simbhol : text) dc += chardecipher(simbhol) ;
        return dc ;
    }

    string cipher(string text)
    {
        string cp;
        for (auto simbhol : text) cp += charcipher(simbhol) ;
        return cp;
       
    }
   

private:
    char chardecipher(char ciphered)
    {
        int cp = ciphered + decipher_key;
        char decipher = (cp > max_limit) ? cp - max_limit : cp;
         if (cp < sistem_chars) return ' ';
         else  return decipher ;     
    }
    
    char charcipher(char letter)
    {
        int cp = letter - decipher_key;
        char ccipher = (cp < (int)NULL) ? cp + max_limit : cp;
        return ccipher;
    }
    char decipher_key ;
};

CaesarCipher decoder ;



class Inputstream {
public:
    Inputstream(std::istream& r = std::cin ): m_read(r)   {}
    Inputstream(const Inputstream& other) = default;
    bool eofbit() { return m_read.eof(); }
    ~Inputstream() {}
public:
    string readfromJSON();
private:
     std::istream& m_read;  
};

string Inputstream::readfromJSON()
{
    m_read.ignore(40, '"');
    if (m_read.eof()) throw 0;
    string ciphered_text;
    getline(m_read, ciphered_text, '"');
    m_read.ignore(100, ':');
    string deciphered_text = decoder.decipher(ciphered_text);
    return deciphered_text;    
}

class Outputstream
{
public:
    Outputstream(std::ostream& w = std::cout) : m_write(w) {}
    Outputstream(const Inputstream& other) = default;
    ~Outputstream() {}
public:
    bool writeJSON(string, string, string );
private:
    std::ostream& m_write;
};

bool Outputstream::writeJSON(string q, string a1 , string a2 )
{
    if (m_write.good()) {
        m_write << '{' << '"' << "Question" << '"' << ": " << '"' << decoder.cipher(q) << '"' << ", " <<
            '"' << "Answer1" << '"' << ": " << '"' << decoder.cipher(a1) << '"' << ", " << '"' <<
            "Answer2" << '"' << ": " << '"' << decoder.cipher(a2) << '"' << '}' << endl;
        return true;
    }
    else return false;
}
