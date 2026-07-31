#include "pch.h"
#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "MathUtil.h"
#include "Engine.h"


#include <cmath>
#include "Bullet.h"
#include "Assets.h"

void Enemy::Update(float dt)
{
    m_fire_timer += dt;

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
            m_velocity.x *= (1.0f / (1.0f + m_brake_speed * dt));
        }
        if ((m_velocity.y > 0 && GetTransform().position.y > player->GetTransform().position.y) || (m_velocity.y < 0 && GetTransform().position.y < player->GetTransform().position.y))
        {
            m_velocity.y *= (1.0f / (1.0f + m_brake_speed * dt));
        }

        if (m_fire_timer > m_fire_cooldown)
        {
            m_fire_timer = 0.0f;
            BulletDesc bulletDesc;
            bulletDesc.name = "Bullet";
            bulletDesc.tag = "Enemy_Bullet";
            bulletDesc.model = assets::bulletModel;
            bulletDesc.transform = m_transform;
            bulletDesc.transform.scale = 7.0f;
            bulletDesc.lifespan = 1.5f;
            bulletDesc.speed = 400.0f;

            Bullet* bullet = new Bullet{ bulletDesc };
            m_scene->AddActor(bullet);

            nu::Engine::Get().GetAudio().PlaySound("enemy_shoot");

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

void Enemy::OnCollision(Actor* other)
{
    if (other->GetTag() == "Player_Bullet")
    {
        nu::Engine::Get().GetAudio().PlaySound("explosion");
        SetDestroyed();
        other->SetDestroyed();
    }
}

