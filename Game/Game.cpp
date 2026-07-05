#include "Engine.h"
#include "SDL3/SDL.h"
#include <iostream>


int main()
{
    nu::Renderer r;
    
    r.Initialize("Game Engine", 1920, 1080);

    SDL_Event e;
    bool quit = false;


    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        r.SetColor(0,0,0); // Set render draw color to black
        r.Clear(); // Clear the renderer

        for (int i = 0; i < 10; i++) // Render 10 lines
        {
            r.SetColor(rand() % 256, rand() % 256, rand() % 256); // Set render draw color to green
            r.RenderLine(rand() % 1920, rand() % 1080, rand() % 1920, rand() % 1080);
        }

        for (int i = 0; i < 20; i++) // Render 20 points
        {
            r.SetColor(rand() % 256, rand() % 256, rand() % 256); // Set render draw color to green
            r.RenderPoint(rand() % 1920, rand() % 1080);
        }

        for (int i = 0; i < 5; i++) // Render 5 rectangles
        {
            r.SetColor(rand() % 256, rand() % 256, rand() % 256); // Set render draw color to green
            r.RenderRect(rand() % 1920, rand() % 1080, rand() % 300, rand() % 300, rand() % 2);
        }


        //r.SetColor(255,255,255); // Set render draw color to green
        //SDL_RenderDebugText(renderer, 10, 10, "Hello world!");
        r.RenderPresent();// Render the screen
    }

    r.Quit();

    // Testing edits
    return 0;
}
