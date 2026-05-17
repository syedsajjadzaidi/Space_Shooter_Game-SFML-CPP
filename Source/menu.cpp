#include"menu.h"
Menu::Menu()
{
    font.loadFromFile("fonts/Grind_Demolished.ttf");
    bg_texture.loadFromFile("img/b1.png");
    background.setTexture(bg_texture);
    background.setScale(0.50, 0.52);
    buffer.loadFromFile("sounds/sound1.wav");
}
void Menu::display_menu()
{

    Game g;
    RenderWindow window(VideoMode(960, 540), "Menu");
    Clock clock;
    float timer = 0;
    Sound sound;
    sound.setBuffer(buffer);

    sound.play();
    sound.setLoop(true);

    ////////Play Button/////
    RectangleShape playbutton(Vector2f(150, 50));
    playbutton.setPosition(400, 100);
    playbutton.setFillColor(Color::Transparent);
    Text text("PLAY", font, 40);
    text.setFillColor(Color::White);
    text.setPosition(410, 100);

    ///////////Instruction Button //////
    RectangleShape Instructionbutton(Vector2f(320, 50));
    Instructionbutton.setPosition(320, 200);
    Instructionbutton.setFillColor(Color::Transparent);
    Text text1("INSTRUCTION", font, 40);
    text1.setFillColor(Color::White);
    text1.setPosition(330, 200);

    ///////Stop Button//////
    RectangleShape Stopbutton(Vector2f(150, 50));
    Stopbutton.setPosition(410, 300);
    Stopbutton.setFillColor(Color::Transparent);
    Text text2("QUIT", font, 40);
    text2.setFillColor(Color::White);
    text2.setPosition(420, 300);

    RectangleShape HighScorebutton(Vector2f(150, 50));
    HighScorebutton.setPosition(340, 400);
    HighScorebutton.setFillColor(Color::Transparent);
    Text text3("HighScore", font, 40);
    text3.setFillColor(Color::White);
    text3.setPosition(350, 400);

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            else if (e.type == Event::MouseButtonPressed)
            {

                if (e.mouseButton.button == Mouse::Left)
                {
                    if (playbutton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                    {
                        sound.stop();
                        window.close();
                        g.start_game();
                    }
                    else if (Stopbutton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                    {
                        sound.stop();
                        window.close();
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
                                +=("  Player  " + to_string(NameArray[i])));
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
            if (mouseX >= 410 && mouseY >= 100 && mouseX <= 530 && mouseY <= 150)
                text.setFillColor(Color::Yellow);
            else
                text.setFillColor(Color::White);
            if (mouseX >= 330 && mouseY >= 200 && mouseX <= 615 && mouseY <= 250)
                text1.setFillColor(Color::Yellow);
            else
                text1.setFillColor(Color::White);
            if (mouseX >= 420 && mouseY >= 300 && mouseX <= 560 && mouseY <= 350)
                text2.setFillColor(Color::Yellow);
            else
                text2.setFillColor(Color::White);
            if (mouseX >= 340 && mouseY >= 400 && mouseX <= 615 && mouseY <= 450)
                text3.setFillColor(Color::Yellow);
            else
                text3.setFillColor(Color::White);

        }
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