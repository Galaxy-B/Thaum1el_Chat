#include "ui/screen.hpp"

#include <cwchar>

Screen::Screen()
{
    screen_ = new wchar_t[SCREEN_HEIGHT * SCREEN_WIDTH];

    // instantiate a painter
    painter_ = new Painter(screen_);
}

void Screen::switch_mode(ScreenMode mode)
{
    // clear the whole screen first
    clear(0, 0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1);

    // make sure only one thread is modifying the screen
    std::lock_guard<std::mutex> lock(mutex_);
    mode_ = mode;

    // there can be many modes to render at a time, render each one sepearately
    if (mode & FRAME_MASK)
    {
        // top and bottom rows
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            screen_[j] = L'-';
            screen_[(SCREEN_HEIGHT - 1) * SCREEN_WIDTH + j] = L'-';
        }

        // left and right cols
        for (int i = 1; i < SCREEN_HEIGHT - 1; i++)
        {
            screen_[i * SCREEN_WIDTH] = L'|';
            screen_[i * SCREEN_WIDTH + SCREEN_WIDTH - 1] = L'|';
        }
    }

    if (mode & INPUT_MASK)
    {
        // top and bottom rows of input area
        for (int j = 40; j < 80; j++)
        {
            screen_[40 * SCREEN_WIDTH + j] = L'-';
            screen_[42 * SCREEN_WIDTH + j] = L'-';
        }

        // left and right cols of input area
        screen_[41 * SCREEN_WIDTH + 40] = L'|';
        screen_[41 * SCREEN_WIDTH + 80] = L'|';
    }

    if (mode & CHAT_MASK)
    {
        for (int j = 1; j < SCREEN_WIDTH; j++)
        {
            // split line between chat records and chatroom info
            screen_[50 * SCREEN_WIDTH + j] = L'-';
            
            // split line between chat records and textbox
            screen_[3  * SCREEN_WIDTH + j] = L'-';
        }

        // split line between chat records and online members
        for (int i = 4; i < 50; i++)
        {
            screen_[i  * SCREEN_WIDTH + 100] = L'|';
        }
    }

    if (mode & PROMPT_MASK)
    {
        // fixed prompt for confirmation
        static std::wstring prompt = L"* Press [ENTER] to confirm, or [ESC] to withdraw!";
        
        auto* position = screen_ + 20 * SCREEN_WIDTH + 35;
        std::swprintf(position, L"%s", prompt.data());
    }
}

void Screen::clear(int i)
{
    // make sure only one thread is modifying the screen
    std::lock_guard<std::mutex> lock(mutex_);

    // skip window framework
    for (int j = 1; j < SCREEN_WIDTH - 1; j++)
    {
        screen_[i * SCREEN_WIDTH + j] = L' ';
    }
}

void Screen::clear(int i0, int j0, int i1, int j1)
{
    // make sure only one thread is modifying the screen
    std::lock_guard<std::mutex> lock(mutex_);

    // user should takes window framework into account
    for (int i = i0; i <= i1; i++)
    {
        for (int j = j0; j < j1; j++)
        {
            screen_[i * SCREEN_WIDTH + j] = L' ';
        }
    }
}

int Screen::print(int i, int j, int size, std::wstring& text, bool newline)
{
    // make sure only one thread is modifying the screen
    std::lock_guard<std::mutex> lock(mutex_);
    
    // over-length part of the text will be omitted
    if (!newline)
    {
        auto* position = screen_ + i * SCREEN_WIDTH + j;
        std::swprintf(position, size, L"%s", text.data());
        return 1;
    }
    // divide the whole text into lines 
    else
    {
        int lines = 0; 

        for (int count = 0; lines * size < text.size(); lines++)
        {
            auto* position = screen_ + (i + lines) * SCREEN_WIDTH + j;
            count += std::swprintf(position, size, L"%s", text.substr(count, size).data());
        }

        return lines;
    }
}

void Screen::update()
{
    // make sure only one thread is rendering the screen
    std::lock_guard<std::mutex> lock(mutex_);

    painter_->update();
}

Screen::~Screen()
{
    delete painter_;
    delete screen_;
}