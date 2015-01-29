
#include "character.h"

typedef cCharacter  chara;
using namespace character;


cCharacter::cCharacter() : lane_(Front) {
  // TEST: �C���X�^���X�������ɉ��̃f�[�^�ŏ��������s��
  init(Vec2f(0, 0));
}


/* �퓬�V�X�e���֌W */
////////////////////////////////////////////////////////////

// TIPS: �퓬�J�n���̃p�����[�^������
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
  // TIPS: �s���\�ɂȂ�܂ŁA
  // * ���g�̕␳���ꂽ�X�s�[�h�̕������J�E���g��i�߂�
  turn_ += getStatus().spd_;
  healing();
}


void chara::timeCountReset() {
  // TIPS: �s�������玩�g�̃^�C���Q�[�W�����炵�āA
  // * �A�j���̕`���Ԃ��U���A�N�V�����ɐ؂�ւ���
  turn_ -= UNIT_TURN;
  animeChange(action::Attack);
}


bool chara::isWait() const {
  // TIPS: �܂��s���ł��Ȃ��Ȃ� true ��Ԃ�
  return turn_ < UNIT_TURN;
}


bool chara::isAnimePlaying() {
  bool play_ = timer.motion_ > 0;

  // TIPS: �A�j���[�V�������I��������ҋ@��Ԃɖ߂�
  play_ ? --timer.motion_ :
    anime.state_[Next] = hpGaugeRatio() > 0.25f ?
    action::Stand : action::Danger;

  return play_;
}


bool chara::isDead() {
  // TIPS: �퓬�s�\�Ȃ�`���Ԃ�ύX���āA�ȍ~�̏������֎~����
  if (hp_ <= 0) { anime.state_[Next] = action::Dead; }
  return anime.state_[Now] == action::Dead;
}


bool chara::targetLook(const short& target_lane) {
  switch (info.type_) {
    case Scout: return target_lane == Back  ? true : false;
    default:    return target_lane == Front ? true : false;
  }
}


// TIPS: �U���́A�񕜗ʌv�Z�̂��߂̃p�����[�^���o��
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

  //TODO:�}�b�v�̓�����ʂōU���͂ɉe�����鏈����ǉ�

  return temp;
}


// TIPS: �␳�ς݂̍U���͂��󂯎���Čv�Z���s��
void chara::physicalDamage(const u_short& val) {
  //TODO:�}�b�v�̓�����ʂŖh��͂ɉe�����鏈����ǉ�

  short damage_point = val - getStatus().vit_ / 2;
  hp_ -= damage_point > 1 ? damage_point : 1;

  animeChange(action::Damage);
}


// TIPS: �␳�ς݂̍U���͂��󂯎���Čv�Z���s��
void chara::magicalDamage(const u_short& val) {
  //TODO:�}�b�v�̓�����ʂŖh��͂ɉe�����鏈����ǉ�

  short damage_point = val - getStatus().mag_ / 2;
  hp_ -= damage_point > 1 ? damage_point : 1;

  animeChange(action::Damage);
}


// TIPS: Priest �ɂ���
void chara::recovery(const u_short& val) {
  //TODO:�}�b�v�̓�����ʂŉ񕜗ʂɉe�����鏈����ǉ�

  hp_ += val;
  if (hp_ > hp_max_) { hp_ = hp_max_; }
}


Color chara::hpColor() const {
  Color temp;

  // TIPS: �c�� HP �̊����ɉ����ăJ���[��ύX
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
// TIPS: ���Ԍo�߂ɂ���
void chara::healing() {
  ++timer.heal_;
  if (hp_ < hp_max_ && timer.heal_ >= UNIT_TURN / 10 - status.vit_ * 2) {
    short val = status.vit_ / 10;
    hp_ = val < 10 ? 10 : val;
    timer.heal_ = 0;
  }
}


/* �p�����[�^����i�f�[�^�o�́j�֌W */
////////////////////////////////////////////////////////////

// TIPS: �␳�Ȃ��̃p�����[�^���o��
sParameter chara::getBaseStatus() const {
  return status;
}


// TIPS: �N���X���Ƃ̃p�����[�^�␳����������Ԃŏo��
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


/* �p�����[�^����i�f�[�^�o�́j�֌W */
////////////////////////////////////////////////////////////

// ����̐؂�ւ�
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
  // TIPS: ���łɏ���ɒB���Ă����珈�������Ȃ�
  if (info.level_ >= LEVEL_LIMIT) { info.exp_ = 0; return 0; }

  // TIPS: �o���l�� 100 �Ŋ������l�� 1 �ȏ�Ȃ烌�x���A�b�v
  short temp = info.exp_ / 100;
  info.exp_ %= 100;

  // TIPS: ����𒴂��ă��x���A�b�v���Ȃ��悤�ɂ���
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


// �p�����[�^�̏�����m�F����
// TIPS: �m�F�������p�����[�^���ƃ{�[�i�X�l�������Ƃ��ēn��
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


// �L�����N�^�[���C�L���O�̏��𔽉f
// TIPS: �쐬�������𔽉f������Ƃ������g��
void chara::making(const sCharacterInfo& new_face) {
  info = new_face;
  changeImage(new_face.type_);
  initHpMax();
  initParameter();
}


// �N���X�`�F���W
// TIPS: ���m�^�C�v�ɑΉ������摜�ɐ؂�ւ���
void chara::classChange(const u_short& type0) {
  info.type_ = type0;
  changeImage(type0);
  initHpMax();
  initParameter();
}


/* private */
// �N���X�`�F���W�ɂ��L�����N�^�[�摜�̐؂�ւ�
void chara::changeImage(const short& type0) {
  // TIPS: �����̃N���X�ɑΉ������摜���擾
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
// HP�ő�l�̏��������s��
void chara::initHpMax() {
  sParameter temp = getStatus();
  hp_max_ = temp.vit_ * 2 + temp.pow_ + temp.spd_;
}


/* private */
// �p�����[�^������������
void chara::initParameter() {
  // TIPS: �f�t�H���g�R���X�g���N�^�ŏ�������Ԃ�����Ă���̂ŁA
  //     : ���̃f�[�^���쐬���A���g�ɂ�������̂܂܏㏑������
  sParameter default_;
  status = default_;
}


void chara::animePlay() {
  ++anime.time_;
  if (anime.time_ >= design::Fps - 20) { anime.time_ = 0; }
  anime.blink_ = anime.time_ / (design::Fps / 6);
}


void chara::animeShift() {
  // TIPS: �_���[�W�A�j�����I�������璼�O�̕`��A�j������蒼��
  if (anime.state_[Now] == action::Damage && !timer.motion_) {
    anime.state_[Next] = anime.state_[Last];
    anime.state_[Last] = action::Stand;
  }

  // TIPS: ���̕`���Ԃ��w�肳�ꂽ��^�C�}�[�����Z�b�g���āA
  // * ���݂̏�Ԃɏ㏑�����ăA�j����؂�ւ���
  if (anime.state_[Now] != anime.state_[Next]) {
    anime.time_ = 0;
    anime.state_[Now] = anime.state_[Next];
  }
}


void chara::animeChange(const u_short& act) {
  // TIPS: �`�悷��A�j���[�V�����ɍ��킹���摜�ɐ؂�ւ���
  anime.state_[Next] = act;
  anime.state_[Last] = anime.state_[Now];
  timer.motion_ = design::Fps - 21;
}


void chara::draw(const float& camera_x) {
  // TIPS: �������G���𔻒肵�ăL�����N�^�[�̌�����ύX
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
