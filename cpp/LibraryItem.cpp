#include "LibraryItem.h"

using namespace std;

LibraryItem::LibraryItem(int id, const string& title, int year, bool available)
    : id(id), title(title), year(year), available(available) {}

int LibraryItem::getId() const {return id;}
string LibraryItem::getTitle() const {return title; }
int LibraryItem::getYear() const { return year; }
bool LibraryItem::isAvailable() const {return available;}
void LibraryItem::setAvailable(bool value) { available = value; }
