
#include "politics.h"

#include <iostream>

typedef cPolitics  politics;


cPolitics::cPolitics() :
bg_(Texture("res/png/world_map.png")),
smoke_(Texture("res/png/world_fog.png")),
sea_(Texture("res/png/world_sea.png")),
fog_(Texture("res/png/world_sea_fog.png")),
icon_(Texture("res/png/battle_icon.png")),
size_(Vec2f(200, size::Command_H)),
mode_(data::system.poli_mode_),
state_(data::system.command_state_),
pause_(data::system.pause_) {

  telop_.size(40);
  unit_.size(24);

  text[mode::Funds]      = "資金繰り ";
  text[mode::Armaments]  = "軍備 ";
  text[mode::Strategy]   = "開発 ";
  text[mode::Invasion]   = "侵攻 ";
  text[mode::DataSelect] = "データ ";
  text[mode::Neutral]    = "選択 ";

  icon_name[0] = "火：";
  icon_name[1] = "砲：";
  icon_name[2] = "罠：";
  icon_name[3] = "毒：";

  choice[Save] = "セーブ ";
  choice[Load] = "ロード ";
  choice[Back] = "戻る ";
}


void politics::update() {
  // TIPS: コマンドを選択可能な状態でなければ、入力を許可しない
  if (stateShift()) { return; }

  switch (mode_) {
    case mode::Funds     : funds_.update();     break;
    case mode::Armaments : armaments_.update(); break;
    case mode::Strategy  : strategy_.update();  break;
    case mode::Invasion  : invasion_.update();  break;
    case mode::DataSelect: dataSelect();        break;
    default: commandSelect();
  }
}


bool politics::stateShift() {

  // TIPS: ボタンがアニメーションしていない時のみ、入力を許可できるようにする
  switch (state_) {
    case command::MoveIn : moveMode();  break;
    case command::Blink  : blinkMode(); break;
    case command::MoveOut: backMode();  break;

    default: return false;
  }

  return true;
}


void politics::moveMode() {
  for (i = 0; i < mode::Neutral; ++i) {
    // TIPS: 移動が完了したボタンの処理をスキップ
    if (x[i] <= 0.f) { continue; }

    if (i == 0) { x[i] -= 10.f; }
    else if (x[i - 1] <= design::DefaultPos / 1.5f) { x[i] -= 10.f; }
  }
  if (anime.alpha_ < 0.75f) { anime.alpha_ += 0.0125f; }

  // TIPS: ボタンの移動が完了したら選択モードにする
  if (x[mode::DataSelect] <= 0.f) { ++state_; }
}


void politics::blinkMode() {
  ++anime.blink_;
  if (anime.blink_ >= design::Fps) { ++state_; }
}


void politics::backMode() {
  for (i = 0; i < mode::Neutral; ++i) { x[i] += 10.f; }
  if (anime.alpha_ >= 0.f) { anime.alpha_ -= 0.05f; }
  if (x[mode::DataSelect] >= design::DefaultPos) { commandChange(mode(id_)); }
}


// ボタン選択の処理
void politics::commandSelect() {
  for (i = 0; i < mode::Neutral; ++i) {
    buttonPosTranslate(i);

    if (rectOnMouse(pos_, size_) &&
        win::app->isPushButton(Mouse::LEFT)) {
      data::music.sePlay(se::Click);
      ++state_;
      id_ = i;
    }
  }
}


void politics::dataSelect() {
  //TODO:セーブ、ロード、戻るボタンの処理
}


// コマンドの切り替え
void politics::commandChange(const mode& it) {
  mode_ = it;
  anime.blink_ = 0;
  id_ = mode::Neutral;
  ++state_;
  if (mode_ == mode::DataSelect) { state_ = command::MoveIn; }
}


void politics::init() {
  anime.time_ = 0;
  anime.blink_ = 0;
  anime.scroll_ = 0.f;
  anime.alpha_ = 0.f;

  data::system.poli_mode_ = mode::Neutral;
  state_ = command::MoveIn;
  id_ = mode::Neutral;
  buttonPosInit();

  data::music.stop();
  data::music.play(bgm::Politics);
}


void politics::draw() {
  effectPlay();
  disp_back();
  disp_mode();
  disp_info();

  // TIPS: 各コマンドのボタンと解説の表示
  switch (mode_) {
    case mode::Funds     : funds_.draw();     break;
    case mode::Armaments : armaments_.draw(); break;
    case mode::Strategy  : strategy_.draw();  break;
    case mode::Invasion  : invasion_.draw();  break;
    //case mode::DataSelect: disp_select();     break;
    default: disp_button(); disp_telop();
  }

  // TIPS: 侵攻コマンド選択中はウィンドウの情報を表示しない
  if (mode_ == mode::Invasion) { return; }

  info_strategy();
  info_unit();
}


void politics::effectPlay() {
  ++anime.time_;
  if (anime.time_ >= design::Fps - 10) { anime.time_ = 0; }

  anime.scroll_ += 0.25f;
  if (anime.scroll_ >= size::Sea_W) { anime.scroll_ = 0.f; }
}


void politics::disp_back() {

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

  // 雲
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    anime.scroll_, 0, size::Sea_W, size::Sea_H,
    smoke_, win::color(paint::White, 0.5f));

  // コマンド解説用のウィンドウ
  // TIPS: とりあえずウィンドウだけを表示
  //     : 各コマンドの処理に入った時、それぞれ別々に表示させる
  win::draw(Vec2f(size::BottomPos_X, size::BottomPos_Y),
    Vec2f(size::Bottom_W, size::Bottom_H),
    win::color(paint::Gray, 0.75f));
}


void politics::disp_mode() {
  pos_.x() = size::CommandPos_X;
  pos_.y() = size::CommandPos_Y;
  win::draw(pos_, size_, win::color(paint::Brown, 0.75f));

  pos_.x() += (size_.x() - telop_.getTextLength(text[short(mode_)])) / 2;
  pos_.y() += 15;
  telop_.drawText(text[short(mode_)], pos_, win::color(paint::White));
}


// プレイヤーの情報
void politics::disp_info() {
  // TIPS: 侵攻コマンド選択中はウィンドウの情報を表示しない
  if (mode_ == mode::Invasion) { return; }

  // ウィンドウ
  win::draw(Vec2f(0, size::BottomPos_Y + size::Bottom_H + 10),
    Vec2f(size::Half_W - 10, size::HEIGHT - (size::Bottom_H + 30)),
    win::color(paint::Gray, 0.75f));

  // TIPS: 所持金以外のデータは演出をかけるので、別に描画を行う
  info_money();
}


void politics::info_money() {
  pos_.x() = size::DataPos_X;
  pos_.y() = size::DataPos_Y;
  unit_.drawText("所持金", pos_, win::color(paint::White));

  sstream money;
  money << std::setw(8) << data::user.money_ << " G";

  pos_.y() -= size::Icon_H * 0.75f;
  unit_.drawNumber(money, pos_, win::color(paint::White));
}


void politics::info_strategy() {
  for (i = 0; i < 4; ++i) {
    pos_.x() = size::DataPos_X + (i % 2 + 1) * 160;
    pos_.y() = size::DataPos_Y - size::Icon_H * (i / 2) * 0.75f;

    drawTextureBox(pos_.x(), pos_.y(), size::Icon_W / 2, size::Icon_H / 2,
      size::Icon_W * i, 0, size::Icon_W, size::Icon_H,
      icon_, win::color(paint::White));

    short val;
    switch (i) {
      case 0: val = data::user.strategy.fire_;   break;
      case 1: val = data::user.strategy.cannon_; break;
      case 2: val = data::user.strategy.trap_;   break;
      case 3: val = data::user.strategy.poison_; break;
      default: val = 0;
    }

    pos_.x() += 40;
    sstream temp;
    temp << icon_name[i] << std::setw(3) << val;
    unit_.drawNumber(temp, pos_, win::color(paint::White));
  }
}


void politics::info_unit() {
  begin_ = data::user.player.begin();
  end_ = data::user.player.end();
  for (it_ = begin_, i = 0; it_ != end_; ++it_, ++i) {
    pos_.x() = size::DataPos_X;
    pos_.y() = size::DataPos_Y - size::UnitData_Y * (i + 1.25f);

    sstream name;
    name << " LV: " << it_->getLevel() << "  " << it_->getName();
    unit_.drawNumber(name, pos_, win::color(paint::White));

    pos_.x() += 250;
    sstream hp;
    hp << " HP: " << std::setw(4) << it_->getHP() << " / " << it_->getHPMAX();
    unit_.drawNumber(hp, pos_, win::color(paint::White));

    pos_.x() -= 230;
    pos_.y() -= 30;
    win::gaugeDraw(pos_, Vec2f(400, 24), it_->hpGaugeRatio(), it_->hpColor());
  }
}


void politics::disp_button() {
  select_ = mode_ == mode::DataSelect;
  for (i = 0; i < (select_ ? All_Command : mode::Neutral); ++i) {
    buttonPosTranslate(i);

    on_mouse_ = rectOnMouse(pos_, size_);
    if (state_ != command::Select || pause_) { on_mouse_ = false; }
    win::draw(pos_, size_, win::color(on_mouse_ ? paint::Orange : paint::Blue,
      id_ == i ? (anime.blink_ / 2) % 2 : anime.alpha_), anime.alpha_ * 1.25f);

    pos_.x() += (size_.x() - telop_.getTextLength(select_ ? choice[i] : text[i])) / 2;
    pos_.y() += 15;
    telop_.drawText(select_ ? choice[i] : text[i], pos_, win::color(paint::White,
      id_ == i ? (anime.blink_ / 2) % 2 : 1.f));
  }
}


// 各コマンドの解説テロップ
// TIPS: この関数で表示するのはコマンド選択の解説のみ
void politics::disp_telop() {
}


void politics::buttonPosTranslate(const short& i) {
  pos_.x() = size::CommandPos_X - x[i];
  pos_.y() = size::CommandPos_Y - (i + 1.5f) * (size_.y() + 10);
}


void politics::buttonPosInit() {
  for (i = 0; i < mode::Neutral; ++i) { x[i] = design::DefaultPos; }
}
