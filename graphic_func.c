#include "graphic_func.h"
#include "usable_data.h"
#include <assert.h>

void OutputInitialisation (game_t *game){
    assert (game);

    if (SDL_Init (SDL_INIT_VIDEO) != 0){
        printf("SDL initialisation error: %s\n", SDL_GetError ());
        return 1;
    }

    game->graphic_structure.window = SDL_CreateWindow (
        "TOWER GAME",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HIGHT,
        SDL_WINDOW_SHOWN  // Показываем окно сразу
    );

    if (game->graphic_structure.window == NULL){
        printf ("Window initting error: %s\n", SDL_GetError ());
        SDL_Quit (); 
        return 1;
    }

    game->graphic_structure.renderer = SDL_CreateRenderer (
        game->graphic_structure.window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (game->graphic_structure.renderer == NULL) {
        printf ("Renderer initting error: %s\n", SDL_GetError ());
        SDL_DestroyWindow (game->graphic_structure.window);
        SDL_Quit ();
        return 1;
    }
}


void PrintScreen (game_t *game, size_t platform_quantity, size_t current_left, size_t current_right)
{
    SDL_SetRenderDrawColor (game->graphic_structure.renderer, 0, 0, 255, 255);
    SDL_RenderClear (game->graphic_structure.renderer); // Заливаем холст выбранным цветом
    
    for (size_t i = 0; i <= platform_quantity; i++){ //После нуля возвращается в максимальное значение
        if (game->Platform_array[i] == NULL) break;
        else{
            if (game->Platform_array[i] == INVALID_PLATFORM) return;
            
            SDL_SetRenderDrawColor (game->graphic_structure.renderer, 0, 255, 100, 255);
            SDL_Rect rect = {
                .x = (SCREEN_WIDTH / MAX_SCREEN_SIZE) * , 
                .y = SCREEN_HIGHT / 2 - 25, 
                .w = 50,
                .h = 50
            };

            // Заливаем прямоугольник цветом (fill rect)
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    for (size_t i = 0; i < MAX_SCREEN_HIGHT - platform_quantity; i++){
        printf ("\n" YELLOW);
    }
    
    for (size_t j = 0; j <= MAX_SCREEN_SIZE; j++){
        if (j < current_left || j > current_right) printf (" ");
        else printf ("*");
    }
    printf ("\n");

    for (size_t i = platform_quantity - 1; i <= platform_quantity; i--){ //После нуля возвращается в максимальное значение
        if (game->Platform_array[i] == NULL) printf ("\n");
        else{
            if (game->Platform_array[i] == INVALID_PLATFORM) return;
            for (size_t j = 0; j <= MAX_SCREEN_SIZE; j++){
                if (j < game->Platform_array[i]->left_border || j > game->Platform_array[i]->right_border) printf (" ");
                else printf (GREEN "*");
            }
            printf (NORMAL "\n");
        }
    }
}


/*

int main (int argc, char* argv[])
{
    int const WINDOW_WIDTH = 1920;
    int const WINDOW_HEIGHT = 1080;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // Если что-то пошло не так, SDL_GetError() вернет текст ошибки
        printf("Ошибка инициализации SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Мое первое SDL окно",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN  // Показываем окно сразу
    );

    if (window == NULL) {
        printf("Ошибка создания окна: %s\n", SDL_GetError());
        SDL_Quit(); // Если окно не создалось, нужно выгрузить SDL из памяти
        return 1;
    }

     // 3. Создаем рендерер (холст для рисования)
    // Параметры: окно, индекс драйвера (-1 = авто), флаги ускорения
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED  // Используем видеокарту
    );

    if (renderer == NULL) {
        printf("Ошибка создания рендерера: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
     // --------------------------------------------------
    // 4. Главный игровой цикл (Game Loop)
    // --------------------------------------------------
    bool is_running = true;
    SDL_Event event; // Сюда будут приходить события (нажатие клавиш, закрытие окна и т.д.)

    while (is_running) {
        // --- Обработка ввода (Input) ---
        // Пока в очереди есть события, забираем их
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // Пользователь нажал крестик на окне
                is_running = false;
            }
            // Если хочешь обрабатывать нажатие клавиш, можно добавить:
            // if (event.type == SDL_KEYDOWN) { ... }
        }

        // --- Логика (Update) ---
        // Здесь пока ничего нет. Позже тут будет перемещение объектов, физика.

        // --- Рендеринг (Draw) ---
        // Сначала очищаем экран. SDL_SetRenderDrawColor задает цвет заливки.
        // Параметры: R, G, B, Alpha (прозрачность). Черный цвет: 0,0,0,255
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); // Заливаем холст выбранным цветом

        // Теперь рисуем что-нибудь простенькое.
        // Например, белый квадрат 50x50 пикселей.

        // Меняем цвет рисования на белый (RGB: 255, 255, 255)
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

        // Определяем прямоугольник: x, y, width, height
        SDL_Rect rect = {
            .x = WINDOW_WIDTH / 2 - 25, // Чтобы квадрат был по центру по горизонтали
            .y = WINDOW_HEIGHT / 2 - 25, // По центру по вертикали
            .w = 50,
            .h = 50
        };

        // Заливаем прямоугольник цветом (fill rect)
        SDL_RenderFillRect(renderer, &rect);

        // Можно нарисовать красную линию из угла в угол
        SDL_SetRenderDrawColor(renderer, 125, 125, 0, 255);
        SDL_RenderDrawLine(renderer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        // Показываем то, что нарисовали на экране (меняем задний и передний буфер)
        SDL_RenderPresent(renderer);

        // Небольшая задержка, чтобы процессор не грелся на 100%
        // В реальных играх задержку контролируют через время кадра (delta time),
        // но для простоты поставим 16 мс (~60 FPS)
        SDL_Delay(16);
    }

    // --------------------------------------------------
    // 5. Очистка ресурсов (Cleanup)
    // --------------------------------------------------
    // В C мы сами обязаны удалять все созданные объекты.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // Выгружаем библиотеку

    return 0;
}
    */