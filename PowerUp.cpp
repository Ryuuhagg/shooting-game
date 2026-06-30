#include"PowerUp.h"
#include"DxLib.h"
#include"Image.h"

static int healHandle = -1;
static int rapidHandle = -1;
static int barrierHandle = -1;
static int addBulletHandle = -1;
static int powerHandle = -1;

static void LoadPowerUpImages()
{
	if (healHandle != -1) return;

	healHandle = LoadGraph(heal.path);
	rapidHandle = LoadGraph(rapid.path);
	barrierHandle = LoadGraph(barrier.path);
	addBulletHandle = LoadGraph(addBullet.path);
	powerHandle = LoadGraph(power.path);
}

#pragma region PowerUpÉNÉâÉXä÷êîíËã`
void Heal::Draw(int offsetX, int offsetY)const {
	LoadPowerUpImages();

	DrawRotaGraph(
		(int)x + offsetX,
		(int)y + offsetY,
		0.4,
		0.0,
		healHandle,
		TRUE
	);
}
void Heal::Apply(Player& player)
{
	player.Heal(1);
}
void Rapid::Draw(int offsetX, int offsetY)const {
	LoadPowerUpImages();

	DrawRotaGraph(
		(int)x + offsetX,
		(int)y + offsetY,
		0.4,
		0.0,
		rapidHandle,
		TRUE
	);
}
void Rapid::Apply(Player& player) {
	player.SetRapid();
}
void Barrier::Draw(int offsetX, int offsetY)const {
	LoadPowerUpImages();

	DrawRotaGraph(
		(int)x + offsetX,
		(int)y + offsetY,
		0.4,
		0.0,
		barrierHandle,
		TRUE
	);
}
void Barrier::Apply(Player& player) {
	player.SetBarrier();
}
void AddBullet::Draw(int offsetX, int offsetY)const {
	LoadPowerUpImages();

	DrawRotaGraph(
		(int)x + offsetX,
		(int)y + offsetY,
		0.4,
		0.0,
		addBulletHandle,
		TRUE
	);
}
void AddBullet::Apply(Player& player) {
	player.AddBullet();
}
void AddPower::Draw(int offsetX, int offsetY)const {
	LoadPowerUpImages();

	DrawRotaGraph(
		(int)x + offsetX,
		(int)y + offsetY,
		0.4,
		0.0,
		powerHandle,
		TRUE
	);
}
void AddPower::Apply(Player& player) {
	player.AddPower();
}
#pragma endregion