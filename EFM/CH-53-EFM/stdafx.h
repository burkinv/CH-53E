// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <stdio.h>
#include <CommCtrl.h>

// Visual Studio is rather dumb at times..
// -> moved to project settings
/*#define _USE_MATH_DEFINES*/ 
#include <cmath>

#include <malloc.h>
#include <memory.h>


#ifdef _DEBUG
extern FILE* pConsole;
//#define LOG(s, ...) if ( pConsole != nullptr) { \
//                       fprintf(pConsole, s, __VA_ARGS__); }
#define LOG(n, s, ...) if ( pConsole != nullptr) { \
                       COORD logCoord = {0, n}; \
                       SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), logCoord); \
                       fprintf(pConsole, s, __VA_ARGS__); }
#else
#define LOG(n, s, ...) 
#endif //_DEBUG


