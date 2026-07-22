#pragma once

#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc
{
	float speed;
};

class Player : public nu::Actor
{
public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) :
		Actor{ playerDesc },
		m_speed{ playerDesc.speed}
	{ }

	Player(const nu::Transform& transform) : Actor{ transform } {}
	Player(const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model } {}

	void Update(float dt) override;

	void Draw(const class nu::Renderer& r) const override;
private:
	int m_ammo = 0;
	float m_speed = 175.0f;
	float m_brake_multiplier = 0.97f;
};