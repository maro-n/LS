
#include "pause.h"

typedef cPause  pause;


cPause::cPause() :
font_(Font(FONT_)),
backToTitle_(false) {
  text_[Pause]     = "PAUSE";
  text_[Button_1]  = "再開";
  text_[Button_2]  = "タイトルにもどる";
  text_[Attention] = "データは保存されません。よろしいですか？";
  text_[OK]        = "はい";
  text_[NG]        = "いいえ";
}


bool pause::update() {
  switch (data::system.scene_[play::Now]) {
    default: break;

    case scene::Politics:;
    case scene::Battle:
      if (win::app->isPushButton(Mouse::RIGHT)) {
        data::system.isPause_ = !data::system.isPause_;
      }
  }

  return data::system.isPause_;
}


void pause::draw() {
  draw_bg();
  draw_telop();
  draw_button();
}


void pause::draw_bg() {
  drawFillBox(-size::WIDTH / 2, -size::HEIGHT / 2, size::WIDTH, size::HEIGHT,
    Color(0, 0, 0, 0.5f));

  font_.size(40);

  x_ = -font_.drawSize(text_[Pause]).x() / 2;
  font_.draw(text_[Pause], Vec2f(x_, size::HEIGHT / 8), Color(1, 1, 1));
}


void pause::draw_button() {
  font_.size(40);

  // TIPS: ポーズ画面の状態に対応したボタンの情報を取得
  short button = backToTitle_ ? OK : Button_1;

  for (short i = 0; i < 2; ++i) {
    x_ = -font_.drawSize(text_[button + i]).x() / 2;
    font_.draw(text_[button + i],
      Vec2f(x_, -(size::HEIGHT / 8 + i * 60)), Color(1, 1, 1));
  }
}


void pause::draw_telop() {
  if (backToTitle_) {
    font_.size(40);

    x_ = -font_.drawSize(text_[Attention]).x() / 2;
    font_.draw(text_[Attention], Vec2f(x_, -size::HEIGHT / 8), Color(1, 1, 1));
  }
}
