#pragma once
#define UNICODE

#include <chrono>
#include <vector>
#include <list>
#include <fstream>
using namespace std;

#include <windows.h>



enum {
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007,
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
	//
	PIXEL_SOLID = 0x2588
};



// Pamiêtaj - >>> -std=c++11 

class Sprite {

public:
	Sprite(string path) {
		Storage = new char*[spritesize];
		for (int i = 0; i < spritesize; i++)
			Storage[i] = new char[spritesize];
		Load(path);
	}

	void Reload(string path) {
		Load(path);
	}

	char** GetStorage() {
		return Storage;
	}

	int GetSpriteSize() {
		return spritesize;
	}

	

private:
	int spritesize = 16;
	char** Storage;

	void Load(string path) {
		ifstream sprite(path.c_str());

		for (int i = 0; i < spritesize; i++) {
			for (int j = 0; j < spritesize; j++) {
				sprite >> Storage[i][j];

			}
		}
	}

};
//Declarations ->
class Renderer{

public:
	
	

	void fontsize(int a, int b, HANDLE out) {
		PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
		lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
		GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
		lpConsoleCurrentFontEx->dwFontSize.X = a;
		lpConsoleCurrentFontEx->dwFontSize.Y = b;
		SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	}

	void DrawString(int x, int y, wstring c, short col)
	{
		for (size_t i = 0; i < c.size(); i++)
		{
			m_bufScreen[y * sWidth + x + i].Char.UnicodeChar = c[i];
			m_bufScreen[y * sWidth + x + i].Attributes = col;
		}
	}

	void Draw(int x, int y, wchar_t c, short col)
	{
		if (x >= 0 && x < sWidth && y >= 0 && y < sHeight)
		{
			m_bufScreen[y * sWidth + x].Char.UnicodeChar = c;
			m_bufScreen[y * sWidth + x].Attributes = col;
		}
	}



	void Fill(int x1, int y1, int x2, int y2, wchar_t c, short col)
	{
		Clip(x1, y1);
		Clip(x2, y2);
		for (int x = x1; x < x2; x++)
			for (int y = y1; y < y2; y++)
				Draw(x, y, c, col);
	}

	void DrawLine(int x1, int y1, int x2, int y2, wchar_t c, short col)
	{
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
		dx = x2 - x1;
		dy = y2 - y1;
		dx1 = abs(dx);
		dy1 = abs(dy);
		px = 2 * dy1 - dx1;
		py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = x1;
				y = y1;
				xe = x2;
			}
			else
			{
				x = x2;
				y = y2;
				xe = x1;
			}
			Draw(x, y, c, col);
			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
						y = y + 1;
					else
						y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				Draw(x, y, c, col);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = x1;
				y = y1;
				ye = y2;
			}
			else
			{
				x = x2;
				y = y2;
				ye = y1;
			}
			Draw(x, y, c, col);
			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
						x = x + 1;
					else
						x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				Draw(x, y, c, col);
			}
		}
	}

	void Clip(int &x, int &y)
	{
		if (x < 0) x = 0;
		if (x >= sWidth) x = sWidth;
		if (y < 0) y = 0;
		if (y >= sHeight) y = sHeight;
	}

	void Cls(short col) {
		Fill(0, 0, sWidth - 1, sHeight - 1, 0x2588, col);

	}

	void FillCircle(int xc, int yc, int r, wchar_t c, short col)
	{
		// Taken from wikipedia
		int x = 0;
		int y = r;
		int p = 3 - 2 * r;
		if (!r) return;

		auto drawline = [&](int sx, int ex, int ny)
		{
			for (int i = sx; i <= ex; i++)
				Draw(i, ny, c, col);
		};

		while (y >= x)
		{
			// Modified to draw scan-lines instead of edges
			drawline(xc - x, xc + x, yc - y);
			drawline(xc - y, xc + y, yc - x);
			drawline(xc - x, xc + x, yc + y);
			drawline(xc - y, xc + y, yc + x);
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
	}

	void DrawCircle(int xc, int yc, int r, wchar_t c, short col)
	{
		int x = 0;
		int y = r;
		int p = 3 - 2 * r;
		if (!r) return;

		while (y >= x) // only formulate 1/8 of circle
		{
			Draw(xc - x, yc - y, c, col);//upper left left
			Draw(xc - y, yc - x, c, col);//upper upper left
			Draw(xc + y, yc - x, c, col);//upper upper right
			Draw(xc + x, yc - y, c, col);//upper right right
			Draw(xc - x, yc + y, c, col);//lower left left
			Draw(xc - y, yc + x, c, col);//lower lower left
			Draw(xc + y, yc + x, c, col);//lower lower right
			Draw(xc + x, yc + y, c, col);//lower right right
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
	}

	void DrawSprite(int x, int y, Sprite* sprite) {
		char** Storage = sprite->GetStorage();

		int size = sprite->GetSpriteSize();
		int color;
		//Draw(2, 2, PIXEL_SOLID, Storage[0][0]);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				ofstream a("ugway.txt");
				a << Storage[i][j] << " ";
				switch (Storage[i][j]) {
				case 0:
					
					//continue;

					break;
				case 1:
					Draw(x + j, y + i, PIXEL_SOLID, FG_BLACK); 
					break;
				case 2:
					Draw(x + j, y + i, PIXEL_SOLID, FG_DARK_BLUE);
					break;
				case 3:
					Draw(x + j, y + i, PIXEL_SOLID, FG_DARK_GREEN);
					break;
				case 4:
					Draw(x + j, y + i, PIXEL_SOLID, FG_DARK_CYAN);
					break;
				case 5:
					Draw(x + j, y + i, PIXEL_SOLID, FG_DARK_RED);

					break;
				case 6:
					Draw(x + j, y + i, PIXEL_SOLID, FG_DARK_MAGENTA);
					break;
				case 7:
					Draw(x + j, y + i, PIXEL_SOLID, FG_DARK_YELLOW);
					break;
				case 8:
					Draw(x + j, y + i, PIXEL_SOLID, FG_GREY);
					break;
				case 9:
					Draw(x + j, y + i, PIXEL_SOLID, FG_DARK_GREY);
					break;
				case 10:
					Draw(x + j, y + i, PIXEL_SOLID, FG_BLUE);
					break;
				case 11:
					Draw(x + j, y + i, PIXEL_SOLID, FG_GREEN);
					break;
				case 12:
					Draw(x + j, y + i, PIXEL_SOLID, FG_CYAN);
					break;
				case 13:
					Draw(x + j, y + i, PIXEL_SOLID, FG_RED);
					break;
				case 14:
					Draw(x + j, y + i, PIXEL_SOLID, FG_MAGENTA);
					break;
				case 15:
					Draw(x + j, y + i, PIXEL_SOLID, FG_YELLOW);
					break;
				case 16:
					Draw(x + j, y + i, PIXEL_SOLID, FG_WHITE);
					break;
				}

			}
		}
	}
	
protected:
	int sWidth = 200;
	int sHeight = 150;
	CHAR_INFO *m_bufScreen;
};


//Dostêpne Kolory



