#pragma once
#include <string>
#include <iostream>

using namespace std;

class LibraryItem {
    protected:
        int id;
        string title;
        int year;
        bool available;

    public:
        LibraryItem(int id, const string& title, int year, bool available = true);
        virtual ~LibraryItem() = default;

        int getId() const;
        string getTitle() const;
        int getYear() const;
        bool isAvailable() const;
        void setAvailable(bool value);

        virtual string type() const = 0;
        virtual void printInfo() const = 0;
        virtual string serialize() const = 0;
};
