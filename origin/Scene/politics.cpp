
#include "politics.h"

typedef cPolitics  politics;


cPolitics::cPolitics() :
bg_(Texture("res/png/world_map.png")),
sea_(Texture("res/png/world_sea.png")),
fog_(Texture("res/png/world_sea_fog.png")),
size_(Vec2f(200, size::Command_H)),
mode_(data::system.poli_mode_),
state_(data::system.command_state_) {

  telop_.size(40);

  text[mode::Funds]      = "�����J�� ";
  text[mode::Armaments]  = "�R�� ";
  text[mode::Strategy]   = "�J�� ";
  text[mode::Invasion]   = "�N�U ";
  text[mode::DataSelect] = "�f�[�^ ";
  text[mode::Neutral]    = "�I�� ";

  choice[Save] = "�Z�[�u ";
  choice[Load] = "���[�h ";
  choice[Back] = "�߂� ";
}


void politics::update() {
  // TIPS: �R�}���h��I���\�ȏ�ԂłȂ���΁A���͂������Ȃ�
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

  // TIPS: �{�^�����A�j���[�V�������Ă��Ȃ����̂݁A���͂����ł���悤�ɂ���
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
    // TIPS: �ړ������������{�^���̏������X�L�b�v
    if (x[i] <= 0.f) { continue; }

    if (i == 0) { x[i] -= 10.f; }
    else if (x[i - 1] <= design::DefaultPos / 1.5f) { x[i] -= 10.f; }
  }
  if (anime.alpha_ < 0.75f) { anime.alpha_ += 0.0125f; }

  // TIPS: �{�^���̈ړ�������������I�����[�h�ɂ���
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


// �{�^���I���̏���
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
  //TODO:�Z�[�u�A���[�h�A�߂�{�^���̏���
}


// �R�}���h�̐؂�ւ�
void politics::commandChange(const mode& it) {
  mode_ = it;
  anime.blink_ = 0;
  id_ = mode::Neutral;
  ++state_;
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

  // TIPS: �e�R�}���h�̃{�^���Ɖ���̕\��
  switch (mode_) {
    case mode::Funds     : funds_.draw();     break;
    case mode::Armaments : armaments_.draw(); break;
    case mode::Strategy  : strategy_.draw();  break;
    case mode::Invasion  : invasion_.draw();  break;
    case mode::DataSelect: disp_select();     break;
    default: disp_button(); disp_telop();
  }
}


void politics::effectPlay() {
  ++anime.time_;
  if (anime.time_ >= design::Fps - 10) { anime.time_ = 0; }

  anime.scroll_ += 0.25f;
  if (anime.scroll_ >= size::Sea_W) { anime.scroll_ = 0.f; }
}


void politics::disp_back() {

  // TIPS: �F�������C�ɓ���Ȃ��̂ŁA�Ŕw�ʂɕʂ̐F����������`��
  drawFillBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    win::color(paint::White));

  // �C
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    anime.scroll_ * 2, 0, size::Sea_W, size::Sea_H,
    sea_, win::color(paint::White, 0.5f));

  // �g
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    anime.scroll_, 0, size::Sea_W, size::Sea_H,
    fog_, win::color(paint::SkyBlue, 0.5f));

  // �嗤
  drawTextureBox(0, 0, size::WIDTH, size::HEIGHT,
    0, 0, size::World_W, size::World_H,
    bg_, win::color(paint::Black),
    0, Vec2f(1.01f, 1.01f), Vec2f(size::Half_W, size::Half_H));
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    0, 0, size::World_W, size::World_H,
    bg_, win::color(paint::Orange));

  // �R�}���h����p�̃E�B���h�E
  // TIPS: �Ƃ肠�����E�B���h�E������\��
  //     : �e�R�}���h�̏����ɓ��������A���ꂼ��ʁX�ɕ\��������
  win::draw(Vec2f(size::BottomPos_X, size::BottomPos_Y),
    Vec2f(size::Bottom_W, size::Bottom_H),
    win::color(paint::Green, 0.75f));
}


void politics::disp_mode() {
  pos_.x() = size::CommandPos_X;
  pos_.y() = size::CommandPos_Y;
  win::draw(pos_, size_, win::color(paint::Green, 0.75f));

  pos_.x() += (size_.x() - telop_.getTextLength(text[short(mode_)])) / 2;
  pos_.y() += 15;
  telop_.drawText(text[short(mode_)], pos_, win::color(paint::Gray));
}


// �v���C���[�̏��
void politics::disp_info() {

  // �E�B���h�E
  win::draw(Vec2f(0, size::BottomPos_Y + size::Bottom_H + 10),
    Vec2f(size::Half_W - 10, size::HEIGHT - (size::Bottom_H + 30)),
    win::color(paint::Green, 0.75f));

  //TODO:�v���C���[���̕\��
}


void politics::disp_button() {
  for (i = 0; i < mode::Neutral; ++i) {
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


void politics::disp_select() {
  for (i = 0; i < All_Command; ++i) {
    buttonPosTranslate(i);

    on_mouse_ = rectOnMouse(pos_, size_);
    if (state_ != command::Select) { on_mouse_ = false; }
    win::draw(pos_, size_, win::color(on_mouse_ ? paint::Orange : paint::Blue,
      id_ == i ? (anime.blink_ / 2) % 2 : anime.alpha_), anime.alpha_ * 1.25f);

    pos_.x() += (size_.x() - telop_.getTextLength(choice[i])) / 2;
    pos_.y() += 15;
    telop_.drawText(choice[i], pos_, win::color(paint::White,
      id_ == i ? (anime.blink_ / 2) % 2 : 1.f));
  }
}


// �e�R�}���h�̉���e���b�v
void politics::disp_telop() {
  //TODO:�{�^���Ƀ}�E�X���悹�����A�e�{�^�����Ƃ̐�����\��
}


void politics::buttonPosTranslate(const short& i) {
  pos_.x() = size::CommandPos_X - x[i];
  pos_.y() = size::CommandPos_Y - (i + 1.5f) * (size_.y() + 10);
}


void politics::buttonPosInit() {
  for (i = 0; i < mode::Neutral; ++i) { x[i] = design::DefaultPos; }
}
