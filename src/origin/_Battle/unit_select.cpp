
#include "unit_select.h"

typedef cUnitSelect  unit;


cUnitSelect::cUnitSelect() :
size_(Vec2f(WIDTH / 4 - 2, 64)),
select_(Vec2f(WIDTH / 4, 96)) {
  for (i_ = 0; i_ < PT_Member; ++i_) {
    icon[i_].pos_.x() = (size_.x() + 2) * (i_ / 5 - 2) + 1;
    icon[i_].pos_.y() = (size_.y() + 2) * (3 - i_ % 5);
    icon[i_].state_ = Out;
  }
  pos_.y() = -select_.y();
}


void unit::update() {
  // TIPS: �퓬�ł���l����I��������A�퓬�J�n���邩�I��
  if (selectFinish()) { phaseShift(); return; }

  // TIPS: �o�����郆�j�b�g�̑I��
  for (i_ = 0; i_ < PT_Member; ++i_) {
    icon[i_].state_ != Clicked ? act_out() : act_click();
  }
}


void unit::act_out() {

  // TIPS: �J�[�\�����A�C�R���̏�ɂ��邩����A
  //       �N���b�N�������j�b�g���o�������o�[�ɂ���
  icon[i_].state_ = box_to_cursor(icon[i_].pos_, size_) ? OnMouse : Out;

  if (icon[i_].state_ == OnMouse && win::app->isPushButton(Mouse::LEFT)) {
    icon[i_].state_ = Clicked;
  }
}


void unit::act_click() {
  // TIPS: �o����Ԃ̃��j�b�g���ēx�N���b�N������o�������o�[����O��
  if (box_to_cursor(icon[i_].pos_, size_)) {
    if (win::app->isPushButton(Mouse::LEFT)) { icon[i_].state_ = OnMouse; }
  }
}


void unit::init_select(const short& i) {
  pos_.x() = i ? select_.x() / 4 : -(select_.x() * 1.25f);
}


// TIPS: �I�����ꂽ���j�b�g�̐����o��
bool unit::selectFinish() {
  short num = 0;

  for (i_ = 0; i_ < PT_Member; ++i_) {
    if (icon[i_].state_ == Clicked) { ++num; }
  }

  // TIPS: �퓬�J�n�ł���l���ɂȂ����� true ��Ԃ�
  return !(num < BT_Member);
}


void unit::phaseShift() {
  for (i_ = 0; i_ < 2; ++i_) {
    init_select(i_);
    if (box_to_cursor(pos_, select_) && win::app->isPushButton(Mouse::LEFT)) {
      act_shift(i_);
    }
  }
}


void unit::act_shift(const short& i) {
  switch (i) {
    case  0:
      data::system.phase_ = pState::Fight; break;
    default:
      for (i_ = 0; i_ < PT_Member; ++i_) { icon[i_].state_ = Out; }
  }
}


void unit::init() {
}


void unit::draw() {
  disp_other();
  disp_info();
  disp_unit();

  if (selectFinish()) {
    disp_telop();
    disp_select();
  }
}


// TIPS: �w�i�A�E�B���h�E�ȂǁA�X�V���e�����Ȃ����ڂ̕\��
void unit::disp_other() {
  // �w�i
  // TODO: �摜��p�ӂ��āA�����ɕ`�揈�������

  // ���b�Z�[�W�E�B���h�E
  win::draw(Vec2f(-WIDTH / 2, -HEIGHT / 2), Vec2f(WIDTH, 200),
    win::color(Blue));
}


// TIPS: �J�[�\�������킹�Ă��郆�j�b�g�̏���\��
void unit::disp_info() {
}


void unit::disp_unit() {
  for (i_ = 0; i_ < PT_Member; ++i_) {
    win::draw(icon[i_].pos_, size_,
      icon[i_].state_ == Clicked
      ? win::color(Yellow)    // �N���b�N����
      : icon[i_].state_ == OnMouse
      ? win::color(SkyBlue)   // �J�[�\�����A�C�R���̏�ɂ���
      : win::color(Blue));    // �J�[�\�����Ȃ�
  }
}


// TIPS: �����o�[���m�肵�ďo�����邩�̃��b�Z�[�W��\��
void unit::disp_telop() {
}


// TIPS: �o���ƃL�����Z���̃{�^���\��
void unit::disp_select() {
  for (i_ = 0; i_ < 2; ++i_) {
    init_select(i_);

    win::draw(pos_, select_,
      box_to_cursor(pos_, select_)
      ? win::color(SkyBlue)
      : win::color(Blue));
  }
}
