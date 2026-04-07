#include "Fraction.h"
#include <cmath>      // для std::abs (модуль числа)
#include <algorithm>  // для std::swap (можно и без него, но оставим)

// Конструктор: принимает числитель и знаменатель
Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    // Знаменатель не может быть нулём – исправляем на 1
    if (denominator == 0) denominator = 1;
    // Сразу сокращаем дробь
    simplify();
}

// Сокращение дроби с помощью алгоритма Евклида (НОД)
void Fraction::simplify() {
    // Берём модули чисел, чтобы работать с положительными
    int a = std::abs(numerator);
    int b = std::abs(denominator);

    // Алгоритм Евклида: находим НОД(a, b)
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    int gcd = a;  // теперь gcd – наибольший общий делитель

    // Делим числитель и знаменатель на НОД
    numerator /= gcd;
    denominator /= gcd;

    // Знаменатель должен быть положительным (минус переносим в числитель)
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

// Преобразование дроби в строку вида "числитель/знаменатель"
std::string Fraction::toString() const {
    return std::to_string(numerator) + "/" + std::to_string(denominator);
}

// Сложение двух дробей: a/b + c/d = (a*d + c*b) / (b*d)
Fraction Fraction::sum(const Fraction& other) const {
    int newNum = numerator * other.denominator + other.numerator * denominator;
    int newDen = denominator * other.denominator;
    return Fraction(newNum, newDen);  // конструктор сам сократит результат
}

// Вычитание: a/b - c/d = (a*d - c*b) / (b*d)
Fraction Fraction::sub(const Fraction& other) const {
    int newNum = numerator * other.denominator - other.numerator * denominator;
    int newDen = denominator * other.denominator;
    return Fraction(newNum, newDen);
}

// Умножение: (a/b) * (c/d) = (a*c) / (b*d)
Fraction Fraction::mul(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

// Деление: (a/b) / (c/d) = (a*d) / (b*c)
Fraction Fraction::div(const Fraction& other) const {
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

// Вычитание целого числа: превращаем число в дробь (value/1) и вычитаем
Fraction Fraction::minus(int value) const {
    return sub(Fraction(value, 1));
}