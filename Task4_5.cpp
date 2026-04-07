#include "Task4_5.h"
#include "Name.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

void runTask4_5() {
    std::cout << "\n=== Задача 4.5: Создаем Имена ===\n";
    std::cout << "Выберите способ ввода:\n";
    std::cout << "1 - Ввод с клавиатуры (создание одного имени)\n";
    std::cout << "2 - Случайная генерация (создание одного имени)\n";
    std::cout << "3 - Чтение из файла (создание одного имени)\n";
    std::cout << "4 - Демонстрация указанных имён (Клеопатра, Пушкин, Маяковский, Христофор Бонифатьевич)\n";
    int choice = safeInputInt("Ваш выбор: ");

    if (choice == 1) {
        std::string firstName;
        do {
            firstName = safeInputNamePart("Введите личное имя (обязательно): ");
            if (firstName.empty()) {
                std::cout << "Ошибка! Личное имя не может быть пустым.\n";
            }
        } while (firstName.empty());

        std::string lastName = safeInputNamePart("Введите фамилию (можно оставить пустым): ");
        std::string patronymic = safeInputNamePart("Введите отчество (можно оставить пустым): ");
        Name n(firstName, lastName, patronymic);
        std::cout << "Создано имя: " << n.toString() << std::endl;
    }
    else if (choice == 2) {
        int mode = generateRandomInt(1, 3);
        Name n(""); // временный
        if (mode == 1) {
            n = Name(generateRandomWord());                     // только имя
        }
        else if (mode == 2) {
            n = Name(generateRandomWord(), generateRandomWord()); // имя+фамилия
        }
        else {
            n = Name(generateRandomWord(), generateRandomWord(), generateRandomWord()); // все три
        }
        std::cout << "Сгенерировано имя: " << n.toString() << std::endl;
    }
    else if (choice == 3) {
        std::string filename = safeInputString("Введите имя файла: ");
        std::string firstName = readLineFromFile(filename, 1);
        std::string lastName = readLineFromFile(filename, 2);
        std::string patronymic = readLineFromFile(filename, 3);
        if (firstName.empty()) {
            std::cout << "Ошибка: в файле не указано личное имя.\n";
        }
        else {
            Name n(firstName, lastName, patronymic);
            std::cout << "Имя из файла: " << n.toString() << std::endl;
        }
    }
    else if (choice == 4) {
        std::cout << "\n--- Имена из задания ---\n";
        Name n1("Клеопатра");
        Name n2("Александр", "Пушкин", "Сергеевич");
        Name n3("Владимир", "Маяковский");
        Name n4("Христофор", "Бонифатьевич");  // Бонифатьевич – фамилия
        std::cout << "1. " << n1.toString() << std::endl;
        std::cout << "2. " << n2.toString() << std::endl;
        std::cout << "3. " << n3.toString() << std::endl;
        std::cout << "4. " << n4.toString() << std::endl;
    }
    else {
        std::cout << "Неверный выбор.\n";
    }
}