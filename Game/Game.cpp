#include "Engine.h"

struct Transform
{
    nu::Vector2 position;
    float rotation;
    float scale;
};

class Actor
{
public:
    Actor(const Transform& transform) : m_transform{ transform } {}

    void Update(float dt)
    {
        m_transform.position += (m_velocity * dt);

        m_transform.position.x = nu::math::Clamp(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = nu::math::Clamp(0.0f, 1080.0f, m_transform.position.y);
    }

    void Draw(const nu::Renderer& r) const
    {
        r.SetColor(255, 255, 127);
        r.RenderRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale, true);
    }

    const Transform& GetTransform() const { return m_transform; }

    void SetPosition(const nu::Vector2& position) { m_transform.position = position; }

    void SetRotation(float rotation) { m_transform.rotation = rotation; }

    void SetScale(float scale) { m_transform.scale = scale; }

    nu::Vector2 GetVelocity() const { return m_velocity; }
    void SetVelocity(const nu::Vector2& velocity) { m_velocity = velocity; }

protected:
    Transform m_transform;
    nu::Vector2 m_velocity{ 0.0f, 0.0f };
};

int main()
{
    // INITIALIZATION
    nu::Renderer r;
    r.Initialize("Game Engine", 1920, 1080);

    nu::Input input;
    input.Initialize();
    nu::GameTime time;
    Actor player{ Transform{nu::Vector2{960.0f, 540.0f}, 0.0f, 50.0f} };
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

        input.Update();
        time.Tick();

        if (input.GetMouseDown(nu::Input::Left))
        {

            if (points.empty())
            {
                points.push_back(input.GetMousePosition());
            }
            else
            {
                nu::Vector2 v = points.back() - input.GetMousePosition();

                if (v.Length() > 10.0f)
                {
                    points.push_back(input.GetMousePosition());
                }
            }
            
        }

        if (input.GetMousePressed(nu::Input::Right))
        {
            if (!points.empty()) { points.pop_back(); }
        }

        //if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "Q pressed\n";
        //if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "Q held\n";
        //if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "Q released\n";
        //if (input.GetMousePressed(nu::Input::Left)) std::cout << "Left mouse pressed\n";
        //if (input.GetMouseDown(nu::Input::Left)) std::cout << "Left mouse held\n";
        //if (input.GetMouseReleased(nu::Input::Left)) std::cout << "Left mouse released\n";

        nu::Vector2 mousePosition;
        nu::Vector2 vel{ 0.0f, 0.0f };
        float cursorSpeed = 175.0f;

        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if (input.GetMousePressed(nu::Input::Left))
        {
            points.push_back(input.GetMousePosition());
        }

        nu::Vector2 force{ 0, 0 };

        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -cursorSpeed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = cursorSpeed;
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -cursorSpeed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = cursorSpeed;
        if (input.GetKeyDown(SDL_SCANCODE_LSHIFT)) force *= 2.0f;

        player.SetVelocity(player.GetVelocity() + force * time.GetDeltaTime());
        player.Update(time.GetDeltaTime());

     /*   vel += (force * time.GetDeltaTime());
        */


        // RENDER
        r.SetColor(0,0,0); // Set render draw color to black
        r.Clear(); // Clear the renderer

        r.SetColor(255, 255, 255);
        for (size_t i = 0; i < points.size(); i++) // Render 300 points
        {
            if (i == 0)
            {
                continue;
            }
            else
            {
                r.RenderLine(points.at(i - 1).x, points.at(i - 1).y, points.at(i).x, points.at(i).y);
            }
        }

        player.Draw(r);

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
