#include "House.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

House::House(int floors) : floors(floors) {}

std::string House::toString() const {
    std::string word;
    int n = floors % 100;
    if (n >= 11 && n <= 19) word = "этажами";
    else {
        int last = floors % 10;
        if (last == 1) word = "этажом";
        else word = "этажами";
    }
    return "дом с " + std::to_string(floors) + " " + word;
}

void House::print() const { std::cout << toString(); }

void House::run() {
    std::cout << "\n=== Задача 1.5: Дом ===\n";
    // Обязательная часть: вывод трёх домов по условию
    std::cout << "Три дома из задания:\n";
    House h1(1), h2(5), h3(23);
    h1.print(); std::cout << std::endl;
    h2.print(); std::cout << std::endl;
    h3.print(); std::cout << std::endl;
    std::cout << "\n--- Дополнительно: ввод своих домов ---\n";

    std::cout << "1 - Клавиатура\n2 - Случайная генерация\n3 - Из файла\n";
    int choice = safeInputInt("Выбор: ");
    int floors = 0;

    if (choice == 1) {
        // Используем safeInputPositiveInt – проверяет, что ввод – целое положительное число
        floors = safeInputPositiveInt("Введите количество этажей (целое положительное число): ");
    }
    else if (choice == 2) {
        floors = generateRandomInt(1, 50);
        std::cout << "Случайное количество этажей: " << floors << std::endl;
    }
    else if (choice == 3) {
        std::string fname = safeInputString("Имя файла: ");
        std::string line = readLineFromFile(fname, 1);
        if (!line.empty()) {
            // Проверяем, что строка состоит только из цифр
            bool ok = true;
            for (char c : line) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                floors = std::stoi(line);
                if (floors <= 0) {
                    std::cout << "Ошибка: в файле указано неположительное число. Установлено 1.\n";
                    floors = 1;
                }
            }
            else {
                std::cout << "Ошибка: в файле не целое положительное число. Установлено 1.\n";
                floors = 1;
            }
        }
        else {
            return;
        }
    }
    else {
        std::cout << "Неверный выбор.\n";
        return;
    }

    House h(floors);
    std::cout << "Создан дом: ";
    h.print();
    std::cout << std::endl;
}