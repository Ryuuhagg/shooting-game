#include"DxLib.h"
#include"Bullet.h"
#include<vector>
#include<memory>

using namespace std;

void Bullet::Init(float startX, float startY, float spd, int atk) {
	x = startX;
	y = startY;
	speed = spd;
	damage = atk;
	isActive = true;
	trail.clear();
}

void Bullet::Move() {
	if (trail.size() >= trailLength)
	{
		for (int i = 1; i < trailLength; i++)
			trail[i - 1] = trail[i];

		trail.back() = { (int)x, (int)y };
	}
	else
	{
		trail.push_back({ (int)x, (int)y });
	}
	x += speed;
}

void Bullet::Draw(int offsetX, int offsetY) const {
	for (int i = 0; i < trail.size(); i++) {

		float ratio = (float)i / trail.size();
		int alpha = (int)(150 * ratio);

		SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);

		DrawCircle(
			trail[i].x + offsetX,
			trail[i].y + offsetY,
			radius * 0.7f,
			GetColor(0, 100, 255),
			TRUE
		);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	Circle c;
	c.center = { (int)x + offsetX, (int)y + offsetY };
	c.radius = radius;

	FillCircle(c);
}