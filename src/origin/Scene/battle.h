
#pragma once
#include "../Manager/data_manager.h"
#include "../System/disp_number.hpp"
#include "../Object/collision.h"
#include "../Resource/map_chip.h"
#include "../Resource/telop.h"

//
// êÌì¨âÊñ 
//

class cBattle {
  cTelop telop_;
  cMapData map_data_;

  short i;
  std::vector<cCharacter>::iterator begin, end, target, begin_, end_;

  struct {
    short time_;
    short blink_;
    float alpha_;
  } anime;

  short enemy_num_;
  Vec2f pos_;
  Vec2f cut_;

  void stageFinish();

  void timeCount();
  void unit_anime();
  void unit_action();

  void attack();
  void player_attack();
  void enemy_attack();

  void disp_unit();
  void disp_unitInfo();
  void info_level();
  void info_name();
  void info_hpGauge();
  void info_timeGauge();
  void info_enemy();

public:
  cBattle();

  void update();
  void init();
  void draw();
};
