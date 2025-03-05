#include <raylib.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

struct Player {
  Vector2 pos;
  Color colour;
  int w;
  int h;
  float speed;

  // for rotation
  float pdx;
  float pdy;
  float pa;
};

int mapX = 10;
int mapY = 10;
int mapS = 80;
int map[] =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
  1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

void drawMap() {
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            if (map[y * mapX + x] == 1) {
                DrawRectangle(x * mapS + 1, y * mapS + 1, mapS - 2, mapS - 2, WHITE);
            } else {
                DrawRectangle(x * mapS + 1, y * mapS + 1, mapS - 2, mapS - 2, BLACK);
            }
        }
    }
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raycastah");
  SetTargetFPS(120);

  struct Player p;
  p.pos = (Vector2){100, 100};
  p.colour = GREEN;
  p.w = 20;
  p.h = 20;
  p.speed = 300.0;

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_A)) {
      p.pa -= 0.1;
      if (p.pa < 0) {
        p.pa += 2*PI;
      }
      p.pdx = cos(p.pa) * 5;
      p.pdy = sin(p.pa) * 5;
    }
    if (IsKeyDown(KEY_D)) {
      p.pa += 0.1;
      if (p.pa > 2*PI) {
        p.pa -= 2*PI;
      }
      p.pdx = cos(p.pa) * 5;
      p.pdy = sin(p.pa) * 5;
    }
    if (IsKeyDown(KEY_W)) {
      p.pos.x += p.pdx;
      p.pos.y += p.pdy;
    }
    if (IsKeyDown(KEY_S)) {
      p.pos.x -= p.pdx;
      p.pos.y -= p.pdy;
    }

    // draw
    BeginDrawing();
    ClearBackground(BLACK);

    drawMap();
    DrawRectangle(p.pos.x, p.pos.y, p.w, p.h, p.colour);
    DrawLine(p.pos.x, p.pos.y, p.pos.x+p.pdx*5, p.pos.y+p.pdy*5, RED);
    EndDrawing();
  }

  CloseWindow();
}
