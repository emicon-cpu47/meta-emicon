/** \if nodoxygen
 *  \endif
 */
#include <Windows.h>
#include <Rtapi.h>

/** \if nodoxygen
 *  DllMain must explicitly return TRUE
 *  \endif
 */
BOOL RTAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH: break;
		case DLL_PROCESS_DETACH: break;
    } 
	return TRUE;
}

/** \if nodoxygen
 *  ugly hack to avoid undefined reference to MessageBoxA
 *  generates a lot of warnings but works...
 *  RTX has no MessageBox() but WIN32 must be defined; so in CmpTemplate.c MessageBoxA is called
 *  \endif
 */
int WINAPI MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	RtPrintf("%s: %s\n", lpCaption, lpText);
	return 0;
}
