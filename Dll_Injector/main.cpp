#include"common.h"
#include"injector.h"
#include <stdlib.h>
#include <iostream>
#include "interprocess.h"

#define PROCESS_NAME "melonbooksviewer.exe"
#define DLL_NAME "MelonDumper.dll"

HANDLE InjectionCompletionEventHandle;

int main(int argc, const char *argv[])
{
	InjectionCompletionEventHandle = ::CreateEvent(NULL, TRUE, FALSE, INJECTION_COMPLETION_EVENT_NAME);
	if (InjectionCompletionEventHandle == NULL)
		return EXIT_FAILURE;
	std::string path = BrowseFolder();
	if (path == "")return EXIT_SUCCESS;
	set_global_path(path);

	InjectDLL(getProcID(PROCESS_NAME), CurrentPath() + "\\" + DLL_NAME, InjectionCompletionEventHandle);

	std::cout << "Exiting..." << endl;
	return EXIT_SUCCESS;
}