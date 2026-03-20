#include "colour.h"
#include "game_functions.h"

int main ()
{
    printf("\033[H\033[J");
    fflush(stdout); 
    printf (MAGENTA "Добро можеловать в игру \"Башенки\"!\n");
    printf ("Чтобы начать игру выбери уровень (количество башенок, нужное для победы)\n" NORMAL);
    size_t platform_number;
    scanf ("%lu", &platform_number);
    platform_t const **Platform_array = (platform_t const **)calloc (platform_number, sizeof (platform_t *));
    printf (GREEN "mew\n" NORMAL);
    
    init_terminal ();
    AttemptResult (Platform_array);
    for (size_t i = 1; i < platform_number; i ++)
{
        if (AttemptResult (Platform_array) != 0){
            reset_terminal ();
            Destructor (Platform_array, platform_number);
            return 0;
        }
    }
    reset_terminal ();
    //НАПИСАТЬ ФУНКЦИЮ КОНГРАТЬЮЛЕЙШОНС

    Destructor (Platform_array, platform_number);
    return 0;
}