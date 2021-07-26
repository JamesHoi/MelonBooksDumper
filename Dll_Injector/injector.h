#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <Shlwapi.h>
//Library needed by Linker to check file existance
#pragma comment(lib, "Shlwapi.lib")
using namespace std;


int getProcID(const string& p_name);
bool InjectDLL(const int &pid, const string &DLL_Path);
