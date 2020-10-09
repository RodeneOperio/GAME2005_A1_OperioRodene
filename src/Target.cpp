#include "Target.h"
#include "TextureManager.h"


Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/ThermalDetonator.png","TD");

	const auto size = TextureManager::Instance()->getTextureSize("TD");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(0, 500.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("TD", x, y, 0, 255, true);
}

void Target::update()
{
	m_move();
	m_checkBounds();
}

void Target::clean()
{
}

void Target::m_move()
{
	float deltaTime = 1.0f / 60.0f;
	getRigidBody()->acceleration = glm::vec2(0, 9.8);
	getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;

	if (!isGravityEnabled)
	{
		getRigidBody()->velocity.y = 0;
	}
	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void Target::m_checkBounds()
{
}

void Target::m_reset()
{
}

void Target::doThrow()
{
	getTransform()->position = throwPosition;
	getRigidBody()->velocity = throwSpeed;
}

