
#include "data_select.h"

typedef cDataSelect  d_select;


cDataSelect::cDataSelect() :
font_(Font(FONT_)) {
  text_ = "セーブロード画面（仮）";
}


void d_select::update() {
  if (win::app->isPushButton(Mouse::LEFT)) {
    data::system.scene_[play::Next] = scene::Politics;
  }
  if (win::app->isPushButton(Mouse::RIGHT)) {
    data::system.scene_[play::Next] = scene::Exit;
  }
}


void d_select::draw() {
  font_.size(32);

  x_ = -font_.drawSize(text_).x() / 2;
  font_.draw(text_, Vec2f(x_, size::HEIGHT / 6), Color(1, 1, 1));
}
