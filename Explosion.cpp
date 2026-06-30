#include"Explosion.h"
#include"DxLib.h"
#include<cmath>
void Explosion::Init(float px, float py) {
	centerX = px;
	centerY = py;
	flashLife = 10;

	for (int i = 0; i < PARTICLE_COUNT; i++) {
		float angle = (float)(rand() % 360) * DX_PI / 180.0f;
		float speed = (float)(rand() % 5 + 2);

		particles[i].x = px;
		particles[i].y = py;
		particles[i].vx = cos(angle) * speed;
		particles[i].vy = sin(angle) * speed;
		particles[i].life = rand() % 20 + 20;
		particles[i].color = GetColor(255, 100 + rand() % 155, 0);

	}

	isActive = true;
}

void Explosion::Update() {
	if (!isActive) return;

	if (flashLife > 0)
		flashLife--;

	for (auto& p : particles) {
		p.x += p.vx;
		p.y += p.vy;

		p.vx *= 0.95f;
		p.vy *= 0.95f;

		p.life--;
	}

	if (IsDead()) {
		isActive = false;
	}
}

void Explosion::Draw(int offsetX, int offsetY) const {
	if (!isActive) return;
	if (flashLife > 0)
	{
		int alpha = flashLife * 25;
		SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);

		DrawCircle(
			(int)centerX + offsetX,
			(int)centerY + offsetY,
			25,
			GetColor(255, 255, 255),
			TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ADD, 200);

	for (const auto& p : particles)
	{
		if (p.life > 0)
		{
			DrawCircle((int)p.x + offsetX, (int)p.y + offsetY, 3, p.color, TRUE);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}