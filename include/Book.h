#pragma once
#include "LibraryItem.h"

using namespace std;

class Book : public LibraryItem {
    string author;
    string isbn;

    public:
        Book(int id, const string& title, int year, const string& author, const string& isbn, bool available = true);

        string getAuthor() const;
        string getIsbn() const;

        string type() const override;
        void printInfo() const override;
        string serialize() const override;
};
