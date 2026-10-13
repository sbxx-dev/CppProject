#pragma once
#include "LibraryItem.h"

using namespace std;

class Magazine : public LibraryItem {
    int issueNumber;
    int month;

public:
    Magazine(int id, const string& title, int year,
             int issueNumber, int month, bool available = true);

    int getIssueNumber() const;
    int getMonth() const;

    string type() const override;
    void printInfo() const override;
    string serialize() const override;
};
