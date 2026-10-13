#include "Book.h"
#include "print.hpp"
#include <sstream>
#include <string>

using namespace std;
using namespace cool;

Book::Book(int id, const string& title, int year,
           const string& author, const string& isbn, bool available)
    : LibraryItem(id, title, year, available), author(author), isbn(isbn) {}

string Book::getAuthor() const { return author; }
string Book::getIsbn()   const { return isbn; }
string Book::type()      const { return "Book"; }

void Book::printInfo() const {
    print0("[Книга] id=", id, ", \"", title, "\", год=", year,
           ", автор=", author, ", ISBN=", isbn,
           ", доступно=", (available ? "да" : "нет"));
    println();
}

string Book::serialize() const {
    ostringstream oss;
    oss << "Book;" << id << ";" << title << ";" << year << ";"
        << (available ? 1 : 0) << ";" << author << ";" << isbn;
    return oss.str();
}
