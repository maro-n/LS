
#include "funds.h"

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
cFunds::cFunds() {

  move_speed = 270;
  alpha = 0.f;

  size = Vec2f(200, 50);

  f_mode[Business] = "¤”„";
  f_mode[Worker]   = "•ºŽm”hŒ­";
  f_mode[Sell]     = "Ž‘ŽY”„‹p";
  f_mode[Back]     = "‚à‚Ç‚é";
};

void cFunds::update() {
  if (move_speed > 0.f) { return; }

  for (i = 0; i < 4; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2;
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    if (box_to_cursor(pos_, size)) {
      if (win::app->isPushButton(Mouse::LEFT) && i == 3) {
        data::system.poli_mode_ = mode::Neutral;
        move_speed = 270;
        alpha = 0.f;
      }
    }
  }
}

void cFunds::draw() {
  telop_.size(40);

  for (i = 0; i < 4; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2 - move_speed * (i + 1);
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    win::draw(pos_, size, box_to_cursor(pos_, size)
      ? win::color(paint::Red) : win::color(paint::White, alpha));

    telop_.drawText(f_mode[i], pos_, win::color(paint::Black, alpha));
  }

  if (move_speed > 0.f) { move_speed -= 9.f; }
  if (alpha < 1.f) { alpha += 0.03f; }
}
