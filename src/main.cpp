#include "game.hpp"
#include "buttons.hpp"
#include "inkview.h"

ifont *font;
bool background_pause = false;  // when app goes to background, it pauses

void say_hello(){
    Message(ICON_INFORMATION, "title", "It's Tetris time.  Get ready!", 5000);
}

void initial_draw(){
    SetPanelType(0);
    SetOrientation(0);
    say_hello();
    game.draw_background();
    draw_buttons();
    game.new_game();
    
}

void init(){
    // set font type and size - for menu text
    font = OpenFont("DejaVu Sans", 35, false);
    srand(time(0));
}

void deinit(){
    CloseFont(font);
}

int main_handler(int type, int par1, int par2) {
    switch(type){
    case EVT_INIT:
        init();
        break;
    case EVT_SHOW:
        initial_draw();
        break;
    case EVT_KEYDOWN:
        on_key_down(par1);
        break;
    case EVT_KEYUP:
        on_key_up();
        break;
    case EVT_POINTERDOWN:
        on_pointer_down(par1, par2);
        break;
    case EVT_POINTERUP:
        on_pointer_up();
        break;
    case EVT_BACKGROUND:
        if(!game.is_paused()){
            background_pause = true;
            game.toggle_pause();
        }
        break;
    case EVT_FOREGROUND:
        if(background_pause){
            game.toggle_pause();
            background_pause = false;
        }
        break;
    case EVT_EXIT:
        deinit();
        break;
    }
    return 0;
}

int main(int argc, char **argv){
    InkViewMain(main_handler);
    return 0;
}


