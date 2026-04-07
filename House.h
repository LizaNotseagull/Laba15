#ifndef HOUSE_H
#define HOUSE_H

#include <string>

class House {
private:
    int floors;
public:
    House(int floors);
    std::string toString() const;
    void print() const;
    static void run();
};

#endif