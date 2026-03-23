#include "colour.h"
#include "game_functions.h"

int main ()
{
    int check = '\n';
    printf("\033[H\033[J");
    fflush (stdout); 
    fflush (stdin);
    printf (MAGENTA "Добро можеловать в игру \"Башенки\"!\n");
    printf (CYAN "Хотите играть в бесконечный режим (нажмите i) или с фиксированной максимальной высотой (нажмите f)?\n" NORMAL);

    check =  getc (stdin);
    fprintf (stdout, "aaaaagh%c\n", (char)check);
    platform_t const **Platform_array = NULL;

    switch (check){
        case 'i':
        {
            Platform_array = (platform_t const **)calloc (STARTING_INF_GAME_SIZE, sizeof (platform_t *));
            game_t game_result = {Platform_array, 0, STARTING_INF_GAME_SIZE};
            InitTerminal ();
            InfiniteGame (&game_result);
            ResetTerminal ();
            Destructor (game_result.Platform_array, game_result.certain_maximum);
            break;
        }
        case 'f':
        {
            printf ("Чтобы начать игру выбери уровень (количество башенок, нужное для победы)\n" NORMAL);
            size_t platform_number;
            scanf ("%lu", &platform_number);
            Platform_array = (platform_t const **)calloc (platform_number, sizeof (platform_t *));
            game_t game_res = {Platform_array, 0, platform_number};
            FixedGame (&game_res, platform_number);
            Destructor (Platform_array, platform_number);
            break;
        }
        default:
            assert (0);
    };
    
    
    
    //НАПИСАТЬ ФУНКЦИЮ КОНГРАТЬЮЛЕЙШОНС
    return 0;
}