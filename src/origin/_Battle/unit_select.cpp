
#include "unit_select.h"

typedef cUnitSelect  unit;


cUnitSelect::cUnitSelect() :
size_(Vec2f(WIDTH / 4 - 2, 64)),
select_(Vec2f(WIDTH / 4, 96)) {
  for (i_ = 0; i_ < PT_Member; ++i_) {
    icon[i_].pos_.x() = (size_.x() + 2) * (i_ / 5 - 2) + 1;
    icon[i_].pos_.y() = (size_.y() + 2) * (3 - i_ % 5);
    icon[i_].state_ = Out;
  }
  pos_.y() = -select_.y();
}


void unit::update() {
  // TIPS: 戦闘できる人数を選択したら、戦闘開始するか選択
  if (selectFinish()) { phaseShift(); return; }

  // TIPS: 出撃するユニットの選択
  for (i_ = 0; i_ < PT_Member; ++i_) {
    icon[i_].state_ != Clicked ? act_out() : act_click();
  }
}


void unit::act_out() {

  // TIPS: カーソルがアイコンの上にあるか判定、
  //       クリックしたユニットを出撃メンバーにする
  icon[i_].state_ = box_to_cursor(icon[i_].pos_, size_) ? OnMouse : Out;

  if (icon[i_].state_ == OnMouse && win::app->isPushButton(Mouse::LEFT)) {
    icon[i_].state_ = Clicked;
  }
}


void unit::act_click() {
  // TIPS: 出撃状態のユニットを再度クリックしたら出撃メンバーから外す
  if (box_to_cursor(icon[i_].pos_, size_)) {
    if (win::app->isPushButton(Mouse::LEFT)) { icon[i_].state_ = OnMouse; }
  }
}


void unit::init_select(const short& i) {
  pos_.x() = i ? select_.x() / 4 : -(select_.x() * 1.25f);
}


// TIPS: 選択されたユニットの数を出力
bool unit::selectFinish() {
  short num = 0;

  for (i_ = 0; i_ < PT_Member; ++i_) {
    if (icon[i_].state_ == Clicked) { ++num; }
  }

  // TIPS: 戦闘開始できる人数になったら true を返す
  return !(num < BT_Member);
}


void unit::phaseShift() {
  for (i_ = 0; i_ < 2; ++i_) {
    init_select(i_);
    if (box_to_cursor(pos_, select_) && win::app->isPushButton(Mouse::LEFT)) {
      act_shift(i_);
    }
  }
}


void unit::act_shift(const short& i) {
  switch (i) {
    case  0:
      data::system.phase_ = pState::Fight; break;
    default:
      for (i_ = 0; i_ < PT_Member; ++i_) { icon[i_].state_ = Out; }
  }
}


void unit::init() {
}


void unit::draw() {
  disp_other();
  disp_info();
  disp_unit();

  if (selectFinish()) {
    disp_telop();
    disp_select();
  }
}


// TIPS: 背景、ウィンドウなど、更新が影響しない項目の表示
void unit::disp_other() {
  // 背景
  // TODO: 画像を用意して、ここに描画処理を作る

  // メッセージウィンドウ
  win::draw(Vec2f(-WIDTH / 2, -HEIGHT / 2), Vec2f(WIDTH, 200),
    win::color(Blue));
}


// TIPS: カーソルを合わせているユニットの情報を表示
void unit::disp_info() {
}


void unit::disp_unit() {
  for (i_ = 0; i_ < PT_Member; ++i_) {
    win::draw(icon[i_].pos_, size_,
      icon[i_].state_ == Clicked
      ? win::color(Yellow)    // クリックした
      : icon[i_].state_ == OnMouse
      ? win::color(SkyBlue)   // カーソルがアイコンの上にある
      : win::color(Blue));    // カーソルがない
  }
}


// TIPS: メンバーを確定して出撃するかのメッセージを表示
void unit::disp_telop() {
}


// TIPS: 出撃とキャンセルのボタン表示
void unit::disp_select() {
  for (i_ = 0; i_ < 2; ++i_) {
    init_select(i_);

    win::draw(pos_, select_,
      box_to_cursor(pos_, select_)
      ? win::color(SkyBlue)
      : win::color(Blue));
  }
}
