#ifndef GAME_FUNC
#define GAME_FUNC

#include "colour.h"
#include "usable_data.h"
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

void InitTerminal();
void InitWaitingTerminal();
void ResetTerminal();
int getch(); 
platform_t *Constructor (size_t left, size_t right, platform_t const *prev_platform, size_t number);
void Destructor (platform_t const ** Platform_array, size_t max_plat_quantity);
size_t AttemptResult (platform_t const **Platform_array);
platform_t const *DeterminateNewPlatform (size_t left, size_t right, platform_t const *prev);
void PrintScreen (platform_t const **Platform_array, size_t platform_quantity, size_t left, size_t right);
void InfiniteGame (game_t *result);
int FixedGame (game_t *result, size_t platform_number);

#endif // GAME_FUNC