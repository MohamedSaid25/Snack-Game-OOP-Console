#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>
using namespace std;
//................ properties..........//
enum Direction{Top=1,Down,Rght, Left};
struct Map{int Width, Height,FruitX,FruitY;};
struct Snack{int HeadX,HeadY,Tail_N, Tail_X[50],Tail_Y[50]; Direction Dir;};
struct Player{int Score; bool lose;};
//*****************************************//

Map Map1; Snack Snack1; Player Player1;

void Shift_Right(int arr[], int size){
for(int i=size-2; i>=0 ; i--)
{
	arr[i+1]=arr[i];
}}
void Generate_Fruit(){
	srand(time(NULL));
	Map1.FruitX= rand()% (Map1.Width-2)+1;  //--- form 1 to 38--- //
	Map1.FruitY= rand()% (Map1.Height-2)+1;  //--- form 1 to 18--- //

}
void Setup(){
	//.......... map..........//
	Map1.Width=40;
	Map1.Height=20;
	Generate_Fruit();
	//.......... map..........//

	//..........snack.......//
	Snack1.HeadX=Map1.Width/2;
	Snack1.HeadY=Map1.Height/2;
	Snack1.Tail_N=0;
	//..........snack.......//


	//....player........//

	Player1.Score=0;
	Player1.lose=false;

	//....player........//




}
void Draw(){
	system("cls");
	for(int i=0; i<Map1.Height; i++){
		for(int j=0; j<Map1.Width; j++){

			if(i==0 || i==Map1.Height-1)cout<<"*";
			else if(j==0 || j==Map1.Width-1)cout<<"*";
			else if(i==Snack1.HeadY &&j==Snack1.HeadX) cout<<"O";
			else if(i==Map1.FruitY &&j==Map1.FruitX) cout<<"$";
			else {

			bool Printed= false;
			for(int z= 0; z<Snack1.Tail_N; z++){
				if(Snack1.Tail_X[z]==j&& Snack1.Tail_Y[z]==i){
				cout<<"o";
				Printed=true;
				break;
				}

			}

			if(!Printed)cout<<" ";
			}


		}
	cout<<endl;
	}

	cout<<" Player Score : "<<Player1.Score<<endl;
}
void Input(){

	if(_kbhit()){

	char c=_getch();
	switch (c)
	{

	case 'w': Snack1.Dir=Top; break;
	case 's': Snack1.Dir=Down; break;
	case 'd': Snack1.Dir=Rght; break;
	case 'a': Snack1.Dir=Left; break;
	case 'x': exit(0);
	}


	}

}
void Move(){

	Shift_Right(Snack1.Tail_X,50);
	Shift_Right(Snack1.Tail_Y,50);
	Snack1.Tail_X[0]=Snack1.HeadX;
	Snack1.Tail_Y[0]=Snack1.HeadY;
	switch(Snack1.Dir)
	{

	case Top: Snack1.HeadY--;break;
	case Down: Snack1.HeadY++;break;
	case Rght :Snack1.HeadX++;break;
	case Left: Snack1.HeadX--;break;
	}
	if(Snack1.HeadY>=Map1.Height || Snack1.HeadY<=0|| Snack1.HeadX>=Map1.Width||Snack1.HeadX<=0)
		Player1.lose=true;
	if(Snack1.HeadX==Map1.FruitX && Snack1.HeadY==Map1.FruitY){

	Generate_Fruit();
	Player1.Score+=1;
	Snack1.Tail_N++;
	}
}

int main()
{

Setup();
while(!Player1.lose)
{
Draw();
Input();
Move();
Sleep(50);
}
	system("pause");
return 0;
}
