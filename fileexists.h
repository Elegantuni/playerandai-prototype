#ifndef __FILEEXISTS_H
#define __FILEEXISTS_H

#ifdef INITWINDOWSNOW
#include <Windows.h>
#endif

#include <tchar.h>

int fileExists(const wchar_t* file);

#endif

