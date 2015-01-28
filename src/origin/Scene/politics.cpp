
#include "politics.h"

typedef cPolitics  politics;

cPolitics::cPolitics() {

  move_speed = 270;
  alpha = 0.f;

  mode_[mode::Funds]      = "資金繰り";
  mode_[mode::Armaments]  = "軍備";
  mode_[mode::Strategy]   = "作戦";
  mode_[mode::Invasion]   = "侵攻";
  mode_[mode::DataSelect] = "データ";

  choice_[Yes] = "はい";
  choice_[No]  = "いいえ";

  size_ = Vec2f(200, 50);
}


void politics::update() {

  switch (data::system.poli_mode_) {
    case mode::Funds     : funds_.update();     break;
    case mode::Armaments : armaments_.update(); break;
    case mode::Strategy  : strategy_.update();  break;
    case mode::Invasion  : invasion_.update();  break;
    case mode::DataSelect: break;
    default: modeSelect();
  }
}


// ボタン選択の処理
void politics::modeSelect() {
  if (move_speed > 0.f) { return; }

  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2;
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    if (box_to_cursor(pos_, size_)) {
      if (win::app->isPushButton(Mouse::LEFT)) {
        stateChange(mode(i));
        move_speed = 270;
        alpha = 0.f;
      }
    }
  }
}


// コマンドの切り替え
void politics::stateChange(const mode& it) {
  data::system.poli_mode_ = it;
}


void politics::draw() {
  //TODO: 背景など、必要な描画処理をここに作る
  //draw_bg();

  switch (data::system.poli_mode_) {
    case mode::Funds     : funds_.draw();     break;
    case mode::Armaments : armaments_.draw(); break;
    case mode::Strategy  : strategy_.draw();  break;
    case mode::Invasion  : invasion_.draw();  break;
    case mode::DataSelect: break;
    default: drawButton();
  }
}


void politics::drawButton() {
  telop_.size(40);

  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2 - move_speed * (i + 1);
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    win::draw(pos_, size_, box_to_cursor(pos_, size_)
      ? win::color(paint::Red) : win::color(paint::White, alpha));

    telop_.drawText(mode_[i], pos_, win::color(paint::Black, alpha));
  }

  if (move_speed > 0.f) { move_speed -= 9.f; }
  if (alpha < 1.f) { alpha += 0.03f; }
}
