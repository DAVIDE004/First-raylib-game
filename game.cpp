#include "raylib.h"
#include "raymath.h"
#include <deque>
#define CELLSIZE 20

using namespace std;




int main ()

{
	char str[3];

	int counter = 0;
	InitWindow(800,800,"My first raylib Game");
	SetTargetFPS(4);
	Color green = {0,180,150,255};
	
	class food
	{
		public:
		void draw(){
			DrawCircle(x*CELLSIZE+10,y*CELLSIZE+10,radius,RED);
		}
		void update(){
			x = GetRandomValue(0,40);
			y = GetRandomValue(0,40);
			position = {(float)x,(float)y};
		}

		
		int radius = 10;
		int x = GetRandomValue(0,40);
		int y = GetRandomValue(0,40);
		Vector2 position = {(float)x,(float)y};
		
	};
	
	class snake{
		public:
		deque<Vector2> body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
		Vector2 direction = {1,0};

		void draw()
		{

		
			for (unsigned int i = 0; i < body.size(); i++)
			{
				int x1 = body[i].x;
				int y1 = body[i].y;
				DrawRectangle(x1*CELLSIZE,y1*CELLSIZE,20,20,BLACK);
			}

		}

		void update()
		{
			body.pop_back();
			body.push_front(Vector2Add(body[0],direction));
		}

		void update1()
		{
			
			body.push_front(Vector2Add(body[0],direction));
		}




	};



	snake ser;
	food app;
	
	
	//Game Loop
	while(WindowShouldClose() == false)
	{
		//Events
		if (IsKeyPressed(KEY_DOWN)){
			ser.direction={0,1};
		}else if (IsKeyPressed(KEY_UP)){
			ser.direction = {0,-1};
		}else if (IsKeyPressed(KEY_LEFT)){
			ser.direction = {-1,0};
		}else if (IsKeyPressed(KEY_RIGHT)){
			ser.direction = {1,0};
		}


		if(Vector2Equals(Vector2Add(ser.body[0],ser.direction) ,app.position)){
			app.update();
			ser.update1();
			counter+=1;
		}else{
			ser.update();
		}


		if (ser.body[0].x ==40 || ser.body[0].x == -1){
			ser.body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
			counter = 0;
		}else if (ser.body[0].y ==40 || ser.body[0].y == -1){
			ser.body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
			counter = 0;

		}

		for (unsigned int i = 1; i < ser.body.size();i++){
			if(Vector2Equals(ser.body[0],ser.body[i])){
				ser.body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
				counter = 0;
			}
		}

		sprintf(str,"%d", counter);



		//Drawing
		BeginDrawing();
		ser.draw();
		app.draw();
		DrawText(str,390,30,20,WHITE);
		
		ClearBackground(green);
		
		EndDrawing();
	};



	CloseWindow();
	return 0;
}
