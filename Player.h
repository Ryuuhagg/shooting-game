#pragma once
#include<vector>
#include"BulletManager.h"
using namespace std;
#pragma region プレイヤーClass
class Player {
private:
	//座標
	float x, y;
	//体力
	int hp;
	int maxHp;
	//攻撃力
	int atk;
	//プレイヤーの半径
	float radius;
	//速度
	float speed;
	//次に撃てるまでの間隔
	int shotInterval;
	//撃てるまでの間隔を計るタイマー
	int shotTimer;
	//無敵時間
	int invincibleTimer = 0;
	//弾数
	int powerLevel = 1;
	//一定時間強化用のタイマー
	int maxbulletPowerTimer = 300;
	int bulletPowerTimer = 0;
	//バレットの配列
	BulletManager bullets;
	//バリアのフラグ
	bool barrier = false;
public:
	//プレイヤーのコンストラクタ
	Player(float startX, float startY, float rad, float speed, int interval) : x(startX), y(startY), hp(5), maxHp(5), radius(rad), speed(speed), shotInterval(interval), shotTimer(0), atk(1) { bullets.InitPool(100); }
	//移動関数
	void Move();
	//発射関数
	void Shoot();
	//弾の更新
	void UpdateBullets();
	//描画関数
	void Draw(int offsetX = 0, int offsetY = 0) const;
	void DrawHP() const;
	//ダメージ
	void Damage(int damage);
	//回復
	void Heal(int v);
	//弾の射撃間隔
	void SetRapid();
	//バリア
	void SetBarrier();
	//弾追加
	void AddBullet();
	//攻撃Up
	void AddPower();

	void ReleaseBullet(int index);
	//ゲッター
	bool IsDead() const { return hp <= 0; }
	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetRadius() const { return radius; }
	vector<Bullet>& GetBullets() { return bullets.Get(); }
};
#pragma endregion