
#include "invasion.h"


cInvasion::cInvasion() {

  for (int y = 0; y < 3; ++y) {
    for (int x = 0; x < 4; ++x) {
      button[y][x] = Button(Vec2f(-size::WIDTH / 2 + 300 + (150 * x), size::HEIGHT / 2 - 200 - (150 * y)), win::color(paint::Red), 1);
      on_box_y[y] = -1;
      on_box_x[x] = -1;
    }
  }

  r_x = data::random.fromZeroToLast(4);
  r_y = data::random.fromZeroToLast(3);

  button[r_y][r_x].mode = 0;
  button[r_y][r_x].color = win::color(paint::Blue);
  cmd = Vec2f(-size::WIDTH / 2, 200);
  size = Vec2f(200, 50);
  color = win::color(paint::White);

};

void cInvasion::update() {

  color = win::color(paint::White);

  for (int y = 0; y < 3; ++y) {
    for (int x = 0; x < 4; ++x) {
      on_box_y[y] = -1;
      on_box_x[x] = -1;
      if (rectOnMouse(button[y][x].pos, Vec2f(100, 100))) {
        on_box_y[y] = y;
        on_box_x[x] = x;
        if (win::app->isPushButton(Mouse::LEFT)) {
          if (button[y][x].mode != 0) {
            data::system.scene_[play::Next] = scene::Battle;
          }
        }
      }

      if (rectOnMouse(cmd, size)) {
        color = win::color(paint::Red);
        if (win::app->isPushButton(Mouse::LEFT)) {
          data::system.poli_mode_ = mode::Neutral;
        }
      }
    }
  }
}

void cInvasion::draw() {
  drawFillBox(cmd.x(), cmd.y(), size.x(), size.y(), color);
  for (int y = 0; y < 3; ++y) {
    for (int x = 0; x < 4; ++x) {
      drawFillBox(button[y][x].pos.x(), button[y][x].pos.y(),
        100, 100, button[y][x].color);

      if (on_box_y[y] == y && on_box_x[x] == x) {
        if (button[y][x].mode != 0) {
          drawFillBox(button[y][x].pos.x(), button[y][x].pos.y(), 100, 100, win::color(paint::White, 0.5f));
        }
      }
    }
  }

  telop_.size(50);
  telop_.drawText("‚à‚Ç‚é", Vec2f(-size::WIDTH / 2, 200), win::color(paint::Black));
}
