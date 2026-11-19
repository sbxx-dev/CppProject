#include "Library.h"
#include "Book.h"
#include "Magazine.h"
#include "input.h"
#include "validation.h"
#include "print.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;
using namespace cool;

// ---------- Вспомогательные ----------

LibraryItem* Library::findItem(int id) const {
    for (const auto& item : items)
        if (item->getId() == id) return item.get();
    return nullptr;
}

bool Library::readerExists(int ticket) const {
    for (const auto& r : readers)
        if (r.getTicket() == ticket) return true;
    return false;
}

int Library::generateLoanId() const {
    int maxId = 0;
    for (const auto& l : loans) if (l.getId() > maxId) maxId = l.getId();
    return maxId + 1;
}

// ---------- Публичные методы поиска ----------

LibraryItem* Library::findItemById(int id) const {
    return findItem(id);
}

Reader* Library::findReaderByTicket(int ticket) const {
    for (auto& r : readers)
        if (r.getTicket() == ticket) return const_cast<Reader*>(&r);
    return nullptr;
}

// ---------- 0. Общий addItem ----------

bool Library::addItem(std::unique_ptr<LibraryItem> item) {
    if (!validation::isUniqueItemId(items, item->getId())) {
        return false;
    }
    items.push_back(std::move(item));
    return true;
}

// ---------- 1. Добавить книгу ----------

void Library::addBook() {
    println("\n--- Добавление книги ---");
    int id = readInt("id (1..1000000): ", 1, 1000000);
    string title  = readNonEmpty("Название: ");
    int year      = readInt("Год (1500..2100): ", 1500, 2100);
    string author = readNonEmpty("Автор: ");
    string isbn   = readNonEmpty("ISBN: ");

    auto book = make_unique<Book>(id, title, year, author, isbn, true);
    if (addItem(std::move(book)))
        println("Книга успешно добавлена.");
    else
        println("Ошибка: издание с таким id уже существует.");
}

// ---------- 2. Добавить журнал ----------

void Library::addMagazine() {
    println("\n--- Добавление журнала ---");
    int id = readInt("id (1..1000000): ", 1, 1000000);
    string title = readNonEmpty("Название: ");
    int year     = readInt("Год (1500..2100): ", 1500, 2100);
    int issue    = readInt("Номер выпуска (1..10000): ", 1, 10000);
    int month    = readInt("Месяц (1..12): ", 1, 12);

    auto mag = make_unique<Magazine>(id, title, year, issue, month, true);
    if (addItem(std::move(mag)))
        println("Журнал успешно добавлен.");
    else
        println("Ошибка: издание с таким id уже существует.");
}

// ---------- 3. Зарегистрировать читателя ----------

void Library::registerReader() {
    println("\n--- Регистрация читателя ---");
    int ticket = readInt("Номер билета (1..1000000): ", 1, 1000000);
    if (!validation::isUniqueTicket(readers, ticket)) {
        println("Ошибка: читатель с таким ticket уже существует.");
        return;
    }
    string name = readNonEmpty("ФИО: ");
    try {
        readers.emplace_back(ticket, name);
        println("Читатель зарегистрирован.");
    } catch (const invalid_argument& e) {
        println("Ошибка: ", e.what());
    }
}

// ---------- 4. Найти издание по id ----------

void Library::findItemById() const {
    println("\n--- Поиск издания ---");
    int id = readInt("id: ", 1, 1000000);
    LibraryItem* item = findItem(id);
    if (!item) { println("Издание не найдено."); return; }
    item->printInfo();
}

// ---------- 4.1. Найти читателя по ticket ----------

void Library::findReaderByTicket() const {
    println("\n--- Поиск читателя ---");
    int ticket = readInt("ticket: ", 1, 1000000);
    Reader* reader = findReaderByTicket(ticket);
    if (!reader) { println("Читатель не найден."); return; }
    println("Читатель найден: ticket=", reader->getTicket(),
            ", ФИО=", reader->getFullName());
}

// ---------- 5. Выдать издание ----------

void Library::issueItem() {
    println("\n--- Выдача издания ---");
    int itemId = readInt("id издания: ", 1, 1000000);
    int ticket = readInt("ticket читателя: ", 1, 1000000);

    LibraryItem* item = findItem(itemId);
    if (!item)                 { println("Ошибка: издание не найдено."); return; }
    if (!readerExists(ticket)) { println("Ошибка: читатель не найден.");  return; }
    if (!item->isAvailable())  { println("Ошибка: издание занято.");      return; }

    int loanId = generateLoanId();
    try {
        loans.emplace_back(loanId, ticket, itemId, true);
        item->setAvailable(false);
        println("Издание выдано. Номер выдачи:", loanId);
    } catch (const invalid_argument& e) {
        println("Ошибка: ", e.what());
    }
}

// ---------- 6. Вернуть издание ----------

void Library::returnItem() {
    println("\n--- Возврат издания ---");
    int loanId = readInt("id выдачи: ", 1, 1000000);

    for (auto& loan : loans) {
        if (loan.getId() == loanId) {
            if (!loan.isActive()) {
                println("Ошибка: выдача уже закрыта.");
                return;
            }
            loan.setActive(false);
            LibraryItem* item = findItem(loan.getItemId());
            if (item) item->setAvailable(true);
            println("Издание успешно возвращено.");
            return;
        }
    }
    println("Ошибка: выдача не найдена.");
}

// ---------- 7. Вывести доступные издания ----------

void Library::printAvailableItems() const {
    println("\n--- Доступные издания ---");
    bool found = false;
    for (const auto& item : items) {
        if (item->isAvailable()) { item->printInfo(); found = true; }
    }
    if (!found) println("Нет доступных изданий.");
}

// ---------- 8. Вывести активные выдачи ----------

void Library::printActiveLoans() const {
    println("\n--- Активные выдачи ---");
    bool found = false;
    for (const auto& loan : loans) {
        if (loan.isActive()) {
            println("Выдача id=", loan.getId(),
                    ", издание id=", loan.getItemId(),
                    ", читатель ticket=", loan.getReaderTicket());
            found = true;
        }
    }
    if (!found) println("Активных выдач нет.");
}

// ---------- 9. Сохранить ----------

void Library::save() const {
    {
        ofstream f("items.txt");
        if (!f) { println("Ошибка открытия items.txt"); return; }
        for (const auto& item : items) f << item->serialize() << "\n";
    }
    {
        ofstream f("readers.txt");
        if (!f) { println("Ошибка открытия readers.txt"); return; }
        for (const auto& r : readers) f << r.serialize() << "\n";
    }
    {
        ofstream f("loans.txt");
        if (!f) { println("Ошибка открытия loans.txt"); return; }
        for (const auto& l : loans) f << l.serialize() << "\n";
    }
    println("Данные сохранены.");
}

// ---------- Загрузка ----------

void Library::load() {
    items.clear(); readers.clear(); loans.clear();

    // --- items.txt ---
    {
        ifstream f("items.txt");
        if (!f) return; // отсутствие файла — без ошибки
        string line;
        while (getline(f, line)) {
            if (line.empty()) continue;
            auto p = split(line, ';');
            if (p.size() < 7) {
                println("Предупреждение: пропущена повреждённая строка в items.txt: ", line);
                continue;
            }
            try {
                string type = p[0];
                int id      = stoi(p[1]);
                string title = p[2];
                int year    = stoi(p[3]);
                bool avail  = (p[4] == "1");
                if (type == "Book" || type == "B")
                    items.push_back(make_unique<Book>(id, title, year, p[5], p[6], avail));
                else if (type == "Magazine" || type == "M")
                    items.push_back(make_unique<Magazine>(id, title, year,
                        stoi(p[5]), stoi(p[6]), avail));
                else
                    println("Предупреждение: пропущена повреждённая строка в items.txt: ", line);
            } catch (const std::invalid_argument& e) {
                println("Предупреждение: пропущена повреждённая строка в items.txt: ", line);
            } catch (const std::out_of_range& e) {
                println("Предупреждение: пропущена повреждённая строка в items.txt: ", line);
            }
        }
    }
    // --- readers.txt ---
    {
        ifstream f("readers.txt");
        if (!f) return;
        string line;
        while (getline(f, line)) {
            if (line.empty()) continue;
            auto p = split(line, ';');
            if (p.size() < 2) {
                println("Предупреждение: пропущена повреждённая строка в readers.txt: ", line);
                continue;
            }
            try {
                readers.emplace_back(stoi(p[0]), p[1]);
            } catch (const std::invalid_argument& e) {
                println("Предупреждение: пропущена повреждённая строка в readers.txt: ", line);
            } catch (const std::out_of_range& e) {
                println("Предупреждение: пропущена повреждённая строка в readers.txt: ", line);
            }
        }
    }
    // --- loans.txt ---
    {
        ifstream f("loans.txt");
        if (!f) return;
        string line;
        while (getline(f, line)) {
            if (line.empty()) continue;
            auto p = split(line, ';');
            if (p.size() < 4) {
                println("Предупреждение: пропущена повреждённая строка в loans.txt: ", line);
                continue;
            }
            try {
                loans.emplace_back(stoi(p[0]), stoi(p[1]),
                                   stoi(p[2]), p[3] == "1");
            } catch (const std::invalid_argument& e) {
                println("Предупреждение: пропущена повреждённая строка в loans.txt: ", line);
            } catch (const std::out_of_range& e) {
                println("Предупреждение: пропущена повреждённая строка в loans.txt: ", line);
            }
        }
    }
}
