
#include "pause.h"

typedef cPause  pause;


cPause::cPause() :
size_(Vec2f(350, 60)),
scene_(data::system.scene_[play::Now]),
pause_(data::system.pause_) {

  telop_.size(40);

  text[Pause]     = "PAUSE";
  text[Button_1]  = "�ĊJ ";
  text[Button_2]  = "�^�C�g���ɖ߂� ";
  text[Attention] = "�f�[�^�͕ۑ�����܂���B��낵���ł����H ";
  text[OK]        = "�͂� ";
  text[NG]        = "������ ";
}


bool pause::update() {
  // TIPS: ����A�퓬�ȊO�̃V�[���ł̓|�[�Y����������Ȃ�
  if (scene_ != scene::Politics &&
    scene_ != scene::Battle) { return false; }

  // TIPS: �E�N���b�N�Ń|�[�Y��ʂɂ���
  if (win::app->isPushButton(Mouse::RIGHT)) { pause_ = !pause_; }

  // TIPS: �|�[�Y��ʂłȂ���΁A�|�[�Y��ʂ̑���������Ȃ�
  if (!pause_) { state_ = Select; return pause_; }

  scene_ == scene::Politics ? pauseMenu() : battleMenu();
  return pause_;
}


// TIPS: �P���ȃ|�[�Y��ʂ̏���
void pause::pauseMenu() {
  for (i = 0; i < 2; ++i) {
    buttonPosTranslate(i);

    on_mouse_ = rectOnMouse(pos_, size_);
    if (on_mouse_ && win::app->isPushButton(Mouse::LEFT)) {
      data::music.sePlay(se::Click_Menu);
      commandShift(i);
    }
  }
}


void pause::commandShift(const short& i) {
  switch (state_) {
    case  Select: i == 0 ? backToGame()  : ++state_;     break;
    case Clicked: i == 0 ? backToTitle() : backToGame(); break;
    default: state_ = Select;
  }
}


void pause::backToGame() {
  pause_ = false;
  state_ = Select;
}


void pause::backToTitle() {
  backToGame();
  data::system.scene_[play::Next] = scene::Title;
}


// TIPS: �퓬��ʂ̃|�[�Y�����j���[��ʂ̏���
void pause::battleMenu() {
}


void pause::hoge() {
}


void pause::draw() {
  disp_back();
  scene_ == scene::Battle ? sceneBattle() : scenePolitics();
}


// �|�[�Y��ʂ̕`��
void pause::disp_back() {
  drawFillBox(-size::Half_W, -size::Half_H,
    size::WIDTH, size::HEIGHT, win::color(paint::Black, 0.5f));

  pos_.x() = -telop_.getTextLength(text[Pause]) / 2;
  pos_.y() = size::PausePos_Y;
  telop_.drawText(text[Pause], pos_, win::color(paint::White));

  if (state_ == Clicked) {
    win::draw(Vec2f(-420, size::Attension_Y - 15),
      Vec2f(840, 60), win::color(paint::Red, 0.75f));

    pos_.x() = -telop_.getTextLength(text[Attention]) / 2;
    pos_.y() = size::Attension_Y;
    telop_.drawText(text[Attention], pos_, win::color(paint::White));
  }
}


// �����ʂ̃|�[�Y�\��
void pause::scenePolitics() {
  for (i = 0; i < 2; ++i) {
    buttonPosTranslate(i);

    on_mouse_ = rectOnMouse(pos_, size_);    
    if (on_mouse_) { win::draw(pos_, size_, win::color(paint::Gray, 0.75f)); }
    
    pos_.x() = -telop_.getTextLength(text[button_ + i]) / 2;
    pos_.y() += 15;
    telop_.drawText(text[button_ + i], pos_,
      win::color(on_mouse_ ? paint::Orange : paint::White));
  }
}


// �퓬��ʂ̃|�[�Y�\��
void pause::sceneBattle() {
}


void pause::buttonPosTranslate(const short& i) {
  // TIPS: �|�[�Y��ʂ̏�ԂɑΉ������{�^���̏����擾
  button_ = state_ == Clicked ? OK : Button_1;

  pos_.x() = -size_.x() / 2;
  pos_.y() = -size::Attension_Y - (i + 0.5f) * (size_.y() + 10);
}
