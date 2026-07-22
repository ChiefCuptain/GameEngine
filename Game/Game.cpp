#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include <vector>

int main()
{
    // INITIALIZATION
    nu::Engine::Get().Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;

    audio->createSound("snd_jump.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snd_timer_tick.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snd_timer_pickup.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snd_portal_enter.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snd_evil_heliblo.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    // Mesh / Model

    nu::Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.velocity = nu::Vector2{ 0.0f };
    playerDesc.transform = nu::Transform{ nu::Vector2{960.0f, 540.0f}, 0.0f, 25.0f };
    playerDesc.speed = 175.0f;

    Player* player = new Player{playerDesc};
    scene.AddActor(player);

    EnemyDesc enemyDesc;
    enemyDesc.name = "Enemy";
    enemyDesc.model = assets::playerModel;
    enemyDesc.velocity = nu::Vector2{ 0.0f };
    enemyDesc.speed = 125.0f;

    for (int i = 0; i < 10; ++i)
    {
        enemyDesc.transform = nu::Transform{ nu::Vector2{nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWindowWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWindowHeight())}, 0.0f, 12.0f };
        Enemy* enemy = new Enemy{ enemyDesc };
        scene.AddActor(enemy);
    }
    

    nu::Vector2 position{ 960,540 };

    std::vector<nu::Vector2> points;

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

        nu::Engine::Get().Update();
        audio->update();

        float dt = nu::Engine::Get().GetTime().GetDeltaTime();

        scene.Update(dt);

        if (nu::Engine::Get().GetInput().GetMouseDown(nu::Input::Left))
        {

            if (points.empty())
            {
                points.push_back(nu::Engine::Get().GetInput().GetMousePosition());
            }
            else
            {
                nu::Vector2 v = points.back() - nu::Engine::Get().GetInput().GetMousePosition();

                if (v.Length() > 10.0f)
                {
                    points.push_back(nu::Engine::Get().GetInput().GetMousePosition());
                }
            }
            
        }

        if (nu::Engine::Get().GetInput().GetMousePressed(nu::Input::Right))
        {
            if (!points.empty()) { points.pop_back(); }
        }

        nu::Vector2 mousePosition;
        
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if (nu::Engine::Get().GetInput().GetMousePressed(nu::Input::Left))
        {
            points.push_back(nu::Engine::Get().GetInput().GetMousePosition());
        }

        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds.at(0), nullptr, false, nullptr);
        }
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds.at(1), nullptr, false, nullptr);
        }
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds.at(2), nullptr, false, nullptr);
        }
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds.at(3), nullptr, false, nullptr);
        }
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds.at(4), nullptr, false, nullptr);
        }
        

     /*   vel += (force * time.GetDeltaTime());
        */


        // RENDER
        nu::Engine::Get().GetRenderer().SetColor(0, 0, 0); // Set render draw color to black
        nu::Engine::Get().GetRenderer().Clear(); // Clear the renderer

        //nu::Engine::Get().GetRenderer().SetColor(255, 255, 255);
        //for (size_t i = 0; i < points.size(); i++) // Render 300 points
        //{
        //    if (i == 0)
        //    {
        //        continue;
        //    }
        //    else
        //    {
        //        nu::Engine::Get().GetRenderer().RenderLine(points.at(i - 1).x, points.at(i - 1).y, points.at(i).x, points.at(i).y);
        //    }
        //}

        scene.Draw(nu::Engine::Get().GetRenderer());

        nu::Engine::Get().GetRenderer().RenderPresent();// Render the screen
    }

    // SHUTDOWN
    nu::Engine::Get().Quit();

    // Testing edits
    return 0;
}
