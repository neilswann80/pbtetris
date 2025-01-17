#include "buttons.hpp"
#include "game.hpp"
#include "inkview.h"

enum Button {
    BUTTON_LEFT, BUTTON_RIGHT, BUTTON_UP, BUTTON_DOWN, BUTTON_PAUSE, BUTTON_NEW_GAME, BUTTON_OPT_MENU, BUTTON_DROP
};

const int BUTTON_REPEAT_TIME = 250;

Button last_button_pressed;
void repeat_button_press_timer();

void on_button_press(Button button){
    last_button_pressed = button;

    switch(button){
    case BUTTON_LEFT:
        game.move_tetromino(-1);
        break;
    case BUTTON_RIGHT:
        game.move_tetromino(1);
        break;
    case BUTTON_UP:
        game.rotate_tetromino(1);
        break;
    case BUTTON_DOWN:
        game.rotate_tetromino(-1);
        break;
    case BUTTON_PAUSE:
        game.toggle_pause();
        break;
    case BUTTON_NEW_GAME:
        game.new_game();
        break;
    case BUTTON_OPT_MENU:
        CloseApp();
        break;
    case BUTTON_DROP:
        game.put_tetromino_down();
        break;
    }

    on_key_up();
    if(button <= BUTTON_UP)
        SetHardTimer("REPEAT_BUTTON_PRESS", repeat_button_press_timer, BUTTON_REPEAT_TIME);
}

void repeat_button_press_timer(){
    on_button_press(last_button_pressed);
    SetHardTimer("REPEAT_BUTTON_PRESS", repeat_button_press_timer, BUTTON_REPEAT_TIME);
}

void on_key_down(int key){
    switch(key){
    case KEY_LEFT:
    case IV_KEY_HOME:
        on_button_press(BUTTON_LEFT);
        break;
    case KEY_RIGHT:
    case IV_KEY_MENU:
        on_button_press(BUTTON_RIGHT);
        break;
    case KEY_UP:
    case IV_KEY_NEXT:
        on_button_press(BUTTON_UP);
        break;
    case KEY_DOWN:  
    case IV_KEY_PREV:
        on_button_press(BUTTON_DOWN);
        break;
    }
}

extern const ibitmap buttons_arrows, pause_button, new_game_button, opt_menu_button, drop_button;

const int ARROWS_Y = -134;
// pause and newgame
const int MENU_Y = 1207;
// exit/menu
const int MENU_Y2 = 30;
const int PAUSE_BUTTON_X = -1050; // -215
const int NEW_GAME_BUTTON_X = -940; // -105
const int OPT_MENU_BUTTON_X = -1040; // -995
const int DROP_BUTTON_X = -215;  //-1050

void draw_bitmap(int x, int y, const ibitmap &bmp){
    DrawBitmap(x, y, &bmp);
    PartialUpdate(x, y, bmp.width, bmp.height);
}

void draw_buttons(){
    draw_bitmap(0, ScreenHeight() + ARROWS_Y, buttons_arrows);
    draw_bitmap(ScreenWidth() + PAUSE_BUTTON_X, MENU_Y, pause_button);
    draw_bitmap(ScreenWidth() + NEW_GAME_BUTTON_X, MENU_Y, new_game_button);
    draw_bitmap(ScreenWidth() + OPT_MENU_BUTTON_X, MENU_Y2, opt_menu_button);
    draw_bitmap(ScreenWidth() + DROP_BUTTON_X, MENU_Y, drop_button);
}

void on_pointer_down(int x, int y){
    if(y >= ScreenHeight() + ARROWS_Y){
        // clicked one of arrows
        int button_number = x / 268;
        switch (button_number) {
        case 0:
            on_key_down(KEY_LEFT);
            break;
        case 1:
            on_key_down(KEY_DOWN);
            break;
        case 2:
            on_key_down(KEY_UP);
            break;
        case 3:
            on_key_down(KEY_RIGHT);
            break;
        }
    }
    else if(ScreenWidth() + PAUSE_BUTTON_X <= x && x < ScreenWidth() + PAUSE_BUTTON_X + pause_button.width
            && MENU_Y <= y && y < MENU_Y + pause_button.height){
        game.toggle_pause();
    }
    else if(ScreenWidth() + NEW_GAME_BUTTON_X <= x && x < ScreenWidth() + NEW_GAME_BUTTON_X + new_game_button.width
            && MENU_Y <= y && y < MENU_Y + new_game_button.height){
        game.new_game();
    }
    else if(ScreenWidth() + OPT_MENU_BUTTON_X <= x && x < ScreenWidth() + OPT_MENU_BUTTON_X + opt_menu_button.width
            && MENU_Y2 <= y && y < MENU_Y2 + opt_menu_button.height){
        CloseApp();
    }
    else if(ScreenWidth() + DROP_BUTTON_X <= x && x < ScreenWidth() + DROP_BUTTON_X + drop_button.width
            && MENU_Y <= y && y < MENU_Y + drop_button.height){
        game.put_tetromino_down();
    }
}


void on_key_up(){
    ClearTimer(repeat_button_press_timer);
}

void on_pointer_up(){
    on_key_up();
}
