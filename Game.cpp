#include"Game.h"
#pragma region ゲームclass関数定義
Game::Game() :player(100, 300, 10, 5, 60), spawnTimer(0) {
	currentScene = make_unique<TitleScene>(*this);
	enemyBullets.InitPool(100);
	explosions.Init(100);
	hitSparks.Init(100);
	scorePops.resize(100);
	enemyManager.Init();
	for (int i = 0; i < 100; i++)
	{
		Star s;
		s.x = rand() % WIDTH;
		s.y = rand() % HEIGHT;
		s.speed = (rand() % 3 + 1) * 0.5f;
		s.size = rand() % 2 + 1;

		stars.push_back(s);
	}
}
void Game::Update() {
	if (isFading)
	{
		if (fadeOut)
		{
			fadeAlpha += 10;

			if (fadeAlpha >= 255)
			{
				fadeAlpha = 255;
				currentScene = std::move(nextScene);
				fadeOut = false;
			}
		}
		else
		{
			fadeAlpha -= 10;

			if (fadeAlpha <= 0)
			{
				fadeAlpha = 0;
				isFading = false;
			}
		}
	}
	else
	{
		if (currentScene)
			currentScene->Update();
	}
}
void Game::Draw()const {
	if (currentScene)
		currentScene->Draw();

	if (fadeAlpha > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
		DrawBox(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
void Game::UpdateGame() {
	//次のヒットストップまでの時間
	if (hitStopCooldown > 0)
		hitStopCooldown--;
	//画面揺れ
	if (shakeTimer > 0)
		shakeTimer--;
	//ヒットストップ中
	if (hitStopTimer > 0)
	{
		hitStopTimer--;
		UpdateHitStopObjects();
		return;
	}
	//入力処理
	HandleInput();
	//オブジェクトを動かす処理
	UpdateObjects();
	//衝突判定
	CheckCollision();
	//オブジェクトの削除
	RemoveDestroyedObjects();
}
void Game::DrawGame()const {
	//背景の星
	for (const auto& s : stars)
	{
		DrawCircle((int)s.x, (int)s.y, s.size, WHITE, TRUE);
	}

	int offsetX = 0;
	int offsetY = 0;
	//画面揺れ
	if (shakeTimer > 0)
	{
		offsetX = rand() % (shakePower * 2) - shakePower;
		offsetY = rand() % (shakePower * 2) - shakePower;
	}
	//プレイヤー
	player.Draw(offsetX, offsetY);
	//プレイヤーの体力
	player.DrawHP();
	//パワーアップアイテム
	for (auto& p : powerUps)
		p->Draw(offsetX, offsetY);
	//敵
	enemyManager.Draw(offsetX, offsetY);
	//敵の弾
	enemyBullets.Draw(offsetX, offsetY);
	//敵を倒したときの爆発
	explosions.Draw(offsetX, offsetY);
	//敵に当たった時に出てくる火花
	hitSparks.Draw(offsetX, offsetY);
	//敵を倒したときに出てくるスコア
	for (const auto& sp : scorePops)
	{
		if (!sp.IsActive()) continue;

		sp.Draw(offsetX, offsetY);
	}
	//スコア表示
	score.Draw();
	//ボス戦までのスコア
	if (bossScore <= score.Get()) {
		DrawString(300, 20, "ボス出現中！", WHITE);
	}
	else {
		DrawFormatString(300, 20, WHITE, "next BOSS : %d", bossScore - score.Get());
	}

	int barWidth = 200;
	int barHeight = 20;

	float ratio = (float)(score.Get() - startScore) / (bossScore - startScore);
	//バーがはみ出さないよう制限
	if (ratio < 0.0f)
		ratio = 0.0f;
	if (ratio > 1.0f)
		ratio = 1.0f;
	
	int currentWidth = (int)(barWidth * ratio);

	DrawBox(300, 50, 300 + barWidth, 50 + barHeight, GetColor(100, 100, 100), TRUE);
	DrawBox(300, 50, 300 + currentWidth, 50 + barHeight, GetColor(0, 255, 0), TRUE);

	//現在のフェーズ
	DrawFormatString(20, 80, WHITE, "PHASE : %d", phase);
}
void Game::ResetGame() {
	// ゲーム初期化
	powerUps.clear();
	enemyManager.Init();

	enemyBullets = EnemyBulletManager();
	enemyBullets.InitPool(100);

	explosions.Clear();
	explosions.Init(100);

	scorePops.clear();
	scorePops.resize(100);

	score = Score();

	player = Player(100, 300, 10, 5, 10);

	phase = 1;
	startScore = 0;
	bossScore = 5000;

	bossAlive = false;

	spawnTimer = 0;
	hitStopTimer = 0;
	hitStopCooldown = 0;
	shakeTimer = 0;
	shakePower = 0;

	stars.clear();

	for (int i = 0; i < 100; i++)
	{
		Star s;
		s.x = rand() % WIDTH;
		s.y = rand() % HEIGHT;
		s.speed = (rand() % 3 + 1) * 0.5f;
		s.size = rand() % 2 + 1;

		stars.push_back(s);
	}
}
void Game::HandleInput() {
	player.Move();
	player.Shoot();

}
void Game::UpdateObjects() {
	player.UpdateBullets();
	//背景の星を動かす
	for (auto& s : stars)
	{
		s.x -= s.speed;

		if (s.x < 0)
		{
			s.x = WIDTH;
			s.y = rand() % HEIGHT;
		}
	}
	//パワーアップアイテムを動かす
	for (auto& p : powerUps)
		p->Update();
	//敵を動かす
	enemyManager.Update();
	//敵の弾を動かす
	enemyBullets.Update(player.GetX(), player.GetY());
	//爆発を動かす
	explosions.Update();
	//ヒットスパークを動かす
	hitSparks.Update();
	//スコアポップを動かす
	for (auto& sp : scorePops)
		sp.Update();
	//敵生成
	SpawnEnemy();
}

// ヒットストップ中でも動かしたいもの
void Game::UpdateHitStopObjects()
{
	// 背景の星
	for (auto& s : stars)
	{
		s.x -= s.speed;

		if (s.x < 0)
		{
			s.x = WIDTH;
			s.y = rand() % HEIGHT;
		}
	}

	// 演出系は止めない
	explosions.Update();
	hitSparks.Update();

	for (auto& sp : scorePops)
		sp.Update();
}

void Game::SpawnEnemy()
{
	spawnTimer++;
	//敵が出てくるまでの時間
	int interval = max(20, SPAWN_INTERVAL - phase * 5);
	//ボス出現条件
	if (score.Get() >= bossScore && !bossAlive)
	{
		enemyManager.SpawnBoss(WIDTH + 100, HEIGHT / 2, *this);
		bossAlive = true;
		spawnTimer = 0;
		return;
	}
	//通常敵生成
	if (spawnTimer >= interval && !bossAlive)
	{
		int randomY = rand() % (HEIGHT - 24) + 12;
		int type = rand() % 6;

		enemyManager.Spawn(type, WIDTH + 20, randomY, *this);

		spawnTimer = 0;
	}
}
void Game::CheckCollision() {
	//パワーアップアイテムとプレイヤーの接触
	//画像の拡大率と合わせる
	float ImageScale = 0.4f;
	float powerUpRadius = 100 * ImageScale / 2;
	for (auto& p : powerUps)
	{
		float dx = player.GetX() - p->GetX();
		float dy = player.GetY() - p->GetY();

		if (dx * dx + dy * dy < powerUpRadius * powerUpRadius)
		{
			p->Apply(player);
			p->Kill();
		}
	}
	//敵と弾の接触
	enemyManager.ForEachActive([&](Enemy& enemy) {
		auto& bullets = player.GetBullets();

		for (int i = 0; i < bullets.size(); i++)
		{
			auto& bullet = bullets[i];
			if (!bullet.IsActive()) continue;

			if (bullet.IsHit(enemy.GetX(), enemy.GetY(), enemy.GetRadius()))
			{
				enemy.Damage(bullet.GetDamage());
				player.ReleaseBullet(i);

				if (enemy.IsDead()) {
					AddHitStop(8);
					shakeTimer = 12;
					shakePower = 16;
					enemy.OnDeath(*this);
				}
				else {
					AddHitStop(2);
					shakeTimer = 6;
					shakePower = 4;
					hitSparks.Add(bullet.GetX(), bullet.GetY());
				}
			}
		}
		});


	//敵とプレイヤーの接触
	enemyManager.ForEachActive([&](Enemy& enemy) {
		float dx = enemy.GetX() - player.GetX();
		float dy = enemy.GetY() - player.GetY();

		float r = enemy.GetRadius() + player.GetRadius();

		if (dx * dx + dy * dy <= r * r)
		{
			if (!bossAlive) {
				AddExplosion(enemy.GetX(), enemy.GetY());
				enemy.Kill();
			}

			player.Damage(1);

			if (player.IsDead()) return;

			AddHitStop(10);
			shakeTimer = 15;
			shakePower = 10;
		}
		});
	//敵弾とプレイヤーの接触
	for (auto& b : enemyBullets.Get())
	{
		if (!b.IsActive()) continue;

		if (b.IsHit(player.GetX(), player.GetY(), player.GetRadius()))
		{
			b.Deactivate();  // ← Killじゃない
			player.Damage(1);
		}
	}
}
void Game::RemoveDestroyedObjects() {

	powerUps.erase(
		remove_if(powerUps.begin(), powerUps.end(),
			[](const unique_ptr<PowerUp>& p) { return p->IsDead(); }),
		powerUps.end()
	);
	enemyManager.DeactivateDeadEnemies();
}
void Game::ChangeScene(unique_ptr<Scene> newScene)
{
	nextScene = std::move(newScene);
	isFading = true;
	fadeOut = true;
}
void Game::AddHitStop(int power) {
	if (hitStopCooldown > 0) return;

	if (bossAlive)
		power = max(2, power / 2);

	hitStopTimer = power;
	hitStopCooldown = power + 4;
}
unique_ptr<PowerUp> CreatePowerUp(PowerUpType type, float x, float y)
{
	switch (type)
	{
	case PowerUpType::Heal:
		return make_unique<Heal>(x, y);

	case PowerUpType::Rapid:
		return make_unique<Rapid>(x, y);

	case PowerUpType::Barrier:
		return make_unique<Barrier>(x, y);

	case PowerUpType::AddBullet:
		return make_unique<AddBullet>(x, y);

	case PowerUpType::AddPower:
		return make_unique<AddPower>(x, y);
	}

	return nullptr;
}
void Game::AddPowerUp(float x, float y)
{
	int r = rand() % 5;
	powerUps.push_back(
		CreatePowerUp((PowerUpType)r, x, y)
	);
}
#pragma endregion