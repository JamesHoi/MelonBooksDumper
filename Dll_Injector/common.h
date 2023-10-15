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

string BrowseFolder(const char* initialPath)
{
	TCHAR path[MAX_PATH];

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("Browse for save folder...");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lParam = (LPARAM)initialPath;
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
	string strMapName("ShareMemory");                // ÄÚ´æÓ³Éä¶ÔÏóÃû³Æ
	LPVOID pBuffer;                                  // ¹²ÏúàÚ´æÖ¸ÕE
	HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
	// ´ò¿ªÊ§°Ü£¬´´½¨Ö®
	hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0, path.length() + 1,strMapName.c_str());
	// Ó³Éä¶ÔÏóµÄÒ»¸öÊÓÍ¼£¬µÃµ½Ö¸Ïò¹²ÏúàÚ´æµÄÖ¸ÕE¬ÉèÖÃÀEæµÄÊı¾İ
	pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	strcpy((char*)pBuffer, path.c_str());
	//cout << "Ğ´ÈE²ÏúàÚ´æÊı¾İ£º" << (char *)pBuffer << endl;
}