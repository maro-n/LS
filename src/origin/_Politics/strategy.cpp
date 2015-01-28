
#include "strategy.h"


cStrategy::cStrategy() {

  for (v = 0; v < 5; ++v){
    move_speed[v] = 270;
  }
  alpha = 0.f;

  size = Vec2f(200, 50);

  s_mode[Fire] = "‰ÎŒv";
  s_mode[Bombar] = "–CŒ‚";
  s_mode[Trap] = "ã©";
  s_mode[Poison] = "“Å";
  s_mode[Back] = "‚à‚Ç‚é";

};

void cStrategy::update() {
  if (move_speed[4] > 0.f) { return; }

  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2;
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    if (box_to_cursor(pos_, size)) {
      if (win::app->isPushButton(Mouse::LEFT) && i == 4) {
        data::system.poli_mode_ = mode::Neutral;
        for (v = 0; v < 5; ++v){
          move_speed[v] = 270;
        }
        alpha = 0.f;
      }
    }
  }
}

void cStrategy::draw() {
  telop_.size(40);

  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2 - move_speed[i] * (i + 1);
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    win::draw(pos_, size, box_to_cursor(pos_, size)
      ? win::color(paint::Red) : win::color(paint::White, alpha));

    telop_.drawText(s_mode[i], pos_, win::color(paint::Black, alpha));
  }

  for (i = 0; i < 5; ++i){
    if (move_speed[i] > 0.f){
      if (i == 0){
        move_speed[i] -= 10.f;
      }
      else if (move_speed[i - 1] <= 270 / 1.5f){
        move_speed[i] -= 10.f;
      }
    }
  }
  if (alpha < 1.f) { alpha += 0.03f; }
}
