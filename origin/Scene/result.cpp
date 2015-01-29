
#include "result.h"

typedef cResult  result;


cResult::cResult() :
bg_(Texture("res/png/back_data_select.png")),
phase_(data::system.phase_),
exp_(data::system.exp_) {
  init();
}


void result::update() {
  phase_ == phase::Win ? phaseWin() : phaseLose();
}


void result::phaseWin() {
}


void result::phaseLose() {
}


bool result::isLevelUp() {
  return false;
}


void result::init() {
  anime.wait_ = design::Fps * 2;
  anime.time_ = 0;
  anime.blink_ = 0;
  anime.alpha_ = 0.f;
}


void result::draw() {
  disp_bg();
  disp_logo();
  disp_telop();
}


void result::disp_bg() {
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    0, 0, 512, 512,
    bg_, Color(1, 1, 1));
}


void result::disp_logo() {
  telop_.size(60);
  telop_.textInput("Result");
  pos_ = Vec2f(-telop_.getTextLength() * 1.1f, size::Result_Y);
  telop_.drawText(pos_, win::color(paint::White));
}


void result::disp_telop() {
  phase_ == phase::Win ?
    telop_.textInput("Win") : telop_.textInput("Lose");

  pos_.x() = telop_.getTextLength() / 2;
  telop_.drawText(pos_, phase_ == phase::Win ?
    win::color(paint::Yellow) : win::color(paint::Pink));
}
