#include "DxLib.h"
#include"Game.h"
#pragma region メイン処理
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	SetMainWindowText("シューティングゲーム");
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	Game game;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();

		game.Update();
		game.Draw();
		ScreenFlip();
		WaitTimer(16);
	}
	DxLib_End();
	return 0;
}
#pragma endregion