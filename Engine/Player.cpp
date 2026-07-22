#include "pch.h"
#include "Player.h"
#include "Renderer.h"
#include "MathUtil.h"
#include "Engine.h"

void Player::Update(float dt)
{
    //nu::Vector2 force{ 0, 0 };
    float thrust = 0.0f;

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 180.0f;

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LSHIFT)) 
    {
        thrust *= 2.0f; 
        rotate *= 2.0f; 
    }
    else if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LCTRL))
    {
        thrust *= 0.5f;
        rotate *= 0.5f;
    }


    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 velocity{ 1, 0 };

    velocity = velocity.Rotate(m_transform.rotation * nu::DegToRad) * thrust;

    AddVelocity(velocity * dt);

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) SetVelocity(GetVelocity() * m_brake_multiplier);

    //SetVelocity(GetVelocity() + force * dt);
    //SetRotation(GetTransform().position.Normalized().Angle() * nu::RadToDeg);
    Actor::Update(dt);
}

void Player::Draw(const nu::Renderer& r) const
{
	Actor::Draw(r);
}
