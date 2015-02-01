
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

  text[Worker]      = "���m�h�� ";
  text[Sell_Fire]   = "��:�Ή��r ";
  text[Sell_Bomb]   = "��:�C�� ";
  text[Sell_Trap]   = "��:� ";
  text[Sell_Poison] = "��:�� ";
  text[Back]        = "�߂� ";

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
    // TIPS: �ړ������������{�^���̏������X�L�b�v
    if (x[i] <= 0.f) { continue; }

    if (i == 0) { x[i] -= 10.f; }
    else if (x[i - 1] <= design::DefaultPos / 1.5f) { x[i] -= 10.f; }
  }
  if (anime.alpha_ < 0.75f) { anime.alpha_ += 0.0125f; }

  // TIPS: �{�^���̈ړ�������������I�����[�h�ɂ���
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

    // TIPS: ���p�ł����ԂłȂ���΃N���b�N�������Ȃ�
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

    // �߂�{�^���̎��͉������Ȃ�
    default:;
  }
}


void fund::is_worker() {
  //TODO: �S�̂�HP�����������āA�����������ʂɉ��������z���擾
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


// TIPS: �{�^���̂ݕ`��
//     : �w�i���̑��͂܂Ƃ߂� politics ��ʂŕ`�揈�����s���Ă���
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
    case      Worker: break;//TODO:�̗͂����肷���Ă����狖���Ȃ�
    case   Sell_Fire: is_sell_ = fire_   > 0; break;
    case   Sell_Bomb: is_sell_ = cannon_ > 0; break;
    case   Sell_Trap: is_sell_ = trap_   > 0; break;
    case Sell_Poison: is_sell_ = poison_ > 0; break;

    // TIPS: �܂Ƃ߂Ĕ��菈�������Ă���֌W�ŁA
    //     : �߂�{�^���܂Ŏg���Ȃ��Ȃ�̂ŁA��ɃN���b�N�\�ɂ��Ă���
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
  std::string text_1;   // �P�s�ڂ̃e�L�X�g
  std::string text_2;   // �Q�s�ڂ̃e�L�X�g

  pos_.x() = size::BottomPos_X + 20;
  pos_.y() = size::BottomPos_Y + 85;

  // TIPS: �e�{�^���̉��
  //TODO: �K�v�ȏ������R�s�y�ō쐬�i�I������炱��TODO�R�����g���폜�j
  switch (id) {
    case Worker:
      text_1 = is_sell_ ?
        "�퓬�ȊO�̊����ŋ����𓾂܂�" : "����ȏ㊈���ł��܂���";
      telop_.drawText(text_1, pos_, win::color(paint::White));

      // TIPS: �ȉ��A�Q�s�ڂ̃e�L�X�g
      text_2 = is_sell_ ?
        "�����F�S����HPMAX 5%��  �x�o�F�S����HP -5%" : " ";
      pos_.y() -= 60;
      telop_.drawText(text_2, pos_, win::color(paint::White));
      break;

    case Sell_Fire:
      text_1 = is_sell_ ?
        "�Ή��r�𔄋p���܂��F500 G" : "�Ή��r���������Ă��܂���B";
      telop_.drawText(text_1, pos_, win::color(paint::White));
      break;

    case Sell_Bomb:
      text_1 = is_sell_ ?
        "�C��𔄋p���܂��F 1500 G" : "�C����������Ă��܂���B";
      telop_.drawText(text_1, pos_, win::color(paint::White));
      break;

    case Sell_Trap:
      text_1 = is_sell_ ?
        "㩂𔄋p���܂��F    400 G" : "㩂��������Ă��܂���B";
      telop_.drawText(text_1, pos_, win::color(paint::White));
      break;

    case Sell_Poison:
      text_1 = is_sell_ ?
        "�Ŗ�𔄋p���܂��F  750 G" : "�Ŗ���������Ă��܂���B";
      telop_.drawText(text_1, pos_, win::color(paint::White));
      break;

      // �߂�{�^���͉���s�v
    default:;
  }
}
