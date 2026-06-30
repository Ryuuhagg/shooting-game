#include"EnemyBullet.h"
#include "DxLib.h"
#include <algorithm>
using namespace std;

EnemyBullet::EnemyBullet() : x(0), y(0), vx(0), vy(0), isActive(false) {}

void EnemyBullet::Init(float startX, float startY, float dirX, float dirY, float speed, EnemyBulletType bulletType)
{
	x = startX;
	y = startY;

	type = bulletType;

	switch (type)
	{
	case EnemyBulletType::Normal:
		radius = 6.0f;
		break;

	case EnemyBulletType::Fast:
		radius = 4.0f;
		speed *= 1.5f;
		break;

	case EnemyBulletType::Big:
		radius = 12.0f;
		speed *= 0.7f;
		break;

	case EnemyBulletType::Slow:
		radius = 8.0f;
		speed *= 0.5f;
		break;
	case EnemyBulletType::Homing:
		radius = 4.0f;
		speed *= 0.8f;
		break;
	}

	float len = sqrt(dirX * dirX + dirY * dirY);
	vx = dirX / len * speed;
	vy = dirY / len * speed;

	isActive = true;
}

void EnemyBullet::Update(float playerX, float playerY)
{
	if (type == EnemyBulletType::Homing)
	{
		float dy = playerY - y;

		float targetVy = 0.0f;

		if (dy > 0)
		{
			targetVy = 3.0f;
		}
		else if (dy < 0)
		{
			targetVy = -3.0f;
		}

		float homingPower = 0.05f;
		vy += (targetVy - vy) * homingPower;
	}

	x += vx;
	y += vy;
}

void EnemyBullet::Draw(int offsetX, int offsetY) const
{
	DrawCircle(
		(int)x + offsetX,
		(int)y + offsetY,
		(int)radius,
		GetColor(255, 120, 0),
		TRUE
	);
}