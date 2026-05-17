#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include<cstdlib>
#include<ctime>
using namespace std;
#include "spaceship.h"
#include"Enemy.h"
#include"Animation.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;
class Game
{
public:
    static int LeveL;
    Sprite background, background1; SoundBuffer buffer[7];
    Texture bg_texture,bg_texture1;
    Spaceship S; 
    Text Score_text; Font font;
    int Total_Score; bool GameClose;
    int ShapeCall;  bool AnimationComplete;
    Enemy** EnemyPointer = new Enemy * [16]; bool ShapeCall_flag;
    Animation* Animate; int DumyVar;
    LevelUp** levelup = new LevelUp *[4]; bool LevelAnimationComp;
    Text LevelText;
    Enemy* MonsterPointer;
    bool MonsterComingTransition;
    bool MonsterGoingTransiion; int Count = 0;
    float timer = 0, timer1 = 0, timer2 = 0, MonsterTime = 0.0, LevelTime = 0.0;
    MonsterPNG MonsterCaution;
    Game()
    {
        buffer[0].loadFromFile("sounds/sound2.wav");
        buffer[1].loadFromFile("sounds/danger.wav");
        buffer[2].loadFromFile("sounds/Swipe.wav");
        Animate = NULL; 
        bg_texture.loadFromFile("img/background.jpg");
        bg_texture1.loadFromFile("img/ScoreCount.png");
        background.setTexture(bg_texture);
        background1.setTexture(bg_texture1);
        background.setScale(2, 1.5); 
        background1.setScale(0.38, 0.38);
        Total_Score = 0;
        font.loadFromFile("fonts/norwester.otf");
        Score_text.setFont(font);
        Score_text.setCharacterSize(34);
        Score_text.setFillColor(sf::Color::White);
        Score_text.setPosition(50, 50);

        LevelText.setFont(font);
        LevelText.setString("Level 1");
        LevelText.setCharacterSize(100);
        LevelText.setFillColor(Color::White);
        LevelText.setPosition(240, 350);

        GameClose = false; 
        ShapeCall = -1; DumyVar = 0;
        AnimationComplete = false;
        LevelAnimationComp = false;
        for (int i = 0; i < 16; i++)
        {
            EnemyPointer[i] = NULL;
        }
        ShapeCall_flag = true;
        for (int i = 0; i < 4; i++)
            levelup[i] = NULL;

        MonsterPointer = NULL;
        MonsterComingTransition = false;
        MonsterGoingTransiion = false;

    }
    void ScoreSetString();

    void start_game()
    {
        
        RenderWindow scoreWindow(VideoMode(400, 400), "Score-Count");
        scoreWindow.clear();
        scoreWindow.setPosition(Vector2i(1350, 200));
        scoreWindow.display();
        ScoreSetString();

        Sound sound[7];
        for(int i =0; i<7; i++)
        sound[i].setBuffer(buffer[i]);
        sound[0].play();
        sound[0].setLoop(true);
        
        srand(time(0));
        RenderWindow window(VideoMode(780, 780), title);
        Clock clock;
        
       
        Animate = new Animation(S.x, S.y);
        InitializeLevel();
        while (window.isOpen())
        {
            ScoreSetString();
            if ((ShapeCall == 3||ShapeCall==7) && LevelAnimationComp)
            {
                LevelAnimationComp = false;
                InitializeLevel(); LeveL++;
                AnimationComplete = false;
                S.delta_y = 0.0; S.y = 700; S.delta_x = 0.0; S.x = 340;
                Animate = new Animation(S.x, S.y);
            }
            if (!LevelAnimationComp)
            {
                LevelAnimationComp = LevelUpAnimation();
                if (LevelAnimationComp)
                {
                    for (int i = 0; i < 4; i++)
                        levelup[i] = NULL;   
                    ShapeCall++;
                }
            }

            if(LevelAnimationComp && !AnimationComplete)
            {
                AnimationComplete = SpaceShipAnimation();
                if (AnimationComplete)
                {
                    S.y = 700;
                    Animate = NULL;
                }
            }
            if (AnimationComplete && ShapeCall_flag)
            {
                SettingEnemyPositions();
                ShapeCall_flag = false;
            }
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            if (AnimationComplete)
            {
                timer += time;  timer1 += time;  timer2 += time;
                MonsterTime += time; LevelTime += time;
            }
           
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                {
                    
                    scoreWindow.close();
                    window.close();
                }                     	    
            }
            if (GameClose) 
                window.close();

            if (AnimationComplete)
            {
                if (Keyboard::isKeyPressed(Keyboard::P))
                    PauseScreen();
                if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
                    S.move("l");    // Player will move to left
                if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
                    S.move("r");  //player will move to right
                if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
                    S.move("u");    //playet will move upwards
                if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
                    S.move("d");
            }
            ////////////////////////////////////////////////
            /////  Call your functions here            ////
            if (AnimationComplete)
            {
                S.fire(); 
                S.AddOn_Caller();
                BulletStrikeCheck();
                BombStrikeCheck();
                KillEnemy();
                ShapeChanger();
                CheckSpaceShipStrike();
                if (S.PowerUpVar)
                {
                    Count++;
                    if (Count >= 1500)
                    {
                        S.PowerUpVar = false;
                        Count = 0;
                    }
                }
                if (S.FireUpVar)
                {
                    Count++;
                    if (Count >= 1500)
                    {
                        S.FireUpVar = false;
                        Count = 0;
                    }
                }
            }
            
            ///////////////////////  Finalize//////////////
            if (AnimationComplete)
            for (int i = 0; i < 16; i++)
            {
                if (EnemyPointer[i] != NULL)
                {
                    if (ShapeCall % 2 == 0)
                        EnemyPointer[i]->horizontalMove();
                    else
                        EnemyPointer[i]->VerticalMove();
                    if (i >= 0 && i < 5)
                    {
                        if (timer1 >= 7.0 && EnemyPointer[i]->bomb == NULL)
                        {
                            EnemyPointer[i]->BombTime();
                            if(i==4) timer1 = 0.0;
                        }
                    }
                    else if (i >= 5 && i < 10)
                    {
                        if (timer2 >= 10.0 && EnemyPointer[i]->bomb == NULL)
                        {
                            EnemyPointer[i]->BombTime();
                            if(i==9) timer2 = 0.0;
                        }
                    }
                    else if (i >=10)
                    {
                        if (timer >= 15.0 && EnemyPointer[i]->bomb == NULL)
                        {
                            EnemyPointer[i]->BombTime();
                         if(i==15)   timer = 0.0;
                        }
                    }
                    if (EnemyPointer[i]->bomb != NULL)
                        EnemyPointer[i]->fire();
                }
                    
            }
            
            if (S.Bul[0] == NULL) {
                S.BulletTime();
                
            }
            
            if (MonsterTime >= 50.0 && MonsterPointer == NULL)
            {
                for (int i = 0; i < 16; i++)
                    EnemyPointer[i] = NULL;
                
                int Var = 1 + rand() % 2;
                if(Var ==1)
                    MonsterPointer = new Monster;
                if(Var ==2)
                    MonsterPointer = new Dragon;
                sound[1].play();
            }
            if (MonsterPointer != NULL)
            {
                if (MonsterPointer->ifMOnster && MonsterPointer->Light == NULL
                    && MonsterComingTransition && !MonsterGoingTransiion)
                    MonsterPointer->BombTime();
                else if (!MonsterPointer->ifMOnster && (MonsterPointer->DF[0] == NULL
                    || MonsterPointer->DF[1] == NULL || MonsterPointer->DF[2] == NULL)
                    && MonsterComingTransition && !MonsterGoingTransiion)
                    MonsterPointer->BombTime(S.delta_x+S.x , S.delta_y+S.y);

                if (MonsterPointer->Light != NULL && MonsterComingTransition && !MonsterGoingTransiion)
                {
                    MonsterPointer->fire();
                    if(MonsterPointer!=NULL &&MonsterPointer->Light!=NULL &&
                        MonsterPointer->Light->LightiningY>=400)
                    MonsterPointer->move();
                }
                else if (MonsterPointer->DF != NULL && MonsterComingTransition && !MonsterGoingTransiion)
                {
                    MonsterPointer->fire();
                }
            }
            if (MonsterTime >= 70.0)
            {
                MonsterGoingTransiion = true;
                if (MonsterGoingTransiion)
                {
                    MonsterGoingTransiion = MonsterGTransition();
                    if (MonsterGoingTransiion)
                    {
                        MonsterPointer = NULL;
                        ShapeCall--; 
                        MonsterTime = 0.0; timer = 0; timer1 = 0; timer2 = 0;
                        MonsterGoingTransiion = false;
                        MonsterComingTransition = false;
                    }
                }
                
            }
            if (MonsterPointer != NULL)
            {
                if (!MonsterComingTransition)
                {
                    MonsterComingTransition = MonsterTransition();
                }
            }
            //////////////////////////////////////////////
            if (S.SpaceShip_Lives < 0)
            {
                EndScreen(); if (GameClose) window.close();
            }

            window.clear(Color::Black); //clears the screen
            window.draw(background);  // setting background

            if (LevelAnimationComp)
            {
                window.draw(S.sprite);
                if (S.AddOnPointer != nullptr)
                    window.draw(S.AddOnPointer->AddOn_sprite);

                if (!S.PowerUpVar && AnimationComplete && S.Bul[0] != nullptr)
                    window.draw(S.Bul[0]->Bullet_sprite);

                if ((S.PowerUpVar||S.FireUpVar) && AnimationComplete)
                for (int i = 0; i < 7; i++)
                {
                    if (S.Bul[i] != NULL)
                        window.draw(S.Bul[i]->Bullet_sprite);
                    

                }
            }
            
            
            if(AnimationComplete)
            for (int i = 0; i < 16; i++)
            {
                if (EnemyPointer[i] != NULL)
                {
                    if(EnemyPointer[i]->EnemyDisplayFlag)
                    window.draw(EnemyPointer[i]->Enemy_sprite);

                    if (EnemyPointer[i]->bomb != NULL)
                        window.draw(EnemyPointer[i]->bomb->sprite);
                }
                    
            }

            if (LevelAnimationComp && !AnimationComplete)
            {
                if(Animate != NULL && DumyVar%2 == 0)
                window.draw(Animate->Explosion);
            }

            if (!LevelAnimationComp)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (levelup[i] != NULL)
                        window.draw(levelup[i]->Background);
                }
            }
            if (!LevelAnimationComp)
                window.draw(LevelText);

            if (AnimationComplete)
            if (MonsterPointer != NULL)
            {
                if (MonsterPointer->Light != NULL)
                    window.draw(MonsterPointer->Light->sprite);
                    for (int i = 0; i < 3; i++)
                    {
                        if (MonsterPointer->DF != NULL && MonsterPointer->DF[i] != NULL)
                            window.draw(MonsterPointer->DF[i]->Firesprite);
                    }
                window.draw(MonsterPointer->Enemy_sprite);
            }
            if (MonsterPointer != NULL && !MonsterComingTransition)
            {
                if (DumyVar % 4 == 0)
                {
                    window.draw(MonsterCaution.Explosion);
                }
            }
            window.display(); 

            

            scoreWindow.clear();
            scoreWindow.draw(background1);
            scoreWindow.draw(Score_text);
            scoreWindow.display();
            DumyVar++;
        }
          AllFileHandling();
    }
    void AllFileHandling();
    
    void PauseScreen();
    bool SpaceShipAnimation()
    {
        if (Animate != NULL)
        {
            //Animate->Animation_Y -= 0.1;
            Animate->Explosion.setPosition(S.x+S.delta_x-20, S.y+S.delta_y-20);
        }

        S.delta_y -= 0.1; S.Bul[0]->Bullet_y -= 0.1;
            S.sprite.setPosition(S.x+S.delta_x, S.y+S.delta_y);
            if (S.y+ S.delta_y<= 600)
                return true;
            else
                return false;
    }
    bool EnemyAnimation()
    {

    }
    void SpaceShipLiveChecker();
    void SettingEnemyPositions()
    {
        if (ShapeCall <= 0)
        {
            int j = 0;
            for (int i = 0; i < 8; i++)
                EnemyPointer[i] = new Alpha(95 * i, 0);
            for (int i = 8; i < 12; i++)
            {
                EnemyPointer[i] = new Beta(95* j, 100); j++;
            }
            for (int i = 12; i < 16; i++)
            {
                EnemyPointer[i] = new Gamma(95 * j, 130); j++;
            }
        }
        else if (ShapeCall == 1)
        {
            for (int i = 0; i < 5; i++)
                EnemyPointer[i] = new Alpha(113 *(i+1), 0);
            int j = 1;
            for (int i = 5; i < 9; i++)
            {
                EnemyPointer[i] = new Gamma(136 * j, 80);
                j++;
            }
            j = 1;
            for (int i = 9; i < 12; i++)
            {
                EnemyPointer[i] = new Alpha(170 * j, 160);
                j++;
            }
            j = 1;
            for (int i = 12; i < 13; i++)
            {
                EnemyPointer[i] = new Gamma(256 * j, 240);
                j++;
            }
            j = 1;
            for (int i = 13; i < 14; i++)
                EnemyPointer[i] = new Gamma(426, 240);
            j = 1;
            for (int i = 14; i < 15; i++)
            {
                EnemyPointer[i] = new Alpha(340 * j, 290);
                j++;
            }
                
        }
        else if (ShapeCall == 2)
        {
            EnemyPointer[0] = new Alpha(340, 0);
            for (int i = 1; i < 3; i++)
                EnemyPointer[i] = new Beta(226 * i, 80);
            for (int i = 3; i < 6; i++)
                EnemyPointer[i] = new Alpha(170 * (i - 2), 160);
            for (int i = 6; i < 10; i++)
                EnemyPointer[i] = new Beta(136 * (i - 5), 240);
            for (int i = 10; i < 13; i++)
                EnemyPointer[i] = new Alpha(170 * (i - 9), 320);
            for (int i = 13; i < 15; i++)
                EnemyPointer[i] = new Beta(226 * (i - 12), 400);
            EnemyPointer[15] = new Alpha(340, 480);
        }
        else if (ShapeCall == 5)
        {
            for (int i = 0; i < 5; i++)
                EnemyPointer[i] = new Gamma(113 * (i + 1), 0);
            for (int i = 5; i < 10; i++)
                EnemyPointer[i] = new Alpha(113 * (i - 4), 100);
            for (int i = 10; i < 13; i++)
                EnemyPointer[i] = new Beta(113, 100 * (i - 8));
            for (int i = 13; i < 16; i++)
                EnemyPointer[i] = new Alpha(565, 100 * (i - 11));
        }
        else if (ShapeCall == 6)
        {
            for (int i = 0; i < 3; i++)
                EnemyPointer[i] = new Alpha(170 * (i + 1), 0);
            for (int i = 3; i < 5; i++)
                EnemyPointer[i] = new Beta(226 * (i - 2), 100);
            for (int i = 5; i < 8; i++)
                EnemyPointer[i] = new Gamma(170 * (i - 4), 200);
            for (int i = 8; i < 10; i++)
                EnemyPointer[i] = new Alpha(226 * (i - 7), 300);
            for (int i = 10; i < 13; i++)
                EnemyPointer[i] = new Beta(170 * (i - 9), 400);
        }
        else if (ShapeCall == 9)
        {
            for (int i = 0; i < 5; i++)
                EnemyPointer[i] = new Alpha(113 * (i + 1), 100);
            for (int i = 5; i < 10; i++)
                EnemyPointer[i] = new Beta(113 * (i - 4), 200);
            for (int i = 10; i < 15; i++)
                EnemyPointer[i] = new Gamma(113 * (i - 9), 300);
            EnemyPointer[15] = new Alpha(340, 0);
        }
        else if (ShapeCall == 10)
        {
            for (int i = 0; i < 5; i++)
                EnemyPointer[i] = new Alpha(113 * (i + 1), 100);
            for (int i = 5; i < 10; i++)
                EnemyPointer[i] = new Beta(113 * (i - 4), 200);
            for (int i = 10; i < 15; i++)
                EnemyPointer[i] = new Gamma(113 * (i - 9), 300);
            EnemyPointer[15] = new Alpha(340, 0);
        }
        else if (ShapeCall >= 11)
        {
            for (int i = 0; i < 3; i++)
                EnemyPointer[i] = new Alpha(170 * (i + 1), 0);
            for (int i = 3; i < 5; i++)
                EnemyPointer[i] = new Beta(226 * (i - 2), 100);
            for (int i = 5; i < 8; i++)
                EnemyPointer[i] = new Gamma(170 * (i - 4), 200);
            for (int i = 8; i < 10; i++)
                EnemyPointer[i] = new Alpha(226 * (i - 7), 300);
            for (int i = 10; i < 13; i++)
                EnemyPointer[i] = new Beta(170 * (i - 9), 400); 
        }
    }
    void BulletStrikeCheck()
    {
        for (int i = 0; i < 16; i++)
        {
            if ((!S.PowerUpVar && !S.FireUpVar) && S.Bul!=NULL && S.Bul[0] != NULL)
            {
                int X = S.Bul[0]->Bullet_x;
                int Y = S.Bul[0]->Bullet_y;

                if (EnemyPointer[i] != NULL)
                {
                    int Ex = EnemyPointer[i]->delta_x + EnemyPointer[i]->Enemy_x;
                    int Ey = EnemyPointer[i]->delta_y + EnemyPointer[i]->Enemy_y;
                    if (X + 40 >= Ex && X - 40 <= Ex && Y + 40 >= Ey && Y - 40 <= Ey)
                    {
                        EnemyPointer[i]->EnemyDisplayFlag = false;
                        if (EnemyPointer[i]->ifAlpha) Total_Score += 10;
                        if (EnemyPointer[i]->ifBeta)Total_Score += 20;
                        if (EnemyPointer[i]->ifGama) Total_Score += 30;
                        S.Bul[0] = NULL;
                    }
                }
            }
            else if (S.PowerUpVar  && S.Bul != NULL)
            {
                for (int j = 0; j < 7; j++)
                {
                    if (S.Bul[j] != NULL) {
                        int X = S.Bul[j]->Bullet_x;
                        int Y = S.Bul[j]->Bullet_y;

                        if (EnemyPointer[i] != NULL)
                        {
                            int Ex = EnemyPointer[i]->delta_x + EnemyPointer[i]->Enemy_x;
                            int Ey = EnemyPointer[i]->delta_y + EnemyPointer[i]->Enemy_y;
                            if (X + 40 >= Ex && X - 40 <= Ex && Y + 40 >= Ey && Y - 40 <= Ey)
                            {
                                if (EnemyPointer[i]->EnemyDisplayFlag && EnemyPointer[i]->ifAlpha) Total_Score += 10;
                                if (EnemyPointer[i]->EnemyDisplayFlag && EnemyPointer[i]->ifBeta)Total_Score += 20;
                                if (EnemyPointer[i]->EnemyDisplayFlag && EnemyPointer[i]->ifGama) Total_Score += 30;
                                EnemyPointer[i]->EnemyDisplayFlag = false;  
                                //S.Bul[j] = NULL;
                            }
                        }
                    }
                }
            }
            else if (S.FireUpVar && S.Bul != NULL)
            {
                for (int j = 0; j < 7; j++)
                {
                    if (S.Bul[j] != NULL) {
                        int X = S.Bul[j]->Bullet_x;
                        int Y = S.Bul[j]->Bullet_y;

                        for(int k =0; k<16; k++)
                        if (EnemyPointer[k] != NULL)
                        {
                            for (int l = 0; l < 7; l++)
                            {
                                if (S.Bul[l] != NULL) {
                                    X = S.Bul[l]->Bullet_x;
                                    Y = S.Bul[l]->Bullet_y;
                                }

                                int Ex = EnemyPointer[k]->delta_x + EnemyPointer[k]->Enemy_x;
                                int Ey = EnemyPointer[k]->delta_y + EnemyPointer[k]->Enemy_y;
                                if (X + 80 >= Ex && X - 80 <= Ex && Y + 80 >= Ey && Y - 80 <= Ey)
                                {
                                    if (EnemyPointer[k]->EnemyDisplayFlag  && EnemyPointer[k]->ifAlpha) Total_Score += 10;
                                    if (EnemyPointer[k]->EnemyDisplayFlag  && EnemyPointer[k]->ifBeta)Total_Score += 20;
                                    if (EnemyPointer[k]->EnemyDisplayFlag  && EnemyPointer[k]->ifGama) Total_Score += 30;
                                    EnemyPointer[k]->EnemyDisplayFlag = false;
                                    // S.Bul[j] = NULL;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    void BombStrikeCheck()
    {
        if (S.PowerUpVar)return;
        for (int i = 0; i < 16; i++)
        {
            int X = S.delta_x + S.x;
            int Y = S.delta_y + S.y;
            if (EnemyPointer[i] != NULL && EnemyPointer[i]->bomb!=NULL)
            {
                int Ex = EnemyPointer[i]->bomb->bombX;
                int Ey = EnemyPointer[i]->bomb->bombY;
                if (X + 50 >= Ex && X - 20 <= Ex && Y + 10 >= Ey && Y - 10 <= Ey)
                {
                    this->AnimationComplete = false;
                    S.delta_y = 0.0; S.y = 700; S.delta_x = 0.0; S.x = 340;
                    Animate = new Animation(S.x, S.y);
                    for (int j = 0; j < 16; j++)
                        if(EnemyPointer[j]!=NULL)
                        EnemyPointer[j]->bomb = NULL;
                    this->S.SpaceShip_Lives--;
                }
            }
        }
        if (MonsterPointer != NULL)
        {
            if (MonsterPointer->Light != NULL)
            {
                int Ex = MonsterPointer->Light->LightiningX;
                int Ey = MonsterPointer->Light->LightiningY;
                int X = S.x + S.delta_x;
                int Y = S.y + S.delta_y;
                if (X + 50 >= Ex && X - 20 <= Ex && Y + 10 >= Ey && Y - 10 <= Ey)
                {
                    this->AnimationComplete = false;
                    S.delta_y = 0.0; S.y = 700; S.delta_x = 0.0; S.x = 340;
                    Animate = new Animation(S.x, S.y);
                    MonsterPointer->Light = NULL;
                    this->S.SpaceShip_Lives--;
                    MonsterPointer->Scoreflag = false;
                }
            }
            else if (MonsterPointer->DF != NULL)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (MonsterPointer->DF[i] != NULL)
                    {
                        int Ex = MonsterPointer->DF[i]->DragonfireX;
                        int Ey = MonsterPointer->DF[i]->DragonFireY;
                        int X = S.x + S.delta_x;
                        int Y = S.y + S.delta_y;
                        if (X + 50 >= Ex && X - 20 <= Ex && Y + 10 >= Ey && Y - 10 <= Ey)
                        {
                            this->AnimationComplete = false;
                            S.delta_y = 0.0; S.y = 700; S.delta_x = 0.0; S.x = 340;
                            Animate = new Animation(S.x, S.y);
                            for(int j =0; j<3; j++)
                            MonsterPointer->DF[j] = NULL;
                            this->S.SpaceShip_Lives--;
                            MonsterPointer->Scoreflag = false;
                        }
                    }

                }
            }
        }
    }
    void KillEnemy()
    {
        for (int i = 0; i < 16; i++)
        {
            if (EnemyPointer[i] != NULL && EnemyPointer[i]->EnemyDisplayFlag == false)
            {
                if (EnemyPointer[i]->bomb == NULL)
                    EnemyPointer[i] = NULL;
            }
        }
    }
    void ShapeChanger()
    {
        bool flag = true;
        for (int i = 0; i < 16; i++)
        {
            if (EnemyPointer[i] != NULL)
                flag = false;
        }
        if (flag)
        {
            if (ShapeCall != 7 && ShapeCall != 3 && MonsterPointer == NULL)
            {
                ShapeCall++;
                SettingEnemyPositions();
                //cout << ShapeCall;
            }  
        }
    }
    void AnimationWhileDistroying()
    {

    }
    bool LevelUpAnimation()
    {
        levelup[0]->levelUp_Y -= 0.3;
        levelup[0]->levelUp_X -= 0.3;
        levelup[0]->Background.setPosition(levelup[0]->levelUp_X, levelup[0]->levelUp_Y);

        levelup[1]->levelUp_Y += 0.3;
        levelup[1]->levelUp_X += 0.3;
        levelup[1]->Background.setPosition(levelup[1]->levelUp_X, levelup[1]->levelUp_Y);
        
        levelup[2]->levelUp_Y -= 0.3;
        levelup[2]->levelUp_X += 0.3;
        levelup[2]->Background.setPosition(levelup[2]->levelUp_X, levelup[2]->levelUp_Y);

        levelup[3]->levelUp_Y += 0.3;
        levelup[3]->levelUp_X -= 0.3;
        levelup[3]->Background.setPosition(levelup[3]->levelUp_X, levelup[3]->levelUp_Y);

        if (levelup[0]->levelUp_Y <= 0)
            return true;
        else
            return false;
    }
    void InitializeLevel()
    {
        levelup[0] = new LevelUp;
        levelup[1] = new LevelUp(0, 0, 1);
        levelup[2] = new LevelUp(0, 700, 2);
        levelup[3] = new LevelUp(680, 0, 3);

    }
    bool MonsterTransition()
    {
        if (MonsterPointer != NULL)
        {
            MonsterPointer->Enemy_x += 0.35;
            MonsterPointer->Enemy_y += 0.3;
            MonsterPointer->Enemy_sprite.setPosition(MonsterPointer->Enemy_x, MonsterPointer->Enemy_y);
            if (MonsterPointer->Enemy_y>= 200)
            return true;
            else
                return false;
        }
       
    }
    bool MonsterGTransition()
    {
        if (MonsterPointer != NULL)
        {
            MonsterPointer->Enemy_x += 0.9;
            MonsterPointer->Enemy_y -= 0.3;
            MonsterPointer->Enemy_sprite.setPosition(MonsterPointer->Enemy_x, MonsterPointer->Enemy_y);
            if (MonsterPointer->Enemy_y <= 0 && MonsterPointer->Enemy_x>=680)
                return true;
            else
                return false;
        }
    }
    void CheckSpaceShipStrike()
    {
        if (S.PowerUpVar)return;
        for (int i = 0; i < 16; i++)
        {
            if (EnemyPointer[i] != NULL)
            {
                int Ex = EnemyPointer[i]->Enemy_x + EnemyPointer[i]->delta_x;
                int Ey = EnemyPointer[i]->Enemy_y + EnemyPointer[i]->delta_y;
                int X = S.x + S.delta_x;
                int Y = S.y + S.delta_y;
                if (X + 80 >= Ex && X - 80 <= Ex && Y + 80 >= Ey && Y - 80 <= Ey)
                {
                    this->AnimationComplete = false;
                    S.delta_y = 0.0; S.y = 700; S.delta_x = 0.0; S.x = 340;
                    Animate = new Animation(S.x, S.y);
                    this->S.SpaceShip_Lives--;
                }
            }
        }
        if (MonsterPointer != NULL)
        {
            int Ex = MonsterPointer->delta_x + MonsterPointer->Enemy_x;
            int Ey = MonsterPointer->delta_y + MonsterPointer->Enemy_y;
            int X = S.x + S.delta_x;
            int Y = S.y + S.delta_y;
            if (X + 180 >= Ex && X - 180 <= Ex && Y + 180 >= Ey && Y - 180 <= Ey)
            {
                this->AnimationComplete = false;
                S.delta_y = 0.0; S.y = 700; S.delta_x = 0.0; S.x = 340;
                Animate = new Animation(S.x, S.y);
                this->S.SpaceShip_Lives--;
            }
        }
    }
    void EndScreen();
};


