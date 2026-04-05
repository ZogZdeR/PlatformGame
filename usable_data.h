#ifndef DATA
#define DATA

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Platform
{
    size_t left_border;
    size_t right_border;
    size_t size;
    size_t number;
    struct Platform const *prev;
};

typedef struct Platform platform_t;

struct GameRes
{
    platform_t const **Platform_array;
    size_t platform_quantity;
    size_t certain_maximum;

    struct {
        SDL_Window *window;
        SDL_Renderer *renderer;
    } graphic_structure;
};

typedef struct GameRes game_t;

static platform_t const *INVALID_PLATFORM = (platform_t const*) 0xDEADBABE;

// ========================================================================
// TERMINAL GRAPHIC CONSTANTS
// ========================================================================

size_t const BASIC_PLATFORM_SIZE = 60;
size_t const STARTING_INF_GAME_SIZE = 50;
size_t const MAX_SCREEN_SIZE = 140;
size_t const MAX_SCREEN_HIGHT = 48;

// ========================================================================
// SDL GRAPHIC CONSTANTS
// ========================================================================

int const SCREEN_WIDTH = 1920;
int const SCREEN_HIGHT = 1080;
int const MY_PIXEL_SIZE = 20;

#endif // DATA