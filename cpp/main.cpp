#include "Library.h"
#include "Book.h"
#include "Magazine.h"
#include "print.hpp"
#include <string>
#include <memory>
#include <stdexcept>

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

// ---------- Самодиагностика (УП8, УП9) ----------

static void runSelfTests() {
    println("\n=== Self-tests ===");

    // УП8: Reader валидация — успех
    try {
        Reader r(101, "Анна Смирнова");
        println("✅ Reader(101, \"Анна Смирнова\") — успешно");
    } catch (const invalid_argument& e) {
        println("❌ Reader(101, \"Анна Смирнова\") — ошибка: ", e.what());
    }

    // УП8: Loan валидация — успех
    try {
        Loan l(1, 101, 1, true);
        println("✅ Loan(1, 101, 1, true) — успешно");
    } catch (const invalid_argument& e) {
        println("❌ Loan(1, 101, 1, true) — ошибка: ", e.what());
    }

    // УП8: Reader(0, "Тест") — отказ
    try {
        Reader r(0, "Тест");
        println("❌ Reader(0, \"Тест\") — ожидался отказ");
    } catch (const invalid_argument& e) {
        println("✅ Reader(0, \"Тест\") — отказ: ", e.what());
    }

    // УП8: Reader(5, "") — отказ
    try {
        Reader r(5, "");
        println("❌ Reader(5, \"\") — ожидался отказ");
    } catch (const invalid_argument& e) {
        println("✅ Reader(5, \"\") — отказ: ", e.what());
    }

    // УП8: Reader(5, "   ") — отказ (только пробелы)
    try {
        Reader r(5, "   ");
        println("❌ Reader(5, \"   \") — ожидался отказ");
    } catch (const invalid_argument& e) {
        println("✅ Reader(5, \"   \") — отказ: ", e.what());
    }

    // УП8: Loan(-1, 101, 1, true) — отказ
    try {
        Loan l(-1, 101, 1, true);
        println("❌ Loan(-1, 101, 1, true) — ожидался отказ");
    } catch (const invalid_argument& e) {
        println("✅ Loan(-1, 101, 1, true) — отказ: ", e.what());
    }

    // УП9: findItemById(1) → найдено
    Library lib;
    lib.load();

    LibraryItem* item1 = lib.findItemById(1);
    if (item1) {
        println("✅ findItemById(1) — найдено: ", item1->getTitle());
    } else {
        println("❌ findItemById(1) — не найдено");
    }

    // УП9: findItemById(99) → nullptr
    LibraryItem* item99 = lib.findItemById(99);
    if (!item99)
        println("✅ findItemById(99) — nullptr");
    else
        println("❌ findItemById(99) — ожидался nullptr, но найдено: ", item99->getTitle());

    // УП9: findReaderByTicket(101) → найдено
    Reader* reader101 = lib.findReaderByTicket(101);
    if (reader101) {
        println("✅ findReaderByTicket(101) — найдено: ", reader101->getFullName());
    } else {
        println("❌ findReaderByTicket(101) — не найдено");
    }

    // УП9: findReaderByTicket(999) → nullptr
    Reader* reader999 = lib.findReaderByTicket(999);
    if (!reader999)
        println("✅ findReaderByTicket(999) — nullptr");
    else
        println("❌ findReaderByTicket(999) — ожидался nullptr");

    // УП9: повторный addItem с id=1 → отказ, размер не изменился
    size_t oldSize = lib.getItemCount();
    auto dup = make_unique<Book>(1, "Duplicate", 2020, "Auth", "000");
    bool added = lib.addItem(std::move(dup));
    if (!added && lib.getItemCount() == oldSize)
        println("✅ addItem(id=1 повторно) — отказ, размер не изменился");
    else
        println("❌ addItem(id=1 повторно) — ожидался отказ");

    println("=== Self-tests завершены ===");
}

int main() {
    setCyrillic();

    Library lib;
    lib.load();

    // Запустить самодиагностику
    runSelfTests();

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
            case 7: lib.printAvailableItems(); break;
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
