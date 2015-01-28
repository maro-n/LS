
#include "result.h"

typedef cResult  result;


cResult::cResult() :
font_(Font(FONT_)) {
  text_ = "リザルト（仮）";
  t_ = "左クリックでもどる、右クリックで終わる";//test
}


void result::update() {

  //テスト用
  if (win::app->isPushButton(Mouse::LEFT)) {
    data::system.scene_[play::Next] = scene::Title;
  }
  if (win::app->isPushButton(Mouse::RIGHT)) {
    data::system.scene_[play::Next] = scene::Exit;
  }
}


void result::draw() {
  font_.size(40);

  x_ = -font_.drawSize(text_).x() / 2;
  font_.draw(text_, Vec2f(x_, size::HEIGHT / 6), Color(1, 1, 1));


  //テスト用
  font_.size(40);

  x_ = -font_.drawSize(t_).x() / 2;
  font_.draw(t_, Vec2f(x_, -size::HEIGHT / 8), Color(1, 1, 1));
}
