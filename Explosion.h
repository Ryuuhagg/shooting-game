#pragma region ”š”­Class
class Explosion {
private:
	float centerX, centerY;
	int flashLife;
	struct Particle {
		float x, y;
		float vx, vy;
		int life;
		int color;
	};
	static const int PARTICLE_COUNT = 40;
	Particle particles[PARTICLE_COUNT];
	bool isActive = false;
public:
	Explosion() :centerX(0.0f), centerY(0.0f), flashLife(0) {}

	void Init(float px, float py);

	void Update();

	void Draw(int offsetX = 0, int offsetY = 0) const;

	bool IsDead() const {
		for (const auto& p : particles)
			if (p.life > 0) return false;

		return true;
	}
	bool IsActive() const { return isActive; }
};
#pragma endregion