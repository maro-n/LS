
#include "funds.h"

typedef cFunds  fund;


cFunds::cFunds() :
size_(Vec2f(200, size::Command_H)),
mode_(data::system.poli_mode_),
poli_state_(data::system.command_state_),
money_(data::user.money_),
fire_(data::user.strategy.fire_),
cannon_(data::user.strategy.cannon_),
trap_(data::user.strategy.trap_),
poison_(data::user.strategy.poison_),
pause_(data::system.pause_) {

  telop_.size(40);

  text[Worker]      = "兵士派遣 ";
  text[Sell_Fire]   = "売:火炎瓶 ";
  text[Sell_Bomb]   = "売:砲撃 ";
  text[Sell_Trap]   = "売:罠 ";
  text[Sell_Poison] = "売:毒 ";
  text[Back]        = "戻る ";

  init_ = false;
};


void fund::update() {
  if (!init_) { init(); }
  if (stateChange()) { return; }
  buttonSelect();
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
    // TIPS: 移動が完了したボタンの処理をスキップ
    if (x[i] <= 0.f) { continue; }

    if (i == 0) { x[i] -= 10.f; }
    else if (x[i - 1] <= design::DefaultPos / 1.5f) { x[i] -= 10.f; }
  }
  if (anime.alpha_ < 0.75f) { anime.alpha_ += 0.0125f; }

  // TIPS: ボタンの移動が完了したら選択モードにする
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
    isAbleToSell(i);

    // TIPS: 売却できる状態でなければクリックを許可しない
    if (rectOnMouse(pos_, size_) && is_sell_ &&
        win::app->isPushButton(Mouse::LEFT)) {
      data::music.sePlay(se::Click);
      ++state_;
      id_ = i;
      incomeMoney();
    }
  }
}


void fund::incomeMoney() {
  switch (id_) {
    case      Worker: is_worker(); break;
    case   Sell_Fire: is_fire();   break;
    case   Sell_Bomb: is_bomb();   break;
    case   Sell_Trap: is_trap();   break;
    case Sell_Poison: is_poison(); break;

    // 戻るボタンの時は何もしない
    default:;
  }
}


void fund::is_worker() {
  //TODO: 全体のHPを減少させて、減少させた量に応じた金額を取得
}


void fund::is_fire() {
  money_ += price::Fire / 2;
  --fire_;
}


void fund::is_bomb() {
  money_ += price::Bomb / 2;
  --cannon_;
}


void fund::is_trap() {
  money_ += price::Trap / 2;
  --trap_;
}


void fund::is_poison() {
  money_ += price::Poison / 2;
  --poison_;
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


// TIPS: ボタンのみ描画
//     : 背景その他はまとめて politics 画面で描画処理を行っている
void fund::draw() {
  for (i = 0; i < All_Text; ++i) {
    buttonPosTranslate(i);
    isAbleToSell(i);

    on_mouse_ = rectOnMouse(pos_, size_);
    if (state_ != command::Select || pause_) { on_mouse_ = false; }
    win::draw(pos_, size_, win::color(!is_sell_ ? paint::Gray :
      on_mouse_ ? paint::Orange : paint::Blue,
      id_ == i ? (anime.blink_ / 2) % 2 : anime.alpha_), anime.alpha_ * 1.25f);

    pos_.x() += (size_.x() - telop_.getTextLength(text[i])) / 2;
    pos_.y() += 15;
    telop_.drawText(text[i], pos_, win::color(paint::White,
      id_ == i ? (anime.blink_ / 2) % 2 : 1.f));

    if (on_mouse_) { disp_telop(i); }
  }
}


void fund::isAbleToSell(const short& i) {
  switch (i) {
    case      Worker: break;//TODO:体力が減りすぎていたら許可しない
    case   Sell_Fire: is_sell_ = fire_   > 0; break;
    case   Sell_Bomb: is_sell_ = cannon_ > 0; break;
    case   Sell_Trap: is_sell_ = trap_   > 0; break;
    case Sell_Poison: is_sell_ = poison_ > 0; break;

    // TIPS: まとめて判定処理をしている関係で、
    //     : 戻るボタンまで使えなくなるので、常にクリック可能にしておく
    default: is_sell_ = true;
  };
}


void fund::buttonPosTranslate(const short& i) {
  pos_.x() = size::CommandPos_X - x[i];
  pos_.y() = size::CommandPos_Y - (i + 1.5f) * (size_.y() + 10);
}


void fund::buttonPosInit() {
  for (i = 0; i < All_Text; ++i) { x[i] = design::DefaultPos; }
}


void fund::disp_telop(const short& id) {
  std::string text_1;   // １行目のテキスト
  std::string text_2;   // ２行目のテキスト

  pos_.x() = size::BottomPos_X + 20;
  pos_.y() = size::BottomPos_Y + 85;

  // TIPS: 各ボタンの解説
  //TODO: 必要な処理をコピペで作成（終わったらこのTODOコメントを削除）
  switch (id) {
    case Worker:
      text_1 = is_sell_ ?
        "戦闘以外の活動で給料を得ます" : "これ以上活動できません";
      telop_.drawText(text_1, pos_, win::color(paint::White));

      // TIPS: 以下、２行目のテキスト
      text_2 = is_sell_ ?
        "収入：全員のHPMAX 5%分  支出：全員のHP -5%" : " ";
      pos_.y() -= 60;
      telop_.drawText(text_2, pos_, win::color(paint::White));
      break;

    case Sell_Fire:
      text_1 = is_sell_ ?
        "火炎瓶を売却します：500 G" : "火炎瓶を所持していません。";
      telop_.drawText(text_1, pos_, win::color(paint::White));
      break;

    case Sell_Bomb:
      text_1 = is_sell_ ?
        "砲台を売却します： 1500 G" : "砲台を所持していません。";
      telop_.drawText(text_1, pos_, win::color(paint::White));
      break;

    case Sell_Trap:
      text_1 = is_sell_ ?
        "罠を売却します：    400 G" : "罠を所持していません。";
      telop_.drawText(text_1, pos_, win::color(paint::White));
      break;

    case Sell_Poison:
      text_1 = is_sell_ ?
        "毒矢を売却します：  750 G" : "毒矢を所持していません。";
      telop_.drawText(text_1, pos_, win::color(paint::White));
      break;

      // 戻るボタンは解説不要
    default:;
  }
}
