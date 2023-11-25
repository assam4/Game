#include "freader.hpp"

int main() {
    try {
        InputJSON example_1;
        if (example_1.open_file("Questions.txt")) {
            Game gg;
            gg.QuestionsInit(&example_1);
            if (!gg.is_empty()) {
                gg.gameprocess();
            }

        }
        else {
            cout << "Failed to open the file." << endl;
        }
        return 0;
    }
    catch (const char* s) { cerr << s << endl; exit(1); }
}

