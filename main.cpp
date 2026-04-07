#include "Name.h"
#include "House.h"
#include "StaffDepartment.h"
#include "Task4_5.h"
#include "Task5_5.h"
#include "Utils.h"
#include <iostream>

int main() {
    setupRussianLocale();
#ifdef _WIN32
    system("chcp 1251 > nul");
#endif

    int choice;
    do {
        std::cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n";
        std::cout << "1 - Задача 1.3: Имя\n";
        std::cout << "2 - Задача 1.5: Дом\n";
        std::cout << "3 - Задача 2.4: Сотрудники и отделы (базовая)\n";
        std::cout << "4 - Задача 3.4: Сотрудники и отделы (список через сотрудника)\n";
        std::cout << "5 - Задача 4.5: Создаем Имена\n";
        std::cout << "6 - Задача 5.5: Дроби\n";
        std::cout << "0 - Выход\n";
        choice = safeInputInt("Ваш выбор: ");

        switch (choice) {
        case 1: Name::run(); break;
        case 2: House::run(); break;
        case 3: runEmployeeDepartmentTask(); break;
        case 4: runEmployeeDepartmentTask3(); break;
        case 5: runTask4_5(); break;
        case 6: runTask5_5(); break;
        case 0: std::cout << "Программа завершена.\n"; break;
        default: std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);

    return 0;
}