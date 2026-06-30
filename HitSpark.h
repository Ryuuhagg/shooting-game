#pragma once
class HitSpark {
private:
	struct Particle {
		float x, y;
		float vx, vy;
		int life;
		int color;
	};

	static const int PARTICLE_COUNT = 8;
	Particle particles[PARTICLE_COUNT];
	bool isActive = false;

public:
	HitSpark() {}

	void Init(float x, float y);
	void Update();
	void Draw(int offsetX = 0, int offsetY = 0) const;

	bool IsActive() const { return isActive; }
	bool IsDead() const;
};