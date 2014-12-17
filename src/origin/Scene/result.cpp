
#include "result.h"


// コンストラクタ
Result::Result() :
font(Font(("res/font/MeiryoConsolas.ttf"))) {
  cmd[0] = Vec2f(-WIDTH / 2, 60);
  cmd[1] = Vec2f(-WIDTH / 2, -60);
  size = Vec2f(200, 50);
  font.size(40);
}

// 描画
void Result::draw(int& mode) {
  switch (mode){
  case 1: stage_clear();
    break;
  case 2: game_clear();
    break;
  default: game_over();
  }
}

void Result::stage_clear() {
  drawFillBox(cmd[0].x(), cmd[0].y(), size.x(), size.y(), color[0]);
  str = "続ける";
  font.draw(str, cmd[0], Color(0, 0, 0)); // debug
  font.draw("ステージクリア（仮）", Vec2f(0, -50), Color(1, 1, 1)); //debug
}

void Result::game_over() {
  for (int i = 0; i < 2; ++i) {
    drawFillBox(cmd[i].x(), cmd[i].y(), size.x(), size.y(), color[i]);

    switch (i) {
      case 0: str = "続ける"; break;
      default: str = "やめる";
    }

    font.draw(str, cmd[i], Color(0, 0, 0)); //debug
  }
  font.draw("ゲームオーバー（仮）", Vec2f(0, -50), Color(1, 1, 1)); //debug
}

void Result::game_clear() {
  for (int i = 0; i < 2; ++i) {
    drawFillBox(cmd[i].x(), cmd[i].y(), size.x(), size.y(), color[i]);

    switch (i) {
      case 0: str = "タイトルへ"; break;
      default: str = "やめる";
    }

    font.draw(str, cmd[i], Color(0, 0, 0)); //debug
  }
  font.draw("ゲームクリア（仮）", Vec2f(0, -50), Color(1, 1, 1)); //debug
}

// 更新
void Result::update(bool& click, bool& EXIT) {
  win::mouse_translate();

  // 適当に矩形をだしてあたり判定の動作チェック
  for (int i = 0; i < 2; ++i) {
    color[i] = Color(1, 1, 1);
    if (box_to_cursor(cmd[i], size)) {
      color[i] = color_variation.red;
      if (win::app->isPushButton(Mouse::LEFT)) {
        click = true;
        if (i == 1) {
          EXIT = true;
        }
      }
    }
  }
}

// リセット
void Result::reset() {
}
