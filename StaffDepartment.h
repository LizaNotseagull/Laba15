#ifndef STAFF_DEPARTMENT_H
#define STAFF_DEPARTMENT_H

#include <string>
#include <vector>

class Department;

// ============================================================================
//  КЛАСС Staff – сотрудник
// ============================================================================
class Staff {
private:
    std::string name;           // Имя сотрудника
    Department* department;     // Указатель на отдел, где работает сотрудник (nullptr, если нет отдела)

public:
    // Конструктор: принимает имя сотрудника, отдел пока не назначен
    Staff(const std::string& name);

    // Геттеры
    std::string getName() const;
    Department* getDepartment() const;

    // Сеттер отдела (вызывается при добавлении сотрудника в отдел)
    void setDepartment(Department* dept);

    // Текстовое представление сотрудника (задача 2.4)
    std::string toString() const;
    void print() const;

    // Метод для задачи 3.4: возвращает список всех сотрудников отдела (включая себя)
    std::vector<Staff*> getDepartmentEmployees() const;
};

// ============================================================================
//  КЛАСС Department – отдел
// ============================================================================
class Department {
private:
    std::string title;                  // Название отдела
    Staff* boss;                        // Указатель на начальника отдела
    std::vector<Staff*> employees;      // Вектор указателей на всех сотрудников отдела

public:
    // Конструктор: задаём название, начальник и список сотрудников пока пусты
    Department(const std::string& title);

    // Геттеры
    std::string getTitle() const;
    Staff* getBoss() const;

    // Назначить начальника (если начальник ещё не в отделе – автоматически добавляем)
    void setBoss(Staff* emp);

    // Добавить сотрудника в отдел (устанавливается двусторонняя связь)
    void addEmployee(Staff* emp);

    // Получить вектор всех сотрудников (константная ссылка, чтобы избежать копирования)
    const std::vector<Staff*>& getEmployees() const;

    // Для отладки
    std::string toString() const;
    void print() const;
};

// ============================================================================
//  Функции для запуска задач
// ============================================================================
void runEmployeeDepartmentTask();   // Задача 2.4 – базовая
void runEmployeeDepartmentTask3();  // Задача 3.4 – получение списка отдела через сотрудника

#endif