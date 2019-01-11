#include <stdio.h>
#include <windows.h>

int main(int __argc, char *__argv[])
{
	char sz[255];
	char *psz;

	if ( __argc <= 1 || __argv == NULL)
		return -1;

	if (strstr(__argv[1], "Dep.cpp") == 0)
		return -1;

	strcpy(sz, __argv[1]);
	psz = strstr(sz, "Dep.cpp");
	psz[0] = '\0';
	strcat(sz, ".cpp");

	DeleteFile(sz);
	if (MoveFile(__argv[1], sz) == 0)
		return -1;
	return 1;
}