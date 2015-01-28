
#include "fight.h"

typedef cFight  fight;


cFight::cFight() :
pWin_size_(Vec2f(WIDTH / BT_Member, 96)),
chip_size_(Vec2f(Chip_W * 1.75f, Chip_H * 1.75f)),
gauge_width_(100.f) {
  for (i_ = 0; i_ < Map_X * Map_Y; ++i_) {
    chip[i_].pos_.x() = chip_size_.x() * (i_ % Map_X - Map_X / 2);
    chip[i_].pos_.y() = chip_size_.y() * -(1 + i_ / Map_X) + HEIGHT / 2;
  }
}


void fight::update() {
}


void fight::init() {
}


void fight::draw() {
  for (i_ = 0; i_ < BT_Member; ++i_) {
    //disp_unit(i_);
    disp_parameter(i_);
  }

  for (i_ = 0; i_ < Map_X * Map_Y; ++i_) {
    drawFillBox(chip[i_].pos_.x(), chip[i_].pos_.y(),
      chip_size_.x(), chip_size_.y(),
      box_to_cursor(chip[i_].pos_, chip_size_)
      ? win::color(SkyBlue) : win::color(Blue));
  }
}


void fight::disp_move() {
}


void fight::disp_unit(const short& id) {
  cut_.x() = data::user.player_[data::user.id_[i_]].blink_ * 32;
  cut_.y() = data::user.player_[data::user.id_[i_]].direction_ * 32;

  drawTextureBox(chip[id].pos_.x(), chip[id].pos_.y(), 32, 32,
    cut_.x(), cut_.y(), 32, 32,
    data::user.player_[data::user.id_[id]].own_,
    win::color(White));
}


void fight::disp_parameter(const short& id) {
  pos_.x() = (-WIDTH / 2) + id * (WIDTH / BT_Member + 1);
  pos_.y() = -HEIGHT / 2;

  win::draw(pos_, pWin_size_, win::color(Blue));

  // LPゲージ表示
  //per_ = data::user.player_[data::user.id_[id]].lpGaugeWidth();
  per_ = 0.8f;
  pos_.x() += 80;
  pos_.y() += 34;
  win::gaugeDraw(per_, pos_, Vec2f(gauge_width_, 16),
    per_ > 0.5f ? win::color(Green) :
    per_ > 0.25f ? win::color(Yellow) :
    win::color(Red));

  // タイムゲージ表示
  //per_ = data::user.player_[data::user.id_[id]].lpGaugeWidth();
  per_ = 0.5f;
  pos_.y() -= 22;
  win::gaugeDraw(per_, pos_, Vec2f(gauge_width_, 16), win::color(Orange));
}
