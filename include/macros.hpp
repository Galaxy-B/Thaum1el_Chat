#ifndef _MACROS_HPP_ 
#define _MACROS_HPP_ 

#define SCREEN_HEIGHT 60
#define SCREEN_WIDTH  120

#define FRAME_MASK  0b0001
#define INPUT_MASK  0b0010
#define CHAT_MASK   0b0100
#define PROMPT_MASK 0b1000

enum ScreenMode
{
    frame  = 1,
    input  = 2,
    chat   = 4,
    prompt = 8,
};

#endif