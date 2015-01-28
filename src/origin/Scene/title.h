
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"

//
// ƒ^ƒCƒgƒ‹‰æ–Ê
//

class cTitle {
  //Texture bg_;
  Font font_;
  std::string text_;

  struct {
    short time_;
    short blink_;
  } anime_;

  float x_;

  void draw_bg();
  void draw_logo();
  void draw_telop();

public:
  cTitle();

  void init();

  void update();
  void draw();
};
