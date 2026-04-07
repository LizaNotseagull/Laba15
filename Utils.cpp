#include "Utils.h"
#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// ============================================================
// ФУНКЦИЯ: setupRussianLocale()
// Назначение: настраивает кодировку консоли для корректного
// отображения русского текста (Windows-1251 или UTF-8).
// ============================================================
void setupRussianLocale() {
#ifdef _WIN32
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
#else
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
}

// ============================================================
// ФУНКЦИЯ: safeInputInt()
// Назначение: безопасный ввод целого числа с клавиатуры.
// При ошибке (ввод букв или символов) повторяет запрос.
// ============================================================
int safeInputInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(10000, '\n');
            return value;
        }
        else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка! Введите целое число.\n";
        }
    }
}

// ============================================================
// ФУНКЦИЯ: safeInputPositiveInt()
// Назначение: ввод только положительного целого числа.
// Проверяет, что строка состоит только из цифр и число > 0.
// Отклоняет дробные числа (2.5), отрицательные и буквы.
// ============================================================
int safeInputPositiveInt(const std::string& prompt) {
    std::string line;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        // Проверяем, что строка не пуста и состоит только из цифр
        bool ok = !line.empty();
        for (char c : line) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                ok = false;
                break;
            }
        }
        if (ok) {
            int value = std::stoi(line);
            if (value > 0) {
                return value;
            }
            else {
                std::cout << "Ошибка! Количество этажей должно быть положительным.\n";
            }
        }
        else {
            std::cout << "Ошибка! Введите целое положительное число (без точек, запятых и букв).\n";
        }
    }
}

// ============================================================
// ФУНКЦИЯ: safeInputString()
// Назначение: ввод строки (может содержать пробелы).
// Без проверки содержимого.
// ============================================================
std::string safeInputString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// ============================================================
// ФУНКЦИЯ: safeInputNamePart()
// Назначение: ввод части имени (фамилия, имя, отчество)
// с проверкой, что строка не содержит цифр.
// ============================================================
std::string safeInputNamePart(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        bool hasDigit = false;
        for (char c : value) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                hasDigit = true;
                break;
            }
        }
        if (hasDigit) {
            std::cout << "Ошибка! Имя, фамилия и отчество не должны содержать цифры. Повторите ввод.\n";
        }
        else {
            break;
        }
    }
    return value;
}

// ============================================================
// ФУНКЦИЯ: generateRandomInt()
// Назначение: генерирует случайное целое число в диапазоне [min, max].
// ============================================================
int generateRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// ============================================================
// ФУНКЦИЯ: generateRandomWord()
// Назначение: возвращает случайное слово из предопределённого списка.
// Используется для случайных имён, фамилий, названий отделов.
// ============================================================
std::string generateRandomWord() {
    static const std::vector<std::string> words = {
        "Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов",
        "Александр", "Сергей", "Владимир", "Клеопатра", "Маяковский",
        "Пушкин", "Лермонтов", "Толстой", "Достоевский"
    };
    return words[generateRandomInt(0, words.size() - 1)];
}

// ============================================================
// ФУНКЦИЯ: readLineFromFile()
// Назначение: читает указанную строку из текстового файла.
// Проверяет, что строка не содержит цифр (для ФИО).
// Возвращает пустую строку при ошибке или наличии цифр.
// ============================================================
std::string readLineFromFile(const std::string& filename, int lineNumber) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл: " << filename << std::endl;
        return "";
    }
    std::string line;
    for (int i = 1; i <= lineNumber; ++i) {
        if (!std::getline(file, line)) {
            std::cout << "Недостаточно строк в файле. Запрошена строка " << lineNumber << std::endl;
            return "";
        }
    }
    for (char c : line) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            std::cout << "Ошибка: строка из файла содержит цифры. Игнорируем.\n";
            return "";
        }
    }
    return line;
}