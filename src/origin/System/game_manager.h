
#pragma once
#include "window_create.h"
#include "../../lib/font.hpp"
#include "../Scene/result.h"
#include "../Scene/title.h"
#include "../Game/politics.h"
#include "../Game/stage.h"

//
// ƒQ[ƒ€ŠÇ—ƒNƒ‰ƒX
//

class GameManager {
  Title title_;
  Politics politics_;
  Stage stage_;
  Result result_;

  int mode;
  int poli_mode;
  int stage;

  void title();
  void game();

  void mode_select();
  void pause();
  void politics();
  void stage_play();
  void result();

  bool exit;

public:
  GameManager();

  void play();
};
