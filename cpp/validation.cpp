#include "validation.h"

using namespace std;

namespace validation {
    bool isUniqueItemId(const vector<std::unique_ptr<LibraryItem>>& items, int id) {
        for (const auto& item : items) {
            if (item->getId() == id) return false;
        }
        return true;
    }

    bool isUniqueTicket(const vector<Reader>& readers, int ticket) {
        for (const auto& r : readers) {
            if (r.getTicket() == ticket) return false;
        }
        return true;
    }

    bool isUniqueLoanId(const vector<Loan>& loans, int id) {
        for (const auto& l : loans) {
            if (l.getId() == id) return false;
        }
        return true;
    }
}
