#include "game_functions.h"

platform_t *Constructor (size_t left, size_t right, platform_t const *prev_platform, size_t number){
    platform_t *new_platform = (platform_t *)calloc (1, sizeof (platform_t));
    new_platform->left_border = left;
    new_platform->right_border = right;
    new_platform->size = right - left + 1;
    new_platform->prev = prev_platform;
    return new_platform;
}
void Destructor (platform_t const **Platform_array, size_t max_plat_quantity){
    assert (Platform_array);
    platform_t *noconst_ptr = NULL;
    for (size_t i = 0; i < max_plat_quantity; i ++)
    {
        if (Platform_array[i] != INVALID_PLATFORM && Platform_array[i] != NULL){
            noconst_ptr = (platform_t *) Platform_array[i];
            free (noconst_ptr);
        }
    }
    platform_t **noconst_array_ptr = (platform_t **)Platform_array;
    free (noconst_array_ptr);
}

size_t AttemptResult (platform_t const **Platform_array){

    static size_t plat_number = 0;
    size_t left = 0;
    size_t right = 0;
    if (plat_number) right = Platform_array[plat_number - 1]->size - 1;
    else right = BASIC_PLATFORM_SIZE - 1;
    int direction = 'r';
    int key = '\0';
    while (key != ' ' && key != '\n')
    {
        switch (direction)
        {
            case 'r':
                if (right < MAX_SCREEN_SIZE){
                    left ++;
                    right ++;
                }
                else{
                    direction = 'l';
                    left --;
                    right --;
                }
                break;
            case 'l':
                if (left > 0){
                    left --;
                    right --;
                }
                else{
                    direction = 'r';
                    left ++;
                    right ++;
                }
                break;
            default:
                break;
        };
        key = getch();
        
        if (key == ' ' || key == '\n'){
            switch (plat_number){
                case 0:
                    Platform_array[plat_number] = DeterminateNewPlatform (left, right, NULL);
                    break;
                default:
                    Platform_array[plat_number] = DeterminateNewPlatform (direction == 'r' ? left - 1: left + 1,
                        direction == 'r' ? right - 1: right + 1, Platform_array[plat_number - 1]);
                    break;
            }
            if (Platform_array[plat_number] == INVALID_PLATFORM) return 1;
            plat_number ++;
        }
        PrintScreen (Platform_array, plat_number, left, right);
        usleep (7000);
    }
    return 0;
}

platform_t const *DeterminateNewPlatform (size_t left, size_t right, platform_t const *prev){
    if (prev != NULL){
        if (left >= prev->left_border && left <= prev->right_border) right = prev->right_border; 
        else if (left < prev->left_border && right >= prev->left_border) left = prev->left_border;
        else return INVALID_PLATFORM;
        return (platform_t const *)Constructor (left, right, prev, prev->number + 1);
    }
    else{
        return (platform_t const *)Constructor (left, right, NULL, 0);
    }
}

