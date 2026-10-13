#include "input.h"
#include "print.hpp"
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace cool;

int readInt(const string& prompt, int lo, int hi) {
    while (true) {
        print(prompt);
        string line;
        inputln(line);
        istringstream iss(line);
        int value;
        char extra;
        if ((iss >> value) && !(iss >> extra) && value >= lo && value <= hi) {
            return value;
        }
        println("Ошибка: введите целое число от", lo, "до", hi);
    }
}

string readNonEmpty(const string& prompt) {
    while (true) {
        print(prompt);
        string line;
        inputln(line);
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start != string::npos) {
            size_t end = line.find_last_not_of(" \t\r\n");
            return line.substr(start, end - start + 1);
        }
        println("Ошибка: строка не может быть пустой.");
    }
}

vector<string> split(const string& line, char delimiter) {
    vector<string> result;
    string current;
    for (char c : line) {
        if (c == delimiter) { result.push_back(current); current.clear(); }
        else current += c;
    }
    result.push_back(current);
    return result;
}
