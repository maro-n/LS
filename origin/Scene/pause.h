
#pragma once
#include "../System/draw_window.h"
#include "../System/data_depot.h"
#include "../Object/collision.h"
#include "../Resource/telop.hpp"

//
// É|Å[ÉYâÊñ 
//

class cPause {
  cTelop telop_;

  enum {
    Pause,
    Button_1,
    Button_2,
    Attention,
    OK,
    NG,
  };
  std::string text[6];

  short i;
  short button_;
  Vec2f pos_;
  scene& play_scene_;
  bool pause_;
  bool click_;

  void quitGame();
  void battleMenu();

  void draw_bg();

  void scenePolitics();
  void draw_button();
  void draw_telop();

  void sceneBattle();
  void draw_command();
  void draw_explanation();

  void buttonChange();

public:
  cPause();

  bool isPause();

  void update();
  void draw();
};
