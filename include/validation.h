#pragma once
#include <vector>
#include <memory>
#include "LibraryItem.h"
#include "Reader.h"
#include "Loan.h"

using namespace std;

namespace validation {
    bool isUniqueItemId(const vector<std::unique_ptr<LibraryItem>>& items, int id);
    bool isUniqueTicket(const vector<Reader>& readers, int ticket);
    bool isUniqueLoanId(const vector<Loan>& loans, int id);
}
