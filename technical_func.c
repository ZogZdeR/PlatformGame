#include "game_functions.h"

struct termios old_t;

void init_terminal() {
    struct termios new_t;
    tcgetattr(STDIN_FILENO, &old_t);
    new_t = old_t;
    new_t.c_lflag &= ~(ICANON | ECHO);
    new_t.c_cc[VMIN] = 0;
    new_t.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_t);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void reset_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
}

int getch() {
    unsigned char ch;
    if (read(STDIN_FILENO, &ch, 1) > 0) return ch;
    return 0;
}


void PrintScreen (platform_t const **Platform_array, size_t platform_quantity, size_t current_left, size_t current_right)
{
    for (size_t i = 0; i < MAX_SCREEN_HIGHT - platform_quantity; i++){
        printf ("\n" YELLOW);
    }
    
    for (size_t j = 0; j <= MAX_SCREEN_SIZE; j++){
        if (j < current_left || j > current_right) printf (" ");
        else printf ("*");
    }
    printf ("\n");

    for (size_t i = platform_quantity - 1; i <= platform_quantity; i--){ //После нуля возвращается в максимальное значение
        if (Platform_array[i] == NULL) printf ("\n");
        else{
            if (Platform_array[i] == INVALID_PLATFORM) return;
            for (size_t j = 0; j <= MAX_SCREEN_SIZE; j++){
                if (j < Platform_array[i]->left_border || j > Platform_array[i]->right_border) printf (" ");
                else printf (GREEN "*");
            }
            printf (NORMAL "\n");
        }
    }
}