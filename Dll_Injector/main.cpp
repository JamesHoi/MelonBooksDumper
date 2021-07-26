#include"common.h"
#include"injector.h"
#include <stdlib.h>
#include <iostream>

#define PROCESS_NAME "melonbooksviewer.exe"
#define DLL_NAME "MelonDumper.dll"

int main(int argc, const char *argv[])
{
	std::string path = BrowseFolder();
	if (path == "")return EXIT_SUCCESS;
	set_global_path(path);

	InjectDLL(getProcID(PROCESS_NAME), CurrentPath()+"\\"+DLL_NAME);
	Sleep(200);
	return EXIT_SUCCESS;
}