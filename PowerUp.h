#pragma once

#include"Player.h"

#pragma region パワーアップアイテムクラス
class PowerUp {
protected:
	float x, y;
	float speed;
	bool dead = false;
	bool active = false;
public:
	PowerUp(float x, float y) :x(x), y(y), speed(2) {}
	virtual ~PowerUp() = default;

	virtual void Update() { x -= speed; }
	virtual void Draw(int offsetX, int offsetY)const = 0;

	virtual void Apply(Player& player) = 0;

	float GetX()const { return x; }
	float GetY()const { return y; }

	void Kill() { dead = true; }
	bool IsDead()const { return dead; }
};
#pragma endregion

#pragma region パワーアップタイプ
enum class PowerUpType
{
	Heal,
	Rapid,
	Barrier,
	AddBullet,
	AddPower
};
#pragma endregion

#pragma region パワーアップ派生クラス
class Heal : public PowerUp {
public:
	Heal(float x, float y) :PowerUp(x, y) {}
	void Draw(int offsetX, int offsetY) const override;

	void Apply(Player& player)override;
};
class Rapid : public PowerUp {
public:
	Rapid(float x, float y) :PowerUp(x, y) {}
	void Draw(int offsetX, int offsetY) const override;

	void Apply(Player& player)override;
};
class Barrier : public PowerUp {
public:
	Barrier(float x, float y) :PowerUp(x, y) {}
	void Draw(int offsetX, int offsetY) const override;

	void Apply(Player& player)override;
};
class AddBullet : public PowerUp {
public:
	AddBullet(float x, float y) : PowerUp(x, y) {}
	void Draw(int offsetX, int offsetY)const override;

	void Apply(Player& player)override;
};
class AddPower : public PowerUp {
public:
	AddPower(float x, float y) : PowerUp(x, y) {}
	void Draw(int offsetX, int offsetY)const override;

	void Apply(Player& player)override;
};
#pragma endregion