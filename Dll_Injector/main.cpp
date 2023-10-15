#include"common.h"
#include"injector.h"
#include <stdlib.h>
#include <iostream>

#define PROCESS_NAME "melonbooksviewer.exe"
#define DLL_NAME "MelonDumper.dll"

// usage: Dll_Injector.exe [--path <initial path to save image file>]
int main(int argc, const char *argv[])
{
	const char* initialPath = "";
	for (int index = 1; index < argc; ++index)
	{
		if (strcmp(argv[index], "--path") == 0 && index + 1 < argc)
		{
			++index;
			initialPath = argv[index];
		}
	}
	std::string path = BrowseFolder(initialPath);
	if (path == "")return EXIT_SUCCESS;
	set_global_path(path);

	InjectDLL(getProcID(PROCESS_NAME), CurrentPath()+"\\"+DLL_NAME);
	Sleep(1000);
	std::cout << "Exiting..." << endl;
	return EXIT_SUCCESS;
}