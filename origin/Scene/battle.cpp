
#include "battle.h"

typedef cBattle  battle;


cBattle::cBattle() :
enemy_num_(0), camera_x_(0.f) {
  data::system.phase_ = phase::Standby;

  //TEST
  {
    data::user.player.emplace_back();
    data::user.player.emplace_back();
    data::user.player.emplace_back();
    data::user.player.emplace_back();
    data::user.player.emplace_back();
    data::system.enemy.emplace_back();
    data::system.enemy.emplace_back();
    data::system.enemy.emplace_back();

    sCharacterInfo player_;
    {
      sParameter bonus(10);

      player_.name_ = "�E�҂́[��";
      player_.side_ = true;
      player_.type_ = type::Fighter;
      player_.gender_ = gen::Male;

      data::user.player[0].making(player_);
      data::user.player[0].growth(sParameter(100));
      data::user.player[0].init(Vec2f(-300, 200));

      player_.name_ = "�ق��ق�";
      player_.side_ = true;
      player_.type_ = type::Mage;
      player_.gender_ = gen::Female;

      data::user.player[1].making(player_);
      data::user.player[1].growth(bonus);
      data::user.player[1].init(Vec2f(-300, 50));
      data::user.player[1].laneShift();

      player_.name_ = "�ӂ��ӂ�";
      player_.side_ = true;
      player_.type_ = type::Scout;
      player_.gender_ = gen::Male;

      data::user.player[2].making(player_);
      data::user.player[2].growth(bonus);
      data::user.player[2].init(Vec2f(-300, -100));

      player_.name_ = "�҂�҂�";
      player_.side_ = true;
      player_.type_ = type::Fighter;
      player_.gender_ = gen::Male;

      data::user.player[3].making(player_);
      data::user.player[3].growth(bonus);
      data::user.player[3].init(Vec2f(-300, 200));

      player_.name_ = "�S����΂�";
      player_.side_ = true;
      player_.type_ = type::Fighter;
      player_.gender_ = gen::Male;

      data::user.player[4].making(player_);
      data::user.player[4].growth(bonus);
      data::user.player[4].init(Vec2f(-300, 200));
    }

    sCharacterInfo enemy_;
    {
      enemy_.name_ = "enemy";
      enemy_.side_ = false;
      enemy_.type_ = type::Fighter;
      enemy_.gender_ = gen::Female;

      data::system.enemy[0].making(enemy_);
      data::system.enemy[0].init(Vec2f(280, 200));

      enemy_.name_ = "enemy";
      enemy_.side_ = false;
      enemy_.type_ = type::Scout;
      enemy_.gender_ = gen::Female;

      data::system.enemy[1].making(enemy_);
      data::system.enemy[1].init(Vec2f(280, 50));

      enemy_.name_ = "enemy";
      enemy_.side_ = false;
      enemy_.type_ = type::Scout;
      enemy_.gender_ = gen::Male;

      data::system.enemy[2].making(enemy_);
      data::system.enemy[2].init(Vec2f(280, -100));
      data::system.enemy[2].laneShift();
    }
  }
}


void battle::update() {

  // TIPS: �G���������S�ł�����퓬�I��
  battleFinish();

  // TIPS: �퓬�I���Ɋւ��J�E���g�l��������
  // * �e�i�K�̏������ɃJ�E���g���擾�A�����𖞂�������퓬���I������
  countInit();

  // TIPS: �v���C���[���L�����N�^�[���ׂĂ̏���
  begin = data::user.player.begin();
  end = data::user.player.end();
  unitUpdate();

  // TIPS: ���ׂĂ̓G�̏���
  begin = data::system.enemy.begin();
  end = data::system.enemy.end();
  unitUpdate();
}


// TODO: �����\��
// TIPS: �G���T�̈ȏア��ꍇ�A�c��̓G���t�B�[���h�ɏo��������
void battle::unitSummon() {
}


// TIPS: �퓬�s�\�J�E���g�����Z�b�g
void battle::countInit() {
  dead.player_ = 0;
  dead.enemy_ = 0;
}


// TIPS: �퓬�s�\�̃L�����N�^�[���J�E���g
void battle::deadCount() {
  it->getSide() ? ++dead.player_ : ++dead.enemy_;
}


void battle::battleFinish() {
  // TIPS: ��������...�G���S��
  if (dead.enemy_ == data::system.enemy.size()) {
    data::system.phase_ = phase::Win;
    data::system.scene_[play::Next] = scene::Result;
  }

  // TIPS: �s�k����...�������S��
  if (dead.player_ == data::user.player.size()) {
    data::system.phase_ = phase::Lose;
    data::system.scene_[play::Next] = scene::Result;
  }
}


void battle::unitUpdate() {
  for (it = begin; it != end; ++it) {
    unit_animePlay();

    // TIPS: �퓬�s�\��Ԃ̃L�����N�^�[�̏������X�L�b�v
    if (it->isDead()) { deadCount(); continue; }

    timeCount();
    unit_action();
  }
}


void battle::timeCount() {
  // TIPS: ���炩�̐퓬�A�j���[�V���������s���Ȃ�J�E���g���X�L�b�v
  if (it->isAnimePlaying()) { return; }
  it->timeCount();
}


void battle::unit_animePlay() {
  it->animeShift();
  it->animePlay();
}


void battle::unit_action() {
  // TIPS: �ҋ@���Ԓ��Ȃ珈�����X�L�b�v
  if (it->isWait()) { return; }
  it->timeCountReset();
  it->animeChange(action::Attack);

  // TIPS: �s�����̃L�����ɓG�΂��Ă��鑊��̏����擾
  it->getSide() ? getEnemyInfo() : getPlayerInfo();

  // TIPS: ���g�̃N���X�ɉ������s����I��
  it->getType() == type::Mage ? magicalAttack()
    : it->getType() == type::Priest ? cure()
    : physicalAttack();
}


void battle::physicalAttack() {

  for (target = begin_; target != end_; ++target) {
    // TIPS: �^�[�Q�b�g���퓬�s�\�Ȃ�U���Ώۂɂ��Ȃ�
    if (target->isDead()) { continue; }

    // TIPS: ���g�̃N���X�ƃ^�[�Q�b�g�̑�������؁A�U���ł��邩�𔻒�
    //     : �U���\�Ȃ画�菈�����I���A�U������
    //     : �U���ł���ʒu�ɓG��������Ȃ���΁A���̂܂܍Ō���̓G���U������
    if (it->targetLook(target->getLane())) { break; }
  }

  // TIPS: ����������s���A�����Ȃ�_���[�W��^����
  target->avoidRatio() < data::random.fromZeroToLast(it->hitRatio())
    ? target->physicalDamage(it->getPower())
    : target->animeChange(action::Avoid);
}


void battle::magicalAttack() {
  dead.count_ = 0;

  // TIPS: �퓬�s�\��Ԃ̃L�����N�^�[�̐����擾
  for (target = begin_, i = 0; target != end_; ++target, ++i) {
    if (target->isDead()) { ++dead.count_; }
  }

  // TIPS: �l���������قǁA�P�l������̃_���[�W�ʂ�����
  u_short temp_damage = it->getPower() / (i - dead.count_);

  // TIPS: �퓬�s�\�ȃL�����ȊO�̑S�̂Ƀ_���[�W��^����
  for (target = begin_, i = 0; target != end_; ++target, ++i) {
    if (target->isDead()) { continue; }
    target->magicalDamage(temp_damage);
  }
}


void battle::cure() {
}


// TIPS: �v���C���[���̃L�����N�^�[���s�����Ȃ�A�G�̏����擾
void battle::getEnemyInfo() {
  begin_ = data::system.enemy.begin();
  end_ = data::system.enemy.end();
}


// TIPS: �G�L�������s�����Ȃ�v���C���[�̏����擾������
void battle::getPlayerInfo() {
  begin_ = data::user.player.begin();
  end_ = data::user.player.end();
}


void battle::init() {
  // TIPS: �}�b�v���̏�����
  u_short& stage = data::system.stage_id_;
  map_data_.mapInit(data::user.map_info[stage].id_);

  // TODO: ���̑��̏�����������ǉ�
  countInit();
  camera_x_ = 0.f;

  data::music.stop();
  data::music.play(data::random.fromFirstToLast(bgm::Battle1, bgm::Battle3));
}


void battle::draw() {
  //++anime.time_;
  //if (anime.time_ >= size::WIDTH * 2) { anime.time_ = 0; }
  map_data_.draw(anime.time_);

  dispUnitInfo();

  telop_.size(20);

  // TIPS: �v���C���[���̃L�����N�^�[���ׂĂ̏���
  begin = data::user.player.begin();
  end = data::user.player.end();
  for (it = begin, i = 0; it != end; ++it, ++i) {
    it->draw(it->isDead() ? -camera_x_ : 0.f);
    dispPlayerInfo();
    telop_.flushNumber();
  }

  // TIPS: ���ׂĂ̓G�L�����̏���
  begin = data::system.enemy.begin();
  end = data::system.enemy.end();
  for (it = begin; it != end; ++it) {
    it->draw(camera_x_);
    dispEnemyInfo();
  }
}


void battle::dispUnitInfo() {

  // TIPS: �E�B���h�E������\���A���ۂ̃f�[�^�̓L�����N�^�[�`��Ɠ����ɍs��
  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1);
    pos_.y() = -size::HEIGHT / 2;

    win::draw(pos_, Vec2f(size::UnitInfo_W, size::UnitInfo_H),
      win::color(paint::Blue, 0.8f));
  }
}


// TIPS: �v���C���[���̃L�����N�^�[�̏���\��
void battle::dispPlayerInfo() {

  // ���x��
  {
    telop_.numberInput(it->getLevelString());

    pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1) + size::NamePos_X;
    pos_.y() = -size::HEIGHT / 2 + size::NamePos_Y;
    telop_.drawNumber(pos_, win::color(paint::White));
  }

  // ���O
  {
    pos_.x() += telop_.getNumberLength() * 1.5f;
    telop_.drawText(it->getName(), pos_, win::color(paint::White));
  }

  // HP�Q�[�W
  {
    pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1) + size::GaugePos_X;
    pos_.y() = -size::HEIGHT / 2 + size::GaugePos_Y * 2.5f;

    win::gaugeDraw(pos_, Vec2f(size::Gauge_W, size::Gauge_H),
      it->hpGaugeRatio(), it->hpColor());
  }

  // �^�C���Q�[�W
  {
    pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1) + size::GaugePos_X;
    pos_.y() = -size::HEIGHT / 2 + size::GaugePos_Y;

    win::gaugeDraw(pos_, Vec2f(size::Gauge_W, size::Gauge_H),
      it->timeGaugeRatio(), win::color(paint::Orange));
  }
}


void battle::dispEnemyInfo() {
  pos_ = it->getPos();

  // ���O
  {
    telop_.textInput(it->getName());

    pos_.y() += size::Unit_W * 3;
    telop_.drawText(Vec2f(pos_.x() - telop_.getTextLength() / 2, pos_.y()),
      win::color(paint::Pink));
  }

  // TIPS: �X�p�C�𑗂��Ă��鎞�����\���ł���悤�ɂ���
  if (data::user.strategy.spy_) {

    // HP�Q�[�W
    pos_.x() -= size::GaugePos_X * 2;
    pos_.y() -= size::GaugePos_Y * 6.5f;
    win::gaugeDraw(pos_, Vec2f(size::Gauge_W / 2, size::Gauge_H * 0.75f),
      it->timeGaugeRatio(), win::color(paint::Orange));

    // �^�C���Q�[�W
    pos_.y() += size::GaugePos_Y * 0.8f;
    win::gaugeDraw(pos_, Vec2f(size::Gauge_W / 2, size::Gauge_H * 0.75f),
      it->hpGaugeRatio(), it->hpColor());
  }
}
