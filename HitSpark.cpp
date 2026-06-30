#include"HitSpark.h"
#include"DxLib.h"
#include <cmath>

void HitSpark::Init(float x, float y) {
	for (int i = 0; i < PARTICLE_COUNT; i++) {
		float angle = (float)(rand() % 360) * DX_PI / 180.0f;
		float speed = (float)(rand() % 3 + 2);

		particles[i].x = x;
		particles[i].y = y;
		particles[i].vx = cos(angle) * speed;
		particles[i].vy = sin(angle) * speed;
		particles[i].life = rand() % 8 + 8;
		particles[i].color = GetColor(255, 200 + rand() % 55, 80);
	}

	isActive = true;
}

void HitSpark::Update() {
	if (!isActive) return;

	for (auto& p : particles) {
		if (p.life <= 0) continue;

		p.x += p.vx;
		p.y += p.vy;

		p.vx *= 0.85f;
		p.vy *= 0.85f;

		p.life--;
	}

	if (IsDead()) {
		isActive = false;
	}
}

void HitSpark::Draw(int offsetX, int offsetY) const {
	if (!isActive) return;

	SetDrawBlendMode(DX_BLENDMODE_ADD, 180);

	for (const auto& p : particles) {
		if (p.life <= 0) continue;

		DrawCircle(
			(int)p.x + offsetX,
			(int)p.y + offsetY,
			2,
			p.color,
			TRUE
		);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool HitSpark::IsDead() const {
	for (const auto& p : particles) {
		if (p.life > 0) return false;
	}

	return true;
}