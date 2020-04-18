#include "Engine.h"


class Gravity {
public:

	void startJump() {
		speedY = -5;
		jumping = true;
	}

	bool isJumping() {

		return jumping;
	}
	void nextStep() {
		speedY += step;

	}
	int ChangeX() {

		return speedX;
	}
	int ChangeY() {

		return speedY;
	}
	void leftPress(int actPlayerX) {
		speedX = 1;
		if (actPlayerX == 0)
			speedX = 0;
		if (speedX < 3)
			speedX += step;

	}
	void rightPress(int actPlayerX) {
		speedX = 1;
		if (actPlayerX == boardWidth)
			speedX = 0;
		if (speedX < 3)
			speedX += step;


	}

private:
	double speedX;
	double speedY;
	bool jumping = false;
	double step = 0.2;
	int boardWidth = 200;

};
class Platform{
	public:
		Platform(int x,int y,int width){
			this->x = x;
			this->y = y;
			this->width = width;
		}
		int getX(){
			return x;
		}
		int getY(){
			return y;
		}
		int getWidth(){
			return width;
		}
		bool moveDown(int val){
			y-=val;
			return y >= 0;
		}
	private:
		int x,y, width;
};

class Player : public Gravity {
public:

	void playerStep() {
		if (GetAsyncKeyState(VK_LEFT)) {
			leftPress(x);

		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			rightPress(x);

		}
		if (GetAsyncKeyState(VK_SPACE) && isJumping() == false) {
			startJump();

		}
		x += ChangeX();
		nextStep();
		y += ChangeY();
	}

	double getX() {
		return x;
	}

	double getY() {
		return y;
	}

private:
	double x, y;


};

 
class Board{
public:
	
	int getPlayerX(){
		return player.getX();
	}
	int getPlayerY(){
		return player.getY() - totalMovedY;
	}
	void init(){
		for (int i =20; i<150; i+=30){
			platforms.push_back(Platform(rand()%150,i,50+rand()%50));
		}
	}
	vector<Platform> getPlatforms(){
		return platforms;
	}
	
	void moveBoard(int yMove){
		totalMovedY	+= yMove;
		for(int i=0; i<platforms.size();i++){
			if(platforms[i].moveDown(yMove))
				platforms[i] = Platform(rand()%150,150,50+rand()%50);
		}
	}

private:
	Player player;
	vector <Platform> platforms;
	int totalMovedY = 0;
};




class Game : public Renderer {

public:

	float SetFps(float fElapsedTime) {
		this->fElapsedTime = fElapsedTime;
	}

	float GetFps() {
		return fElapsedTime;
	}
	
	void Start() {
		fontsize(8, 8, hConsole);

		SetConsoleActiveScreenBuffer(hConsole);

		m_bufScreen = new CHAR_INFO[sWidth*sHeight];
		memset(m_bufScreen, 0, sizeof(CHAR_INFO) * sWidth*sHeight);
		m_rectWindow = { 0, 0, (short)sWidth, (short)sHeight };

	


		Cls(FG_GREY);
		storag = new char*[16];
		for (int i = 0; i < 16; i++)
			storag[i] = new char[16];

		


	}

	void Refresh() {
		
		
		
			

			DrawSprite(5, 5, Player_Sprite);
			//DrawCircle(15, 15, 5, PIXEL_SOLID, FG_RED);
			//Display The Frame ->
			wchar_t s[256];
			swprintf(s, 256, L"%s", m_sAppName.c_str());
			SetConsoleTitleW(s);
			WriteConsoleOutput(hConsole, m_bufScreen, { (short)sWidth, (short)sHeight }, { 0,0 }, &m_rectWindow);
		


	}

	void GraphicMaker() {

		
		switch (actualc) {
		case 0:
			DrawString(20, 2, L"E", BG_GREY);
			break;
		case 1:
			Draw(20, 2, PIXEL_SOLID, FG_BLACK);
			break;
		case 2:
			Draw(20, 2, PIXEL_SOLID, FG_DARK_BLUE);
			break;
		case 3:
			Draw(20, 2, PIXEL_SOLID, FG_DARK_GREEN);
			break;
		case 4:
			Draw(20, 2, PIXEL_SOLID, FG_DARK_CYAN);
			break;
		case 5:
			Draw(20, 2, PIXEL_SOLID, FG_DARK_RED);
			break;
		case 6:
			Draw(20, 2, PIXEL_SOLID, FG_DARK_MAGENTA);
			break;
		case 7:
			Draw(20, 2, PIXEL_SOLID, FG_DARK_YELLOW);
			break;
		case 8:
			Draw(20, 2, PIXEL_SOLID, FG_GREY);
			break;
		case 9:
			Draw(20, 2, PIXEL_SOLID, FG_DARK_GREY);
			break;
		case 10:
			Draw(20, 2, PIXEL_SOLID, FG_BLUE);
			break;
		case 11:
			Draw(20, 2, PIXEL_SOLID, FG_GREEN);
			break;
		case 12:
			Draw(20, 2, PIXEL_SOLID, FG_CYAN);
			break;
		case 13:
			Draw(20, 2, PIXEL_SOLID, FG_RED);
			break;
		case 14:
			Draw(20, 2, PIXEL_SOLID, FG_MAGENTA);
			break;
		case 15:
			Draw(20, 2, PIXEL_SOLID, FG_YELLOW);
			break;
		case 16:
			Draw(20, 2, PIXEL_SOLID, FG_WHITE);
			break;
		}


		for (int i = 0; i < 16; i++) {
			for (int j = 0;j < 17; j++){
				if(j == 16)
				Draw(i, j, PIXEL_SOLID, FG_RED);
				else
				Draw(i, j, PIXEL_SOLID, FG_BLACK);
			}
		}
		

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && x < 15) {
			x++;
		}
		else if(GetAsyncKeyState(VK_LEFT) & 0x8000 && x > 0) {
			x--;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && y < 15) {
			y++;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000 && y > 0) {
			y--;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
			storag[x][y] = actualc;
			
		}

		if (GetAsyncKeyState('E') & 0x0001 && actualc < 16) {
			actualc++;
		 
		}
		else if (GetAsyncKeyState('Q') & 0x0001 && actualc > 0) {
			actualc--;
		}
		else if (GetAsyncKeyState('R') & 0x0001 && actualc > 0) {
			for (int i = 0; i < 16; i++)
				for (int j = 0; j < 16; j++)
					storag[j][i] = 0;
		}


		for (int i = 0; i < 16; i++) 
			for (int j = 0; j < 16; j++) 
		switch ((int)storag[i][j]) {
		case 0:
			continue;
			break;
		case 1:
			Draw(i , j , PIXEL_SOLID, FG_BLACK);
			break;
		case 2:
			Draw(i , j , PIXEL_SOLID, FG_DARK_BLUE);
			break;
		case 3:
			Draw(i , j , PIXEL_SOLID, FG_DARK_GREEN);
			break;
		case 4:
			Draw(i , j , PIXEL_SOLID, FG_DARK_CYAN);
			break;
		case 5:
			Draw(i , j , PIXEL_SOLID, FG_DARK_RED);
			break;
		case 6:
			Draw(i , j , PIXEL_SOLID, FG_DARK_MAGENTA);
			break;
		case 7:
			Draw(i , j , PIXEL_SOLID, FG_DARK_YELLOW);
			break;
		case 8:
			Draw(i, j , PIXEL_SOLID, FG_GREY);
			break;
		case 9:
			Draw(i , j , PIXEL_SOLID, FG_DARK_GREY);
			break;
		case 10:
			Draw(i, j , PIXEL_SOLID, FG_BLUE);
			break;
		case 11:
			Draw(i , j , PIXEL_SOLID, FG_GREEN);
			break;
		case 12:
			Draw(i , j , PIXEL_SOLID, FG_CYAN);
			break;
		case 13:
			Draw(i , j , PIXEL_SOLID, FG_RED);
			break;
		case 14:
			Draw(i , j , PIXEL_SOLID, FG_MAGENTA);
			break;
		case 15:
			Draw(i , j , PIXEL_SOLID, FG_YELLOW);
			break;
		case 16:
			Draw(i , j , PIXEL_SOLID, FG_WHITE);
			break;
		}
		Draw(x, y + 1, 0x2191, FG_GREEN);

		Sleep(50);
		wchar_t s[256];
		swprintf(s, 256, L"%s - %d", m_sAppName.c_str(),actualc);
		SetConsoleTitleW(s);
		WriteConsoleOutput(hConsole, m_bufScreen, { (short)sWidth, (short)sHeight }, { 0,0 }, &m_rectWindow);

		if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
			
			ofstream file("Player.txt");
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 16; j++) {
					file << (int)storag[i][j] << " ";
				}
				file << endl;
			}
			DrawString(20, 20, L"SAVED!", BG_GREY);
		}

	}


private:

	

	Sprite* Player_Sprite = new Sprite("Player.txt");;
	int x = 0, y = 0, actualc = 2;
	char** storag;
	float fElapsedTime = 60.f;
	wstring m_sAppName = L"IcyTower";
	SMALL_RECT m_rectWindow;

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	wchar_t *screen = new wchar_t[sWidth*sHeight];


};





int main() {

		//Basic Declarations ->	

		Board board;
		board.init();
		
		
		while (1) {
			demo.Refresh();
			demo.GraphicMaker();
			
			board.moveBoard(1);
			sleep(50); //20FPS
		}
}



