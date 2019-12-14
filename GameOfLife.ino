#include <SPI.h>
#include <TFT_eSPI.h>
#include <esp_task_wdt.h>

TFT_eSPI g = TFT_eSPI();

#define WIDTH 80
#define HEIGHT 45
#define RESIZER 3
#define LANDSCAPE 1
#define LIFE_VALUE 75

boolean liveCellMap[WIDTH][HEIGHT];

void setup() {
  g.init();
  g.setRotation(LANDSCAPE);
  g.fillScreen(TFT_BLACK);
  
  //ENDLESS LOOPING SNAKE
  /*liveCellMap[0+15][0+15]=true;
  liveCellMap[1+15][1+15]=true;
  liveCellMap[2+15][0+15]=true;
  liveCellMap[2+15][1+15]=true;
  liveCellMap[1+15][2+15]=true;*/

  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      //TO DISABLE WHEN TRYING SNAKE
      boolean isAlive = random(0, 100) > LIFE_VALUE;
      liveCellMap[i][j] = isAlive;
      //TO DISABLE WHEN TRYING SNAKE
      if (liveCellMap[i][j]) {
        g.fillRect(i * RESIZER, j * RESIZER, RESIZER, RESIZER, random(0, 255 * 255 * 255));
      }
    }
  }
}

void loop() {
  boolean templiveCellMap[WIDTH][HEIGHT];
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      templiveCellMap[i][j] = liveCellMap[i][j];
    }
  }
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      int livingNeighbours = count(i, j);
      if (livingNeighbours < 2 && liveCellMap[i][j]) {
        templiveCellMap[i][j] = false;
      }
      if ((livingNeighbours == 3 || livingNeighbours == 2) && liveCellMap[i][j]) {
        templiveCellMap[i][j] = true;
      }
      if (livingNeighbours > 3 && liveCellMap[i][j]) {
        templiveCellMap[i][j] = false;
      }
      if (!liveCellMap[i][j] && livingNeighbours == 3) {
        templiveCellMap[i][j] = true;
      }
    }
  }
  g.fillScreen(TFT_BLACK);
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      liveCellMap[i][j] = templiveCellMap[i][j];
      if (liveCellMap[i][j]) {
        g.fillRect(i * RESIZER, j * RESIZER, RESIZER, RESIZER, random(0, 255 * 255 * 255));
      }
    }
  }
  delay(17);
}

int count(int x, int y) {
  int counter = 0;
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if ((i != -1 && i != WIDTH && j != -1 && j != HEIGHT) && (i != x || j != y)) {
        if (liveCellMap[i][j]) {
          counter++;
        }
      }
    }
  }
  return counter;
}
