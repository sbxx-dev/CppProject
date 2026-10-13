#pragma once
#include <vector>
#include <memory>
#include <string>
#include "LibraryItem.h"
#include "Reader.h"
#include "Loan.h"

using namespace std;

class Library {
    vector<std::unique_ptr<LibraryItem>> items;
    vector<Reader> readers;
    vector<Loan> loans;

    LibraryItem* findItem(int id) const;
    bool readerExists(int ticket) const;
    int generateLoanId() const;

public:
    void addBook();
    void addMagazine();
    void registerReader();
    void findItemById() const;
    void issueItem();
    void returnItem();
    void printAvailable() const;
    void printActiveLoans() const;
    void save() const;
    void load();
};
