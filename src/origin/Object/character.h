
#pragma once
#include "../Manager/win_manager.h"
#include "../Resource/image.h"
#include <string>

//
// キャラクターデータ
//

class cCharacter {
  Texture own_;

public:

  // アニメーションの状態
  struct {
    u_short state_[3];
    u_short time_;
    u_short blink_;
    float alpha_;
  } anime;

  struct {
    u_short heal_;
    u_short motion_;
  } timer;

  sCharacterInfo info;
  sParameter status;
  u_short level_;
  u_short exp_;
  u_short bonus_;

  u_short hp_max_;
  short hp_;

  float turn_;
  u_short lane_;   // 隊列：攻撃の狙われやすさに影響

  Vec2f target_;
  Vec2f move_;
  Vec2f pos_;
  Vec2f cut_;

  void initHpMax();
  void initImage(const short&);
  void initParameter();

  cCharacter();

  void init(const Vec2f&);
  void laneShift();

  void act_move();
  void act_attack();
  void act_damage();
  void act_avoid();
  void act_();

  void animePlay();
  void animeShift();
  void animeChange(const u_short&);
  void draw();

  void timeCount();
  void timeCountReset();

  bool isEnableAction() const;
  bool isAnimePlaying();
  bool isDead();

  void damage(const u_short&);
  void recovery(const u_short&);
  void healing();

  short levelUp();
  void growth(const sParameter&);
  bool isLimit(const short&, const short&) const;

  sParameter getBaseStatus() const;
  sParameter getStatus() const;

  void targetPos(const Vec2f&);
  Vec2f getPos() const;
  u_short getLane() const;
  u_short getType() const;
  bool getSide() const;

  u_short hitRatio() const;
  u_short avoidRatio() const;

  std::string getName() const;
  sstream getLevel() const;
  Color hpColor() const;
  float hpGaugeRatio() const;
  float timeGaugeRatio() const;

  void making(const sCharacterInfo&);
  void classChange(const u_short&);
};
