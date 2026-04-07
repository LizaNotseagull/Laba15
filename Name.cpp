#include "Name.h"
#include "Utils.h"
#include <iostream>

// Конструкторы
Name::Name(const std::string& firstName) : firstName(firstName) {}
Name::Name(const std::string& firstName, const std::string& lastName)
    : firstName(firstName), lastName(lastName) {
}
Name::Name(const std::string& firstName, const std::string& lastName, const std::string& patronymic)
    : firstName(firstName), lastName(lastName), patronymic(patronymic) {
}

std::string Name::toString() const {
    std::string res;
    if (!lastName.empty())   res += lastName + " ";
    if (!firstName.empty())  res += firstName + " ";
    if (!patronymic.empty()) res += patronymic;
    if (!res.empty() && res.back() == ' ') res.pop_back();
    return res;
}

void Name::print() const { std::cout << toString(); }

void Name::run() {
    std::cout << "\n=== Задача 1.3: Имя ===\n";
    // Обязательные имена (все с личным именем)
    std::cout << "Три имени из задания:\n";
    Name n1("Клеопатра");
    Name n2("Александр", "Пушкин", "Сергеевич");
    Name n3("Владимир", "Маяковский");
    std::cout << "1. " << n1.toString() << std::endl;
    std::cout << "2. " << n2.toString() << std::endl;
    std::cout << "3. " << n3.toString() << std::endl;
    std::cout << "\n--- Дополнительно: ввод своих имён ---\n";

    std::cout << "Выберите способ ввода:\n1 - Клавиатура\n2 - Случайная генерация\n3 - Из файла\n";
    int choice = safeInputInt("Ваш выбор: ");

    if (choice == 1) {
        // Личное имя – обязательно, проверяем на пустоту
        std::string fn;
        do {
            fn = safeInputNamePart("Личное имя (обязательно): ");
            if (fn.empty()) {
                std::cout << "Ошибка! Личное имя не может быть пустым. Повторите ввод.\n";
            }
        } while (fn.empty());

        std::string ln = safeInputNamePart("Фамилия (можно оставить пустым): ");
        std::string pat = safeInputNamePart("Отчество (можно оставить пустым): ");
        Name n(fn, ln, pat);
        std::cout << "Имя: "; n.print(); std::cout << std::endl;
    }
    else if (choice == 2) {
        // Случайная генерация всегда создаёт имя с личным именем
        int mode = generateRandomInt(1, 3);
        Name n(""); // временный, будет заменён
        if (mode == 1) {
            n = Name(generateRandomWord());   // только личное имя
        }
        else if (mode == 2) {
            n = Name(generateRandomWord(), generateRandomWord()); // имя + фамилия
        }
        else {
            n = Name(generateRandomWord(), generateRandomWord(), generateRandomWord()); // все три
        }
        std::cout << "Сгенерировано: "; n.print(); std::cout << std::endl;
    }
    else if (choice == 3) {
        std::string fname = safeInputString("Имя файла: ");
        std::string ln = readLineFromFile(fname, 1);   // фамилия
        std::string fn = readLineFromFile(fname, 2);   // имя
        std::string pat = readLineFromFile(fname, 3);  // отчество
        if (fn.empty()) {
            std::cout << "Ошибка: в файле не указано личное имя.\n";
        }
        else {
            Name n(fn, ln, pat);
            std::cout << "Имя из файла: "; n.print(); std::cout << std::endl;
        }
    }
    else {
        std::cout << "Неверный выбор.\n";
    }
}