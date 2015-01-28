
#include "armaments.h"

// コンストラクタ
cArmaments::cArmaments() {

  for (v = 0; v < 5; ++v){
    move_speed[v] = 270;
  }
  alpha = 0.f;

  size_ = Vec2f(200, 50);

  a_mode[Training]    = "訓練";
  a_mode[Making]      = "雇用";
  a_mode[Restructur]  = "解雇";
  a_mode[Development] = "兵器開発";
  a_mode[Back]        = "もどる";

};

void cArmaments::update() {
  if (move_speed[4] > 0.f) { return; }

  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2;
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    if (box_to_cursor(pos_, size_)) {
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

void cArmaments::draw() {
  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2 - move_speed[i] * (i + 1);
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    win::draw(pos_, size_, box_to_cursor(pos_, size_)
      ? win::color(paint::Red) : win::color(paint::White, alpha));

    telop_.drawText(a_mode[i], pos_, win::color(paint::Black, alpha));
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
