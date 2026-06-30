#pragma once
#include"Enemy.h"
#include<vector>
using namespace std;
class Game;
class EnemyManager {
private:
	vector<StraightEnemy> straightPool;
	vector<WaveEnemy> wavePool;
	vector<ZigZagEnemy> zigzagPool;
	vector<ShotEnemy> shotPool;
	vector<StalkerEnemy> stalkerPool;
	vector<BigEnemy> bigPool;
	vector<Boss> bossPool;

public:
	void Init();
	void Spawn(int type, float x, float y, Game& game);
	void SpawnBoss(float x, float y, Game& game);
	void Update();
	void Draw(int offsetX, int offsetY) const;
	void DeactivateDeadEnemies();
	template <typename Func>
	void ForEachActive(Func func) {
		for (auto& e : straightPool)
			if (e.IsActive()) func(e);

		for (auto& e : wavePool)
			if (e.IsActive()) func(e);

		for (auto& e : zigzagPool)
			if (e.IsActive()) func(e);

		for (auto& e : shotPool)
			if (e.IsActive()) func(e);

		for (auto& e : stalkerPool)
			if (e.IsActive()) func(e);

		for (auto& e : bigPool)
			if (e.IsActive()) func(e);

		for (auto& e : bossPool)
			if (e.IsActive()) func(e);
	}
};