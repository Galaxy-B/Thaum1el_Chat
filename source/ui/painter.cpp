#include "ui/painter.hpp"
#include <cstddef>
#include <handleapi.h>
#include <wincon.h>
#include <winnt.h>

Painter::Painter(wchar_t* screen) : screen_(screen)
{
    // create a console buffer and make it active
    console_buf_ = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    SetConsoleActiveScreenBuffer(console_buf_);
}

void Painter::update()
{
    // flush everything in screen array to console buffer
    WriteConsoleOutputCharacterW(console_buf_, screen_, SCREEN_HEIGHT * SCREEN_WIDTH, {0, 0}, &bytes_written_);
}
    
Painter::~Painter()
{
    // close the console buffer
    CloseHandle(console_buf_);
}