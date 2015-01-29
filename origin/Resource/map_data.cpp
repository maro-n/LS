
#include "map_data.h"

typedef cMapData  mapdata;


cMapData::cMapData() :
back_ground_(Texture("res/png/back_grass.png")) {
}


// �}�b�v���̏�����
// TIPS: �N�U���A�󂯎�����ԍ��ɑΉ������}�b�v����W�J
// TIPS: �f�[�^�̎擾�ɐ��������Ƃ��̂� true ��Ԃ�
bool mapdata::mapInit(const u_short& id) {
  std::string chip_pass;

  // TIPS: �ԍ��ɑΉ������t�@�C���p�X���擾
  // CAUTION: �ǉ���Ƃ̓R�s�y�̂݁Bcase �ȊO��ύX���Ȃ�����
  switch (data::user.map_info[id].id_) {
    case  0: chip_pass = "res/png/stage_grass.png";    break;
    case  1: chip_pass = "res/png/stage_forest.png";   break;
    case  2: chip_pass = "res/png/stage_mountain.png"; break;

    // TIPS: �ُ�Ȓl���󂯎�����珈���𒆒f
    default: return false;
  }

  // TIPS: �擾�����p�X�����ƂɃt�@�C����ǂݍ���
  map_ = Texture(chip_pass);

  return true;
}


// TIPS: �X�N���[���p�̃f�[�^�������Ƃ��ēn��
void mapdata::draw(const float& camera_x) {

  // TIPS: �w�i�`��
  {
    drawTextureBox(-size::WIDTH / 2, size::HEIGHT / 4, size::WIDTH, size::HEIGHT / 4,
      camera_x * 0.25f, 0, 512, 128,
      back_ground_, Color(1, 1, 1));

    drawTextureBox(-size::WIDTH / 2, 0, size::WIDTH, size::HEIGHT / 4,
      camera_x * 0.5f, 128, 512, 128,
      back_ground_, Color(1, 1, 1));
  }

  drawTextureBox(-size::WIDTH / 2, -size::HEIGHT / 2, size::WIDTH, size::HEIGHT,
    camera_x, 0, size::WIDTH, size::HEIGHT,
    map_, Color(1, 1, 1),
    0, Vec2f(1, 1), Vec2f(0, 0));
}
