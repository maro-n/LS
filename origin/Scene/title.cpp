
#include "title.h"

typedef cTitle  title;


cTitle::cTitle() :
bg_(Texture("res/png/world_map.png")),
sea_(Texture("res/png/world_sea.png")),
fog_(Texture("res/png/world_sea_fog.png")),
logo_(Texture("res/png/back_title_logo.png")),
size_(Vec2f(size::Mode_W, size::Mode_H)),
clear_(data::system.clear_) {

  telop_.size(60);

  text[Click]    = "Click Start";
  text[Back]   = "RightClick Back";
  text[NewGame]  = "New Game";
  text[Continue] = "Continue";
  text[Easy]     = "ＥＡＳＹ ";
  text[Normal]   = "ＮＯＲＭＡＬ ";
  text[Hard]     = "ＨＡＲＤ ";
}


void title::update() {
  sceneChange();
  if (clickStart()) { return; }
  modeSelect();
}


bool title::clickStart() {

  // TIPS: クリックされたら高速で点滅、ゲームを開始する
  switch (state_) {
    case Start:
      if (win::app->isPushButton(Mouse::LEFT)) {
        ++state_;
        data::music.sePlay(se::Click);
      }
      break;

    case Blink1:;
    case Blink2:;
    case Blink3:
      ++blink_timer_;
      if (blink_timer_ > design::Fps) {
        ++state_;
        blink_timer_ = 0;
      }
      break;

    case Change:
      anime.alpha_ -= 0.05f;
      if (anime.alpha_ <= 0.f) {
        ++state_;
        click_mode_ = -1;
      }
      break;

    case Cancel:
      anime.alpha_ -= 0.05f;
      if (anime.alpha_ <= 0.f) { state_ = Mode; }
      break;

    default:;
  }

  return (state_ != Mode && state_ != Select);
}


void title::modeSelect() {
  buttonDataTranslate();

  for (i = begin_; i < end_; ++i) {
    buttonPosTranslate(i);
    on_mouse_ = rectOnMouse(pos_, size_);

    if (on_mouse_ && win::app->isPushButton(Mouse::LEFT)) {
      data::music.sePlay(se::Click);
      ++state_;
      click_mode_ = i;
    }
  }

  if (state_ == Select &&
    win::app->isPushButton(Mouse::RIGHT)) { state_ = Cancel; }
}


void title::sceneChange() {
  if (state_ > Blink3) {
    clear_ ? data::reStart(dif(click_mode_ - Easy)) :
      data::newGame(dif(click_mode_ - Easy));
    data::system.scene_[play::Next] = scene::Politics;
  }

  if (click_mode_ == Continue && state_ > Blink2) {
    data::system.scene_[play::Last] = scene::Title;
    data::system.scene_[play::Next] = scene::Load;
  }
}


// 演出の初期化
// TIPS: ループの開始時に一度だけ初期化を行う
void title::init() {
  anime.time_ = 0;
  anime.blink_ = 0;
  anime.scroll_ = 0.f;
  anime.alpha_ = 0.f;

  state_ = Start;
  blink_timer_ = 0;
  click_mode_ = -1;

  data::music.stop();
  data::music.play(bgm::Title);
}


void title::draw() {
  effectPlay();
  disp_title();
  disp_click();
  disp_mode();
}


// タイトル画面の演出
void title::effectPlay() {
  ++anime.time_;
  if (anime.time_ >= design::Fps - 10) { anime.time_ = 0; }
  anime.blink_ = anime.time_ / (design::Fps / 6);

  anime.scroll_ += 0.25f;
  if (anime.scroll_ >= size::Sea_W) { anime.scroll_ = 0.f; }
}


// 背景の描画
void title::disp_title() {

  // TIPS: 色合いが気に入らないので、最背面に別の色をこっそり描画
  drawFillBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    win::color(paint::White));

  // 海
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    anime.scroll_ * 2, 0, size::Sea_W, size::Sea_H,
    sea_, win::color(paint::White, 0.5f));

  // 波
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    anime.scroll_, 0, size::Sea_W, size::Sea_H,
    fog_, win::color(paint::SkyBlue, 0.5f));

  // 大陸
  drawTextureBox(0, 0, size::WIDTH, size::HEIGHT,
    0, 0, size::World_W, size::World_H,
    bg_, win::color(paint::Black),
    0, Vec2f(1.01f, 1.01f), Vec2f(size::Half_W, size::Half_H));
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    0, 0, size::World_W, size::World_H,
    bg_, win::color(paint::Orange));

  // ロゴ
  drawTextureBox(0, size::LogoPos_Y, size::Logo_W, size::Logo_H,
    0, size::Logo_H * anime.blink_, size::Logo_W, size::Logo_H,
    logo_, win::color(paint::White),
    0, Vec2f(3.f, 3.f), Vec2f(size::Logo_W / 2, 0));
}


// クリック操作の表示
void title::disp_click() {
  // TIPS: 難易度を決定したら表示しない
  if (state_ > Select) { return; }

  pos_.x() =
    -telop_.getTextLength(text[state_ == Select ? Back : Click]) / 2;
  pos_.y() = 0;

  telop_.drawText(text[state_ == Select ? Back : Click], pos_,
    win::color(state_ > Change ? paint::Green : paint::Black,
    state_ == Blink1 ? (blink_timer_ / 2) % 2 : anime.time_ / (design::Fps - 35)));
}


// コマンドの描画
void title::disp_mode() {
  // TIPS: １回クリックされるまでボタンを表示しない
  if (state_ < Mode) { return; }

  if (anime.alpha_ < 0.75f && state_ != Change) { anime.alpha_ += 0.05f; }

  buttonDataTranslate();

  for (i = begin_; i < end_; ++i) {
    buttonPosTranslate(i);
    on_mouse_ = rectOnMouse(pos_, size_);

    // TIPS: エフェクト実行中はボタンの色を変えない
    if (state_ != Mode && state_ != Select) { on_mouse_ = false; }

    // ボタンの描画
    win::draw(pos_, size_,
      win::color(on_mouse_ ? paint::Orange : paint::Blue,
      click_mode_ == i ? (blink_timer_ / 2) % 2 : anime.alpha_));

    // テロップの表示
    pos_.x() = -telop_.getTextLength(text[i]) / 2;
    pos_.y() += 15;
    telop_.drawText(text[i], pos_,
      win::color(on_mouse_ ? paint::Black : paint::White,
      click_mode_ == i ? (blink_timer_ / 2) % 2 : 1.f));
  }
}


void title::buttonPosTranslate(const short& i) {
  short pos_y = (state_ < Select) ? NewGame : Easy;

  pos_.x() = -size::Mode_W / 2;
  pos_.y() = (size::ModePos_Y) * (1.5f + i - pos_y);
}


void title::buttonDataTranslate() {
  begin_ = (state_ < Select) ? NewGame : Easy;
  end_ = (state_ < Select) ? Easy : All_Text;
}
