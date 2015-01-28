
#pragma once
#include "../Manager/data_manager.h"
#include "../Object/collision.h"

//
// �Ґ����
//

class cUnitSelect {
  short i_;
  const Vec2f size_;
  const Vec2f select_;
  Vec2f pos_;

  struct {
    Vec2f pos_;
    SelectState state_;
  } icon[PT_Member];


  void act_out();
  void act_click();
  void init_select(const short&);

  bool selectFinish();
  void phaseShift();
  void act_shift(const short&);

  void disp_other();
  void disp_info();
  void disp_unit();
  void disp_telop();
  void disp_select();

public:
  cUnitSelect();

  void update();
  void init();
  void draw();
};


/*�������X�g

�����ς�

�E�N���b�N����
�E�N���b�N�񐔏��
�E�퓬�V�[���ڍs
�E�{�^���J���[�̏ڍאݒ�
�E�E�B���h�E�A�{�^���̕`��


�\��

�E���݂��Ȃ����j�b�g�͑I��s�\
�E���݂��Ȃ����j�b�g�̃{�^���J���[�ύX
�E�e���b�v�\��
�E�L�����N�^�[���̕`��
�E�o�������o�[�̓o�^����


���v�摜

�E�w�i�`��
�E�L�����N�^�[�`��

*/
