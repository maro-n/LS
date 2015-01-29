
#include "battle.h"

typedef cBattle  battle;


cBattle::cBattle() :
enemy_num_(0), camera_x_(0.f), exp_(data::system.exp_) {
  data::system.phase_ = phase::Standby;

  //TEST
  {
    data::user.player.emplace_back();
    data::user.player.emplace_back();
    data::user.player.emplace_back();
    data::system.enemy.emplace_back();
    data::system.enemy.emplace_back();
    data::system.enemy.emplace_back();

    sCharacterInfo player_;
    {
      sParameter bonus(10);

      player_.name_ = "なんだか";
      player_.side_ = true;
      player_.type_ = type::Fighter;
      player_.gender_ = gen::Male;

      data::user.player[0].making(player_);
      data::user.player[0].growth(bonus);
      data::user.player[0].init(Vec2f(280, 200));
      data::user.player[0].init(Vec2f(-300, 200));

      player_.name_ = "いけそうな";
      player_.side_ = true;
      player_.type_ = type::Mage;
      player_.gender_ = gen::Female;

      data::user.player[1].making(player_);
      data::user.player[1].growth(bonus);
      data::user.player[1].init(Vec2f(-300, 50));
      data::user.player[1].laneShift();

      player_.name_ = "きがする";
      player_.side_ = true;
      player_.type_ = type::Scout;
      player_.gender_ = gen::Male;

      data::user.player[2].making(player_);
      data::user.player[2].growth(bonus);
      data::user.player[2].init(Vec2f(-300, -100));
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

  // TIPS: 敵か味方が全滅したら戦闘終了
  battleFinish();

  // TIPS: 戦闘終了に関わるカウント値を初期化
  // * 各段階の処理中にカウントを取得、条件を満たしたら戦闘を終了する
  countInit();

  // TIPS: プレイヤー側キャラクターすべての処理
  begin = data::user.player.begin();
  end = data::user.player.end();
  unitUpdate();

  // TIPS: すべての敵の処理
  begin = data::system.enemy.begin();
  end = data::system.enemy.end();
  unitUpdate();
}


// TODO: 実装予定
// TIPS: 敵が５体以上いる場合、残りの敵をフィールドに出現させる
void battle::unitSummon() {
}


// TIPS: 戦闘不能カウントをリセット
void battle::countInit() {
  dead.player_ = 0;
  dead.enemy_ = 0;
}


// TIPS: 戦闘不能のキャラクターをカウント
void battle::deadCount() {
  it->getSide() ? ++dead.player_ : ++dead.enemy_;
}


void battle::battleFinish() {
  // TIPS: 勝利判定...敵が全滅
  if (dead.enemy_ == data::system.enemy.size()) {
    data::system.phase_ = phase::Win;
    data::system.scene_[play::Next] = scene::Result;

    begin = data::user.player.begin();
    end = data::user.player.end();
    for (it = begin; it != end; ++it) {
      if (it->isDead()) { continue; }
      it->expCount(exp_);
    }
  }

  // TIPS: 敗北判定...味方が全滅
  if (dead.player_ == data::user.player.size()) {
    data::system.phase_ = phase::Lose;
    data::system.scene_[play::Next] = scene::Result;
    exp_ /= 2;

    begin = data::user.player.begin();
    end = data::user.player.end();
    for (it = begin; it != end; ++it) {
      if (it->isDead()) { continue; }
      it->expCount(exp_);
    }
  }
}


void battle::unitUpdate() {
  for (it = begin; it != end; ++it) {
    unit_animePlay();

    // TIPS: 戦闘不能状態のキャラクターの処理をスキップ
    if (it->isDead()) { deadCount(); continue; }

    timeCount();
    unit_action();
  }
}


void battle::timeCount() {
  // TIPS: 何らかの戦闘アニメーションを実行中ならカウントをスキップ
  if (it->isAnimePlaying()) { return; }
  it->timeCount();
}


void battle::unit_animePlay() {
  it->animeShift();
  it->animePlay();
}


void battle::unit_action() {
  // TIPS: 待機時間中なら処理をスキップ
  if (it->isWait()) { return; }
  it->timeCountReset();
  it->animeChange(action::Attack);

  // TIPS: 行動中のキャラに敵対している相手の情報を取得
  it->getSide() ? getEnemyInfo() : getPlayerInfo();

  // TIPS: 自身のクラスに応じた行動を選択
  it->getType() == type::Mage ? magicalAttack()
    : it->getType() == type::Priest ? cure()
    : physicalAttack();
}


void battle::physicalAttack() {

  for (target = begin_; target != end_; ++target) {
    // TIPS: ターゲットが戦闘不能なら攻撃対象にしない
    if (target->isDead()) { continue; }

    // TIPS: 自身のクラスとターゲットの隊列を検証、攻撃できるかを判定
    //     : 攻撃可能なら判定処理を終了、攻撃する
    //     : 攻撃できる位置に敵が見つからなければ、そのまま最後尾の敵を攻撃する
    if (it->targetLook(target->getLane())) { break; }
  }

  // TIPS: 命中判定を行い、命中ならダメージを与える
  target->avoidRatio() < data::random.fromZeroToLast(it->hitRatio())
    ? target->physicalDamage(it->getPower())
    : target->animeChange(action::Avoid);
}


void battle::magicalAttack() {
  dead.count_ = 0;

  // TIPS: 戦闘不能状態のキャラクターの数を取得
  for (target = begin_, i = 0; target != end_; ++target, ++i) {
    if (target->isDead()) { ++dead.count_; }
  }

  // TIPS: 人数が多いほど、１人あたりのダメージ量が減衰
  u_short temp_damage = it->getPower() / (i - dead.count_);

  // TIPS: 戦闘不能なキャラ以外の全体にダメージを与える
  for (target = begin_, i = 0; target != end_; ++target, ++i) {
    if (target->isDead()) { continue; }
    target->magicalDamage(temp_damage);
  }
}


void battle::cure() {
}


// TIPS: プレイヤー側のキャラクターが行動中なら、敵の情報を取得
void battle::getEnemyInfo() {
  begin_ = data::system.enemy.begin();
  end_ = data::system.enemy.end();
}


// TIPS: 敵キャラが行動中ならプレイヤーの情報を取得させる
void battle::getPlayerInfo() {
  begin_ = data::user.player.begin();
  end_ = data::user.player.end();
}


void battle::init() {
  // TIPS: マップ情報の初期化
  u_short& stage = data::system.stage_id_;
  map_data_.mapInit(data::user.map_info[stage].id_);

  // TODO: その他の初期化処理を追加
  countInit();
  camera_x_ = 0.f;
}


void battle::draw() {
  ++anime.time_;
  if (anime.time_ >= size::WIDTH * 2) { anime.time_ = 0; }
  //map_data_.draw(anime.time_);

  dispUnitInfo();

  telop_.size(20);

  // TIPS: プレイヤー側のキャラクターすべての処理
  begin = data::user.player.begin();
  end = data::user.player.end();
  for (it = begin, i = 0; it != end; ++it, ++i) {
    it->draw(it->isDead() ? -camera_x_ : 0.f);
    dispPlayerInfo();
    telop_.flushNumber();
  }

  // TIPS: すべての敵キャラの処理
  begin = data::system.enemy.begin();
  end = data::system.enemy.end();
  for (it = begin; it != end; ++it) {
    it->draw(camera_x_);
    dispEnemyInfo();
  }
}


void battle::dispUnitInfo() {

  // TIPS: ウィンドウだけを表示、実際のデータはキャラクター描画と同時に行う
  for (i = 0; i < 5; ++i) {
    pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1);
    pos_.y() = -size::HEIGHT / 2;

    win::draw(pos_, Vec2f(size::UnitInfo_W, size::UnitInfo_H),
      win::color(paint::Blue, 0.8f));
  }
}


// TIPS: プレイヤー側のキャラクターの情報を表示
void battle::dispPlayerInfo() {

  // レベル
  {
    telop_.numberInput(it->getLevelString());

    pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1) + size::NamePos_X;
    pos_.y() = -size::HEIGHT / 2 + size::NamePos_Y;
    telop_.drawNumber(pos_, win::color(paint::White));
  }

  // 名前
  {
    pos_.x() += telop_.getNumberLength() * 1.5f;
    telop_.drawText(it->getName(), pos_, win::color(paint::White));
  }

  // HPゲージ
  {
    pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1) + size::GaugePos_X;
    pos_.y() = -size::HEIGHT / 2 + size::GaugePos_Y * 2.5f;

    win::gaugeDraw(pos_, Vec2f(size::Gauge_W, size::Gauge_H),
      it->hpGaugeRatio(), it->hpColor());
  }

  // タイムゲージ
  {
    pos_.x() = -size::WIDTH / 2 + i * (size::UnitInfo_W + 1) + size::GaugePos_X;
    pos_.y() = -size::HEIGHT / 2 + size::GaugePos_Y;

    win::gaugeDraw(pos_, Vec2f(size::Gauge_W, size::Gauge_H),
      it->timeGaugeRatio(), win::color(paint::Orange));
  }
}


void battle::dispEnemyInfo() {
  pos_ = it->getPos();

  // 名前
  {
    telop_.textInput(it->getName());

    pos_.y() += size::Unit_W * 3;
    telop_.drawText(Vec2f(pos_.x() - telop_.getTextLength() / 2, pos_.y()),
      win::color(paint::Pink));
  }

  // TIPS: スパイを送っている時だけ表示できるようにする
  if (data::user.strategy.spy_) {

    // HPゲージ
    pos_.x() -= size::GaugePos_X * 2;
    pos_.y() -= size::GaugePos_Y * 6.5f;
    win::gaugeDraw(pos_, Vec2f(size::Gauge_W / 2, size::Gauge_H * 0.75f),
      it->timeGaugeRatio(), win::color(paint::Orange));

    // タイムゲージ
    pos_.y() += size::GaugePos_Y * 0.8f;
    win::gaugeDraw(pos_, Vec2f(size::Gauge_W / 2, size::Gauge_H * 0.75f),
      it->hpGaugeRatio(), it->hpColor());
  }
}
