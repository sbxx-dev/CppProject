#include "Reader.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <functional>

using namespace std;

Reader::Reader(int ticket, const string& fullName) {
    if (ticket <= 0)
        throw invalid_argument("ticket должен быть > 0");
    if (fullName.empty() || all_of(fullName.begin(), fullName.end(),
                                   [](unsigned char c){ return isspace(c); }))
        throw invalid_argument("Имя читателя не может быть пустым");
    this->ticket = ticket;
    this->fullName = fullName;
}

int Reader::getTicket() const { return ticket; }
string Reader::getFullName() const { return fullName; }

string Reader::serialize() const {
    std::ostringstream oss;
    oss << ticket << ";" << fullName;
    return oss.str();
}
