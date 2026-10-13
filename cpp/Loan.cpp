#include "Loan.h"
#include <sstream>

using namespace std;

Loan::Loan(int id, int readerTicket, int itemId, bool active)
    : id(id), readerTicket(readerTicket), itemId(itemId), active(active) {}

int Loan::getId() const { return id; }
int Loan::getReaderTicket() const { return readerTicket; }
int Loan::getItemId() const { return itemId; }
bool Loan::isActive() const { return active; }
void Loan::setActive(bool value) { active = value; }

string Loan::serialize() const {
    std::ostringstream oss;
    oss << id << ";" << readerTicket << ";" << itemId << ";"
        << (active ? 1 : 0);
    return oss.str();
}