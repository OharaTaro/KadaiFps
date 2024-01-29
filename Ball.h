#pragma once
#include "Vec2.h"

class Ball
{
public:
	Ball(unsigned int color);
	virtual ~Ball();

	void init();
	void update();
	void draw();

private:
	unsigned int m_color;
	Vec2	m_pos;
	Vec2	m_vec;
};

