
#pragma once
#include "../System/draw_window.h"
#include <fstream>

//
// �L�����N�^�[�f�[�^
//

class cCharacter {
  Texture own_;

  // �A�j���[�V�����̏��
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
  u_short lane_;   // ����F�U���̑_���₷���ɉe��

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

  /* �퓬�V�X�e���֌W */

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


  /* �p�����[�^����i�f�[�^�o�́j�֌W */

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


  /* �p�����[�^����i�ݒ�j�֌W */

  void laneShift();

  void aliasTargetPos(const Vec2f&);

  void expCount(const u_short&);
  short levelUp();
  void growth(const sParameter&);
  bool isLimit(const short&, const short&) const;

  void making(const sCharacterInfo&);
  void classChange(const u_short&);


  /* �A�j���[�V�����֌W */

  void animePlay();
  void animeShift();
  void animeChange(const u_short&);
  void draw(const float&);


  /* �f�[�^�Ǘ��֌W */

  void fileLoad(std::ifstream&);

  sCharacterInfo getInfo() const;
};
