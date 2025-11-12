#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int minesweeper()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    int w=32; // width of tile
    int grid[12][12]; // bombs and numbers
    int sgrid[12][12]; // covered tiles

    Texture t;
    t.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite s(t);

    for (int i=1;i<=10;i++) // 10 = covered tile
     for (int j=1;j<=10;j++)
      {
        sgrid[i][j]=10;
        if (rand()%5==0)  grid[i][j]=9; // 9 = bomb
        else grid[i][j]=0;
      }

    for (int i=1;i<=10;i++) // checks for adjecant bombs
     for (int j=1;j<=10;j++)
      {
        int n=0;
        if (grid[i][j]==9) continue;
        if (grid[i+1][j]==9) n++;
        if (grid[i][j+1]==9) n++;
        if (grid[i-1][j]==9) n++;
        if (grid[i][j-1]==9) n++;
        if (grid[i+1][j+1]==9) n++;
        if (grid[i-1][j-1]==9) n++;
        if (grid[i-1][j+1]==9) n++;
        if (grid[i+1][j-1]==9) n++;
        grid[i][j]=n;
      }

    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x/w;
        int y = pos.y/w;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
              if (e.key.code == Mouse::Left) sgrid[x][y]=grid[x][y]; // reveals square
              else if (e.key.code == Mouse::Right) sgrid[x][y]=11; // places flag
        }

        app.clear(Color::White);

        for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
          {
           if (sgrid[x][y]==9) sgrid[i][j]=grid[i][j]; // uncovers board if bomb is selected
           s.setTextureRect(IntRect(sgrid[i][j]*w,0,w,w));// otherwise fills board normally
           s.setPosition(i*w, j*w);
           app.draw(s);
          }

        app.display();
    }

    return 0;
}
