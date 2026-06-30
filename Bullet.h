#pragma once
#include<vector>
#include"Constant.h"
using namespace std;
#pragma region ’eClass
class Bullet {
private:
	float x, y;
	float speed;
	float radius;
	int damage;
	vector<Vector2> trail;
	bool isActive = false;
public:
	Bullet(float startX, float startY, float spd, int atk) : x(startX), y(startY), speed(spd), radius(5), damage(atk) {}
	Bullet() : x(0), y(0), speed(0), radius(5), damage(1), isActive(false) {}
	void Init(float startX, float startY, float spd, int atk);
	static const int trailLength = 10;

	void Move();
	void Draw(int offsetX = 0, int offsetY = 0) const;
	void Deactivate() {
		isActive = false;
	}

	bool IsActive() const { return isActive; }
	bool IsHit(float px, float py, float pr) const {
		float dx = x - px;
		float dy = y - py;
		return dx * dx + dy * dy <= (radius + pr) * (radius + pr);
	}
	bool IsOutOfScreen() const {
		return x > WIDTH;
	}
	float GetX() const { return x; }
	float GetY() const { return y; }
	int GetDamage() const { return damage; }
	float GetRadius() const { return radius; }
};
#pragma endregion