#ifndef _PAINTER_HPP_
#define _PAINTER_HPP_

#include <cwchar>
#include <windows.h>

#include "macros.hpp"

/******************************************************************* 

 * Painter class provides a wrapper of double buffering, exposing a

 * update() interface for the user to render the current screen.

*******************************************************************/

class Painter
{
private:
    // handle of the console buffer for double buffering
    HANDLE console_buf_;

    // actual amount of the bytes written to buffer
    DWORD bytes_written_;

    // the memory it points to is allocated by Screen class, which holds a Painter member 
    wchar_t* screen_;

public:
    Painter(wchar_t* screen);

    // non thread-safe interface provided for updating the console output
    void update();

    ~Painter();
};

#endif