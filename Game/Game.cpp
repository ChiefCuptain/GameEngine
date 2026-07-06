#include "Engine.h"

#include <iostream>
#include <vector>

int main()
{
    // INITIALIZATION
    nu::Renderer r;
    r.Initialize("Game Engine", 1920, 1080);
    nu::Vector2 vel{ 0.5f, 0.0f };

    std::vector<nu::Vector2> v;
    for (int i = 0; i < 30000; i++)
    {
        v.push_back(nu::Vector2{ nu::RandomFloat(1920), nu::RandomFloat(1080) });
    }

    // MAIN LOOP
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // UPDATE
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // RENDER
        r.SetColor(0,0,0); // Set render draw color to black
        r.Clear(); // Clear the renderer

        //for (int i = 0; i < 10; i++) // Render 10 lines
        //{
        //    r.SetColorFloat(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat()); // Set render draw color to green
        //    r.RenderLine(nu::RandomFloat(1920), nu::RandomFloat(1080), rand() % 1920, rand() % 1080);
        //}

        for (size_t i = 0; i < v.size(); i++) // Render 300 points
        {
            r.SetColorFloat(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat()); // Set render draw color to green
            v.at(i) = v.at(i) + vel;
            r.RenderPoint(v.at(i).x, v.at(i).y);
        }

        //for (int i = 0; i < 5; i++) // Render 5 rectangles
        //{
        //    r.SetColorFloat(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat()); // Set render draw color to green
        //    r.RenderRect(nu::RandomFloat(1920), nu::RandomFloat(1080), nu::RandomFloat(300), nu::RandomFloat(300), nu::RandomInt(2));
        //}


        //r.SetColor(255,255,255); // Set render draw color to green
        //SDL_RenderDebugText(renderer, 10, 10, "Hello world!");
        r.RenderPresent();// Render the screen
    }

    // SHUTDOWN
    r.Quit();

    // Testing edits
    return 0;
}
