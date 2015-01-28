
#include "character.h"

typedef cCharacter  chara;
using namespace character;


cCharacter::cCharacter() : level_(1), exp_(0), bonus_(0) {
  init(Vec2f(0, 0));
}


// TIPS: 戦闘開始時のパラメータ初期化
void chara::init(const Vec2f& pos0) {
  pos_ = pos0;

  hp_ = hp_max_;
  turn_ = 0.f;

  anime.state_[Now]  = action::Stand;
  anime.state_[Next] = action::Stand;
  anime.time_ = 0;
  anime.blink_ = 0;
  anime.alpha_ = 0.f;

  timer.heal_ = 0;
  timer.motion_ = 0;
}


void chara::laneShift() {
  lane_ = (lane_ == Front) ? Back : Front;
}


void chara::act_move() {
}


void chara::act_attack() {
  animeChange(action::Attack);
}


void chara::animePlay() {
  ++anime.time_;
  if (anime.time_ >= design::Fps) { anime.time_ = 0; }
  anime.blink_ = anime.time_ / (design::Fps / 4);

  if (timer.heal_ < UNIT_TURN / 10 - status.vit_ * 2) { ++timer.heal_; }
}


void chara::animeShift() {
  if (anime.state_[Now] != anime.state_[Next]) {
    anime.time_ = 0;
    anime.state_[Now] = anime.state_[Next];
  }
}


void chara::animeChange(const u_short& act) {
  anime.state_[Next] = act;
}


void chara::draw() {
  cut_.x() = info.side_
    ? anime.blink_ * size::Unit_W + info.gender_ * (size::Unit_W * 4)
    : (anime.blink_ + 1) * size::Unit_W + info.gender_ * (size::Unit_W * 4);
  cut_.y() = anime.state_[Now] * size::Unit_H;

  drawTextureBox(pos_.x(), pos_.y(), size::Unit_W, size::Unit_H,
    cut_.x(), cut_.y(), info.side_ ? size::Unit_W : -size::Unit_W, size::Unit_H,
    own_, Color(1, 1, 1),
    0, Vec2f(3.f, 3.f), Vec2f(size::Unit_W / 2, 0));
}


void chara::timeCount() {
  turn_ += getStatus().spd_;
}


void chara::timeCountReset() {
  turn_ -= UNIT_TURN;
  timer.motion_ = design::Fps - 1;
}


bool chara::isEnableAction() const {
  return turn_ < UNIT_TURN;
}


bool chara::isAnimePlaying() {
  bool play_ = timer.motion_ > 0;

  play_ ? --timer.motion_ :
    anime.state_[Next] = hpGaugeRatio() > 0.25f ? action::Stand : action::Danger;

  return play_;
}


bool chara::isDead() {
  if (hp_ <= 0) { anime.state_[Next] = action::Dead; }
  return anime.state_[Now] == action::Dead;
}


// TIPS: 補正済みの攻撃力を受け取って計算を行う
void chara::damage(const u_short& val) {
  short damage_point = val - getStatus().vit_ / 2;
  hp_ -= damage_point > 1 ? damage_point : 1;
}


// TIPS: Priest による回復
void chara::recovery(const u_short& val) {
  hp_ += val;
  if (hp_ > hp_max_) { hp_ = hp_max_; }
}


// TIPS: 時間経過による回復
void chara::healing() {
  if (hp_ < hp_max_ && timer.heal_ >= UNIT_TURN / 10 - status.vit_ * 2) {
    short val = status.vit_ / 10;
    hp_ = val < 10 ? 10 : val;
    timer.heal_ = 0;
  }
}


short chara::levelUp() {

  // TIPS: すでに上限に達していたら処理をしない
  if (level_ >= LEVEL_LIMIT) { exp_ = 0; return 0; }

  // TIPS: 経験値を 100 で割った値が 1 以上ならレベルアップ
  short temp = exp_ / 100;
  exp_ %= 100;

  // TIPS: 上限を超えてレベルアップしないようにする
  short level_limit = LEVEL_LIMIT - level_;
  if (temp > level_limit) { temp = level_limit; }
  return temp;
}


void chara::growth(const sParameter& bonus) {
  status.pow_ += bonus.pow_;
  status.vit_ += bonus.vit_;
  status.mag_ += bonus.mag_;
  status.spd_ += bonus.spd_;
  status.dex_ += bonus.dex_;
  status.luk_ += bonus.luk_;

  initHpMax();
}


// パラメータの上限を確認する
// TIPS: 確認したいパラメータ名とボーナス値を引数として渡す
bool chara::isLimit(const short& status0, const short& val) const {
  short temp;

  switch (status0) {
    case Pow: temp = status.pow_ + val; break;
    case Vit: temp = status.vit_ + val; break;
    case Mag: temp = status.mag_ + val; break;
    case Spd: temp = status.spd_ + val; break;
    case Dex: temp = status.dex_ + val; break;
    case Luk: temp = status.luk_ + val; break;

    default: return false;
  }

  return temp < PARAM_LIMIT;
}


sParameter chara::getBaseStatus() const {
  return status;
}


// TIPS: クラスごとのパラメータ補正を加えた状態で出力
sParameter chara::getStatus() const {
  sParameter temp;

  switch (info.type_) {
    case Fighter:
      temp.pow_ = status.pow_ * 1.1f;
      temp.vit_ = status.vit_ * 1.1f;
      temp.mag_ = status.mag_ * 0.9f;
      temp.spd_ = status.spd_ * 1.2f;
      temp.dex_ = status.dex_ * 1.0f;
      temp.luk_ = status.luk_ * 0.7f;
      break;

    case Scout:
      temp.pow_ = status.pow_ * 1.0f;
      temp.vit_ = status.vit_ * 1.0f;
      temp.mag_ = status.mag_ * 1.0f;
      temp.spd_ = status.spd_ * 1.1f;
      temp.dex_ = status.dex_ * 1.2f;
      temp.luk_ = status.luk_ * 0.7f;
      break;

    case Armor:
      temp.pow_ = status.pow_ * 1.2f;
      temp.vit_ = status.vit_ * 1.2f;
      temp.mag_ = status.mag_ * 0.8f;
      temp.spd_ = status.spd_ * 0.9f;
      temp.dex_ = status.dex_ * 1.1f;
      temp.luk_ = status.luk_ * 0.8f;
      break;

    case Mage:
      temp.pow_ = status.pow_ * 0.8f;
      temp.vit_ = status.vit_ * 0.9f;
      temp.mag_ = status.mag_ * 1.2f;
      temp.spd_ = status.spd_ * 1.0f;
      temp.dex_ = status.dex_ * 0.9f;
      temp.luk_ = status.luk_ * 1.2f;
      break;

    case Priest:
      temp.pow_ = status.pow_ * 0.9f;
      temp.vit_ = status.vit_ * 0.8f;
      temp.mag_ = status.mag_ * 1.1f;
      temp.spd_ = status.spd_ * 0.8f;
      temp.dex_ = status.dex_ * 0.8f;
      temp.luk_ = status.luk_ * 1.6f;
      break;

    case Noob:
      temp.pow_ = status.pow_ * 0.8f;
      temp.vit_ = status.vit_ * 0.8f;
      temp.mag_ = status.mag_ * 0.8f;
      temp.spd_ = status.spd_ * 0.8f;
      temp.dex_ = status.dex_ * 0.8f;
      temp.luk_ = status.luk_ * 0.8f;
      break;

    case Boss:
      temp.pow_ = status.pow_ * 1.2f;
      temp.vit_ = status.vit_ * 1.2f;
      temp.mag_ = status.mag_ * 1.2f;
      temp.spd_ = status.spd_ * 1.2f;
      temp.dex_ = status.dex_ * 1.2f;
      temp.luk_ = status.luk_ * 1.2f;
  }

  return temp;
}


void chara::targetPos(const Vec2f& t) {
  target_ = t;
}


Vec2f chara::getPos() const {
  return pos_;
}


u_short chara::getLane() const {
  return lane_;
}


u_short chara::getType() const {
  return info.type_;
}


bool chara::getSide() const {
  return info.side_;
}


std::string chara::getName() const {
  return info.name_;
}


sstream chara::getLevel() const {
  sstream temp;
  temp << "LV:" << std::setw(2) << level_;
  return temp;
}


Color chara::hpColor() const {
  Color temp;

  temp = hpGaugeRatio() > 0.5f ? win::color(paint::Green)
    : hpGaugeRatio() > 0.25f ? win::color(paint::Yellow)
    : win::color(paint::Red);

  return temp;
}


float chara::hpGaugeRatio() const {
  return float(hp_) / hp_max_;
}


float chara::timeGaugeRatio() const {
  return float(turn_ < UNIT_TURN ? turn_ : UNIT_TURN) / UNIT_TURN;
}


// キャラクターメイキングの情報を反映
// TIPS: 作成した情報を反映させるときだけ使う
void chara::making(const sCharacterInfo& new_face) {
  info = new_face;
  initHpMax();
  initImage(new_face.type_);
  initParameter();
}


// クラスチェンジ
// TIPS: 兵士タイプに対応した画像に切り替える
void chara::classChange(const u_short& type0) {
  info.type_ = type0;
  initHpMax();
  initImage(type0);
  initParameter();
}


void chara::initHpMax() {
  sParameter temp = getStatus();
  hp_max_ = temp.vit_ * 2 + temp.pow_ + temp.spd_;
}


void chara::initImage(const short& type0) {
  switch (type0) {
    case Fighter: own_ = Texture("res/png/unit_fighter.png"); break;
    case   Scout: own_ = Texture("res/png/unit_scout.png");   break;
    case   Armor: own_ = Texture("res/png/unit_fighter.png"); break;
    case    Mage: own_ = Texture("res/png/unit_fighter.png"); break;
    case  Priest: own_ = Texture("res/png/unit_fighter.png"); break;
    case    Noob: own_ = Texture("res/png/unit_fighter.png"); break;
    case    Boss: own_ = Texture("res/png/unit_fighter.png"); break;

    default: own_ = Texture("res/png/unit_fighter.png");
  }
}


// TIPS: パラメータを初期化する
void chara::initParameter() {
  sParameter default_;
  status = default_;
}
