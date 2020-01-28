#ifndef __FREEBSDDEPENDS_H
#define __FREEBSDDEPENDS_H

#ifdef INITOPENINDIANA
#include <cstdlib>
#include <cstring>
#endif

#ifdef FREEBSD
#include <cstdlib>
#include <cstring>
#endif

#ifdef INITWINDOWSNOW
#include <Windows.h>
#endif

#ifndef INITWINDOWSNOW
size_t strnlen(const char *str, size_t len);
#endif

char *strndup(const char *str, size_t len);

#endif

