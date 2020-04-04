#include<iostream>
#include<cstdio>
#include<windows.h>
using namespace std;

class Gravity{
	public:
		Gravity(int boardWidth){
			this->boardWidth=boardWidth;
			
		}
		void startJump(){
			speedY=-5;
			jumping=true;
		}
		
		bool isJumping(){
			
			return jumping;
		}
		void nextStep(){
			speedY+=step;
			
		}
		int getChangeX(){
			
			return speedX;
		}
		int getChangeY(){
		
			return speedY;
		}
		void leftPress(int actPlayerX){
			speedX=1;
			if(actPlayeX==0)
				speedX=0;
			if(speedX<3)
				speedX+=step;
			
		}
		void rightPress(int actPlayerX){
			speedX=1;
			if(actPlayeX==boardWidth)
				speedX=0;
			if(speedX<3)
				speedX+=step;
			
		
		}
		
	private:
		double speedX;
		double speedY;
		bool jumping=false;
		double step=0.2;
			
};

