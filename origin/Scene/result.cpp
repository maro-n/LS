
#include "result.h"

typedef cResult  result;


cResult::cResult() :
bg_(Texture("res/png/back_data_select.png")),
size_(Vec2f(200, size::Command_H)),
next_(data::system.scene_[play::Next]),
phase_(data::system.phase_),
stage_id_(data::system.stage_id_),
ending_(data::system.clear_),
battle_(data::user.count.battle_),
command_(data::user.count.command_),
dif_(data::user.dif_) {

  telop_.size(60);
  info_.size(40);

  text[Result] = "Result";
  text[Win]    = "Win";
  text[Lose]   = "Lose";
  text[Clear]  = "Congratulation !!";
  text[Telop1] = "���ׂĂ̒n��𐧈����܂��� ";
  text[Telop2] = "NewGame �Ńf�[�^�������p���ōŏ�����V�ׂ܂� ";
  text[Telop3] = "�ĊJ������A�K���Z�[�u���Ă������� ";
}


void result::update() {
  if (stateChange()) { return; }
}


bool result::stateChange() {
  switch (state_) {
    case  FadeIn: fadeInMode();  break;
    case   Blink: blinkMode();   break;
    case FadeOut: fadeOutMode(); break;

    default: return false;
  }

  return true;
}


void result::fadeInMode() {
  // TIPS: �t�F�[�h�C���������I������瑀����󂯕t����悤�ɂ���
  anime.alpha_ += 0.05f;
  if (anime.alpha_ >= 1.f) { ++state_; }
}


void result::blinkMode() {
}


void result::fadeOutMode() {
}


void result::init() {
  anime.wait_ = design::Fps;
  anime.time_ = 0;
  anime.blink_ = 0;
  anime.alpha_ = 0.f;

  state_ = FadeIn;
  result_ = phase_ == phase::Win;

  levelAverage();
  ending_ = stageCount();

  // TIPS: �G���f�B���O�Ȃ�N���A�����N�̌v�Z���s��
  if (ending_) {
    rank_ = (battle_ - design::AllStage) + (command_ - (dif_ + 1) * 2);
  }

  musicPlay();
}


// TIPS: �퓬���ʂ̏��s�A�G���f�B���O�𔻒�A�Ή����� BGM ���Đ�����
void result::musicPlay() {
  data::music.stop();

  // FIXME: �G���f�B���OBGM �͌�������ւ�
  data::music.play(ending_ ? bgm::Result_Win :
    result_ ? bgm::Result_Win : bgm::Result_Lose);
}


void result::levelAverage() {
  lv_average.player_ = 0;
  lv_average.enemy_ = 0;

  std::vector<cCharacter>::iterator it, begin, end;

  begin = data::user.player.begin();
  end = data::user.player.begin();
  for (it = begin; it != end; ++it) { lv_average.player_ += it->getLevel(); }
  lv_average.player_ /= data::user.player.size();

  begin = data::system.enemy.begin();
  end = data::system.enemy.begin();
  for (it = begin; it != end; ++it) { lv_average.enemy_ += it->getLevel(); }
  lv_average.enemy_ /= data::system.enemy.size();
}


bool result::stageCount() {
  short stage_count = 0;
  for (short i = 0; i < design::AllStage; ++i) {
    if (data::user.map_info[i].flag_) { ++stage_count; }
  }

  return stage_count == design::AllStage;
}


void result::draw() {
  disp_back();
  disp_button();
  ending_ ? disp_clear() : disp_score();
}


void result::disp_back() {

  // �w�i
  drawTextureBox(-size::Half_W, -size::Half_H, size::WIDTH, size::HEIGHT,
    0, 0, 512, 512,
    bg_, win::color(paint::White, state_ != FadeOut ? 1.f : anime.alpha_));

  ending_ ? disp_ending() : disp_logo();
}


void result::disp_logo() {
  pos_ = Vec2f(-telop_.getTextLength(text[Result]) * 1.1f, size::Result_Y);
  telop_.drawText(text[Result], pos_,
    win::color(paint::White, state_ != FadeOut ? 1.f : anime.alpha_));

  // ���s
  pos_.x() = telop_.getTextLength(result_ ? text[Win] : text[Lose]) / 2;
  telop_.drawText(result_ ? text[Win] : text[Lose], pos_,
    win::color(result_ ? paint::Yellow : paint::Pink, anime.alpha_));
}


void result::disp_ending() {
  pos_.x() = -telop_.getTextLength(text[Clear]) / 2;
  pos_.y() = size::Result_Y;
  telop_.drawText(text[Clear], pos_, win::color(paint::Yellow, anime.alpha_));

  pos_.x() = -info_.getTextLength(text[Telop1]) / 2;
  pos_.y() -= 50;
  info_.drawText(text[Telop1], pos_, win::color(paint::Yellow, anime.alpha_));
}


// �X�e�[�W�N���A�̕]��
void result::disp_score() {
}


// �Q�[���N���A
void result::disp_clear() {
  //pos_.x() = -size::Half_W + size::WIDTH / 6;
  pos_.x() = -size::Half_W / 2;
  pos_.y() = size::HEIGHT / 6 - 10;

  // �퓬��
  sstream battle;
  battle << "�@�@�@�@�퓬�񐔁F " << std::setw(4) << battle_;
  info_.drawNumber(battle, pos_, win::color(paint::White, anime.alpha_));

  // ����R�}���h��
  pos_.y() -= 50;
  sstream command;
  command << "�헪�R�}���h�񐔁F " << std::setw(4) << command_;
  info_.drawNumber(command, pos_, win::color(paint::White, anime.alpha_));

  // �N���A�����N
  pos_.y() -= 75;
  info_.drawText("�@�@�N���A�����N�F", pos_,
    win::color(paint::White, anime.alpha_));
  pos_.x() = 150;
  info_.drawText(getRank(), pos_,
    win::color(getRankColor(), anime.alpha_));

  // ����v���C�̐���
  pos_.x() = -info_.getTextLength(text[Telop2]) / 2;
  pos_.y() -= 75;
  info_.drawText(text[Telop2], pos_, win::color(paint::White, anime.alpha_));

  // �x��
  pos_ = Vec2f(-360, pos_.y() - 80);
  win::draw(pos_, Vec2f(-pos_.x() * 2, size::Command_H),
    win::color(paint::Red, anime.alpha_ * 0.75f), anime.alpha_);

  pos_.x() = -info_.getTextLength(text[Telop3]) / 2;
  pos_.y() += 15;
  info_.drawText(text[Telop3], pos_, win::color(paint::White, anime.alpha_));
}


void result::disp_button() {
  pos_.x() = -size_.x() / 2;
  pos_.y() = -size::Half_H + size_.y() * 1.5f;

  on_mouse_ = rectOnMouse(pos_, size_);
  win::draw(pos_, size_,
    win::color(on_mouse_ ? paint::Orange : paint::Blue, anime.alpha_ * 0.75f),
    anime.alpha_);

  std::string back = "�߂� ";
  pos_.x() = -info_.getTextLength(back) / 2;
  pos_.y() += 15;
  info_.drawText(back, pos_, win::color(paint::White, anime.alpha_));
}


std::string result::getRank() {
  return
    rank_ < rank::S ? "�r" :
    rank_ < rank::A ? "�`" :
    rank_ < rank::B ? "�a" : "�b";
}


short result::getRankColor() {
  return
    rank_ < rank::S ? paint::Yellow :
    rank_ < rank::A ? paint::Pink :
    rank_ < rank::B ? paint::Green : paint::Purple;
}
