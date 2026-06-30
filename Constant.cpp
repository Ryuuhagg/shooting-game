#include"Constant.h"
#include<algorithm>
#pragma region 関数定義

void DrawHexItem(float x, float y, float size, float angle)
{
	const int VERT = 6;
	float px[VERT], py[VERT];

	for (int i = 0; i < VERT; i++)
	{
		float a = angle + DX_PI_F * 2 * i / VERT;
		px[i] = x + cosf(a) * size;
		py[i] = y + sinf(a) * size;
	}

	// 外枠
	for (int i = 0; i < VERT; i++)
	{
		int j = (i + 1) % VERT;
		DrawLine((int)px[i], (int)py[i], (int)px[j], (int)py[j], GetColor(0, 255, 255));
	}

	// 中央のコア
	DrawCircle((int)x, (int)y, (int)(size * 0.3f), GetColor(255, 255, 255), TRUE);
}

void DrawWaveItem(float x, float y, float time)
{
	for (int i = 0; i < 3; i++)
	{
		float t = fmodf(time + i * 20, 60);
		float radius = t * 1.5f;

		int alpha = (int)(255 * (1.0f - t / 60.0f));

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawCircle((int)x, (int)y, (int)radius, GetColor(0, 255, 255), FALSE);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 中央
	DrawCircle((int)x, (int)y, 5, GetColor(255, 255, 255), TRUE);
}

int getIntersectionX(int x1, int y1, int x2, int y2, int y)
{
	return (int)((float)x1 + (float)(y - y1) * (x2 - x1) / (y2 - y1));
}

void TranslationPolygon(MyPolygon& p, Vector2 t)
{
	//頂点を先頭から順番に頂点を平行移動
	for (int i = 0; i < p.ps.size(); i++)
	{
		p.ps[i].x = p.ps[i].x + t.x;		//x座標の変換
		p.ps[i].y = p.ps[i].y + t.y;		//y座標の変換
	}
}

void FillPolygon(MyPolygon p, int color)
{
	for (int i = 0; i < p.ps.size(); i++)
	{
		p.ps[i].x = (int)(p.ps[i].x + 0.5);
		p.ps[i].y = (int)(p.ps[i].y + 0.5);
	}

	int miny = p.ps[0].y;
	int maxy = p.ps[0].y;
	for (int i = 1; i < p.ps.size(); i++)
	{
		if (miny > p.ps[i].y) miny = p.ps[i].y;
		if (maxy < p.ps[i].y) maxy = p.ps[i].y;
	}

	p.ps.push_back(p.ps[0]);
	for (int y = miny; y < maxy; y++)
	{
		std::vector<int> xlist;
		for (int i = 0; i < p.ps.size() - 1; i++)
		{
			if (p.ps[i].y != p.ps[i + 1].y
				&& (y >= p.ps[i].y && y <= p.ps[i + 1].y || y >= p.ps[i + 1].y && y <= p.ps[i].y))
			{
				int x = getIntersectionX(p.ps[i].x, p.ps[i].y, p.ps[i + 1].x, p.ps[i + 1].y, y);
				bool isFound = std::find(xlist.begin(), xlist.end(), x) != xlist.end();
				if (isFound)
				{
					if (p.ps[i].x == x && (p.ps[i - 1].y<p.ps[i].y && p.ps[i + 1].y< p.ps[i].y
						|| p.ps[i - 1].y > p.ps[i].y && p.ps[i + 1].y > p.ps[i].y))
					{
						xlist.push_back(x);
					}
				}
				else
				{
					xlist.push_back(x);
				}
			}
		}
		sort(xlist.begin(), xlist.end());

		for (int i = 0; i < xlist.size() - 1; i += 2)
		{
			DrawLine(xlist[i], y, xlist[i + 1], y, color);
		}
	}
}

void FillCircle(Circle c) {
	int cx = c.center.x;
	int cy = c.center.y;
	int r = (int)c.radius;

	for (int y = -r; y <= r; y++)
	{
		for (int x = -r; x <= r; x++)
		{
			int dist2 = x * x + y * y;

			if (dist2 <= r * r)
			{
				float dist = sqrt((float)dist2);
				float ratio = dist / r;   // 0～1

				// 中心が明るく、外側が暗い
				int red = (int)(255 * (1.0f - ratio));
				int green = (int)(100 * (1.0f - ratio));
				int blue = 255;

				int color = GetColor(red, green, blue);

				DrawPixel(cx + x, cy + y, color);
			}
		}
	}
}

#pragma endregion
