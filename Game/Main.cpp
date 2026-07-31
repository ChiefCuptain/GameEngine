#include "EvilSpaceGame.h"
#include <vector>
#include <map>

int main()
{

    // INITIALIZATION
    nu::Engine::Get().Initialize();
    EvilSpaceGame game;
    game.Initialize();


    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;

    audio->createSound("Assets/Audio/snd_jump.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("Assets/Audio/snd_timer_tick.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("Assets/Audio/snd_timer_pickup.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("Assets/Audio/snd_portal_enter.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("Assets/Audio/snd_evil_heliblo.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    
    // MAIN LOOP
    bool quit = false;



    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // UPDATE
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        // Engine
        nu::Engine::Get().Update();
        audio->update();

        float dt = nu::Engine::Get().GetTime().GetDeltaTime();

        // Game
        game.Update(dt);

        //if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        //{
        //    audio->playSound(sounds.at(0), nullptr, false, nullptr);
        //}
        //if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2))
        //{
        //    audio->playSound(sounds.at(1), nullptr, false, nullptr);
        //}
        //if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_3))
        //{
        //    audio->playSound(sounds.at(2), nullptr, false, nullptr);
        //}
        //if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_4))
        //{
        //    audio->playSound(sounds.at(3), nullptr, false, nullptr);
        //}
        //if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_5))
        //{
        //    audio->playSound(sounds.at(4), nullptr, false, nullptr);
        //}




        // RENDER
        nu::Engine::Get().GetRenderer().SetColor(0, 0, 0); // Set render draw color to black
        nu::Engine::Get().GetRenderer().Clear(); // Clear the renderer

        game.Draw(nu::Engine::Get().GetRenderer());

        nu::Engine::Get().GetRenderer().RenderPresent();// Render the screen
    }

    // SHUTDOWN
    nu::Engine::Get().Quit();

    // Testing edits
    return 0;
}
