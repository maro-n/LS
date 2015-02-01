
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

  short i;
  short button_;
  Vec2f pos_;
  const Vec2f size_;

  scene& scene_;
  bool& pause_;
  bool on_mouse_;

  enum {
    Pause,
    Button_1,
    Button_2,
    Attention,
    OK,
    NG,
  };
  std::string text[6];

  enum {
    Select,
    Clicked,
  };
  short state_;

  void pauseMenu();
  void commandShift(const short&);
  void backToGame();
  void backToTitle();

  void battleMenu();
  void hoge();

  void disp_back();
  void scenePolitics();
  void sceneBattle();

  void buttonPosTranslate(const short&);

public:
  cPause();

  bool update();
  void draw();
};
