
#include "invasion.h"

typedef cInvasion  inv;


cInvasion::cInvasion() :
icon_(Texture("res/png/world_icon.png")),
size_(Vec2f(200, size::Command_H)),
icon_size_(Vec2f(size::Icon_W, size::Icon_H)),
mode_(data::system.poli_mode_),
poli_state_(data::system.command_state_),
pause_(data::system.pause_),
stage_id_(data::system.stage_id_) {

  telop_.size(40);
  telop_.textInput("戻る ");

  init_ = false;
};


void inv::update() {
  if (!init_) { init(); }
  if (stateChange()) { return; }
  buttonSelect();
  back_command();
}


bool inv::stateChange() {
  switch (state_) {
    case command::MoveIn : moveMode();  break;
    case command::Blink  : blinkMode(); break;
    case command::MoveOut: backMode();  break;

    default: return false;
  }

  return true;
}


void inv::moveMode() {
  if (x > 0.f) { x -= 10.f; }

  for (i = 0; i < design::AllStage; ++i) {
    if (icon_y[i] > 0.f) { icon_y[i] -= 10.f; }
  }
  if (anime.alpha_ < 0.75f) { anime.alpha_ += 0.0125f; }

  // TIPS: ボタンの移動が完了したら選択モードにする
  if (icon_y[design::AllStage - 1] <= 0.f) { ++state_; }
}


void inv::blinkMode() {
  ++anime.blink_;
  if (anime.blink_ >= design::Fps) { ++state_; }
}


void inv::backMode() {
  for (i = 0; i < design::AllStage; ++i) { icon_y[i] += 10.f; }
  if (anime.alpha_ >= 0.f) { anime.alpha_ -= 0.05f; }
  if (icon_y[design::AllStage - 1] >= design::DefaultPos * 2) {
    if (id_ != Back) {
      stage_id_ = id_;
      data::system.scene_[play::Next] = scene::Battle;
    }
    mode_ = mode::Neutral;
    poli_state_ = command::MoveIn;
    init_ = false;
  }
}


// 侵攻するマスの処理
void inv::buttonSelect() {
  for (i = 0; i < design::AllStage; ++i) {
    buttonPosTranslate(i);

    if (rectOnMouse(pos_, icon_size_) &&
      win::app->isPushButton(Mouse::LEFT)) {
      data::music.sePlay(se::Click);
      ++state_;
      id_ = i;
    }
  }
}


// 戻るボタンの処理
void inv::back_command() {
  pos_.x() = size::CommandPos_X - x;
  pos_.y() = size::CommandPos_Y - 1.5f * (size_.y() + 10);

  if (rectOnMouse(pos_, size_) &&
    win::app->isPushButton(Mouse::LEFT)) {
    data::music.sePlay(se::Click);
    ++state_;
    id_ = Back;
  }
}


void inv::init() {
  buttonPosInit();

  anime.time_ = 0;
  anime.blink_ = 0;
  anime.alpha_ = 0.f;

  state_ = command::MoveIn;
  id_ = -1;
  init_ = true;
}


// 侵攻するマス
void inv::draw() {
  for (i = 0; i < design::AllStage; ++i) {
    buttonPosTranslate(i);

    on_mouse_ = rectOnMouse(pos_, icon_size_);
    if (state_ != command::Select || pause_) { on_mouse_ = false; }

    flag_ = data::user.map_info[i].flag_;

    drawTextureBox(pos_.x(), pos_.y(), size::Icon_W, size::Icon_H,
      0, 0, size::Icon_W, size::Icon_H,
      icon_, win::color(!flag_ ? on_mouse_ ? paint::Orange : paint::Red : paint::Blue,
      id_ == i ? (anime.blink_ / 2) % 2 : 1.f));
  }

  disp_command();
}


// 戻るボタン
void inv::disp_command() {
  pos_.x() = size::CommandPos_X - x;
  pos_.y() = size::CommandPos_Y - 1.5f * (size_.y() + 10);

  on_mouse_ = rectOnMouse(pos_, size_);
  if (state_ != command::Select || pause_) { on_mouse_ = false; }
  win::draw(pos_, size_, win::color(on_mouse_ ? paint::Orange : paint::Blue,
    id_ == Back ? (anime.blink_ / 2) % 2 : anime.alpha_), anime.alpha_ * 1.25f);

  pos_.x() += (size_.x() - telop_.getTextLength()) / 2;
  pos_.y() += 15;
  telop_.drawText(pos_, win::color(paint::White,
    id_ == Back ? (anime.blink_ / 2) % 2 : anime.alpha_ * 1.25f));
}


void inv::buttonPosTranslate(const short& i) {
  pos_.x() = size::InvasionPos_X + (i % design::InvasionIcon_X) * size::Invasion_W;
  pos_.y() = size::InvasionPos_Y - (i / design::InvasionIcon_X) * size::Invasion_H + icon_y[i];
}


void inv::buttonPosInit() {
  x = design::DefaultPos;
  for (i = 0; i < design::AllStage; ++i) { icon_y[i] = design::DefaultPos * 2; }
}
