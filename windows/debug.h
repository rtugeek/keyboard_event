#pragma once

#ifdef _DEBUG
#    include <windows.h>

#    include <iostream>
#    include <sstream>
#    include <stdio.h>
#    include <tchar.h>

extern WCHAR logFile[MAX_PATH];
extern FILE *logStream;

#    ifndef UNICODE
typedef std::ostringstream tostringstream;
#        define ftprintf(file, fmt, ...) fprintf(file, fmt, __VA_ARGS__)
#    else
typedef std::wostringstream tostringstream;
#        define ftprintf(file, fmt, ...) fwprintf(file, fmt, __VA_ARGS__)
#    endif

void log(const tostringstream &line);

template <typename... Args>
void Mydebug(Args &&... args)
{
    tostringstream stream;
    //(stream << ... << std::forward<Args>(args)) << '\n';

    ((stream << std::forward<Args>(args)), ...) << _T('\n');

    OutputDebugString(stream.str().c_str());
    log(stream);
}

#    define debug(format, ...) Mydebug(format, __VA_ARGS__)

#else

#    define debug(format, ...)

#endif