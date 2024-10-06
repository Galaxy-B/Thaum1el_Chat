#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include <mutex>
#include <string>

#include "macros.hpp"
#include "ui/painter.hpp"

/************************************************************************ 

 * Screen class provides interfaces to modify the content of the current 
   screen. Also, it holds a Painter member and wraps its update() into a 
   thread-safe interface for the user to call. 

************************************************************************/

class Screen
{
private:
    std::mutex mutex_;

    // pointer to the memory holding the actual content of current screen
    wchar_t* screen_;

    // painter for rendering
    Painter* painter_;

    // current mode of the screen
    ScreenMode mode_;

public:
    Screen();

    // when called, the screen will be flushed and switch to the specified ui mode
    void switch_mode(ScreenMode mode);

    // clear specified line of content on the screen
    void clear(int i);

    // clear specified rectangular area of content on the screen
    void clear(int i0, int j0, int i1, int j1);

    // print text of at most SIZE wchars in one line beginning at (i,j) to the screen
    // enable auto wrap if newline = true
    // return how many lines the text takes in total 
    int print(int i, int j, int size, std::wstring& text, bool newline); 

    // thread-safe interface provided for updating the console output
    void update();

    ~Screen();
};

#endif