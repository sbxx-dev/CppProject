#include "Magazine.h"
#include "print.hpp"
#include <sstream>
#include <string>

using namespace std;
using namespace cool;

Magazine::Magazine(int id, const string& title, int year,
                   int issueNumber, int month, bool available)
    : LibraryItem(id, title, year, available),
      issueNumber(issueNumber), month(month) {}

int Magazine::getIssueNumber() const { return issueNumber; }
int Magazine::getMonth()       const { return month; }
string Magazine::type()        const { return "Magazine"; }

void Magazine::printInfo() const {
    print0("[Журнал] id=", id, ", \"", title, "\", год=", year,
           ", выпуск=", issueNumber, ", месяц=", month,
           ", доступно=", (available ? "да" : "нет"));
    println();
}

string Magazine::serialize() const {
    ostringstream oss;
    oss << "Magazine;" << id << ";" << title << ";" << year << ";"
        << (available ? 1 : 0) << ";" << issueNumber << ";" << month;
    return oss.str();
}
