
#include "data_select.h"

typedef cDataSelect  d_select;


cDataSelect::cDataSelect() :
bg_(Texture("res/png/back_data_select.png")),
slot_size_(Vec2f(250, 60)),
now_(data::system.scene_[play::Now]) {

  telop_.size(40);

  text[Slot1] = "スロット１ ";
  text[Slot2] = "スロット２ ";
  text[Slot3] = "スロット３ ";
  text[Back]  = "戻る";
  text[Save]  = "Save";
  text[Load]  = "Load";
}


void d_select::update() {
  for (i = Slot1; i < Save; ++i) {
    buttonPosTranslate(i == Back ? i + 1 : i);
    on_mouse_ = rectOnMouse(pos_, slot_size_);

    if (on_mouse_ && win::app->isPushButton(Mouse::LEFT)) {
      data::system.scene_[play::Next] = data::system.scene_[play::Last];
    }
  }
}


void d_select::init() {
  data::music.stop();
  data::music.play(bgm::DataSelect);
}


void d_select::draw() {
  disp_back();
  disp_slot();
  disp_info();
}


void d_select::disp_back() {
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    0, 0, size::Result_W, size::Result_H,
    bg_, win::color(paint::White));

  text_id_ = now_ == scene::Save ? Save : Load;
  pos_.x() = -telop_.getTextLength(text[text_id_]) / 2;
  pos_.y() = size::Result_Y;
  telop_.drawText(text[text_id_], pos_,
    win::color(text_id_ == Save ?
    paint::Yellow : paint::Green));
}


void d_select::disp_slot() {
  for (i = Slot1; i < Save; ++i) {
    buttonPosTranslate(i == Back ? i + 1 : i);
    on_mouse_ = rectOnMouse(pos_, slot_size_);

    win::draw(pos_, slot_size_, win::color(on_mouse_ ?
      paint::Yellow : paint::Blue, 0.5f));

    pos_.x() += (slot_size_.x() - telop_.getTextLength(text[i])) / 2;
    pos_.y() += 15;
    telop_.drawText(text[i], pos_, win::color(paint::White));
  }
}


// セーブデータの情報
//TODO:実装予定
void d_select::disp_info() {
  win::draw(Vec2f(size::InfoPos_X, size::InfoPos_Y),
    Vec2f(size::Info_W, size::Info_H), win::color(paint::Green, 0.75f));
}


void d_select::buttonPosTranslate(const short& i) {
  pos_.x() = size::SlotPos_X;
  pos_.y() = size::SlotPos_Y - (i * size::Slot_H);
}
