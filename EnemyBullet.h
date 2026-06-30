#pragma once
#include"Constant.h"

#pragma region “G’eŽí—Þ
enum class EnemyBulletType {
	Normal,
	Fast,
	Big,
	Slow,
	Homing
};

#pragma endregion
#pragma region “G’eClass
class EnemyBullet {
private:
	EnemyBulletType type;
	float x, y;
	float vx, vy;
	float radius = 6.0f;
	bool isActive = false;
public:
	EnemyBullet();
	void Init(float startX, float startY, float dirX, float dirY, float speed, EnemyBulletType bulletType);

	void Update(float playerX, float playerY);
	void Draw(int offsetX, int offsetY)const;

	void Deactivate() { isActive = false; }
	bool IsActive() const { return isActive; }

	bool IsHit(float px, float py, float pr) const {
		float dx = x - px;
		float dy = y - py;
		return dx * dx + dy * dy <= (radius + pr) * (radius + pr);
	}

	bool IsOutOfScreen() const {
		return x < -radius || x > WIDTH + radius || y < -radius || y > HEIGHT + radius;
	}

	float GetX() const { return x; }
	float GetY() const { return y; }
};
#pragma endregion