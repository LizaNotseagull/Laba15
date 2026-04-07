#include "StaffDepartment.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <vector>

// ============================================================================
//  РЕАЛИЗАЦИЯ КЛАССА Staff
// ============================================================================

// Конструктор: сохраняем имя, отдел пока не назначен (nullptr)
Staff::Staff(const std::string& name) : name(name), department(nullptr) {}

// Геттер имени
std::string Staff::getName() const { return name; }

// Геттер отдела (указатель)
Department* Staff::getDepartment() const { return department; }

// Сеттер отдела – используется при добавлении сотрудника в отдел
void Staff::setDepartment(Department* dept) { department = dept; }

// Текстовое представление сотрудника (по требованию задачи 2.4)
// Возможны три варианта:
// 1) Сотрудник не в отделе -> "Имя (без отдела)"
// 2) Сотрудник является начальником -> "Имя начальник отдела Название"
// 3) Рядовой сотрудник -> "Имя работает в отделе Название, начальник которого Имя_начальника"
// Если начальник не назначен, пишем "(без начальника)"
std::string Staff::toString() const {
    if (!department) return name + " (без отдела)";
    Staff* boss = department->getBoss();
    if (boss == this)
        return name + " начальник отдела " + department->getTitle();
    else if (boss)
        return name + " работает в отделе " + department->getTitle() +
        ", начальник которого " + boss->getName();
    else
        return name + " работает в отделе " + department->getTitle() +
        " (без начальника)";
}
void Staff::print() const { std::cout << toString(); }

// Метод для задачи 3.4: возвращает список всех сотрудников отдела
// Если сотрудник не привязан к отделу, возвращает пустой вектор
std::vector<Staff*> Staff::getDepartmentEmployees() const {
    if (department) return department->getEmployees();
    return {};
}

// ============================================================================
//  РЕАЛИЗАЦИЯ КЛАССА Department
// ============================================================================

// Конструктор: задаём название, начальник пока не назначен
Department::Department(const std::string& title) : title(title), boss(nullptr) {}

std::string Department::getTitle() const { return title; }
Staff* Department::getBoss() const { return boss; }

// Назначить начальника отдела.
// Важно: если начальник ещё не добавлен в отдел, добавляем его автоматически
void Department::setBoss(Staff* emp) {
    boss = emp;
    if (emp && emp->getDepartment() != this)
        emp->setDepartment(this);
}

// Добавить сотрудника в отдел. Устанавливаем связь: сотрудник.отдел = this
void Department::addEmployee(Staff* emp) {
    employees.push_back(emp);
    emp->setDepartment(this);
}

// Вернуть вектор всех сотрудников 
const std::vector<Staff*>& Department::getEmployees() const { return employees; }

// Вспомогательный метод для отладки
std::string Department::toString() const {
    return "Отдел " + title + ", начальник: " + (boss ? boss->getName() : "не назначен");
}
void Department::print() const { std::cout << toString(); }

// ============================================================================
//  ЗАДАЧА 2.4 – базовая (вывод текстового представления сотрудников)
// ============================================================================

// Тестовое задание: Петров, Козлов, Сидоров, отдел IT
static void testTask24() {
    std::cout << "\n--- Тестовое задание 2.4 (Петров, Козлов, Сидоров, IT) ---\n";
    Department itDept("IT");
    std::vector<Staff*> emps;
    emps.push_back(new Staff("Петров"));
    emps.push_back(new Staff("Козлов"));
    emps.push_back(new Staff("Сидоров"));
    for (auto e : emps) itDept.addEmployee(e);
    itDept.setBoss(emps[1]); // Козлов – начальник
    for (auto e : emps) { e->print(); std::cout << std::endl; }
    // Освобождаем память
    for (auto e : emps) delete e;
}

// Ручной ввод для задачи 2.4
static void keyboardInput24() {
    std::cout << "\n--- Ручной ввод (задача 2.4) ---\n";
    std::string deptName = safeInputString("Название отдела: ");
    int count = safeInputInt("Количество сотрудников: ");
    if (count <= 0) count = 1;
    Department dept(deptName);
    std::vector<Staff*> employees;
    for (int i = 0; i < count; ++i) {

        std::string name = safeInputNamePart("Имя сотрудника " + std::to_string(i + 1) + ": ");
        employees.push_back(new Staff(name));
        dept.addEmployee(employees.back());
    }
    std::cout << "Начальник (1-" << count << "): ";
    int bossIdx = safeInputInt("") - 1;
    if (bossIdx >= 0 && bossIdx < count) dept.setBoss(employees[bossIdx]);
    for (auto e : dept.getEmployees()) { e->print(); std::cout << std::endl; }
    for (auto e : employees) delete e;
}

// Случайная генерация для задачи 2.4
static void randomInput24() {
    std::cout << "\n--- Случайная генерация (задача 2.4) ---\n";
    // Название отдела – случайное слово из списка
    std::string deptName = generateRandomWord();
    int count = generateRandomInt(1, 10);
    std::cout << "Отдел: " << deptName << ", сотрудников: " << count << std::endl;
    Department dept(deptName);
    std::vector<Staff*> employees;
    for (int i = 0; i < count; ++i) {
        employees.push_back(new Staff(generateRandomWord()));
        dept.addEmployee(employees.back());
    }
    int bossIdx = generateRandomInt(0, count - 1);
    dept.setBoss(employees[bossIdx]);
    for (auto e : dept.getEmployees()) { e->print(); std::cout << std::endl; }
    for (auto e : employees) delete e;
}

// Чтение из файла для задачи 2.4
// Формат файла:
//   строка 1: название отдела
//   строка 2: количество сотрудников
//   далее N строк: имена сотрудников
//   последняя строка: номер начальника (1..N)
static void fileInput24() {
    std::cout << "\n--- Чтение из файла (задача 2.4) ---\n";
    std::string fname = safeInputString("Имя файла: ");
    std::ifstream file(fname);
    if (!file.is_open()) { std::cout << "Ошибка открытия.\n"; return; }
    std::string deptName; std::getline(file, deptName);
    int count; file >> count; file.ignore();
    if (count <= 0) return;
    Department dept(deptName);
    std::vector<Staff*> employees;
    for (int i = 0; i < count; ++i) {
        std::string name; std::getline(file, name);
        // readLineFromFile уже проверяет на цифры (см. Utils.cpp)
        employees.push_back(new Staff(name));
        dept.addEmployee(employees.back());
    }
    int bossIdx; file >> bossIdx;
    if (bossIdx >= 1 && bossIdx <= count) dept.setBoss(employees[bossIdx - 1]);
    for (auto e : dept.getEmployees()) { e->print(); std::cout << std::endl; }
    for (auto e : employees) delete e;
}

// Главное меню задачи 2.4
void runEmployeeDepartmentTask() {
    std::cout << "\n=== Сотрудники и отделы (задача 2.4) ===\n";
    std::cout << "1 - Ручной ввод\n2 - Случайная генерация\n3 - Из файла\n4 - Тестовое задание\n";
    int mode = safeInputInt("Выбор: ");
    switch (mode) {
    case 1: keyboardInput24(); break;
    case 2: randomInput24(); break;
    case 3: fileInput24(); break;
    case 4: testTask24(); break;
    default: std::cout << "Неверный выбор.\n";
    }
}

// ============================================================================
//  ЗАДАЧА 3.4 – расширенная: через сотрудника получить список отдела
// ============================================================================

// Тестовое задание: пользователь выбирает сотрудника (Петров, Козлов или Сидоров)
static void testTask34() {
    std::cout << "\n--- Тестовое задание 3.4 (Петров, Козлов, Сидоров, IT) ---\n";
    Department itDept("IT");
    std::vector<Staff*> emps;
    emps.push_back(new Staff("Петров"));
    emps.push_back(new Staff("Козлов"));
    emps.push_back(new Staff("Сидоров"));
    for (auto e : emps) itDept.addEmployee(e);
    itDept.setBoss(emps[1]); // Козлов начальник

    // Выбор сотрудника для демонстрации
    std::cout << "Выберите сотрудника, через которого получить список отдела:\n";
    for (size_t i = 0; i < emps.size(); ++i) {
        std::cout << i + 1 << " - "; emps[i]->print(); std::cout << std::endl;
    }
    int choice = safeInputInt("Ваш выбор (1-3): ") - 1;
    if (choice < 0 || choice >= (int)emps.size()) choice = 0;
    Staff* selected = emps[choice];

    std::cout << "Сотрудник: "; selected->print(); std::cout << std::endl;
    std::cout << "Список всех сотрудников отдела:\n";
    for (auto c : selected->getDepartmentEmployees()) {
        std::cout << "  "; c->print(); std::cout << std::endl;
    }
    for (auto e : emps) delete e;
}

// Ручной ввод для задачи 3.4 
static void keyboardInput34() {
    std::cout << "\n--- Ручной ввод (задача 3.4) ---\n";
    std::string deptName = safeInputString("Название отдела: ");
    int count = safeInputInt("Количество сотрудников: ");
    if (count <= 0) count = 1;
    Department dept(deptName);
    std::vector<Staff*> employees;
    for (int i = 0; i < count; ++i) {
        // Проверка на цифры
        std::string name = safeInputNamePart("Имя сотрудника " + std::to_string(i + 1) + ": ");
        employees.push_back(new Staff(name));
        dept.addEmployee(employees.back());
    }
    std::cout << "Начальник (1-" << count << "): ";
    int bossIdx = safeInputInt("") - 1;
    if (bossIdx >= 0 && bossIdx < count) dept.setBoss(employees[bossIdx]);

    // Выбор сотрудника для демонстрации
    std::cout << "\nВыберите сотрудника, через которого получить список отдела:\n";
    for (size_t i = 0; i < employees.size(); ++i) {
        std::cout << i + 1 << " - " << employees[i]->getName() << std::endl;
    }
    int choice = safeInputInt("Ваш выбор: ") - 1;
    if (choice < 0 || choice >= count) choice = 0;
    Staff* sample = employees[choice];
    std::cout << "\nЧерез сотрудника " << sample->getName() << " получаем коллег:\n";
    for (auto c : sample->getDepartmentEmployees()) {
        std::cout << "  "; c->print(); std::cout << std::endl;
    }
    for (auto e : employees) delete e;
}

// Случайная генерация для задачи 3.4
static void randomInput34() {
    std::cout << "\n--- Случайная генерация (задача 3.4) ---\n";
    std::string deptName = generateRandomWord();
    int count = generateRandomInt(1, 8);
    std::cout << "Отдел: " << deptName << ", сотрудников: " << count << std::endl;
    Department dept(deptName);
    std::vector<Staff*> employees;
    for (int i = 0; i < count; ++i) {
        employees.push_back(new Staff(generateRandomWord()));
        dept.addEmployee(employees.back());
    }
    int bossIdx = generateRandomInt(0, count - 1);
    dept.setBoss(employees[bossIdx]);

    // Случайный выбор сотрудника для демонстрации
    int sampleIdx = generateRandomInt(0, count - 1);
    Staff* sample = employees[sampleIdx];
    std::cout << "Сотрудник (выбран случайно): " << sample->getName() << std::endl;
    std::cout << "Коллеги по отделу:\n";
    for (auto c : sample->getDepartmentEmployees()) {
        std::cout << "  "; c->print(); std::cout << std::endl;
    }
    for (auto e : employees) delete e;
}

// Чтение из файла для задачи 3.4 (с выбором сотрудника)
static void fileInput34() {
    std::cout << "\n--- Чтение из файла (задача 3.4) ---\n";
    std::string fname = safeInputString("Имя файла: ");
    std::ifstream file(fname);
    if (!file.is_open()) { std::cout << "Ошибка открытия.\n"; return; }
    std::string deptName; std::getline(file, deptName);
    int count; file >> count; file.ignore();
    if (count <= 0) return;
    Department dept(deptName);
    std::vector<Staff*> employees;
    for (int i = 0; i < count; ++i) {
        std::string name; std::getline(file, name);
        employees.push_back(new Staff(name));
        dept.addEmployee(employees.back());
    }
    int bossIdx; file >> bossIdx;
    if (bossIdx >= 1 && bossIdx <= count) dept.setBoss(employees[bossIdx - 1]);

    // Выбор сотрудника для демонстрации
    std::cout << "\nВыберите сотрудника, через которого получить список отдела:\n";
    for (size_t i = 0; i < employees.size(); ++i) {
        std::cout << i + 1 << " - " << employees[i]->getName() << std::endl;
    }
    int choice = safeInputInt("Ваш выбор: ") - 1;
    if (choice < 0 || choice >= count) choice = 0;
    Staff* sample = employees[choice];
    std::cout << "Сотрудник: " << sample->getName() << std::endl;
    for (auto c : sample->getDepartmentEmployees()) {
        std::cout << "  "; c->print(); std::cout << std::endl;
    }
    for (auto e : employees) delete e;
}

// Главная функция задачи 3.4
void runEmployeeDepartmentTask3() {
    std::cout << "\n=== Сотрудники и отделы (задача 3.4: список через сотрудника) ===\n";
    std::cout << "1 - Ручной ввод\n2 - Случайная генерация\n3 - Из файла\n4 - Тестовое задание\n";
    int mode = safeInputInt("Выбор: ");
    switch (mode) {
    case 1: keyboardInput34(); break;
    case 2: randomInput34(); break;
    case 3: fileInput34(); break;
    case 4: testTask34(); break;
    default: std::cout << "Неверный выбор.\n";
    }
}