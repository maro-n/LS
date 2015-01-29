
#include "funds.h"

typedef cFunds  fund;


cFunds::cFunds() :
size_(Vec2f(200, size::Command_H)),
mode_(data::system.poli_mode_),
poli_state_(data::system.command_state_),
money_(data::user.assets.money_),
food_(data::user.assets.food_),
fire_(data::user.strategy.fire_),
cannon_(data::user.strategy.cannon_),
trap_(data::user.strategy.trap_),
poison_(data::user.strategy.poison_) {

  telop_.size(40);

  text[Worker] = "•ºŽm”hŒ­ ";
  text[Sell_fire] = "”„:‰Î‰Š•r ";
  text[Sell_bomb] = "”„:–CŒ‚ ";
  text[Sell_trap] = "”„:ã© ";
  text[Sell_poison] = "”„:“Å ";
  text[Back] = "–ß‚é ";

  Worker_count = 0;
  init_ = false;
};


void fund::update() {
  if (!init_) { init(); }
  if (stateChange()) { return; }
  buttonSelect();
  std::cout << fire_ << " " << cannon_ << " "
    << trap_ << " " << poison_ << std::endl;
}

void fund::earn(){
  switch (id_){
    case Worker: Worker_count += 1;/*í“¬ƒNƒŠƒAŒã‚Ì•ñV‚É+”hŒ­‰ñ”~5%’Ç‰Á*/ break;

    case Sell_fire:
      if (fire_ > 0){
        money_ += price::Fire / 2;
        --fire_;
      }
      break;

    case Sell_bomb:
      if (cannon_ > 0){
        money_ += price::Bomb / 2;
        --cannon_;
      }
      break;

    case Sell_trap:
      if (trap_ > 0){
        money_ += price::Trap / 2;
        --trap_;
      }
      break;

    case Sell_poison:
      if (poison_ > 0){
        money_ += price::Poison / 2;
        --poison_;
      }
      break;

    default:; //do not
  }
}

bool fund::stateChange() {
  switch (state_) {
  case command::MoveIn : moveMode();  break;
  case command::Blink  : blinkMode(); break;
  case command::MoveOut: backMode();  break;

  default: return false;
  }

  return true;
}


void fund::moveMode() {
  for (i = 0; i < All_Text; ++i) {
    // TIPS: ˆÚ“®‚ªŠ®—¹‚µ‚½ƒ{ƒ^ƒ“‚Ìˆ—‚ðƒXƒLƒbƒv
    if (x[i] <= 0.f) { continue; }

    if (i == 0) { x[i] -= 10.f; }
    else if (x[i - 1] <= design::DefaultPos / 1.5f) { x[i] -= 10.f; }
  }
  if (anime.alpha_ < 0.75f) { anime.alpha_ += 0.0125f; }

  // TIPS: ƒ{ƒ^ƒ“‚ÌˆÚ“®‚ªŠ®—¹‚µ‚½‚ç‘I‘ðƒ‚[ƒh‚É‚·‚é
  if (x[Back] <= 0.f) { ++state_; }
}


void fund::blinkMode() {
  ++anime.blink_;
  if (anime.blink_ >= design::Fps) { ++state_; }
}


void fund::backMode() {
  for (i = 0; i < All_Text; ++i) { x[i] += 10.f; }
  if (anime.alpha_ >= 0.f) { anime.alpha_ -= 0.05f; }
  if (x[Back] >= design::DefaultPos) {
    mode_ = mode::Neutral;
    poli_state_ = command::MoveIn;
    init_ = false;
  }
}


void fund::buttonSelect() {
  for (i = 0; i < All_Text; ++i) {
    buttonPosTranslate(i);

    if (rectOnMouse(pos_, size_) &&
      win::app->isPushButton(Mouse::LEFT)) {
      data::music.sePlay(se::Click);
      ++state_;
      id_ = i;
    }
  }
}


void fund::init() {
  buttonPosInit();

  anime.time_ = 0;
  anime.blink_ = 0;
  anime.alpha_ = 0.f;

  state_ = command::MoveIn;
  id_ = -1;
  init_ = true;
}


void fund::draw() {
  for (i = 0; i < All_Text; ++i) {
    buttonPosTranslate(i);

    on_mouse_ = rectOnMouse(pos_, size_);
    if (state_ != command::Select) { on_mouse_ = false; }
    win::draw(pos_, size_, win::color(on_mouse_ ? paint::Orange : paint::Blue,
      id_ == i ? (anime.blink_ / 2) % 2 : anime.alpha_), anime.alpha_ * 1.25f);

    pos_.x() += (size_.x() - telop_.getTextLength(text[i])) / 2;
    pos_.y() += 15;
    telop_.drawText(text[i], pos_, win::color(paint::White,
      id_ == i ? (anime.blink_ / 2) % 2 : 1.f));
  }
}


void fund::buttonPosTranslate(const short& i) {
  pos_.x() = size::CommandPos_X - x[i];
  pos_.y() = size::CommandPos_Y - (i + 1.5f) * (size_.y() + 10);
}


void fund::buttonPosInit() {
  for (i = 0; i < All_Text; ++i) { x[i] = design::DefaultPos; }
}
