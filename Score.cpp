#include"Score.h"
#include"DxLib.h"

void Score::Add(int value) {
	score += value;
}

void Score::Draw()const {
	DrawFormatString(20, 20, GetColor(255, 255, 255),
		"SCORE : %07d", score);
}

void ScorePop::Init(float px, float py, int val)
{
	x = px;
	y = py;
	value = val;

	life = 60;
	maxLife = life;

	active = true;
}

void ScorePop::Update() {
	if (!active) return;

	y -= 1.0f;
	life--;

	if (life <= 0)
		active = false;
}

void ScorePop::Draw(int offsetX, int offsetY) const {
	float ratio = (float)life / maxLife;
	int alpha = (int)(255 * ratio);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawFormatString(
		(int)x + offsetX,
		(int)y + offsetY,
		GetColor(0, 255, 0),
		"+%d",
		value
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}