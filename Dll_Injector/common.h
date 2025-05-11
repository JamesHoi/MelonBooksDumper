#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNING


#include <windows.h>
#include <string>
#include <shlobj.h>
#include <iostream>
#include <sstream>

using namespace std;

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

	if (uMsg == BFFM_INITIALIZED)
	{
		//string tmp = (const char *)lpData;
		//cout << "path: " << tmp << endl;
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	}
	return 0;
}

string BrowseFolder()
{
	TCHAR path[MAX_PATH];

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("Browse for save folder...");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = BrowseCallbackProc;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		//get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		return path;
	}
	return "";
}

string CurrentPath() {
	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);
	return NPath;
}

void set_global_path(string path) {
	string strMapName("ShareMemory");                // Memory mapped object name
	LPVOID pBuffer;                                  // Shared memory pointer

	HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
	// Failed to open, create it
	hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0, path.length() + 1,strMapName.c_str());
	// Map a view of the object, get the pointer to the shared memory, and set the data inside
	pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	strcpy((char*)pBuffer, path.c_str());
	//cout << "Write shared memory data: " << (char *)pBuffer << endl;
}