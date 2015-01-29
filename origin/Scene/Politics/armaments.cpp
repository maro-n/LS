
#include "armaments.h"

typedef cArmaments  arma;


cArmaments::cArmaments() :
size_(Vec2f(200, size::Command_H)),
mode_(data::system.poli_mode_),
poli_state_(data::system.command_state_),
money_(data::user.assets.money_) {

  telop_.size(40);

  text[Growth]      = "育成 ";
  text[ClassChange] = "兵種変更 ";
  text[ReMake]      = "雇用 ";
  text[Delete]      = "除名 ";
  text[Back]        = "戻る ";

  init_ = false;
};


void arma::update() {
  if (!init_) { init(); }
  if (stateChange()) { return; }
  buttonSelect();
}


bool arma::stateChange() {
  switch (state_) {
    case command::MoveIn: moveMode();  break;
    case command::Blink: blinkMode(); break;
    case command::MoveOut: backMode();  break;

    default: return false;
  }

  return true;
}


void arma::moveMode() {
  for (i = 0; i < All_Text; ++i) {
    // TIPS: 移動が完了したボタンの処理をスキップ
    if (x[i] <= 0.f) { continue; }

    if (i == 0) { x[i] -= 10.f; }
    else if (x[i - 1] <= design::DefaultPos / 1.5f) { x[i] -= 10.f; }
  }
  if (anime.alpha_ < 0.75f) { anime.alpha_ += 0.0125f; }

  // TIPS: ボタンの移動が完了したら選択モードにする
  if (x[Back] <= 0.f) { ++state_; }
}


void arma::blinkMode() {
  ++anime.blink_;
  if (anime.blink_ >= design::Fps) { ++state_; }
}


void arma::backMode() {
  for (i = 0; i < All_Text; ++i) { x[i] += 10.f; }
  if (anime.alpha_ >= 0.f) { anime.alpha_ -= 0.05f; }
  if (x[Back] >= design::DefaultPos) {
    mode_ = mode::Neutral;
    poli_state_ = command::MoveIn;
    init_ = false;
  }
}


void arma::buttonSelect() {
  for (i = 0; i < All_Text; ++i) {
    buttonPosTranslate(i);

    if (rectOnMouse(pos_, size_) &&
      win::app->isPushButton(Mouse::LEFT)) {
      data::music.sePlay(se::Click);
      ++state_;
      id_ = i;
    }
  }
}


void arma::init() {
  buttonPosInit();

  anime.time_ = 0;
  anime.blink_ = 0;
  anime.alpha_ = 0.f;

  state_ = command::MoveIn;
  id_ = -1;
  init_ = true;
}


void arma::draw() {
  for (i = 0; i < All_Text; ++i) {
    buttonPosTranslate(i);

    on_mouse_ = rectOnMouse(pos_, size_);
    if (state_ != command::Select) { on_mouse_ = false; }
    win::draw(pos_, size_, win::color(on_mouse_ ? paint::Orange : paint::Blue,
      id_ == i ? (anime.blink_ / 2) % 2 : anime.alpha_), anime.alpha_ * 1.25f);

    pos_.x() += (size_.x() - telop_.getTextLength(text[i])) / 2;
    pos_.y() += 15;
    telop_.drawText(text[i], pos_, win::color(paint::White,
      id_ == i ? (anime.blink_ / 2) % 2 : 1.f));
  }
}


void arma::buttonPosTranslate(const short& i) {
  pos_.x() = size::CommandPos_X - x[i];
  pos_.y() = size::CommandPos_Y - (i + 1.5f) * (size_.y() + 10);
}


void arma::buttonPosInit() {
  for (i = 0; i < All_Text; ++i) { x[i] = design::DefaultPos; }
}
