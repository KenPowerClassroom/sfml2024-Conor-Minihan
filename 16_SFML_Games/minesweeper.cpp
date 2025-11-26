#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

void setupTiles(int t_uncovered[][12], int t_game[][12]);

int minesweeper()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    int tileWidth=32; // width of tile
    int uncoveredGrid[12][12]; // bombs and numbers
    int gameGrid[12][12]; // covered tiles

    Texture t;
    t.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite tile(t);

   setupTiles(uncoveredGrid, gameGrid);

    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x/tileWidth;
        int y = pos.y/tileWidth;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
              if (e.key.code == Mouse::Left) gameGrid[x][y]=uncoveredGrid[x][y]; // reveals square
              else if (e.key.code == Mouse::Right) gameGrid[x][y]=11; // places flag
        }

        app.clear(Color::White);

        for (int row=1;row<=10;row++)
         for (int column=1;column<=10;column++)
          {
           if (gameGrid[x][y]==9) gameGrid[row][column]=uncoveredGrid[row][column]; // uncovers board if bomb is selected
           tile.setTextureRect(IntRect(gameGrid[row][column]*tileWidth,0,tileWidth,tileWidth));// otherwise fills board normally
           tile.setPosition(row*tileWidth, column*tileWidth);
           app.draw(tile);
          }

        app.display();
    }

    return 0;
}

void setupTiles(int t_uncovered[][12], int t_game[][12])
{
    for (int row = 1; row <= 10; row++) // 10 = covered tile
        for (int column = 1; column <= 10; column++)
        {
            t_game[row][column] = 10;
            if (rand() % 5 == 0)  t_uncovered[row][column] = 9; // 9 = bomb
            else t_uncovered[row][column] = 0;
        }
    t_uncovered[1][1] = 9;
    for (int row = 1; row <= 10; row++) // checks for adjecant bombs
        for (int column = 1; column <= 10; column++)
        {
            int n = 0;
            if (t_uncovered[row][column] == 9) continue;
            if (t_uncovered[row + 1][column] == 9) n++;
            if (t_uncovered[row][column + 1] == 9) n++;
            if (t_uncovered[row - 1][column] == 9) n++;
            if (t_uncovered[row][column - 1] == 9) n++;
            if (t_uncovered[row + 1][column + 1] == 9) n++;
            if (t_uncovered[row - 1][column - 1] == 9) n++;
            if (t_uncovered[row - 1][column + 1] == 9) n++;
            if (t_uncovered[row + 1][column - 1] == 9) n++;
            t_uncovered[row][column] = n;
        }
}