
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"
#include "../Object/collision.h"

//
// リザルト画面
//

class cResult {
  Font font_;
  std::string text_;
  std::string t_;//test
  float x_;

public:
  cResult();

  void update();
  void draw();
};
