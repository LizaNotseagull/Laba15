#ifndef NAME_H
#define NAME_H

#include <string>

class Name {
private:
    std::string lastName;
    std::string firstName;  // личное имя – обязательно
    std::string patronymic;
public:
    // Конструкторы: все требуют личное имя (firstName)
    Name(const std::string& firstName);                         // только личное имя
    Name(const std::string& firstName, const std::string& lastName); // имя + фамилия
    Name(const std::string& firstName, const std::string& lastName, const std::string& patronymic); // все три

    std::string toString() const;
    void print() const;
    static void run();
};

#endif