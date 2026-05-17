#include"game.h"
int Game::LeveL = 1;
void Game :: PauseScreen()
{
    Sprite background;
    Texture bg_texture;
    Font font;
    font.loadFromFile("fonts/Grind_Demolished.ttf");

    bg_texture.loadFromFile("img/Pause Screen.png");
    background.setTexture(bg_texture);
    background.setScale(0.75, 0.75);

    RectangleShape playbutton(Vector2f(150, 50));
    playbutton.setPosition(270, 300);
    playbutton.setFillColor(Color::Transparent);
    Text text("Resume", font, 40);
    text.setFillColor(Color::White);
    text.setPosition(280, 300);

    RectangleShape Instructionbutton(Vector2f(320, 50));
    Instructionbutton.setPosition(230, 400);
    Instructionbutton.setFillColor(Color::Transparent);
    Text text1("INSTRUCTION", font, 40);
    text1.setFillColor(Color::White);
    text1.setPosition(240, 400);

    RectangleShape Stopbutton(Vector2f(150, 50));
    Stopbutton.setPosition(310, 500);
    Stopbutton.setFillColor(Color::Transparent);
    Text text2("QUIT", font, 40);
    text2.setFillColor(Color::White);
    text2.setPosition(315, 500);

    RectangleShape HighScorebutton(Vector2f(150, 50));
    HighScorebutton.setPosition(240, 600);
    HighScorebutton.setFillColor(Color::Transparent);
    Text text3("HighScore", font, 40);
    text3.setFillColor(Color::White);
    text3.setPosition(250, 600);

    RenderWindow window(VideoMode(780, 780), "Pause");
    Clock clock;
    float timer = 0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {

                window.close();
                return;
            }
        }
       // if (Keyboard::isKeyPressed(Keyboard::P))
         //   return;
        if (e.type == Event::MouseButtonPressed)
        {

            if (e.mouseButton.button == Mouse::Left)
            {
                if (playbutton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                {
                    timer = 0; timer1 = 0; timer2 = 0;  LevelTime = 0.0;
                    window.close(); return;

                }
                else if (Stopbutton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                {
                    GameClose = true;
                    window.close(); return;
                }
                else if (Instructionbutton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                {
                    {
                        Sprite background_1;
                        Texture bg_texture_1;
                        bg_texture_1.loadFromFile("img/Instructions.PNG");
                        background_1.setTexture(bg_texture_1);
                        background_1.setScale(0.50, 0.52);
                        RenderWindow window1(VideoMode(540, 540), "Instructions");
                        Clock clock1;
                        float timer1 = 0;

                        while (window1.isOpen())
                        {
                            float time1 = clock1.getElapsedTime().asSeconds();
                            clock1.restart();
                            timer1 += time1;
                            Event Eve;
                            while (window1.pollEvent(Eve))
                            {
                                if (Eve.type == Event::Closed)
                                    window1.close();
                            }
                            window1.draw(background_1);
                            window1.display();
                        }
                    }
                }
                else if (HighScorebutton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                {
                    {
                        Sprite background_1;
                        Texture bg_texture_1;
                        bg_texture_1.loadFromFile("img/HIGHSCORE.PNG");
                        background_1.setTexture(bg_texture_1);
                        background_1.setScale(0.50, 0.52);
                        RenderWindow Scorewindow(VideoMode(540, 540), "HighestScore");
                        Font f;
                        int ArrayScore[3];
                        f.loadFromFile("fonts/BebasNeue-Regular.otf");
                        ifstream File("Score.txt");
                        for (int i = 0; i < 3; i++)
                        {
                            File >> ArrayScore[i];
                        }
                        int NameArray[3] = { 1,2,3 };
                        File.close();
                        for (int i = 0; i < 3; i++)
                        {
                            for (int j = i; j < 3; j++)
                            {
                                if (ArrayScore[i] < ArrayScore[j])
                                {
                                    int temp = ArrayScore[i];
                                    ArrayScore[i] = ArrayScore[j];
                                    ArrayScore[j] = temp;
                                    temp = NameArray[i];
                                    NameArray[i] = NameArray[j];
                                    NameArray[j] = temp;
                                }
                            }
                        }
                        Text Last5[3];
                        for (int i = 0; i < 3; i++) {
                            Last5[i].setFont(font);
                            Last5[i].setCharacterSize(24);
                            Last5[i].setFillColor(Color::White);
                            Last5[i].setString(std::to_string(ArrayScore[i])
                                += ("  Player  " + to_string(NameArray[i])));
                            Last5[i].setPosition(120, 250 + i * 50);
                        }

                        while (Scorewindow.isOpen())
                        {

                            Event event1;
                            while (Scorewindow.pollEvent(event1))
                            {
                                if (event1.type == Event::Closed) {
                                    Scorewindow.close();
                                }
                            }
                            Scorewindow.clear();
                            Scorewindow.draw(background_1);
                            for (int i = 0; i < 3; i++) {
                                Scorewindow.draw(Last5[i]);
                            }

                            Scorewindow.display();

                        }
                    }
                }
            }
        }
        Vector2i mousePos = Mouse::getPosition(window);
        int mouseX = mousePos.x;
        int mouseY = mousePos.y;
        if (mouseX >= 280 && mouseY >= 300 && mouseX <= 420 && mouseY <= 350)
            text.setFillColor(Color::Yellow);
        else
            text.setFillColor(Color::White);
        if (mouseX >= 240 && mouseY >= 400 && mouseX <= 500 && mouseY <= 450)
            text1.setFillColor(Color::Yellow);
        else
            text1.setFillColor(Color::White);
        if (mouseX >= 315 && mouseY >= 500 && mouseX <= 415 && mouseY <= 550)
            text2.setFillColor(Color::Yellow);
        else
            text2.setFillColor(Color::White);
        if (mouseX >= 250 && mouseY >= 600 && mouseX <= 550 && mouseY <= 650)
            text3.setFillColor(Color::Yellow);
        else
            text3.setFillColor(Color::White);

        window.clear(Color::Black);
        window.draw(background);
        window.draw(playbutton);
        window.draw(text);
        window.draw(Instructionbutton);
        window.draw(text1);
        window.draw(Stopbutton);
        window.draw(text2);
        window.draw(HighScorebutton);
        window.draw(text3);

        window.display();
    }

}
void Game :: ScoreSetString()
{
    if (MonsterPointer != NULL)
        Total_Score += MonsterPointer->ScoreCount;
    Total_Score += S.Score;
    Score_text.setString("Score :" + to_string(Total_Score)
        + "\n\nLives :" + to_string(S.SpaceShip_Lives)
        + "\n\nLeveL :" + to_string(LeveL));
    LevelText.setString("LeveL " + to_string(LeveL));
}
void Game :: AllFileHandling()
{
    std::ifstream file("Score.txt", std::ios::app);
    int OLDSCORE[50]; int Total = 0;
    while (1)
    {
        if (!(file >> OLDSCORE[Total])) break; Total++;
    }
    file.clear(); file.close();

    for (int i = Total + 1; i > 0; i--)
        OLDSCORE[i] = OLDSCORE[i - 1];
    OLDSCORE[0] = Total_Score;
    Total++;
    ofstream File("Score.txt");
    for (int i = 0; i < Total; i++)
        File << OLDSCORE[i] << endl;
}
void Game::SpaceShipLiveChecker()
{
    if (S.SpaceShip_Lives <= 0)
    {
        this->GameClose = true;
    }
}
void Game::EndScreen()
{
    Sprite background;
    Texture bg_texture;
    Font font;
    font.loadFromFile("fonts/Grind_Demolished.ttf");

    bg_texture.loadFromFile("img/endScreen.png");
    background.setTexture(bg_texture);
    background.setScale(0.75, 0.75);

    RectangleShape playbutton(Vector2f(150, 50));
    playbutton.setPosition(150, 400);
    playbutton.setFillColor(Color::Transparent);
    Text text("Continue", font, 40);
    text.setFillColor(Color::White);
    text.setPosition(160, 400);

    RectangleShape Instructionbutton(Vector2f(320, 50));
    Instructionbutton.setPosition(190, 500);
    Instructionbutton.setFillColor(Color::Transparent);
    Text text1("Give Up", font, 40);
    text1.setFillColor(Color::White);
    text1.setPosition(180, 500);
    RenderWindow window(VideoMode(780, 780), "Pause");
    Clock clock;
    float timer = 0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {

                window.close();
                this->S.SpaceShip_Lives = 3;
                return;
            }
        }
        if (e.type == Event::MouseButtonPressed)
        {

            if (e.mouseButton.button == Mouse::Left)
            {
                if (playbutton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                {
                    this->S.SpaceShip_Lives = 3;
                    timer = 0; timer1 = 0; timer2 = 0;  LevelTime = 0.0;
                    window.close(); return;

                }
                else if (Instructionbutton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                {
                    GameClose = true;
                    window.close(); return;
                }
               
            }
        }
        Vector2i mousePos = Mouse::getPosition(window);
        int mouseX = mousePos.x;
        int mouseY = mousePos.y;
        if (mouseX >= 150 && mouseY >= 400 && mouseX <= 420 && mouseY <= 450)
            text.setFillColor(Color::Yellow);
        else
            text.setFillColor(Color::White);
        if (mouseX >= 190 && mouseY >= 500 && mouseX <= 500 && mouseY <= 550)
            text1.setFillColor(Color::Yellow);
        else
            text1.setFillColor(Color::White);
     

        window.clear(Color::Black);
        window.draw(background);
        window.draw(playbutton);
        window.draw(text);
        window.draw(Instructionbutton);
        window.draw(text1);

        window.display();
    }
}