
#pragma once
#include "../System/draw_window.h"
#include <fstream>

//
// キャラクターデータ
//

class cCharacter {
  Texture own_;

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

  u_short hp_max_;
  short hp_;

  float turn_;
  u_short lane_;   // 隊列：攻撃の狙われやすさに影響

  Vec2f target_;
  Vec2f move_;
  Vec2f pos_;
  Vec2f cut_;


  void healing();

  void changeImage(const short&);
  void initHpMax();
  void initParameter();

public:
  cCharacter();

  /* 戦闘システム関係 */

  void init(const Vec2f&);

  void timeCount();
  void timeCountReset();

  bool isWait() const;
  bool isAnimePlaying();
  bool isDead();

  bool targetLook(const short&);
  u_short getPower();
  void physicalDamage(const u_short&);
  void magicalDamage(const u_short&);
  void recovery(const u_short&);

  Color hpColor() const;
  float hpGaugeRatio() const;
  float timeGaugeRatio() const;


  /* パラメータ操作（データ出力）関係 */

  sParameter getBaseStatus() const;
  sParameter getStatus() const;

  Vec2f getPos() const;
  u_short getLane() const;
  u_short getType() const;
  bool getSide() const;

  u_short hitRatio() const;
  u_short avoidRatio() const;

  std::string getName() const;
  u_short getLevel() const;
  sstream getLevelString() const;
  u_short getHP() const;
  u_short getHPMAX() const;


  /* パラメータ操作（設定）関係 */

  void laneShift();

  void aliasTargetPos(const Vec2f&);

  void expCount(const u_short&);
  short levelUp();
  void growth(const sParameter&);
  bool isLimit(const short&, const short&) const;

  void making(const sCharacterInfo&);
  void classChange(const u_short&);


  /* アニメーション関係 */

  void animePlay();
  void animeShift();
  void animeChange(const u_short&);
  void draw(const float&);


  /* データ管理関係 */

  void fileLoad(std::ifstream&);

  sCharacterInfo getInfo() const;
};
