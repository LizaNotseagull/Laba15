#ifndef UTILS_H
#define UTILS_H

#include <string>

void setupRussianLocale();
int safeInputInt(const std::string& prompt);
std::string safeInputString(const std::string& prompt);
std::string safeInputNamePart(const std::string& prompt);
int safeInputPositiveInt(const std::string& prompt); // Новая функция для положительных целых чисел
int generateRandomInt(int min, int max);
std::string generateRandomWord();
std::string readLineFromFile(const std::string& filename, int lineNumber);

#endif