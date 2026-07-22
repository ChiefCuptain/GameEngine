#include "pch.h"
#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "MathUtil.h"
#include "Engine.h"


#include <cmath>

void Enemy::Update(float dt)
{
    Player* player = m_scene->GetActorByName<Player>("Player");
    if (player)
    {
        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * nu::RadToDeg);
        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::DegToRad);
        AddVelocity(forward * m_speed * dt);

        if ((m_velocity.x > 0 && GetTransform().position.x > player->GetTransform().position.x) || (m_velocity.x < 0 && GetTransform().position.x < player->GetTransform().position.x))
        {
            m_velocity.x *= m_brake_multiplier;
        }
        if ((m_velocity.y > 0 && GetTransform().position.y > player->GetTransform().position.y) || (m_velocity.y < 0 && GetTransform().position.y < player->GetTransform().position.y))
        {
            m_velocity.y *= m_brake_multiplier;
        }

    }

    //float thrust = m_speed;

    //float rotate = 0.0f;

    //float angleToTarget;

    //if (m_target != nullptr)
    //{
    //    angleToTarget = m_transform.position.AngleTo(m_target->GetTransform().position);
    //    SetRotation(angleToTarget * nu::DegToRad);
    //    nu::Vector2 velocity{ 1, 0 };

    //    velocity = m_transform.position.DirectionTo(m_target->GetTransform().position) * thrust;

    //    AddVelocity(velocity * dt);
    //}

    



    Actor::Update(dt);
}

void Enemy::Draw(const nu::Renderer& r) const
{
    Actor::Draw(r);
}
