
#include "title.h"

typedef cTitle  title;


cTitle::cTitle() :
font_(Font(FONT_)) {
  text_ = "Click Start";
}


// ���o�̏�����
// TIPS: ���[�v�̊J�n���Ɉ�x�������������s��
void title::init() {
  anime_.time_  = 0;
  anime_.blink_ = 0;
}


void title::update() {

  // �e�X�g
  if (win::app->isPushButton(Mouse::LEFT)) {
    data::system.scene_[play::Next] = scene::Politics;
  }
}


void title::draw() {
  draw_bg();
  draw_logo();
  draw_telop();
}


// �w�i�̕`��
void title::draw_bg() {
}


// �^�C�g�����S�̕`��
void title::draw_logo() {
}


// �e���b�v�Ȃǂ̕`��
void title::draw_telop() {
  font_.size(40);

  x_ = -font_.drawSize(text_).x() / 2;
  font_.draw(text_, Vec2f(x_, size::HEIGHT / 6), Color(1, 1, 1));
}
