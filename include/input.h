#pragma once
#include <string>
#include <vector>

using namespace std;

int readInt(const string& prompt, int lo, int hi);
string readNonEmpty(const string& prompt);
vector<string> split(const string& line, char delimiter);
