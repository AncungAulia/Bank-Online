#ifndef UTILITY_H
#define UTILITY_H

#include <string>

class Utility {
public:
    static std::string generateAccountNumber();
    static std::string formatCurrency(double amount);
    static std::string getCurrentDateTime();
    static void clearScreen();
    static void showSuccessMessage(const std::string& message);
    static void showErrorMessage(const std::string& message);
    static void showColoredText(const std::string& text, int color);
};

#endif 