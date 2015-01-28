
#include "armaments.h"

// �R���X�g���N�^
cArmaments::cArmaments() {

  move_speed = 270;
  alpha = 0.f;

  size_ = Vec2f(200, 50);

  a_mode[Training]    = "�P��";
  a_mode[Making]      = "�ٗp";
  a_mode[Restructur]  = "����";
  a_mode[Development] = "����J��";
  a_mode[Back]        = "���ǂ�";

};

void cArmaments::update() {
  for (short i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2;
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    if (box_to_cursor(pos_, size_)) {
      if (win::app->isPushButton(Mouse::LEFT) && i == 4) {
        data::system.poli_mode_ = mode::Neutral;
        move_speed = 270;
        alpha = 0.f;
      }
    }
  }
}

void cArmaments::draw() {
  for (int i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2 - move_speed * (i + 1);
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    win::draw(pos_, size_, box_to_cursor(pos_, size_)
      ? win::color(paint::Red) : win::color(paint::White, alpha));

    telop_.drawText(a_mode[i], pos_, win::color(paint::Black, alpha));
  }

  if (move_speed > 0.f) { move_speed -= 9.f; }
  if (alpha < 1.f) { alpha += 0.03f; }
}
