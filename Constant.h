#pragma once
#include "DxLib.h"
#include<vector>
#pragma region íËêî
const int RED = GetColor(255, 0, 0);
const int BLUE = GetColor(0, 0, 255);
const int GREEN = GetColor(0, 255, 0);
const int WHITE = GetColor(255, 255, 255);
const int BRACK = GetColor(0, 0, 0);
const int WIDTH = 800, HEIGHT = 600;
const int SPAWN_INTERVAL = 60;
#pragma endregion
#pragma region mitame
void DrawHexItem(float x, float y, float size, float angle);
void DrawWaveItem(float x, float y, float time);
#pragma endregion
#pragma region ê}å`çÏê¨
struct Vector2 {
	int x, y;
};
struct MyPolygon
{
	std::vector<Vector2> ps;

	MyPolygon(std::initializer_list<Vector2> list)
	{
		for (auto a : list) { ps.push_back(a); }
	}
	MyPolygon() {}
};
struct Circle
{
	Vector2 center;		//íÜêS
	float radius;		//îºåa
};
struct Star {
	float x, y;
	float speed;
	int size;
};
#pragma endregion
#pragma region ä÷êîêÈåæ
void FillPolygon(MyPolygon p, int color = 0xffffff);
void FillCircle(Circle c);
int getIntersectionX(int x1, int y1, int x2, int y2, int y);
void TranslationPolygon(MyPolygon& p, Vector2 t);
#pragma endregion