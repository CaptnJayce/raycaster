#include <math.h>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

struct Player {
  Vector2 pos;
  Color colour;
  int w;
  int h;

  // for rotation
  float pdx;
  float pdy;
  float pa;
};

int mapX = 10;
int mapY = 10;
int mapS = 80;
int map[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
             1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
             1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1,
             1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
             1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

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

void drawRays(struct Player p) {
  int r, mx, my, mp, dof;
  float rx, ry, ra, xo, yo;

  ra = p.pa;

  for (r = 0; r < 1; r++) {
    dof = 0;
    float aTan = -1 / tan(ra);

    if (ra > PI) {
      ry = (((int)p.pos.y / mapS) * mapS) - 0.0001;
      rx = (p.pos.y - ry) * aTan + p.pos.x;
      yo = -mapS;
      xo = -yo * aTan;
    } else if (ra < PI) {
      ry = (((int)p.pos.y / mapS) * mapS) + mapS;
      rx = (p.pos.y - ry) * aTan + p.pos.x;
      yo = mapS;
      xo = -yo * aTan;
    } else {
      rx = p.pos.x;
      ry = p.pos.y;
      dof = 8;
    }

    while (dof < 8) {
      mx = (int)(rx) / mapS;
      my = (int)(ry) / mapS;
      mp = my * mapX + mx;

      if (mp > 0 && mp < mapX * mapY && map[mp] == 1) {
        dof = 8;
      } else {
        rx += xo;
        ry += yo;
        dof += 1;
      }
    }

    DrawLine(p.pos.x + 10, p.pos.y + 10, rx, ry, RED);
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
  p.pdx = cos(p.pa) * 5;
  p.pdy = sin(p.pa) * 5;

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_A)) {
      p.pa -= 0.1;
      if (p.pa < 0) {
        p.pa += 2 * PI;
      }
      p.pdx = cos(p.pa) * 5;
      p.pdy = sin(p.pa) * 5;
    }
    if (IsKeyDown(KEY_D)) {
      p.pa += 0.1;
      if (p.pa > 2 * PI) {
        p.pa -= 2 * PI;
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
    drawRays(p);
    EndDrawing();
  }

  CloseWindow();
}
