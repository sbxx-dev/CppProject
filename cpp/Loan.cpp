#include "Loan.h"
#include <sstream>
#include <stdexcept>

using namespace std;

Loan::Loan(int id, int readerTicket, int itemId, bool active) {
    if (id <= 0)
        throw invalid_argument("id выдачи должен быть > 0");
    if (readerTicket <= 0)
        throw invalid_argument("ticket читателя должен быть > 0");
    if (itemId <= 0)
        throw invalid_argument("id издания должен быть > 0");
    this->id = id;
    this->readerTicket = readerTicket;
    this->itemId = itemId;
    this->active = active;
}

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
