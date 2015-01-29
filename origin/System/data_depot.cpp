
#include "data_depot.h"


std::string data::file_;

cSystem data::system;
cUser   data::user;
Random  data::random;

cMusicResource data::music;


// �f�[�^�̐������`�F�b�N
// TIPS: ���[�v�̍ŏ��Ɏ��s����
void data::bugProof() {

  // �N���A��
  // TIPS: �񐔂����������Ă��Ȃ�������
  {
    u_short& clear = user.count.clear_;
    clear = (clear < 100) ? clear : 100;
  }
}


// �Q�[���J�n���̕`��V�[���w��
// TIPS: ��{�I�Ƀf�o�b�O�p�B�����łł� Title �݂̂��w�肷��
void data::sceneInit(const state::SceneMode& scene0) {
  system.scene_[play::Last] = scene::None;
  system.scene_[play::Now]  = scene::None;
  system.scene_[play::Next] = scene0;
  system.poli_mode_ = mode::Neutral;
  system.phase_ = phase::Standby;
}


// �V�K�Q�[��
void data::newGame(const dif& difficulty) {
  user.dif_ = difficulty;

  // TIPS: �������g���ăX�e�[�W�̏�Ԃ�ݒ�
  short r = random.fromZeroToLast(design::AllStage);
  for (short i = 0; i < design::AllStage; ++i) {
    user.map_info[i].flag_ = (r == i) ? true : false;
    user.map_info[i].id_ = random.fromZeroToLast(3);
  }

  user.count.clear_ = 0;
  user.count.battle_ = 0;
  user.count.turn_ = 0;

  user.assets.money_ = 1000;
  user.assets.food_ = 10;

  user.strategy.poison_ = 0;
  user.strategy.fire_ = 0;
  user.strategy.cannon_ = 0;
  user.strategy.spy_ = true;
}


// �X���b�g�̃t�@�C���p�X���擾
// TIPS: �p�X�̎擾�ɐ��������� true ��Ԃ�
bool data::getFilePass(const short& num) {
  switch (num) {
    case 0: file_ = "res/data/system/user_data1.txt"; break;
    case 1: file_ = "res/data/system/user_data2.txt"; break;
    case 2: file_ = "res/data/system/user_data3.txt"; break;

    // CAUTION: �����̏����͕ύX���Ȃ�����
    // TIPS: �ُ�Ȓl���󂯎������A�����������I�ɏI��������
    default: return false;
  }

  return true;
}


// �X���b�g�̎g�p�󋵂��m�F
void data::slotCheck() {

  bool& slot1 = data::system.slot_state_[0];
  bool& slot2 = data::system.slot_state_[1];
  bool& slot3 = data::system.slot_state_[2];

  // TIPS: �X���b�g�����ׂāu���g�p�v�Ƃ��ď�����
  slot1 = slot2 = slot3 = false;

  std::ifstream load("res/data/system/slot_state.txt");
  if (load) { load >> slot1 >> slot2 >> slot3; }
}


// �f�[�^�ۑ�
// TIPS: �ۑ��ł��Ȃ������� false ��Ԃ�
bool data::saveUserData(const short& num) {

  // �t�@�C���p�X���擾�B���s�Ȃ珈���𒆒f
  if (!getFilePass(num)) { return false; }

  std::ofstream fstr(file_);
  if (fstr) {

    // TIPS: �Q�[���̓�Փx��ۑ�
    fstr << user.dif_;

    // TIPS: �}�b�v�f�[�^��ۑ�
    for (short i = 0; i < design::AllStage; ++i) {
      fstr << user.map_info[i].flag_ << user.map_info[i].id_;
    }

    // TIPS: �N���A�񐔂ȂǁA�V�X�e���Ɋւ��f�[�^�̕ۑ�
    fstr
      << user.count.clear_
      << user.count.battle_
      << user.count.turn_;

    // TIPS: �����ȂǁA�����ʂɊւ��f�[�^��ۑ�
    fstr << user.assets.money_ << user.assets.food_;

    // TIPS: ���R�}���h�̃f�[�^��ۑ�
    fstr
      << user.strategy.poison_
      << user.strategy.fire_
      << user.strategy.cannon_
      << user.strategy.spy_;

    // TIPS: �쐬�ς݂̃L�����N�^�[����ۑ�
    fstr << user.player.size();

    // TIPS: �L�����N�^�[�f�[�^��ۑ�
    std::vector<cCharacter>::iterator it;
    for (it = user.player.begin(); it != user.player.end(); ++it) {
      fstr
        << it->getInfo().side_
        << it->getInfo().name_
        << it->getInfo().type_
        << it->getInfo().gender_
        << it->getInfo().level_
        << it->getInfo().exp_

        << it->getBaseStatus().pow_
        << it->getBaseStatus().vit_
        << it->getBaseStatus().mag_
        << it->getBaseStatus().spd_
        << it->getBaseStatus().dex_
        << it->getBaseStatus().luk_;
    }

    return true;
  }

  return false;
}


// �f�[�^�ǂݍ���
// TIPS: �ǂݍ��݂Ɏ��s������ false ��Ԃ�
bool data::loadUserData(const short& num) {

  // �t�@�C���p�X���擾�B���s�Ȃ珈���𒆒f
  if (!getFilePass(num)) { return false; }

  std::ifstream fstr(file_);
  if (fstr) {

    // TIPS: �Q�[���̓�Փx���擾
    short temp;
    fstr >> temp;
    user.dif_ = dif(temp);

    // TIPS: �}�b�v�f�[�^���擾
    for (short i = 0; i < design::AllStage; ++i) {
      fstr >> user.map_info[i].flag_ >> user.map_info[i].id_;
    }

    // TIPS: �N���A�񐔂ȂǁA�V�X�e���Ɋւ��f�[�^�̎擾
    fstr
      >> user.count.clear_
      >> user.count.battle_
      >> user.count.turn_;

    // TIPS: �����ȂǁA�����ʂɊւ��f�[�^���擾
    fstr >> user.assets.money_ >> user.assets.food_;

    // TIPS: ���R�}���h�̃f�[�^���擾
    fstr
      >> user.strategy.poison_
      >> user.strategy.fire_
      >> user.strategy.cannon_
      >> user.strategy.spy_;

    // TIPS: �쐬�ς݂̃L�����N�^�[�����擾�A�z����m�ۂ���
    short num;
    fstr >> num;
    for (short i = 0; i < num; ++i) { user.player.emplace_back(); }

    // TIPS: �L�����N�^�[�f�[�^���擾
    std::vector<cCharacter>::iterator it, begin, end;
    begin = user.player.begin();
    end = user.player.end();
    for (it = begin; it != end; ++it) { it->fileLoad(fstr); }

    return true;
  }

  return false;
}


// �l���ςݗ̒n�̐����擾
short data::getTerritory() {
  short num = 0;

  for (short i = 0; i < design::AllStage; ++i) {
    if (user.map_info[i].flag_) { ++num; }
  }

  return num;
}
