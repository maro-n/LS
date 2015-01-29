
#include "pause.h"

typedef cPause  pause;


cPause::cPause() :
play_scene_(data::system.scene_[play::Now]),
pause_(false), click_(false) {
  telop_.size(40);

  text[Pause]     = "PAUSE";
  text[Button_1]  = "再開";
  text[Button_2]  = "タイトルに戻る";
  text[Attention] = "データは保存されません。よろしいですか？";
  text[OK]        = "はい";
  text[NG]        = "いいえ";
}


bool pause::isPause() {
  return pause_;
}


void pause::update() {
  switch (play_scene_) {
    default: break;

    case scene::Politics:;
    case scene::Battle:
      if (win::app->isPushButton(Mouse::RIGHT)) { pause_ = !pause_; }
  }

  if (pause_) {
    play_scene_ == scene::Politics ? quitGame() : battleMenu();
  }
}


void pause::quitGame() {
  buttonChange();

  for (i = 0; i < 2; ++i) {
    pos_ = Vec2f(-telop_.getTextLength(text[button_ + i]), -(size::PausePos_Y + i * 60));

    if (rectOnMouse(pos_, telop_.getTextSize(text[button_ + i])) &&
        win::app->isPushButton(Mouse::LEFT)) {
      //TODO:処理
    }
  }
}


void pause::battleMenu() {
}


void pause::draw() {
  draw_bg();
  play_scene_ == scene::Politics ? scenePolitics() : sceneBattle();
}


void pause::draw_bg() {
  drawFillBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    win::color(paint::Black, 0.5f));

  telop_.drawText(text[Pause],
    Vec2f(-telop_.getTextLength(text[Pause]) / 2, size::PausePos_Y),
    win::color(paint::White));
}


void pause::scenePolitics() {
  draw_button();
  draw_telop();
}


void pause::draw_button() {
  buttonChange();

  for (i = 0; i < 2; ++i) {
    pos_ = Vec2f(-telop_.getTextLength(text[button_ + i]), -(size::PausePos_Y + i * 60));

    telop_.drawText(text[button_ + i], pos_,
      rectOnMouse(pos_, telop_.getTextSize(text[button_ + i])) ?
      win::color(paint::Yellow) : win::color(paint::White));
  }
}


void pause::draw_telop() {
  if (click_) {
    telop_.drawText(text[Attention],
      Vec2f(telop_.getTextLength(text[Attention]), size::PausePos_Y),
      win::color(paint::White));
  }
}


void pause::sceneBattle() {
}


void pause::draw_command() {
}


void pause::draw_explanation() {
}


void pause::buttonChange() {
  // TIPS: ポーズ画面の状態に対応したボタンの情報を取得
  button_ = click_ ? OK : Button_1;
}
