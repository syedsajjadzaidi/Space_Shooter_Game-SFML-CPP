#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string.h>
#include<iostream>
#include"bullet.h"
#include"Add_on.h"
using namespace sf;
using namespace std;
class Spaceship {
public:
	Texture tex; static int SpaceShip_Lives; 
	Sprite sprite;
	float speed = 0.5; 
	float x, y; float delta_x, delta_y;

	 Bullet** Bul = new Bullet*[7];

	 float Bullet_time;
	 int AddCall; bool SpaceShipAlive; 
	 float Random_No;
	 AddOn* AddOnPointer;
	 bool PowerUpVar; bool FireUpVar;
	 int Score;
	Spaceship()
	{
		Bullet_time = 0.0; AddCall = 0; SpaceShipAlive = true; Random_No = 0.0;  Score = 0;
		AddOnPointer = nullptr;
		delta_x=0.0; delta_y = 0.0;
		tex.loadFromFile("img/player_ship.png");
		sprite.setTexture(tex);
		x = 340.0;y = 700.0;
		sprite.setPosition(x, y);
		sprite.setScale(0.75, 0.75);

		for (int i = 0; i < 5; i++)
			Bul[i] = NULL;
		BulletTime();
		PowerUpVar = false;
		FireUpVar = false;
	}
	void BulletTime()
	{
		if(!PowerUpVar)
		if(Bul[0] == NULL)
			Bul[0] = new Bullet(x + delta_x, y + delta_y);
		if (PowerUpVar)
		{
			for(int i =0; i<7; i++)
				Bul[i] = new Bullet(x + delta_x, y + delta_y, 1);
		}
		if (FireUpVar)
		{
			for (int i = 0; i < 7; i++)
				Bul[i] = new Bullet(x + delta_x, y + delta_y, 2);
		}
	}
	void fire()
	{
		if (!PowerUpVar && !FireUpVar)
		{
			if (Bul[0] != NULL)
			{
				Bul[0]->Bullet_y -= 1.7;
				Bul[0]->Bullet_sprite.setPosition(Bul[0]->Bullet_x + 33, Bul[0]->Bullet_y - 47);
			}
			if (Bul[0] != NULL && Bul[0]->Bullet_y <= 0.0)
			{
				Bul[0] = NULL;
				BulletTime(); 
			}
		}
		else if (PowerUpVar)
		{
			if (Bul[0] != NULL)
				Bul[0]->Bullet_y -= 1.7;
			if (Bul[1] != NULL)
			{
				Bul[1]->Bullet_y -= 1.7;
				Bul[1]->Bullet_x -= 0.7;
			}
			if (Bul[2] != NULL)
			{
				Bul[2]->Bullet_y -= 1.7;
				Bul[2]->Bullet_x -= 0.2;
			}
			if (Bul[3] != NULL)
			{
				Bul[3]->Bullet_y -= 1.7;
				Bul[3]->Bullet_x += 0.7;
			}
			if (Bul[4] != NULL)
			{
				Bul[4]->Bullet_y -= 1.7;
				Bul[4]->Bullet_x += 0.2;
			}
			if (Bul[5] != NULL)
			{
				Bul[5]->Bullet_y -= 1.7;
				Bul[5]->Bullet_x -= 0.5;
			}
			if (Bul[6] != NULL)
			{
				Bul[6]->Bullet_y -= 1.7;
				Bul[6]->Bullet_x += 0.5;
			}
			for (int i = 0; i < 7; i++)
				if(Bul[i]!=NULL)
				Bul[i]->Bullet_sprite.setPosition(Bul[i]->Bullet_x, Bul[i]->Bullet_y);
			for (int i = 0; i < 7; i++)
			{
				if (Bul[i] != NULL && Bul[i]->Bullet_y <= 0.0)
					Bul[i] = NULL;
			}
		}
		else if (FireUpVar)
		{
			int j = 6;
			for (int i = 0; i < 7; i++)
			{
				if (Bul[i] != NULL)
				{
					Bul[i]->Bullet_y -= 1.7;
					Bul[i]->Bullet_sprite.setPosition(Bul[i]->Bullet_x+33, Bul[i]->Bullet_y+(j*-50)-47);
				}
				j--;
			}
			for (int i = 0; i < 7; i++)
			{
				if (Bul[i] != NULL && Bul[i]->Bullet_y <= 0.0)
					Bul[i] = NULL;
			}
		}

	}
	void move(std::string s) 
	{
		wrapEnviroment();
		if (s == "l") delta_x += -1 * speed;
		else if (s == "r") delta_x += 1 * speed;
		if (s == "u") delta_y += -1 * speed;
		else if (s == "d") delta_y += 1 * speed;
		sprite.setPosition(x + delta_x, y + delta_y);
	}
	void wrapEnviroment()
	{
		if (delta_x <= -340.0) delta_x = 339.0;
		else if (delta_x >= 340.0) delta_x = -339.0;
		if (delta_y <= -700) delta_y = -0.9;
		else if (delta_y >= 0.0) delta_y = -699;
		if (delta_x <= -340.0 && delta_y <= -700)
		{
			delta_x = 339.0; delta_y = -0.9;
		}
		else if (delta_x <= -340.0 && delta_y >= 0.0)
		{
			delta_x = 339.0; delta_y = -699;
		}
		else if (delta_x >= 340 && delta_y <= -700)
		{
			delta_x = -339.0; delta_y = -0.9;
		}
		else if (delta_x >= 340 && delta_y >= 0.0)
		{
			delta_x = -339.0;delta_y = -699;
		}
	    
		sprite.setPosition(x + delta_x, y + delta_y);
		
	}
	void AddOn_Caller()
	{
		Random_No += 1.0; int Var = 0;   
		if (Random_No >= 600 && AddOnPointer == NULL)
		{
			Var =  1 + rand() % 4; Random_No = 0.0;
		}
		if (Var == 1)
			AddOnPointer = new Lives;
		else if (Var == 2)
			AddOnPointer = new Danger;
		else if (Var == 3)
			AddOnPointer = new FireAddOn;
		else if (Var == 4)
			AddOnPointer = new PowerUp;

		if (AddOnPointer != NULL)
		{
			AddOnPointer->fall();
			
		}
		if (AddOnPointer != NULL && AddOnPointer->AddOn_y >= 680.0)
		{
			if (AddOnPointer->DangerFlag)
				Score = 10;
			AddOnPointer = NULL;
		}
		else Score = 0;

		if (AddOnPointer != NULL && AddOnPointer->strikeCheck(delta_x + x, delta_y + y))
		{
			if (AddOnPointer->LivesFlag == true)
				LivesAvail();
			if (AddOnPointer->DangerFlag == true)
				DangerAvail();
			if (AddOnPointer->PowerUpFlag == true)
				PowerUpAvail();
			if (AddOnPointer->FireFlag == true)
				FireAvail();
			AddOnPointer = NULL;
		}
	}
	void LivesAvail()
	{
		this->SpaceShip_Lives++;
	}
	void DangerAvail()
	{
		this->SpaceShip_Lives--;
	}
	void PowerUpAvail()
	{
		PowerUpVar = true;
		Bul[0] = NULL;
		BulletTime();
	} 
	void FireAvail()
	{
		for (int i = 0; i < 7; i++)
			Bul[i] = NULL;
		FireUpVar = true;
		BulletTime();
	}
};

