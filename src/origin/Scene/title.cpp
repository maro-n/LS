
#include "title.h"

typedef cTitle  title;


cTitle::cTitle() :
font_(Font(FONT_)) {
  text_ = "Click Start";
}


// 演出の初期化
// TIPS: ループの開始時に一度だけ初期化を行う
void title::init() {
  anime_.time_  = 0;
  anime_.blink_ = 0;
}


void title::update() {

  // テスト
  if (win::app->isPushButton(Mouse::LEFT)) {
    data::system.scene_[play::Next] = scene::Politics;
  }
}


void title::draw() {
  draw_bg();
  draw_logo();
  draw_telop();
}


// 背景の描画
void title::draw_bg() {
}


// タイトルロゴの描画
void title::draw_logo() {
}


// テロップなどの描画
void title::draw_telop() {
  font_.size(40);

  x_ = -font_.drawSize(text_).x() / 2;
  font_.draw(text_, Vec2f(x_, size::HEIGHT / 6), Color(1, 1, 1));
}
