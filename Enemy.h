#pragma once
#pragma region “GClass
class Game;
class Enemy {
protected:
	float x, y;
	float radius;
	bool isDead = false;
	int hp;
	float speed;
	bool isActive = false;

	void InitBase(float startX, float startY, float r, int health, float spd);
	
public:
	Enemy():x(0), y(0), radius(0), hp(0), speed(0) {}
	Enemy(float startX, float startY, float r, int health, float speed) : x(startX), y(startY), radius(r), hp(health), speed(speed) {}
	virtual ~Enemy() = default;

	virtual void Move() = 0;
	virtual void Draw(int offsetX, int offsetY) const = 0;
	virtual void OnDeath(Game& game) {}

	void Deactivate() {
		isActive = false;
		isDead = false;
	}
	bool IsActive() const {
		return isActive;
	}

	void Damage(int d) {
		hp -= d;
		if (hp <= 0) {
			isDead = true;
		}
	}

	void Kill() { isDead = true; }
	bool IsDead() const { return isDead; }
	bool IsOutOfScreen() const { return x < -radius; }

	int GetHP() const { return hp; }
	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetRadius() const { return radius; }
};
#pragma endregion
#pragma region “G”h¶ƒNƒ‰ƒX
class StraightEnemy : public Enemy {
public:
	StraightEnemy() : Enemy() {}
	StraightEnemy(float startX, float startY, float hp, float spd) : Enemy(startX, startY, 12.0f, hp, spd) {}
	void Init(float startX, float startY, int hp, float spd);
	void Move() override;
	void Draw(int offsetX, int offsetY) const override;
	void OnDeath(Game& game) override;
};
class WaveEnemy : public Enemy {
private:
	float baseY;
	float angle = 0;
public:
	WaveEnemy() : Enemy(), baseY(0), angle(0) {}
	WaveEnemy(float startX, float startY, int hp, float spd) : Enemy(startX, startY, 12.0f, hp, spd), baseY(startY) {}
	void Init(float startX, float startY, int hp, float spd);
	void Move() override;
	void Draw(int offsetX, int offsetY) const override;
	void OnDeath(Game& game) override;
};
class ZigZagEnemy : public Enemy {
	int changeTimer;
	int changeInterval;
	float speedY;
public:
	ZigZagEnemy() : Enemy(), changeTimer(0), changeInterval(40), speedY(0) {}
	ZigZagEnemy(float startX, float startY, int hp, float spd) : Enemy(startX, startY, 12.0f, hp, spd), changeTimer(0), changeInterval(40), speedY(speed / 2) {}
	void Init(float startX, float startY, int hp, float spd);
	void Move() override;
	void Draw(int offsetX, int offsetY)const override;
	void OnDeath(Game& game) override;
};
class ShotEnemy :public Enemy {
private:
	Game* game = nullptr;
	int interval;
	int timer;
	int attackTimer;
	int life;
public:
	ShotEnemy() : Enemy(), interval(40), timer(0), attackTimer(0), life(3000) {}
	ShotEnemy(float startX, float startY, Game& g, float hp) : Enemy(startX, startY, 12.0f, hp, 3.0f), interval(40), timer(0), attackTimer(0), game(&g), life(3000) {}
	void Init(float startX, float startY, Game& g, int hp);
	void Move()override;
	void Draw(int offsetX, int offsetY)const override;
	void OnDeath(Game& game)override;
};
class StalkerEnemy :public Enemy {
private:
	Game* game = nullptr;
public:
	StalkerEnemy() : Enemy() {}
	StalkerEnemy(float startX, float startY, Game& g, float hp, float spd):Enemy(startX, startY, 12.0f, hp, 3.0f), game(&g) {}
	void Init(float startX, float startY, Game& g, int hp, float spd);
	void Move()override;
	void Draw(int offsetX, int offsetY)const override;
	void OnDeath(Game& game)override;
};
class BigEnemy : public Enemy {
public:
	BigEnemy() : Enemy(){}
	void Init(float startX, float startY, Game& g, int hp, float spd);
	void Move()override;
	void Draw(int offsetX, int offsetY)const override;
	void OnDeath(Game& game)override;
};
#pragma endregion
#pragma region BossƒNƒ‰ƒX
class Boss : public Enemy {
private:
	int maxHp;
	int attackTimer = 0;
	int attackCount = 0;
	Game* game = nullptr;
public:
	Boss() : Enemy(), maxHp(0), attackTimer(0), attackCount(0) {}
	Boss(float startX, float startY, Game& g, float hp) : Enemy(startX, startY, 40.0f, hp, 5.0f), game(&g), maxHp(hp) {}
	void Init(float startX, float startY, Game& g, int hp);
	void Move()override;
	void Draw(int offsetX, int offsetY)const override;
	void OnDeath(Game& game) override;
};
#pragma endregion