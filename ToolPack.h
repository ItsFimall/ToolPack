#pragma once
#include <iomanip>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <thread>
#include <chrono>
#include <ctime>
#include <tchar.h>
#include <climits>
#include <cstdlib>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>

#ifndef FIMALLTOOLPACK_H_
#define FIMALLTOOLPACK_H_
// ToolPack By Fimall

// Function to generate a random string composed of alphabetical characters (A-Z).
std::string generateRandomAlphabeticalString(size_t length);

// Function to generate a random string composed of alphabetical characters (A-Z) and symbols.
std::string generateRandomMixedString(size_t length);

// Function to generate a random string composed of numerical digits (0-9).
std::string generateRandomNumberString(size_t length);

// Function to generate a random string composed of symbols.
std::string generateRandomSymbolString(size_t length);

// Function to generate a random number within the specified range.
long long generateRandomNumber(int min, int max);

// Initialize the random number generator.
void initializeRandomSeed();

// Convert a string to a character array.
const char* stringToCharArray(std::string str);

// Print text with specified color to the Windows console.
void printColoredText(const char* s, int color);

// Replace all occurrences of a substring in a string.
bool replaceSubstring(std::string& str, const std::string& from, const std::string& to);

// Delete all occurrences of a substring from a string.
bool deleteSubstring(std::string& str, const std::string& toDelete);

// Erase a specified number of lines from the console output.
void eraseConsoleLines(int count);

// Check if a process with the given name is running.
bool isProcessRunning(const char* processName);

// Run the program in the background by hiding the console window.
void runInBackground();

// Suspend all threads of a specified process.
void suspendProcessThreads(DWORD processId);

// Terminate all instances of a specified process.
void terminateProcess(const char* filename);

// Check Internet Connection by using "system"
bool checkConnectivity(const std::string& ipAddress);

// Get Formatted System time
std::string getFormattedTime();

// Logger Function
void Logger(const std::ofstream& logFile, std::string& type, const std::string& logMsg, int logCode = 0);

// Convert LPCSTR To std::string
LPCSTR StringToLPCSTR(const std::string& str);

// Generate a random string containing alphabetical characters (A-Z).
std::string generateRandomAlphabeticalString(size_t length) {
    const char* charmap = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const size_t charmapLength = strlen(charmap);
    auto generator = [&]() { return charmap[rand() % charmapLength]; };
    std::string result;
    result.reserve(length);
    generate_n(back_inserter(result), length, generator);
    return result;
}

// Generate a random string containing alphabetical characters, symbols, and digits.
std::string generateRandomMixedString(size_t length) {
    const char* charmap = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()-=_+[]{}:;\'\"|\\<>,./?";
    const size_t charmapLength = strlen(charmap);
    auto generator = [&]() { return charmap[rand() % charmapLength]; };
    std::string result;
    result.reserve(length);
    generate_n(back_inserter(result), length, generator);
    return result;
}

// Generate a random string containing numerical digits (0-9).
std::string generateRandomNumberString(size_t length) {
    const char* charmap = "0123456789";
    const size_t charmapLength = strlen(charmap);
    auto generator = [&]() { return charmap[rand() % charmapLength]; };
    std::string result;
    result.reserve(length);
    generate_n(back_inserter(result), length, generator);
    return result;
}

// Generate a random string containing basic symbols.
std::string generateRandomSymbolString(size_t length) {
    const char* charmap = "!@#$%^&*`()-=_+[]{}:;\'\"<>,./?";
    const size_t charmapLength = strlen(charmap);
    auto generator = [&]() { return charmap[rand() % charmapLength]; };
    std::string result;
    result.reserve(length);
    generate_n(back_inserter(result), length, generator);
    return result;
}

// Generate a random number within the specified range.
long long generateRandomNumber(int min, int max) {
    // Generate a number between min and max (inclusive).
    return min + rand() % (max - min + 1);
}

// Initialize the random number generator using the current time.
void initializeRandomSeed() {
    srand(static_cast<unsigned int>(time(NULL)));
}

// Convert a string to a null-terminated character array.
const char* stringToCharArray(std::string str) {
    return str.c_str();
}

// Print text with a specified color to the Windows console.
void printColoredText(const char* s, int color) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
    printf(s);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

// Replace all occurrences of a substring in a string.
bool replaceSubstring(std::string& str, const std::string& from, const std::string& to) {
    // Find the first occurrence of 'from' in 'str'.
    size_t start_pos = str.find(from);
    // If not found, return false.
    if (start_pos == std::string::npos)
        return false;
    // Replace 'from' with 'to'.
    str.replace(start_pos, from.length(), to);
    return true;
}

// Delete all occurrences of a substring from a string.
bool deleteSubstring(std::string& str, const std::string& toDelete) {
    // Find the first occurrence of 'toDelete' in 'str'.
    size_t start_pos = str.find(toDelete);
    // If not found, return false.
    if (start_pos == std::string::npos)
        return false;
    // Erase 'toDelete' from 'str'.
    str.erase(start_pos, toDelete.length());
    return true;
}

// Erase a specified number of lines from the console output.
void eraseConsoleLines(int count) {
    if (count > 0) {
        // Delete the current line.
        std::cout << "\x1b[2K";
        // Move the cursor up and delete each line.
        for (int i = 1; i < count; i++) {
            std::cout
                << "\x1b[1A" // Move cursor up one line.
                << "\x1b[2K"; // Delete the entire line.
        }
        // Resume the cursor at the beginning of the line.
        std::cout << "\r";
    }
}

// Check if a process with the given name is running.
bool isProcessRunning(const wchar_t* processName) {
    wchar_t pName[MAX_PATH];
    wcscpy(pName, processName);
    CharLowerBuffW(pName, MAX_PATH); // Convert to lowercase.
    PROCESSENTRY32 currentProcess;
    currentProcess.dwSize = sizeof(currentProcess);
    HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcess == INVALID_HANDLE_VALUE) {
        printf("CreateToolhelp32Snapshot() failed to run\n");
        return false;
    }

    bool bMore = Process32First(hProcess, &currentProcess);
    while (bMore) {
        CharLowerBuffW(currentProcess.szExeFile, MAX_PATH);
        if (wcscmp(currentProcess.szExeFile, pName) == 0) {
            CloseHandle(hProcess);
            return true;
        }
        bMore = Process32Next(hProcess, &currentProcess);
    }

    CloseHandle(hProcess);
    return false;
}


// Run the program in the background by hiding the console window.
void runInBackground() {
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window, 0);
}

// Suspend all threads of a specified process.
void suspendProcessThreads(DWORD processId) {
    HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    THREADENTRY32 threadEntry;
    threadEntry.dwSize = sizeof(THREADENTRY32);

    Thread32First(hThreadSnapshot, &threadEntry);

    do {
        if (threadEntry.th32OwnerProcessID == processId) {
            HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, threadEntry.th32ThreadID);
            SuspendThread(hThread);
            CloseHandle(hThread);
        }
    } while (Thread32Next(hThreadSnapshot, &threadEntry));

    CloseHandle(hThreadSnapshot);
}

// Terminate all instances of a specified process.
void terminateProcess(const wchar_t* filename) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes) {
        if (wcscmp(pEntry.szExeFile, filename) == 0) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
            if (hProcess != NULL) {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}


bool checkConnectivity(const std::string& hostAddress) {
    std::string command = "ping -c 1 " + hostAddress + " > NUL";  // 构建ping命令
    int result = system(command.c_str());  // 执行命令
    // 检查命令执行的返回值
    if (result == 0) {
        return true;
    }
    else {
        return false;
    }
}

std::string getFormattedTime() {
    // 获取当前系统时间点
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // 将时间点转换为time_t类型
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // 使用本地时间将time_t格式化为字符串
    std::tm* localTime = std::localtime(&currentTime);

    // 提取年、月、日、小时、分钟和秒
    int year = localTime->tm_year + 1900;  // 年份需要加上1900
    int month = localTime->tm_mon + 1;     // 月份从0开始，需要加上1
    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    // 格式化时间为字符串
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

    // 返回格式化后的时间字符串
    return std::string(buffer);
}

void Logger(std::ofstream& logFile, std::string& type, const std::string& logMsg, int logCode) {
    std::string outputText = getFormattedTime() + " [" + type + "] - " + std::to_string(logCode) + "-" + logMsg;
    if (logFile.is_open()) {
        logFile << outputText << std::endl;
    }
    else {
        throw std::runtime_error("Unable to open LogFile");
    }
}


LPCSTR StringToLPCSTR(const std::string& str) {
    // 使用c_str()方法获取指向字符串数据的指针
    return str.c_str();
}

#endif
