#include "Ball.h"
#include "DxLib.h"

namespace
{
	constexpr float kSpeedX = 4.0f;
	constexpr float kGravity = 0.8f;

	constexpr float kStartX = 8.0f;
	constexpr float kStartY = 120.0f;

	constexpr float kFieldY = 480.0f;
}

Ball::Ball(unsigned int color):
	m_color(color)
{
}

Ball::~Ball()
{
}

void Ball::init()
{
	m_pos.x = kStartX;
	m_pos.y = kStartY;

	m_vec.x = kSpeedX;
	m_vec.y = 0.0f;
}

void Ball::update()
{
	m_pos += m_vec;

	m_vec.y += kGravity;
	if (m_vec.y >= 0.0f && m_pos.y > kFieldY)
	{
		m_vec.y *= -1.0f;
	}
}

void Ball::draw()
{
	DrawCircle(m_pos.x, m_pos.y, 8.0f, m_color, true);
}
