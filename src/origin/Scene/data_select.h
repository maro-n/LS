
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"

//
// �f�[�^�̃Z�[�u�A���[�h
//

class cDataSelect {
  Font font_;
  std::string text_;
  float x_;

public:
  cDataSelect();

  void update();
  void draw();
};
