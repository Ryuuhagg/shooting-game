#include"Player.h"

#pragma region プレイヤークラス関数定義
void Player::Move() {
	float dx = 0;
	float dy = 0;
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))    dy -= 1;
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))  dy += 1;
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))  dx -= 1;
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) dx += 1;
	//正規化
	if (dx != 0 || dy != 0) {
		float length = sqrt(dx * dx + dy * dy);
		dx /= length;
		dy /= length;
	}
	x += dx * speed;
	y += dy * speed;
	//画面外に出ない処理
	if (x < radius) x = radius;
	if (x > WIDTH - radius) x = WIDTH - radius;
	if (y < radius) y = radius;
	if (y > HEIGHT - radius) y = HEIGHT - radius;
	//無敵時間のタイマー
	if (invincibleTimer > 0)
		invincibleTimer--;
	//一定時間強化のタイマー
	if (bulletPowerTimer)
		bulletPowerTimer--;
}
void Player::Shoot() {
	if (shotTimer > 0) {
		shotTimer--;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && shotTimer <= 0) {
		if (powerLevel == 1)
		{
			bullets.Add(x + radius, y, 10, atk);
		}
		else if (powerLevel == 2)
		{
			bullets.Add(x + radius, y - 8, 10, atk);
			bullets.Add(x + radius, y + 8, 10, atk);
		}
		else
		{
			if (bulletPowerTimer > 0)
			{
				bullets.Add(x + radius, y - 20, 10, atk);
				bullets.Add(x + radius, y - 10, 10, atk);
				bullets.Add(x + radius, y, 10, atk);
				bullets.Add(x + radius, y + 10, 10, atk);
				bullets.Add(x + radius, y + 20, 10, atk);
			}
			else {
				bullets.Add(x + radius, y - 12, 10, atk);
				bullets.Add(x + radius, y, 10, atk);
				bullets.Add(x + radius, y + 12, 10, atk);
			}
		}
		shotTimer = shotInterval;
	}
}
void Player::UpdateBullets() {
	bullets.Update();
}
void Player::Draw(int offsetX, int offsetY) const {
	int drawX = (int)x + offsetX;
	int drawY = (int)y + offsetY;

	// 点滅
	if (invincibleTimer > 0 && (invincibleTimer / 5) % 2 == 0)
		return;
	//プレイヤーの描画
	DrawCircle(drawX, drawY, (int)radius, WHITE, TRUE);
	//弾の描画
	bullets.Draw(offsetX, offsetY);

	if (barrier)
	{
		DrawCircle(
			drawX,
			drawY,
			radius + 6,
			GetColor(0, 255, 255),
			FALSE
		);
	}
	//強化中に見えるバー
	if (bulletPowerTimer > 0) {
		int barWidth = 80;
		int barHeight = 10;

		float ratio = (float)bulletPowerTimer / maxbulletPowerTimer;
		int currentWidth = (int)(barWidth * ratio);

		DrawBox(drawX - 40, drawY + 30, drawX - 40 + barWidth, drawY + 30 + barHeight, GetColor(100, 100, 100), TRUE);
		DrawBox(drawX - 40, drawY + 30, drawX - 40 + currentWidth, drawY + 30 + barHeight, GetColor(0, 255, 0), TRUE);
	}

}
//HPバー表示
void Player::DrawHP() const {
	int barWidth = 200;
	int barHeight = 20;

	float ratio = (float)hp / maxHp;
	int currentWidth = (int)(barWidth * ratio);

	DrawBox(20, 50, 20 + barWidth, 50 + barHeight, GetColor(100, 100, 100), TRUE);
	DrawBox(20, 50, 20 + currentWidth, 50 + barHeight, GetColor(0, 255, 0), TRUE);
}
void Player::Damage(int damage) {
	if (invincibleTimer > 0) return;
	invincibleTimer = 60;
	if (barrier) {
		barrier = false;
		return;
	}
	hp -= damage;
}
void Player::Heal(int v) {
	hp += v;
	if (hp > maxHp)hp = maxHp;
}
void Player::SetRapid() {
	speed = max(7, speed + 0.1f);
}
void Player::SetBarrier() {
	barrier = true;
}
void Player::AddBullet() {
	if (powerLevel >= 3) {
		bulletPowerTimer = maxbulletPowerTimer;
		return;
	}
	powerLevel = min(powerLevel + 1, 3);

	
}
void Player::AddPower() {
	atk += 1;
}
void Player::ReleaseBullet(int index) {
	bullets.Release(index);
}
#pragma endregion