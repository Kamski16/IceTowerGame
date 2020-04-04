#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;


    class Player{
        public:
            Player(Gravity gravity){
                this.gravity=gravity
            }
            void playerStep(){
                if(GetAsyncState(VK_LEFT)){
                    gravity.leftPress();

                }
                if(GetAsyncState(VK_RIGHT)){
                    gravity.rightPress();

                    }
                if(GetAsyncState(VK_SPACE)&&gravity.isJumping==false){
                    gravity.startJump();

                }
            x+=gravity.ChangeX();
            gravity.nextStep();
            y+=gravity.ChangeY();
            }


        private:
            double x,y;


    };

