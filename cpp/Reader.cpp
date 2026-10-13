#include "Reader.h"
#include <sstream>

using namespace std;

Reader::Reader(int ticket, const string& fullName)
    : ticket(ticket), fullName(fullName) {}

int Reader::getTicket() const { return ticket; }
string Reader::getFullName() const { return fullName; }

string Reader::serialize() const {
    std::ostringstream oss;
    oss << ticket << ";" << fullName;
    return oss.str();
}
