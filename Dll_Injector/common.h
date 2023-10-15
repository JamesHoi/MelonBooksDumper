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
	string strMapName("ShareMemory");                // 内存映射对象名称
	LPVOID pBuffer;                                  // 共销嘹存指諄E
	HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
	// 打开失败，创建之
	hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0, path.length() + 1,strMapName.c_str());
	// 映射对象的一个视图，得到指向共销嘹存的指諄E柚美丒娴氖�
	pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	strcpy((char*)pBuffer, path.c_str());
	//cout << "写葋E蚕诖媸荩�" << (char *)pBuffer << endl;
}