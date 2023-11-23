#include "freader.hpp"
#include <fstream>
#include <vector>
using namespace std;

static vector<string> questions;
static vector<string> answer1;
static vector<string> answer2;

string answer_shadow(const string& answer)
{
	if (answer[0] == '*') return answer.substr(1);
	else return answer;
}

void game()
{
	ifstream is("Questions.txt");
	if (!is.is_open()) throw "Cannot loading game...Try latter";
	Inputstream read(is);
		while (!read.eofbit())
		{
			questions.push_back(read.readfromJSON());
			answer1.push_back(read.readfromJSON());
			answer2.push_back(read.readfromJSON());
		}

	if (questions.empty()) throw "No data...";

	for (int index = 0; index < questions.size(); ++index)
	{
		cout << questions[index] << endl;
		cout << "[1] " << answer_shadow(answer1[index]) << " [2] " << answer_shadow(answer2[index]) << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			if (answer1[index][0] == '*')
			{
				cout << "Good." << endl;
				break;
			}
			else throw "Wrong choice... Game Over !";
		case 2:
			if (answer2[index][0] == '*')
			{
				cout << "Good." << endl;
				break;
			}
			else throw "Wrong choice... Game Over !";
		default:
			throw "Wrong choice... Game Over !";

		};



	}
}

	int main()
	{
		try
		{
			game();
		}
		catch (const char* s)
		{
			cerr << s << endl;
		}
		return 0;
	}
