
#include "data_manager.h"


std::string data::file_;

std::vector<cCharacter>::iterator data::it;
cSystem data::system;
cUser   data::user;
Random  data::random;


// �Q�[���J�n���̕`��V�[���w��
// TIPS: ��{�I�Ƀf�o�b�O�p�B�����łł� Title �݂̂��w�肷��
void data::sceneInit(const state::SceneMode& scene0) {
  system.scene_[play::Last] = scene::None;
  system.scene_[play::Now]  = scene::None;
  system.scene_[play::Next] = scene0;
  system.isPause_ = false;
  system.poli_mode_ = mode::Neutral;
}


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

  std::fstream fstr(file_);
  if (fstr) {
    return true;
  }

  return false;
}


// �f�[�^�ǂݍ���
// TIPS: �ǂݍ��݂Ɏ��s������ false ��Ԃ�
bool data::loadUserData(const short& num) {

  // �t�@�C���p�X���擾�B���s�Ȃ珈���𒆒f
  if (!getFilePass(num)) { return false; }

  std::fstream fstr(file_);
  if (fstr) {
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
