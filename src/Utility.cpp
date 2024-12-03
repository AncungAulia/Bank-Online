#include "Utility.h"
#include <random>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

std::string Utility::generateAccountNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000000, 99999999);
    return std::to_string(dis(gen));
}

std::string Utility::formatCurrency(double amount) {
    std::stringstream ss;
    ss << "Rp ";
    
    // Convert to string with 2 decimal places
    ss << std::fixed << std::setprecision(2) << amount;
    std::string str = ss.str();
    
    // Add thousand separators
    size_t dot_pos = str.find('.');
    if (dot_pos == std::string::npos) {
        dot_pos = str.length();
    }
    
    for (int i = dot_pos - 3; i > 3; i -= 3) {
        str.insert(i, ".");
    }
    
    return str;
}

std::string Utility::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void Utility::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Utility::showColoredText(const std::string& text, int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    std::cout << text << std::endl;
    SetConsoleTextAttribute(hConsole, 7); // Reset to default color
#else
    std::cout << "\033[1;" << (30 + color) << "m" << text << "\033[0m" << std::endl;
#endif
}

void Utility::showSuccessMessage(const std::string& message) {
    showColoredText(message, 2); // Green color
}

void Utility::showErrorMessage(const std::string& message) {
    showColoredText(message, 4); // Red color
}
