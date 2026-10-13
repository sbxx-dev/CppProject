#pragma once
#include <string>

using namespace std;

class Loan {
    int id;
    int readerTicket;
    int itemId;
    bool active;

public:
    Loan(int id, int readerTicket, int itemId, bool active = true);
    int getId() const;
    int getReaderTicket() const;
    int getItemId() const;
    bool isActive() const;
    void setActive(bool value);
    string serialize() const;
};