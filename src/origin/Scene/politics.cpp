
#include "politics.h"

typedef cPolitics  politics;

cPolitics::cPolitics() {
  for (v = 0; v < 5; ++v){
    move_speed[v] = 270;
  }
  alpha = 0.f;

  mode_[mode::Funds]      = "Ž‘‹àŒJ‚è";
  mode_[mode::Armaments]  = "ŒR”õ";
  mode_[mode::Strategy]   = "ìí";
  mode_[mode::Invasion]   = "NU";
  mode_[mode::DataSelect] = "ƒf[ƒ^";

  choice_[Yes] = "‚Í‚¢";
  choice_[No]  = "‚¢‚¢‚¦";

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


// ƒ{ƒ^ƒ“‘I‘ð‚Ìˆ—
void politics::modeSelect() {
  if (move_speed[4] > 0.f) { return; }

  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + 2;
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    if (box_to_cursor(pos_, size_)) {
      if (win::app->isPushButton(Mouse::LEFT)) {
        stateChange(mode(i));
        for (v = 0; v < 5; ++v){
          move_speed[v] = 270;
        }
        alpha = 0.f;
      }
    }
  }
}


// ƒRƒ}ƒ“ƒh‚ÌØ‚è‘Ö‚¦
void politics::stateChange(const mode& it) {
  data::system.poli_mode_ = it;
}


void politics::draw() {
  //TODO: ”wŒi‚È‚ÇA•K—v‚È•`‰æˆ—‚ð‚±‚±‚Éì‚é
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
    pos_.x() = -size::WIDTH / 2 + 2 - move_speed[i] * (i + 1);
    pos_.y() = size::HEIGHT / 2 - (i + 4) * 60;

    win::draw(pos_, size_, box_to_cursor(pos_, size_)
      ? win::color(paint::Red) : win::color(paint::White, alpha));

    telop_.drawText(mode_[i], pos_, win::color(paint::Black, alpha));
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
  if (alpha < 1.f) { alpha += 0.025f; }
}
