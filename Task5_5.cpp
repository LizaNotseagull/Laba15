#include "Task5_5.h"
#include "Fraction.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Вспомогательная функция: строка вида "a/b" -> Fraction
static Fraction parseFraction(const std::string& s) {
    std::stringstream ss(s);
    int num, den;
    char slash;
    ss >> num >> slash >> den;
    if (den == 0) den = 1;
    return Fraction(num, den);
}

// Применить операцию к двум дробям
static Fraction applyOp(const Fraction& a, const Fraction& b, char op) {
    switch (op) {
    case '+': return a.sum(b);
    case '-': return a.sub(b);
    case '*': return a.mul(b);
    case '/': return a.div(b);
    default: return a;
    }
}

// Вычисление выражения вида "дробь операция дробь операция ..." с учётом * и /
static Fraction evaluateExpression(const std::string& expr) {
    std::stringstream ss(expr);
    std::vector<Fraction> nums;
    std::vector<char> ops;

    // Считываем первую дробь
    std::string token;
    ss >> token;
    nums.push_back(parseFraction(token));

    // Считываем пары (операция дробь)
    while (ss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            ops.push_back(token[0]);
            ss >> token;
            nums.push_back(parseFraction(token));
        }
        else {
            std::cerr << "Ошибка: нужны пробелы (пример: 1/3 + 2/3)\n";
            return Fraction(0, 1);
        }
    }

    // Сначала выполняем * и /
    for (size_t i = 0; i < ops.size(); ) {
        if (ops[i] == '*' || ops[i] == '/') {
            Fraction res = applyOp(nums[i], nums[i + 1], ops[i]);
            nums[i] = res;
            nums.erase(nums.begin() + i + 1);
            ops.erase(ops.begin() + i);
        }
        else {
            ++i;
        }
    }
    // Теперь только + и -
    Fraction result = nums[0];
    for (size_t i = 0; i < ops.size(); ++i) {
        result = applyOp(result, nums[i + 1], ops[i]);
    }
    return result;
}

// Режим 1: ручной ввод
static void manualExpression() {
    std::cout << "\n--- Ручной ввод выражения ---\n";
    std::cout << "Пример: 1/3 + 2/3 * 3/4\n";
    std::string expr;
    std::cout << "Выражение: ";
    std::getline(std::cin, expr);
    if (expr.empty()) {
        std::cout << "Пустая строка.\n";
        return;
    }
    Fraction result = evaluateExpression(expr);
    std::cout << "Результат: " << result.toString() << std::endl;
}

// Режим 2: случайное выражение (одна операция)
static void randomExpression() {
    std::cout << "\n--- Случайное выражение ---\n";
    Fraction a(generateRandomInt(1, 10), generateRandomInt(1, 10));
    Fraction b(generateRandomInt(1, 10), generateRandomInt(1, 10));
    char op = "+-*/"[generateRandomInt(0, 3)];
    Fraction res = applyOp(a, b, op);
    std::cout << a.toString() << " " << op << " " << b.toString() << " = " << res.toString() << std::endl;
}

// Режим 3: чтение из файла
static void fileExpression() {
    std::cout << "\n--- Чтение выражения из файла ---\n";
    std::string filename = safeInputString("Имя файла: ");
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла.\n";
        return;
    }
    std::string expr;
    std::getline(file, expr);
    file.close();
    if (expr.empty()) {
        std::cout << "Файл пуст.\n";
        return;
    }
    std::cout << "Выражение: " << expr << std::endl;
    Fraction result = evaluateExpression(expr);
    std::cout << "Результат: " << result.toString() << std::endl;
}

// Режим 4: тестовое задание (по условию)
static void testTask() {
    std::cout << "\n--- Тестовое задание (дроби 1/3, 2/3, 3/4) ---\n";
    Fraction f1(1, 3), f2(2, 3), f3(3, 4);
    std::cout << f1.toString() << " + " << f2.toString() << " = " << f1.sum(f2).toString() << std::endl;
    std::cout << f1.toString() << " - " << f2.toString() << " = " << f1.sub(f2).toString() << std::endl;
    std::cout << f1.toString() << " * " << f2.toString() << " = " << f1.mul(f2).toString() << std::endl;
    std::cout << f1.toString() << " / " << f2.toString() << " = " << f1.div(f2).toString() << std::endl;
    std::cout << f1.toString() << " - 5 = " << f1.minus(5).toString() << std::endl;
    Fraction result = f1.sum(f2).div(f3).minus(5);
    std::cout << "(" << f1.toString() << " + " << f2.toString() << ") / " << f3.toString() << " - 5 = " << result.toString() << std::endl;
}

// Главная функция
void runTask5_5() {
    std::cout << "\n=== Задача 5.5: Дроби ===\n";
    std::cout << "Выберите режим:\n";
    std::cout << "1 - Калькулятор (ввести выражение)\n";
    std::cout << "2 - Случайное выражение (одна операция)\n";
    std::cout << "3 - Чтение из файла\n";
    std::cout << "4 - Тестовое задание\n";
    int choice = safeInputInt("Ваш выбор: ");
    switch (choice) {
    case 1: manualExpression(); break;
    case 2: randomExpression(); break;
    case 3: fileExpression(); break;
    case 4: testTask(); break;
    default: std::cout << "Неверный выбор.\n";
    }
}