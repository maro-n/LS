
#include "battle.h"

typedef cBattle  battle;


cBattle::cBattle() {
  data::system.phase_ = phase::Standby;

  //TEST
  {
    data::user.player.emplace_back();
    data::user.player.emplace_back();
    data::user.player.emplace_back();
    data::user.enemy.emplace_back();
    data::user.enemy.emplace_back();
    data::user.enemy.emplace_back();

    sCharacterInfo player_;
    {
      sParameter bonus(50);

      player_.name_ = "なんかもう";
      player_.side_ = true;
      player_.type_ = type::Fighter;
      player_.gender_ = gen::Male;

      data::user.player[0].making(player_);
      data::user.player[0].growth(bonus);
      data::user.player[0].init(Vec2f(280, 200));

      player_.name_ = "だめぽ";
      player_.side_ = true;
      player_.type_ = type::Fighter;
      player_.gender_ = gen::Male;

      data::user.player[1].making(player_);
      data::user.player[1].growth(bonus);
      data::user.player[1].init(Vec2f(280, 50));

      player_.name_ = "タヒねる";
      player_.side_ = true;
      player_.type_ = type::Scout;
      player_.gender_ = gen::Male;

      data::user.player[2].making(player_);
      data::user.player[2].growth(bonus);
      data::user.player[2].init(Vec2f(280, -100));
    }

    sCharacterInfo enemy_;
    {
      enemy_.name_ = "enemy";
      enemy_.side_ = false;
      enemy_.type_ = type::Fighter;
      enemy_.gender_ = gen::Female;

      data::user.enemy[0].making(enemy_);
      data::user.enemy[0].init(Vec2f(-300, 200));

      enemy_.name_ = "enemy";
      enemy_.side_ = false;
      enemy_.type_ = type::Scout;
      enemy_.gender_ = gen::Female;

      data::user.enemy[1].making(enemy_);
      data::user.enemy[1].init(Vec2f(-300, 50));

      enemy_.name_ = "enemy";
      enemy_.side_ = false;
      enemy_.type_ = type::Scout;
      enemy_.gender_ = gen::Male;

      data::user.enemy[2].making(enemy_);
      data::user.enemy[2].init(Vec2f(-300, -100));
    }
  }
}


void battle::stageFinish() {

  // プレイヤー
  begin = data::user.player.begin();
  end = data::user.player.end();
  for (data::it = begin; data::it != end; ++data::it) {
    if (!data::it->isDead()) { break; }
  }
  if (data::it == end) {
    data::system.phase_ = phase::Lose;
    data::system.scene_[play::Next] = scene::Result;
  }

  // 敵
  begin_ = data::user.enemy.begin();
  end_ = data::user.enemy.end();
  for (data::it = begin_; data::it != end_; ++data::it) {
    if (!data::it->isDead()) { break; }
  }
  if ( data::it == end_) {
    data::system.phase_ = phase::Win;
    data::system.scene_[play::Next] = scene::Result;
  }
}


void battle::update() {
  stageFinish();
  timeCount();
  unit_anime();
  unit_action();
}


void battle::timeCount() {

  // プレイヤー
  begin = data::user.player.begin();
  end = data::user.player.end();
  for (data::it = begin; data::it != end; ++data::it) {
    if (data::it->isDead() || data::it->isAnimePlaying()) { continue; }
    data::it->timeCount();
  }

  // 敵
  begin = data::user.enemy.begin();
  end = data::user.enemy.end();
  for (data::it = begin; data::it != end; ++data::it) {
    if (data::it->isDead() || data::it->isAnimePlaying()) { continue; }
    data::it->timeCount();
  }
}


void battle::unit_anime() {

  // プレイヤー
  begin = data::user.player.begin();
  end = data::user.player.end();
  for (data::it = begin; data::it != end; ++data::it) {
    if (data::it->isDead()) { continue; }
    data::it->animeShift();
    data::it->animePlay();
  }

  // 敵
  begin = data::user.enemy.begin();
  end = data::user.enemy.end();
  for (data::it = begin; data::it != end; ++data::it) {
    if (data::it->isDead()) { continue; }
    data::it->animeShift();
    data::it->animePlay();
  }
}


void battle::unit_action() {

  // プレイヤー
  begin = data::user.player.begin();
  end = data::user.player.end();
  for (data::it = begin; data::it != end; ++data::it) {
    if (data::it->isDead() || data::it->isEnableAction()) { continue; };
    data::it->timeCountReset();
    data::it->act_attack();
    attack();
  }

  // 敵
  begin = data::user.enemy.begin();
  end = data::user.enemy.end();
  for (data::it = begin; data::it != end; ++data::it) {
    if (data::it->isDead() || data::it->isEnableAction()) { continue; };
    data::it->timeCountReset();
  }
}


void battle::attack() {
  data::it->getSide() ? player_attack() : enemy_attack();
}


void battle::player_attack() {

  // BUG: オーバーキルしてる
  begin_ = data::user.enemy.begin();
  end_ = data::user.enemy.end();
  for (target = begin_; target != end_; ++target) {
    if (target->isDead()) { continue; }
    if (data::it->getType() == target->getType()) {
      target->damage(data::it->getStatus().pow_);
      break;
    }
  }
}


void battle::enemy_attack() {
}


void battle::init() {

  // マップ情報の初期化
  {
    u_short& stage = data::system.stage_id_;
    map_data_.mapInit(data::user.map_info[stage].id_);
  }
}


void battle::draw() {
  //map_data_.draw();
  disp_unitInfo();
  disp_unit();
}


void battle::disp_unit() {

  // プレイヤー
  begin = data::user.player.begin();
  end = data::user.player.end();
  for (data::it = begin; data::it != end; ++data::it) { data::it->draw(); }

  // 敵
  begin = data::user.enemy.begin();
  end = data::user.enemy.end();
  for (data::it = begin; data::it != end; ++data::it) { data::it->draw(); }
}


void battle::disp_unitInfo() {

  // TIPS: ウィンドウだけを先に表示
  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1);
    pos_.y() = -size::HEIGHT / 2;

    win::draw(pos_, Vec2f(size::UnitInfo_W, size::UnitInfo_H),
      win::color(paint::Blue, 0.8f));
  }

  telop_.size(20);

  // TIPS: キャラクターの数だけ情報を表示
  begin = data::user.player.begin();
  end = data::user.player.end();
  for (data::it = begin, i = 0; data::it != end; ++data::it, ++i) {
    info_level();
    info_name();
    info_hpGauge();
    info_timeGauge();
    telop_.flushNumber();
  }

  // TIPS: 敵の数だけゲージを表示
  begin = data::user.enemy.begin();
  end = data::user.enemy.end();
  for (data::it = begin, i = 0; data::it != end; ++data::it, ++i) { info_enemy(); }
}


void battle::info_level() {
  telop_.numberInput(data::it->getLevel());

  pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1) + size::NamePos_X;
  pos_.y() = -size::HEIGHT / 2 + size::NamePos_Y;
  telop_.drawNumber(pos_, win::color(paint::White));
}


void battle::info_name() {
  pos_.x() += telop_.getNumberLength() * 1.5f;
  telop_.drawText(data::it->getName(), pos_, win::color(paint::White));
}


void battle::info_hpGauge() {
  pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1) + size::GaugePos_X;
  pos_.y() = -size::HEIGHT / 2 + size::GaugePos_Y * 2.5f;

  win::gaugeDraw(pos_, Vec2f(size::Gauge_W, size::Gauge_H),
    data::it->hpGaugeRatio(), data::it->hpColor());
}


void battle::info_timeGauge() {
  pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1) + size::GaugePos_X;
  pos_.y() = -size::HEIGHT / 2 + size::GaugePos_Y;

  win::gaugeDraw(pos_, Vec2f(size::Gauge_W, size::Gauge_H),
    data::it->timeGaugeRatio(), win::color(paint::Orange));
}

void battle::info_enemy() {
  pos_ = data::it->getPos();

  pos_.x() -= size::GaugePos_X * 2;
  pos_.y() -= size::GaugePos_Y * 1.2f;
  win::gaugeDraw(pos_, Vec2f(size::Gauge_W / 2, size::Gauge_H * 0.75f),
    data::it->timeGaugeRatio(), win::color(paint::Orange));

  pos_.y() += size::GaugePos_Y * 0.8f;
  win::gaugeDraw(pos_, Vec2f(size::Gauge_W / 2, size::Gauge_H * 0.75f),
    data::it->hpGaugeRatio(), data::it->hpColor());
}
