#pragma once
#include<memory>
#include"Player.h"
#include"PowerUp.h"
#include"Scene.h"
#include"EnemyBulletManager.h"
#include"ExplosionManager.h"
#include"Score.h"
#include"Enemy.h"
#include "EnemyManager.h"
#include"HitSparkManager.h"
#pragma region ゲームClass
class Scene;
class Game {
private:
	Player player;
	vector<Star> stars;
	EnemyManager enemyManager;
	ExplosionManager explosions;
	HitSparkManager hitSparks;
	Score score;
	vector<ScorePop> scorePops;
	unique_ptr<Scene> currentScene;
	EnemyBulletManager enemyBullets;
	vector<unique_ptr<PowerUp>> powerUps;
	unique_ptr<Scene> nextScene;
	int spawnTimer;
	int hitStopTimer = 0;
	int hitStopCooldown = 0;
	int shakeTimer = 0;
	int shakePower = 0;
	int fadeAlpha = 0;
	int phase = 1;
	int startScore = 0;
	int bossScore = 5000;
	bool bossAlive = false;
	bool isFading = false;
	bool fadeOut = true;
	//入力処理
	void HandleInput();
	//更新処理
	void UpdateObjects();
	//敵生成
	void SpawnEnemy();
	//衝突判定
	void CheckCollision();
	//削除
	void RemoveDestroyedObjects();
	// ヒットストップ中でも動かしたいもの
	void UpdateHitStopObjects();
public:
	Game();
	//シーンを変える関数
	void ChangeScene(unique_ptr<Scene> newScene);
	//更新処理
	void Update();
	//描画処理
	void Draw() const;
	//プレイヤーの生死
	bool IsPlayerDead() const {
		return player.IsDead();
	}
	//スコアのゲッター
	int GetScore()const { return score.Get(); }
	//ヒットストップを発生させる関数
	void AddHitStop(int power);
	//敵の弾を出すやつ
	void AddEnemyBullet(float x, float y, float dirX, float dirY, float speed, EnemyBulletType type) {
		enemyBullets.Add(x, y, dirX, dirY, speed, type);
	}
	//爆発エフェクトを出すやつ
	void AddExplosion(float x, float y) { explosions.Add(x, y); }
	//スコア加算
	void AddScore(int value, float x, float y) {
		score.Add(value);
		for (auto& sp : scorePops)
		{
			if (!sp.IsActive())
			{
				sp.Init(x, y, value);
				break;
			}
		}
	}
	//パワーアップアイテムを出す
	void AddPowerUp(float x, float y);
	//次のフェーズに行くやつ
	void NextPhase() {
		phase++;
		//ボスまでのスコアを現在スコア+前回のボスまでのスコア*フェーズにする
		startScore = score.Get();
		bossScore = score.Get() + bossScore * phase;
	}
	//ボス死亡判定
	void bossDeath() {
		bossAlive = false;
	}
	//現在のフェーズ
	int GetPhase() const {
		return phase;
	}
	//プレイヤーの座標
	float GetPlayerX() const { return player.GetX(); }
	float GetPlayerY() const { return player.GetY(); }
	//更新
	void UpdateGame();
	//描画
	void DrawGame() const;
	//リセット
	void ResetGame();
};
#pragma endregion