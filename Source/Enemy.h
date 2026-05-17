#include <SFML/Graphics.hpp>
#include<cstdlib>
#include <ctime>
#include<iostream>
using namespace sf;
class Bomb
{
public: 
	Sprite sprite; 
	Texture texture;
	float bombX, bombY; 
	Bomb(int X, int Y)
	{
		bombX = X+40; bombY = Y+30; 
		texture.loadFromFile("img/PNG/Meteors/meteorBrown_med1.png");
		sprite.setTexture(texture);
		sprite.setPosition(bombX, bombY);
		sprite.setScale(0.55, 0.55);
	}
};
class Lightining
{
public:
	Sprite sprite;
	Texture texture;
	float LightiningX, LightiningY;
	Lightining(int X, int Y)
	{
		LightiningX = X + 80; LightiningY = Y + 30;
		texture.loadFromFile("img/PNG/Lasers/laserGreen10.png");
		sprite.setTexture(texture);
		sprite.setPosition(LightiningX, LightiningY);
		sprite.setScale(1.95, 1.95);
	}
};
class DragonFire
{
public:
	Sprite Firesprite;
	Texture FireTex;
	float DragonfireX; float DragonFireY;
	DragonFire(float X, float Y)
	{
		DragonfireX = X+90; DragonFireY = Y+90;
		FireTex.loadFromFile("img/PNG/Lasers/LaserGreen011.png");
		Firesprite.setTexture(FireTex);
		Firesprite.setPosition(DragonfireX, DragonFireY);
		Firesprite.setScale(0.95, 0.95);
	}
};
class Enemy
{
public:
	Lightining* Light; DragonFire** DF = new DragonFire*[3];
	Bomb* bomb;      bool MoveflagX; bool MoveflagY; static int EnemyLevel;
	Texture Enemy_tex;
	Sprite Enemy_sprite;
	float Enemy_x, Enemy_y;
	virtual void fire() =0;
	virtual void move() = 0;
	virtual void BombTime(float X =0.0, float Y=0.0) = 0; int ScoreCount;
	virtual void VerticalMove() = 0;
	virtual void horizontalMove() = 0;
	bool VmoveFlag; float delta_x, delta_y;
	bool EnemyDisplayFlag;
	bool ifMOnster;
	bool ifAlpha, ifBeta, ifGama;
	bool Scoreflag;
	float PlayerPosition;
};
class Invader : public Enemy
{
public:
	Invader(){}
	virtual void fire() = 0;
	virtual void move() = 0;
	virtual void BombTime(float X = 0.0, float Y = 0.0) = 0;
	virtual void VerticalMove() = 0;
	virtual void horizontalMove() = 0;
};
class Alpha : public Invader
{
public: 
	Alpha(float randomX=0.0, float randomY =0.0)
	{
		Enemy_x = randomX;
		Enemy_y = randomY;
		Enemy_tex.loadFromFile("img/enemy_1.png");
		Enemy_sprite.setTexture(Enemy_tex);
		Enemy_sprite.setPosition(Enemy_x, Enemy_y);
		Enemy_sprite.setScale(0.85, 0.85); bomb = NULL; MoveflagX = true; MoveflagY = true;
		delta_x = 0; delta_y = 0; VmoveFlag = true;
		EnemyDisplayFlag = true;
		for (int i = 0; i < 3; i++)
			DF[i] = NULL;
		ifAlpha = true;
		ifBeta = false;
		ifGama = false; PlayerPosition = 0;
	}
	void BombTime(float X=0.0, float Y=0.0)
	{
		bomb = new Bomb(Enemy_x+delta_x, Enemy_y+delta_y);
	}
	void fire()
	{
		if (EnemyLevel == 1)
			bomb->bombY += 0.5;
		if (EnemyLevel == 2)
			bomb->bombY += 0.7;
		if(EnemyLevel >=3)
			bomb->bombY += 0.9;
		bomb->sprite.setPosition(bomb->bombX, bomb->bombY);
		
		if (bomb->bombY >= 680)
		{
			bomb = NULL;
		}
	}
	void move()
	{
		if (MoveflagX) Enemy_x += 0.1;
		if (Enemy_x >= 680.0) MoveflagX = false;
		if (!MoveflagX) Enemy_x -= 0.1;
		if (Enemy_x <= 0.0) MoveflagX = true;
		if (MoveflagY) Enemy_y += 0.1;
		if (Enemy_y >= 180.0) MoveflagY = false;
		if (!MoveflagY) Enemy_y -= 0.1;
		if (Enemy_y <= 0.0) MoveflagY = true;
		Enemy_sprite.setPosition(Enemy_x, Enemy_y);
	}
	void VerticalMove()
	{
		if (VmoveFlag == true)
		{
			delta_y += 0.1;
		}
		if (delta_y >=  100)
		{
			VmoveFlag = false;
		}
		if (VmoveFlag == false)
			delta_y -= 0.1;
		if (delta_y < 0)
		{
			VmoveFlag = true;
		}
		Enemy_sprite.setPosition(Enemy_x, Enemy_y + delta_y);
	}
	void horizontalMove()
	{
		if (VmoveFlag == true)
			delta_x += 0.1;
		if (delta_x >= 100)
			VmoveFlag = false;
		if (VmoveFlag == false)
			delta_x -= 0.1;
		if (delta_x < -100)
			VmoveFlag = true;
		Enemy_sprite.setPosition(Enemy_x+delta_x, Enemy_y + delta_y);
	}
	
};
class Beta : public Invader
{
public:
	Beta(float randomX =0.0, float randomY =0.0)
	{
		Enemy_x = randomX;
		Enemy_y = randomY;
		Enemy_tex.loadFromFile("img/enemy_2.png");
		Enemy_sprite.setTexture(Enemy_tex);
		Enemy_sprite.setPosition(Enemy_x, Enemy_y);
		Enemy_sprite.setScale(0.75, 0.75);
		bomb = NULL; MoveflagX = true; MoveflagY = true;
		delta_x = 0; delta_y = 0; VmoveFlag = true;
		EnemyDisplayFlag = true;
		for (int i = 0; i < 3; i++)
			DF[i] = NULL;
		ifAlpha = false;
		ifBeta = true;
		ifGama = false; PlayerPosition = 0;
	}
	void BombTime(float X = 0.0, float Y = 0.0)
	{
		bomb = new Bomb(Enemy_x + delta_x, Enemy_y + delta_y);
	}
	void fire()
	{
		if (EnemyLevel == 1)
			bomb->bombY += 0.5;
		if (EnemyLevel == 2)
			bomb->bombY += 0.7;
		if (EnemyLevel >= 3)
			bomb->bombY += 0.9;
		bomb->sprite.setPosition(bomb->bombX, bomb->bombY);

		if (bomb->bombY >= 680)
		{
			bomb = NULL;
		}
	}
	void move()
	{
		if (MoveflagX) Enemy_x += 0.1;
		if (Enemy_x >= 680.0) MoveflagX = false;
		if (!MoveflagX) Enemy_x -= 0.1;
		if (Enemy_x <= 0.0) MoveflagX = true;
		if (MoveflagY) Enemy_y += 0.1;
		if (Enemy_y >= 180.0) MoveflagY = false;
		if (!MoveflagY) Enemy_y -= 0.1;
		if (Enemy_y <= 0.0) MoveflagY = true;
		Enemy_sprite.setPosition(Enemy_x, Enemy_y);
	}
	void VerticalMove()
	{
		if (VmoveFlag == true)
		{
			delta_y += 0.1;
		}
		if (delta_y >= 100)
		{
			VmoveFlag = false;
		}
		if (VmoveFlag == false)
			delta_y -= 0.1;
		if (delta_y < 0)
		{
			VmoveFlag = true;
		}
		Enemy_sprite.setPosition(Enemy_x, Enemy_y + delta_y);
	}
	void horizontalMove()
	{
		if (VmoveFlag == true)
			delta_x += 0.1;
		if (delta_x >= 100)
			VmoveFlag = false;
		if (VmoveFlag == false)
			delta_x -= 0.1;
		if (delta_x < -100)
			VmoveFlag = true;
		Enemy_sprite.setPosition(Enemy_x + delta_x, Enemy_y + delta_y);
	}
};
class Gamma : public Invader
{
public:
	Gamma(float randomX, float randomY)
	{
		Enemy_x = randomX;
		Enemy_y = randomY;
		Enemy_tex.loadFromFile("img/enemy_3.png");
		Enemy_sprite.setTexture(Enemy_tex);
		Enemy_sprite.setPosition(Enemy_x, Enemy_y);
		Enemy_sprite.setScale(0.55, 0.55);
		bomb = NULL; MoveflagX = true; MoveflagY = true;
		delta_x = 0; delta_y = 0; VmoveFlag = true;
		EnemyDisplayFlag = true;
		for (int i = 0; i < 3; i++)
			DF[i] = NULL;
		ifAlpha = false;
		ifBeta = false;
		ifGama = true; PlayerPosition = 0;
	}
	void BombTime(float X = 0.0, float Y = 0.0)
	{
		bomb = new Bomb(Enemy_x + delta_x, Enemy_y + delta_y);
	}
	void fire() 
	{
		if(EnemyLevel == 1)
			bomb->bombY += 0.5;
		if(EnemyLevel==2)
			bomb->bombY += 0.7;
		if (EnemyLevel >= 3)
			bomb->bombY += 0.9;

		bomb->sprite.setPosition(bomb->bombX, bomb->bombY);

		if (bomb->bombY >= 680)
		{
			bomb = NULL;
		}
	}
	void move()
	{
		if (MoveflagX) Enemy_x += 0.1;
		if (Enemy_x >= 680.0) MoveflagX = false;
		if (!MoveflagX) Enemy_x -= 0.1;
		if (Enemy_x <= 0.0) MoveflagX = true;
		if (MoveflagY) Enemy_y += 0.1;
		if (Enemy_y >= 180.0) MoveflagY = false;
		if (!MoveflagY) Enemy_y -= 0.1;
		if (Enemy_y <= 0.0) MoveflagY = true;
		Enemy_sprite.setPosition(Enemy_x, Enemy_y);
	}
	void VerticalMove()
	{
		if (VmoveFlag == true)
		{
			delta_y += 0.1;
		}
		if (delta_y >= 100)
		{
			VmoveFlag = false;
		}
		if (VmoveFlag == false)
			delta_y -= 0.1;
		if (delta_y < 0)
		{
			VmoveFlag = true;
		}
		Enemy_sprite.setPosition(Enemy_x, Enemy_y + delta_y);
	}
	void horizontalMove()
	{
		if (VmoveFlag == true)
			delta_x += 0.1;
		if (delta_x >= 100)
			VmoveFlag = false;
		if (VmoveFlag == false)
			delta_x -= 0.1;
		if (delta_x < -100)
			VmoveFlag = true;
		Enemy_sprite.setPosition(Enemy_x + delta_x, Enemy_y + delta_y);
	}
};
class Dragon : public Enemy
{
public:
	Dragon()
	{
		Enemy_x = -100;
		Enemy_y = -100;
		Enemy_tex.loadFromFile("img/dragon.png");
		Enemy_sprite.setTexture(Enemy_tex);
		Enemy_sprite.setPosition(Enemy_x, Enemy_y);
		Enemy_sprite.setScale(0.95, 0.95);
		for (int i = 0; i < 3; i++)
			DF[i] = NULL;
		ifMOnster = false;
		Scoreflag = true; PlayerPosition = 0;
	}
	void BombTime(float X = 0.0, float Y = 0.0)
	{
			PlayerPosition = X;
			DF[0] = new DragonFire(Enemy_x, Enemy_y);
			DF[1] = new DragonFire(Enemy_x, Enemy_y);
			DF[2] = new DragonFire(Enemy_x, Enemy_y);
	}
	void fire()
	{
		for (int i = 0; i < 3; i++)
		{
			if(DF[i]!=NULL)
			DF[i]->DragonFireY += (0.4*i);
		}
		if (PlayerPosition < 280)
		{
			for (int i = 0; i < 3; i++)
				if (DF[i] != NULL)
					DF[i]->DragonfireX -= 0.4;
		}
		else if (PlayerPosition > 400)
		{
			for (int i = 0; i < 3; i++)
				if (DF[i] != NULL)
					DF[i]->DragonfireX += 0.4;
		}
		
		
		for (int i = 0; i < 3; i++)
		{
			if(DF[i]!=NULL)
			DF[i]->Firesprite.setPosition(DF[i]->DragonfireX, DF[i]->DragonFireY);
		}
			
		for (int i = 0; i < 3; i++)
			{
			if (DF[i] != NULL && DF[i]->DragonFireY >= 680)
			{
				DF[i] = NULL;
				if(Scoreflag)
				ScoreCount = 50;
			}
			else

				ScoreCount = 0;
			}
		bool flag = false;
		for (int i = 0; i < 3; i++)
		{
			if (DF[i] != NULL)
				flag = true;
		}
		if (!flag) Scoreflag = true;
				
		
	}
	void move(){}
	void VerticalMove() {}
	void horizontalMove() {}
	


};
class Monster : public Enemy
{
public:
	Monster(float random =0.0)
	{
		Enemy_x = -100;
		Enemy_y = -100;
		if(EnemyLevel==1)
		    Enemy_tex.loadFromFile("img/monster.png");
		if(EnemyLevel >=2)
			Enemy_tex.loadFromFile("img/monster1.png");

		Enemy_sprite.setTexture(Enemy_tex);
		Enemy_sprite.setPosition(Enemy_x, Enemy_y);
		Enemy_sprite.setScale(0.15, 0.15);
		MoveflagX = true; MoveflagY = true; Light = NULL; ScoreCount = 0;
		for (int i = 0; i < 3; i++)
			DF[i] = NULL;
		DF = NULL;
		Scoreflag = true;
		ifMOnster = true; PlayerPosition = 0;
	}
	void BombTime(float X = 0.0, float Y = 0.0)
	{
		Light = new Lightining(Enemy_x, Enemy_y); ScoreCount = 0;
	}
	void fire()
	{
		if(EnemyLevel == 1)
		Light->LightiningY += 0.7;

		if (EnemyLevel >= 2)
		Light->LightiningY += 0.9;

		Light->sprite.setPosition(Light->LightiningX, Light->LightiningY);

		if (Light->LightiningY >= 680)
		{
			Light = NULL;
			if(Scoreflag)
			ScoreCount = 40;
		}
		else
			ScoreCount = 0;
		if (Light == NULL)
			Scoreflag = true;
	}
	void move()
	{
		if (MoveflagX) Enemy_x += 0.3;
		if (Enemy_x >= 600.0) MoveflagX = false;
		if (!MoveflagX) Enemy_x -= 0.3;
		if (Enemy_x <= 0.0) MoveflagX = true;
		Enemy_sprite.setPosition(Enemy_x, Enemy_y);
	}
	void VerticalMove()
	{

	}
	void horizontalMove()
	{

	}
};
