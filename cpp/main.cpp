#include "Library.h"
#include "print.hpp"
#include <string>

using namespace std;
using namespace cool;

static void printMenu() {
    println("\n=== Библиотека колледжа ===");
    println("1 - Добавить книгу");
    println("2 - Добавить журнал");
    println("3 - Зарегистрировать читателя");
    println("4 - Найти издание по id");
    println("5 - Выдать издание");
    println("6 - Вернуть издание");
    println("7 - Вывести доступные издания");
    println("8 - Вывести активные выдачи");
    println("9 - Сохранить");
    println("0 - Выход");
    print("Выберите пункт: ");
}

int main() {
    setCyrillic();

    Library lib;
    lib.load();

    while (true) {
        printMenu();
        string line;
        inputln(line);

        int choice;
        try { choice = stoi(line); }
        catch (...) { choice = -1; }

        switch (choice) {
            case 1: lib.addBook();          break;
            case 2: lib.addMagazine();      break;
            case 3: lib.registerReader();   break;
            case 4: lib.findItemById();     break;
            case 5: lib.issueItem();        break;
            case 6: lib.returnItem();       break;
            case 7: lib.printAvailable();   break;
            case 8: lib.printActiveLoans(); break;
            case 9: lib.save();             break;
            case 0:
                lib.save();
                println("Выход.");
                return 0;
            default:
                println("Неизвестная команда");
        }
    }
    return 0;
}
