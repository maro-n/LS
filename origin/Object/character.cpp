
#include "character.h"

typedef cCharacter  chara;
using namespace character;


cCharacter::cCharacter() : lane_(Front) {
  // TEST: インスタンス生成時に仮のデータで初期化を行う
  init(Vec2f(0, 0));
}


/* 戦闘システム関係 */
////////////////////////////////////////////////////////////

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


void chara::timeCount() {
  // TIPS: 行動可能になるまで、
  // * 自身の補正されたスピードの分だけカウントを進める
  turn_ += getStatus().spd_;
  healing();
}


void chara::timeCountReset() {
  // TIPS: 行動したら自身のタイムゲージを減らして、
  // * アニメの描画状態を攻撃アクションに切り替える
  turn_ -= UNIT_TURN;
  animeChange(action::Attack);
}


bool chara::isWait() const {
  // TIPS: まだ行動できないなら true を返す
  return turn_ < UNIT_TURN;
}


bool chara::isAnimePlaying() {
  bool play_ = timer.motion_ > 0;

  // TIPS: アニメーションが終了したら待機状態に戻す
  play_ ? --timer.motion_ :
    anime.state_[Next] = hpGaugeRatio() > 0.25f ?
    action::Stand : action::Danger;

  return play_;
}


bool chara::isDead() {
  // TIPS: 戦闘不能なら描画状態を変更して、以降の処理を禁止する
  if (hp_ <= 0) { anime.state_[Next] = action::Dead; }
  return anime.state_[Now] == action::Dead;
}


bool chara::targetLook(const short& target_lane) {
  switch (info.type_) {
    case Scout: return target_lane == Back  ? true : false;
    default:    return target_lane == Front ? true : false;
  }
}


// TIPS: 攻撃力、回復量計算のためのパラメータを出力
u_short chara::getPower() {
  u_short temp;

  switch (info.type_) {
    case Fighter: temp = getStatus().pow_; break;
    case   Scout: temp = getStatus().pow_; break;
    case  Knight: temp = getStatus().pow_; break;
    case    Mage: temp = getStatus().mag_; break;
    case  Priest: temp = getStatus().mag_; break;
    case Soldier: temp = getStatus().pow_; break;
    case    Boss: temp = getStatus().pow_; break;
    default: temp = 0;
  }

  //TODO:マップの特殊効果で攻撃力に影響する処理を追加

  return temp;
}


// TIPS: 補正済みの攻撃力を受け取って計算を行う
void chara::physicalDamage(const u_short& val) {
  //TODO:マップの特殊効果で防御力に影響する処理を追加

  short damage_point = val - getStatus().vit_ / 2;
  hp_ -= damage_point > 1 ? damage_point : 1;

  animeChange(action::Damage);
}


// TIPS: 補正済みの攻撃力を受け取って計算を行う
void chara::magicalDamage(const u_short& val) {
  //TODO:マップの特殊効果で防御力に影響する処理を追加

  short damage_point = val - getStatus().mag_ / 2;
  hp_ -= damage_point > 1 ? damage_point : 1;

  animeChange(action::Damage);
}


// TIPS: Priest による回復
void chara::recovery(const u_short& val) {
  //TODO:マップの特殊効果で回復量に影響する処理を追加

  hp_ += val;
  if (hp_ > hp_max_) { hp_ = hp_max_; }
}


Color chara::hpColor() const {
  Color temp;

  // TIPS: 残り HP の割合に応じてカラーを変更
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


/* private */
// TIPS: 時間経過による回復
void chara::healing() {
  ++timer.heal_;
  if (hp_ < hp_max_ && timer.heal_ >= UNIT_TURN / 10 - status.vit_ * 2) {
    short val = status.vit_ / 10;
    hp_ = val < 10 ? 10 : val;
    timer.heal_ = 0;
  }
}


/* パラメータ操作（データ出力）関係 */
////////////////////////////////////////////////////////////

// TIPS: 補正なしのパラメータを出力
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

    case Knight:
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

    case Soldier:
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


u_short chara::hitRatio() const {
  sParameter temp = getStatus();
  return temp.dex_ + (temp.spd_ + temp.luk_) / 10;
}


u_short chara::avoidRatio() const {
  sParameter temp = getStatus();
  return (temp.spd_ + temp.luk_) / 10;
}


std::string chara::getName() const {
  return info.name_;
}


u_short chara::getLevel() const {
  return info.level_;
}


sstream chara::getLevelString() const {
  sstream temp;
  temp << "LV:" << std::setw(2) << info.level_;
  return temp;
}


u_short chara::getHP() const {
  return hp_;
}


u_short chara::getHPMAX() const {
  return hp_max_;
}


/* パラメータ操作（データ出力）関係 */
////////////////////////////////////////////////////////////

// 隊列の切り替え
void chara::laneShift() {
  lane_ = (lane_ == Front) ? Back : Front;
}


void chara::aliasTargetPos(const Vec2f& t) {
  target_ = t;
}


void chara::expCount(const u_short& point) {
  info.exp_ += point;
}


short chara::levelUp() {
  // TIPS: すでに上限に達していたら処理をしない
  if (info.level_ >= LEVEL_LIMIT) { info.exp_ = 0; return 0; }

  // TIPS: 経験値を 100 で割った値が 1 以上ならレベルアップ
  short temp = info.exp_ / 100;
  info.exp_ %= 100;

  // TIPS: 上限を超えてレベルアップしないようにする
  short level_limit = LEVEL_LIMIT - info.level_;
  if (temp > level_limit) { temp = level_limit; }
  info.level_ += temp;

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


// キャラクターメイキングの情報を反映
// TIPS: 作成した情報を反映させるときだけ使う
void chara::making(const sCharacterInfo& new_face) {
  info = new_face;
  changeImage(new_face.type_);
  initHpMax();
  initParameter();
}


// クラスチェンジ
// TIPS: 兵士タイプに対応した画像に切り替える
void chara::classChange(const u_short& type0) {
  info.type_ = type0;
  changeImage(type0);
  initHpMax();
  initParameter();
}


/* private */
// クラスチェンジによるキャラクター画像の切り替え
void chara::changeImage(const short& type0) {
  // TIPS: 自分のクラスに対応した画像を取得
  switch (type0) {
    case Fighter: own_ = Texture("res/png/unit_fighter.png"); break;
    case   Scout: own_ = Texture("res/png/unit_scout.png");   break;
    case  Knight: own_ = Texture("res/png/unit_knight.png");  break;
    case    Mage: own_ = Texture("res/png/unit_mage.png");    break;
    case  Priest: own_ = Texture("res/png/unit_priest.png");  break;
    case Soldier: own_ = Texture("res/png/unit_soldier.png"); break;
    case    Boss: own_ = Texture("res/png/unit_boss.png");    break;

    default: own_ = Texture("res/png/unit_soldier.png");
  }
}


/* private */
// HP最大値の初期化を行う
void chara::initHpMax() {
  sParameter temp = getStatus();
  hp_max_ = temp.vit_ * 2 + temp.pow_ + temp.spd_;
}


/* private */
// パラメータを初期化する
void chara::initParameter() {
  // TIPS: デフォルトコンストラクタで初期化状態を作っているので、
  //     : 仮のデータを作成し、自身にそれをそのまま上書きする
  sParameter default_;
  status = default_;
}


void chara::animePlay() {
  ++anime.time_;
  if (anime.time_ >= design::Fps - 20) { anime.time_ = 0; }
  anime.blink_ = anime.time_ / (design::Fps / 6);
}


void chara::animeShift() {
  // TIPS: ダメージアニメが終了したら直前の描画アニメをやり直す
  if (anime.state_[Now] == action::Damage && !timer.motion_) {
    anime.state_[Next] = anime.state_[Last];
    anime.state_[Last] = action::Stand;
  }

  // TIPS: 次の描画状態を指定されたらタイマーをリセットして、
  // * 現在の状態に上書きしてアニメを切り替える
  if (anime.state_[Now] != anime.state_[Next]) {
    anime.time_ = 0;
    anime.state_[Now] = anime.state_[Next];
  }
}


void chara::animeChange(const u_short& act) {
  // TIPS: 描画するアニメーションに合わせた画像に切り替える
  anime.state_[Next] = act;
  anime.state_[Last] = anime.state_[Now];
  timer.motion_ = design::Fps - 21;
}


void chara::draw(const float& camera_x) {
  // TIPS: 味方か敵かを判定してキャラクターの向きを変更
  cut_.x() = info.side_
    ? (anime.blink_ + 1) * size::Unit_W + info.gender_ * (size::Unit_W * 4)
    : anime.blink_ * size::Unit_W + info.gender_ * (size::Unit_W * 4);

  cut_.y() = anime.state_[Now] * size::Unit_H;

  drawTextureBox(pos_.x() + camera_x, pos_.y(), size::Unit_W, size::Unit_H,
    cut_.x(), cut_.y(), info.side_ ? -size::Unit_W : size::Unit_W, size::Unit_H,
    own_, Color(1, 1, 1),
    0, Vec2f(3.f, 3.f), Vec2f(size::Unit_W / 2, 0));
}


void chara::fileLoad(std::ifstream& fstr) {
  fstr
    >> info.side_
    >> info.name_
    >> info.type_
    >> info.gender_
    >> info.level_
    >> info.exp_

    >> status.pow_
    >> status.vit_
    >> status.mag_
    >> status.spd_
    >> status.dex_
    >> status.luk_;
}


sCharacterInfo chara::getInfo() const {
  return info;
}
