
#pragma once
#include "../common.h"
#include <vector>

//
// �V�X�e���i���l�֌W�j
//

class cDispNumber {
  Texture number_;
  std::vector<short> val_;
  std::vector<short>::iterator it_;
  short i;

  enum CutSize {
    Num_W = 32,   // Number Width
    Num_H = 40,   // Number Height
  };

public:
  cDispNumber() :
    number_(Texture("res/png/sys02_number.png")) {}

  // ���l�̕\��
  // pos : �\����������W���Ƃ��i���S�_�j
  // scale : �摜�̏k��
  // color : �F�ired, green, blue, alpha�j
  void dispValue(const Vec2f& pos,
                 const float& scale = 1.0f,
                 const Color& color = Color(1.f, 1.f, 1.f, 1.f)) {

    // TIPS: �P�̌������ԑ傫�����Ɍ������ĕ`�悷��i�E���獶�Ɂj
    for (it_ = val_.begin(), i = 0; it_ != val_.end(); ++it_, ++i) {

      drawTextureBox(pos.x() - i * (Num_W * scale), pos.y(),
        Num_W, Num_H,
        0, (*it_) * Num_H, Num_W, Num_H,
        number_, color,
        0, Vec2f(scale, scale), Vec2f(Num_W / 2, Num_H / 2));
    }
  }

  // �f�[�^�̌����Ƃɒl�𒊏o
  void inputValue(int n) {
    // TIPS: �Ăяo�������Ƀf�[�^���c���Ă������Ƀ��Z�b�g����
    if (val_.size()) { val_.clear(); }

    // TIPS: �z�񂪋�Ȃ̂ŁA�K���P�͗v�f���擾����
    do {
      val_.emplace_back(n % 10);
      n /= 10;
    } while (n > 0);
  }
};
