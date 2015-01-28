
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"
#include "../Object/collision.h"

//
// �|�[�Y���
//

class cPause {
  Font font_;
  std::string text_[6];
  enum {
    Pause,
    Button_1,
    Button_2,
    Attention,
    OK,
    NG,
  };

  // TIPS: ������𒆉��ɕ`�悷�邽�߂ɁA���R���̔����̒�����ێ�
  float x_;

  Vec2f button_pos_[2];
  bool backToTitle_;

  void draw_bg();
  void draw_button();
  void draw_telop();

public:
  cPause();

  bool update();
  void draw();
};
