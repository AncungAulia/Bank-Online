#include "Utility.h"
#include <random> //Untuk generateAccountNumber
#include <ctime> //Untuk getCurrentDateTime (localtime)
#include <sstream> // Manipulasi string
#include <iomanip> // Manipulasi format output (setpresicion dan put_time)
#include <chrono> //untuk getCurrentDateTime (system_clock::now())
#include <iostream> //cout

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
    
    ss << std::fixed << std::setprecision(2) << amount;
    std::string str = ss.str();
    
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
    SetConsoleTextAttribute(hConsole, 7); // Warna default
#else
    std::cout << "\033[1;" << (30 + color) << "m" << text << "\033[0m" << std::endl;
#endif
}

void Utility::showSuccessMessage(const std::string& message) {
    showColoredText(message, 2); // Hijau (32)
}

void Utility::showErrorMessage(const std::string& message) {
    showColoredText(message, 4); // Merah (34)
}
