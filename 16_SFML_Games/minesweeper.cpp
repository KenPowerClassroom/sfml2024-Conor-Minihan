#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

void setupTile(int t_uncovered[][12], int t_game[][12]);

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

    //for (int row=1;row<=10;row++) // 10 = covered tile
    // for (int column=1;column<=10;column++)
    //  {
    //    gameGrid[row][column]=10;
    //    if (rand()%5==0)  uncoveredGrid[row][column]=9; // 9 = bomb
    //    else uncoveredGrid[row][column]=0;
    //  }

   setupTile(uncoveredGrid, gameGrid);

    for (int row=1;row<=10;row++) // checks for adjecant bombs
     for (int column=1;column<=10;column++)
      {
        int n=0;
        if (uncoveredGrid[row][column]==9) continue;
        if (uncoveredGrid[row+1][column]==9) n++;
        if (uncoveredGrid[row][column+1]==9) n++;
        if (uncoveredGrid[row-1][column]==9) n++;
        if (uncoveredGrid[row][column-1]==9) n++;
        if (uncoveredGrid[row+1][column+1]==9) n++;
        if (uncoveredGrid[row-1][column-1]==9) n++;
        if (uncoveredGrid[row-1][column+1]==9) n++;
        if (uncoveredGrid[row+1][column-1]==9) n++;
        uncoveredGrid[row][column]=n;
      }

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

void setupTile(int t_uncovered[][12], int t_game[][12])
{
    for (int row = 1; row <= 10; row++) // 10 = covered tile
        for (int column = 1; column <= 10; column++)
        {
            t_game[row][column] = 10;
            if (rand() % 5 == 0)  t_uncovered[row][column] = 9; // 9 = bomb
            else t_uncovered[row][column] = 0;
        }
}