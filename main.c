#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

struct Player {
  Vector2 pos;
  Color colour;
  int w;
  int h;
  float speed;
  float rot;
};

int mapX = 10;
int mapY = 10;
int mapS = 80;
int map[] =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
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
  p.speed = 200.0;

  while (!WindowShouldClose()) {
    // update
    if (IsKeyDown(KEY_W)) {
      p.pos.y -= p.speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
      p.pos.y += p.speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A)) {
      p.pos.x -= p.speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_D)) {
      p.pos.x += p.speed * GetFrameTime();
    }

    // draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    drawMap();
    DrawRectangle(p.pos.x, p.pos.y, p.w, p.h, p.colour);

    EndDrawing();
  }

  CloseWindow();
}
