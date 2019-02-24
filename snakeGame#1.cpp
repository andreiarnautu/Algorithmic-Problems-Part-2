/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int width = 20;
const int height = 20;
const int maxSize = 400;

/*-------- Data --------*/
struct Cell {
  int x, y;

  Cell() {x = 1; y = 1;}

  bool operator ==(const Cell &other) const {
    return this->x == other.x && this->y == other.y;
  }
};

Cell next, fruit;
int score;

Cell tail[maxSize];
int tailSize = 0;

enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction dir;

bool gameOver;
/*-------- --------*/

void GoTo(int x, int y) {
  SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), {x, y});
}

void Initialize() {
  //  Make the cursor invisible

  CONSOLE_CURSOR_INFO info;
  info.bVisible = false;
  info.dwSize = 100;
  SetConsoleCursorInfo(GetStdHandle( STD_OUTPUT_HANDLE ), &info);

  srand(time(NULL));

  next.x = width / 2; next.y = height / 2;

  fruit.x = rand() % width + 1; fruit.y = rand() % height + 1;

  score = 0; dir = STOP; gameOver = false;

  for(int i = 0; i <= width + 1; i++) {
    printf("#");
  }
  printf("\n");

  for(int i = 1; i <= height; i++) {
    for(int j = 0; j <= width + 1; j++) {
      if(j == 0 || j == width + 1) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }

  for(int i = 0; i <= width + 1; i++) {
    printf("#");
  }
  printf("\n");
}

void SetScreen() {
  for(int i = 1; i <= height; i++) {
    for(int j = 1; j <= width; j++) {
      if(next.x == j && next.y == i) {
        GoTo(j, i); printf("O");
      } else if(fruit.x == j && fruit.y == i) {
        GoTo(j, i); printf("F");
      } else {
        bool print = false;
        for(int itr = 0; itr < tailSize; itr++) {
          if(tail[itr].x == j && tail[itr].y == i) {
            print = true; break;
          }
        }

        GoTo(j, i);
        if(!print) {
          printf(" ");
        } else {
          printf("o");
        }
      }
    }
  }

  GoTo(0, height + 2);
  printf("Score: %d", score);

  GoTo(0, height + 4);
}

void GetInput() {
  if(_kbhit()) {
    switch(_getch()) {
      case KEY_UP :
        if(dir != DOWN) dir = UP;
        break;

      case KEY_DOWN :
        if(dir != UP) dir = DOWN;
        break;

      case KEY_LEFT :
        if(dir != RIGHT) dir = LEFT;
        break;

      case KEY_RIGHT :
        if(dir != LEFT) dir = RIGHT;
        break;
    }
  }
}

void Logic() {
  for(int i = tailSize - 1; i > 0; i--) {
    tail[i] = tail[i - 1];
  }
  tail[0] = next;

  switch(dir) {
    case LEFT :
      next.x--;
      break;

    case RIGHT :
      next.x++;
      break;

    case UP :
      next.y--;
      break;

    case DOWN :
      next.y++;
      break;

    default :
      break;
  }

  //  Check if the snake hits a wall
  if(next.x >= width + 1) {
    next.x = 0;
  } else if(next.x <= 0) {
    next.x = width;
  }

  if(next.y >= height + 1) {
    next.y = 0;
  } else if(next.y <= 0) {
    next.y = height;
  }

  //  Check if the snake hits itself
  for(int i = 0; i < tailSize; i++) {
    if(next == tail[i]) {
      gameOver = true;
    }
  }

  if(next == fruit) {
    score++;

    fruit.x = rand() % width + 1;
    fruit.y = rand() % height + 1;

    tailSize++;
  }
}

int main() {
  Initialize();

  SetScreen();

  while(!gameOver) {
    SetScreen();
    GetInput();
    Logic();

    Sleep(75);
  }


  GoTo(0, height + 5);
  return 0;
}
