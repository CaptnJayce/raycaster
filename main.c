#include <math.h>
#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define P2 PI / 2
#define P3 3 * PI / 2
#define DR 0.0174533 //one degree in radians

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
// linter messed up the array :(
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

float dist(float ax, float ay, float bx, float by, float ang) {
  return(sqrt((bx - ax) * (bx - ax) + (by - ay) * (by -ay)));
}

void drawRays(struct Player p) {
  int r, mx, my, mp, dof;
  float rx, ry, ra, xo, yo;

  ra = p.pa - DR * 30;
  if (ra < 0) {
    ra += 2*PI;
  }
  if (ra > 2 * PI) {
    ra -= 2* PI;
  }

  for (r = 0; r < 60; r++) {
    // Check horizontal lines
    dof = 0;
    float disH = 10000000;
    float hx = p.pos.x;
    float hy = p.pos.y;
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
        hx = rx;
        hy = ry;
        disH = dist(p.pos.x, p.pos.y, hx, hy, ra);
        dof = 8;
      } else {
        rx += xo;
        ry += yo;
        dof += 1;
      }
    }

    // Check vertical lines
    dof = 0;
    float disV = 10000000;
    float vx = p.pos.x;
    float vy = p.pos.y;
    float nTan = -tan(ra);

    if (ra > P2 && ra < P3) {
      rx = (((int)p.pos.x / mapS) * mapS) - 0.0001;
      ry = (p.pos.x - rx) * nTan + p.pos.y;
      xo = -mapS;
      yo = -xo * nTan;
    } else if (ra < P2 || ra > P3) {
      rx = (((int)p.pos.x / mapS) * mapS) + mapS;
      ry = (p.pos.x - rx) * nTan + p.pos.y;
      xo = mapS;
      yo = -xo * nTan;
    } else {
      ry = p.pos.y;
      rx = p.pos.x;
      dof = 8;
    }

    while (dof < 8) {
      mx = (int)(rx) / mapS;
      my = (int)(ry) / mapS;
      mp = my * mapX + mx;

      if (mp > 0 && mp < mapX * mapY && map[mp] == 1) {
        vx = rx;
        vy = ry;
        disV = dist(p.pos.x, p.pos.y, vx, vy, ra);
        dof = 8;
      } else {
        rx += xo;
        ry += yo;
        dof += 1;
      }
    }
    if (disV < disH) {
      rx = vx;
      ry = vy;
    }
    if (disH < disV) {
      rx = hx;
      ry = hy;
    }
    DrawLine(p.pos.x + 10, p.pos.y + 10, rx, ry, RED);
    ra += DR;
    if (ra < 0) {
      ra += 2 * PI;
    }
    if (ra > 2 * PI) {
      ra -= 2  * PI;
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
