#include"DxLib.h"
#include"Enemy.h"
#include"Game.h"
#include <vector>
#pragma region ìGäÓëb
void Enemy::InitBase(float startX, float startY, float r, int health, float spd) {
	x = startX;
	y = startY;
	radius = r;
	hp = health;
	speed = spd;
	isDead = false;
	isActive = true;
}
#pragma endregion
#pragma region ìGíËã`
void StraightEnemy::Init(float startX, float startY, int hp, float spd) {
	InitBase(startX, startY, 12.0f, hp, spd);
}
void StraightEnemy::Move() {
	x -= speed;
}
void StraightEnemy::Draw(int offsetX, int offsetY)const {
	int left = (int)(x - radius) + offsetX;
	int top = (int)(y - radius) + offsetY;
	int right = (int)(x + radius) + offsetX;
	int bottom = (int)(y + radius) + offsetY;

	DrawBox(
		left,
		top,
		right,
		bottom,
		GetColor(255, 0, 0),
		TRUE
	);
}
void StraightEnemy::OnDeath(Game& game)
{
	if (rand() % 5 == 0)
		game.AddPowerUp(x, y);
	game.AddExplosion(x, y);
	game.AddScore(100, x, y);
}
void WaveEnemy::Init(float startX, float startY, int hp, float spd) {
	InitBase(startX, startY, 12.0f, hp, spd);
	baseY = startY;
	angle = 0;
}
void WaveEnemy::Move() {
	x -= speed;
	angle += 0.1f;
	y = baseY + sin(angle) * 60;
}
void WaveEnemy::Draw(int offsetX, int offsetY)const {
	int left = (int)(x - radius) + offsetX;
	int top = (int)(y - radius) + offsetY;
	int right = (int)(x + radius) + offsetX;
	int bottom = (int)(y + radius) + offsetY;

	DrawBox(
		left,
		top,
		right,
		bottom,
		GetColor(0, 255, 255),
		TRUE
	);
}
void WaveEnemy::OnDeath(Game& game) {
	if (rand() % 5 == 0)
		game.AddPowerUp(x, y);
	game.AddExplosion(x, y);
	game.AddScore(200, x, y);
}
void ZigZagEnemy::Init(float startX, float startY, int hp, float spd) {
	InitBase(startX, startY, 12.0f, hp, spd);
	changeTimer = 0;
	changeInterval = 40;
	speedY = speed / 2;
}
void ZigZagEnemy::Move() {
	changeTimer++;
	x -= speed;
	y += speedY;
	if (changeTimer >= changeInterval) {
		speedY *= -1;
		changeTimer = 0;
		changeInterval = rand() % 60 + 20;
	}
}
void ZigZagEnemy::Draw(int offsetX, int offsetY)const {
	int left = (int)(x - radius) + offsetX;
	int top = (int)(y - radius) + offsetY;
	int right = (int)(x + radius) + offsetX;
	int bottom = (int)(y + radius) + offsetY;

	DrawBox(
		left,
		top,
		right,
		bottom,
		GetColor(0, 255, 100),
		TRUE
	);
}
void ZigZagEnemy::OnDeath(Game& game) {
	if (rand() % 5 == 0)
		game.AddPowerUp(x, y);
	game.AddExplosion(x, y);
	game.AddScore(400, x, y);
}
void ShotEnemy::Init(float startX, float startY, Game& g, int hp) {
	InitBase(startX, startY, 12.0f, hp, 3.0f);
	game = &g;
	interval = 40;
	timer = 0;
	attackTimer = 0;
	life = (int)(5 + (g.GetPhase() % 10));
}
void ShotEnemy::Move() {
	if (life < 0) {
		isActive = false;
	}
	if (x > WIDTH - 200)
		x -= speed;
	else {
		timer++;
		y += speed;
	}

	attackTimer++;
	if (timer >= interval) {
		speed *= -1;
		timer = 0;
		interval = rand() % 60 + 20;
	}
	//íeî≠éÀ
	if (attackTimer >= 90 - (game->GetPhase() % 10)) {
		if(game->GetPhase() < 10)
			game->AddEnemyBullet(x, y, -1, 0, 12,EnemyBulletType::Normal);
		else 
			game->AddEnemyBullet(x, y, -1, 0, 12, EnemyBulletType::Homing);
		life--;
		attackTimer = 0;
	}
}
void ShotEnemy::Draw(int offsetX, int offsetY)const {
	int left = (int)(x - radius) + offsetX;
	int top = (int)(y - radius) + offsetY;
	int right = (int)(x + radius) + offsetX;
	int bottom = (int)(y + radius) + offsetY;

	DrawBox(
		left,
		top,
		right,
		bottom,
		GetColor(100, 255, 100),
		TRUE
	);
}
void ShotEnemy::OnDeath(Game& game) {
	if (rand() % 5 == 0)
		game.AddPowerUp(x, y);
	game.AddExplosion(x, y);
	game.AddScore(500, x, y);
}

void StalkerEnemy::Init(float startX, float startY, Game& g, int hp, float spd) {
	InitBase(startX, startY, 12.0f, hp, spd);
	game = &g;
}
void StalkerEnemy::Move() {
	float pY = game->GetPlayerY();

	y += (pY - y) * 0.05f; 
	x -= speed;           
}
void StalkerEnemy::Draw(int offsetX, int offsetY)const {
	int left = (int)(x - radius) + offsetX;
	int top = (int)(y - radius) + offsetY;
	int right = (int)(x + radius) + offsetX;
	int bottom = (int)(y + radius) + offsetY;

	DrawBox(
		left,
		top,
		right,
		bottom,
		GetColor(255, 100, 255),
		TRUE
	);
}
void StalkerEnemy::OnDeath(Game& game) {
	if (rand() % 5 == 0)
		game.AddPowerUp(x, y);
	game.AddExplosion(x, y);
	game.AddScore(300, x, y);
}

void BigEnemy::Init(float startX, float startY, Game& g, int hp, float spd) {
	InitBase(startX, startY, 12.0f, hp, spd);
	hp *= 3;
	radius *= 2;
}
void BigEnemy::Move() {
	x -= speed / 2;
}
void BigEnemy::Draw(int offsetX, int offsetY)const {
	int left = (int)(x - radius) + offsetX;
	int top = (int)(y - radius) + offsetY;
	int right = (int)(x + radius) + offsetX;
	int bottom = (int)(y + radius) + offsetY;

	DrawBox(
		left,
		top,
		right,
		bottom,
		GetColor(255, 255, 100),
		TRUE
	);
}
void BigEnemy::OnDeath(Game& game) {
	if (rand() % 5 == 0)
		game.AddPowerUp(x, y);
	game.AddExplosion(x, y);
	game.AddScore(300, x, y);
}

#pragma endregion
#pragma region BossíËã`
void Boss::Init(float startX, float startY, Game& g, int hp) {
	InitBase(startX, startY, 40.0f, hp, 5.0f);
	game = &g;
	maxHp = hp;
	attackTimer = 0;
	attackCount = 0;
}
void Boss::Move() {
	if (x > WIDTH - 150)
		x -= speed;
	else
	{
		y += sin(GetNowCount() * 0.002f) * 2.0f;
	}

	attackTimer++;

	int interval = max(35, 70 - game->GetPhase() * 2);

	if (attackTimer >= interval) {
		attackCount++;

		if (attackCount % 3 == 0)
		{
			float dx = game->GetPlayerX() - x;
			float dy = game->GetPlayerY() - y;
			float len = sqrt(dx * dx + dy * dy);

			if (len > 0)
			{
				dx /= len;
				dy /= len;

				game->AddEnemyBullet(x, y, dx, dy, 7, EnemyBulletType::Homing);
				game->AddEnemyBullet(x, y - 18, dx, dy, 7, EnemyBulletType::Homing);
				game->AddEnemyBullet(x, y + 18, dx, dy, 7, EnemyBulletType::Homing);
			}
		}
		else
		{
			const int bulletCount = 10 + game->GetPhase();

			float rotate = attackCount * 0.25f;

			for (int i = 0; i < bulletCount; i++)
			{
				float angle = i * DX_PI * 2 / bulletCount + rotate;

				float dirX = cos(angle);
				float dirY = sin(angle);

				EnemyBulletType type = EnemyBulletType::Fast;

				if (attackCount % 2 == 0)
				{
					type = EnemyBulletType::Slow;
				}

				game->AddEnemyBullet(x, y, dirX, dirY, 6, type);
			}
		}

		attackTimer = 0;
	}
}
void Boss::Draw(int offsetX, int offsetY)const {
	int left = (int)(x - radius) + offsetX;
	int top = (int)(y - radius) + offsetY;
	int right = (int)(x + radius) + offsetX;
	int bottom = (int)(y + radius) + offsetY;
	//ñ{ëÃ
	DrawBox(
		left,
		top,
		right,
		bottom,
		GetColor(255, 100, 255),
		TRUE
	);

	// HPÉoÅ[
	int barWidth = 100;
	int hpWidth = (int)((float)hp / maxHp * barWidth);

	DrawBox((int)x - 50, (int)y - 60,
		(int)x - 50 + barWidth, (int)y - 50,
		GetColor(100, 100, 100), TRUE);

	DrawBox((int)x - 50, (int)y - 60,
		(int)x - 50 + hpWidth, (int)y - 50,
		GetColor(255, 0, 0), TRUE);
}
void Boss::OnDeath(Game& game) {
	for (int i = 0; i < 10; i++)
	{
		game.AddExplosion(x + rand() % 40 - 20, y + rand() % 40 - 20);
	}

	game.AddScore(5000, x, y);

	game.NextPhase();

	game.bossDeath();
}
#pragma endregion
