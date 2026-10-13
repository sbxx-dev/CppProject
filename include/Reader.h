#pragma once
#include <string>

using namespace std;

class Reader {
    int ticket;
    string fullName;

public:
    Reader(int ticket, const string& fullName);
    int getTicket() const;
    string getFullName() const;
    string serialize() const;
};
