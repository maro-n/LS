
#include "strategy.h"


cStrategy::cStrategy() {

  move_speed = 270;
  alpha = 0.f;

  size = Vec2f(200, 50);

  s_mode[Fire] = "‰ÎŒv";
  s_mode[Bombar] = "–CŒ‚";
  s_mode[Trap] = "ã©";
  s_mode[Poison] = "“Å";
  s_mode[Back] = "‚à‚Ç‚é";

};

void cStrategy::update() {
  for (short i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2;
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    if (box_to_cursor(pos_, size)) {
      if (win::app->isPushButton(Mouse::LEFT) && i == 4) {
        data::system.poli_mode_ = mode::Neutral;
        move_speed = 270;
        alpha = 0.f;
      }
    }
  }
}

void cStrategy::draw() {
  telop_.size(40);

  for (int i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2 - move_speed * (i + 1);
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    win::draw(pos_, size, box_to_cursor(pos_, size)
      ? win::color(paint::Red) : win::color(paint::White, alpha));

    telop_.drawText(s_mode[i], pos_, win::color(paint::Black, alpha));
  }

  if (move_speed > 0.f) { move_speed -= 9.f; }
  if (alpha < 1.f) { alpha += 0.03f; }
}
