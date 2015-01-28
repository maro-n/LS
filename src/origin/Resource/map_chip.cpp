
#include "map_chip.h"

typedef cMapData  mapdata;


cMapData::cMapData() {
}


// �}�b�v���̏�����
// TIPS: �N�U���A�󂯎�����ԍ��ɑΉ������}�b�v����W�J
// TIPS: �f�[�^�̎擾�ɐ��������Ƃ��̂� true ��Ԃ�
bool mapdata::mapInit(const u_short& id) {
  std::string chip_pass;

  // TIPS: �ԍ��ɑΉ������t�@�C���p�X���擾
  // CAUTION: �ǉ���Ƃ̓R�s�y�̂݁Bcase �ȊO��ύX���Ȃ�����
  switch (data::user.map_info[id].id_) {
    case  0: chip_pass = "res/png/map_01.png"; break;
      //TODO:�摜�p�X��ǉ�

    // TIPS: �ُ�Ȓl���󂯎�����珈���𒆒f
    default: return false;
  }

  // TIPS: �擾�����p�X�����ƂɃt�@�C����ǂݍ���
  map_ = Texture(chip_pass);

  return true;
}


//TODO:�؂���T�C�Y�𐳋K�̃f�[�^�ɒu������
void mapdata::draw(const float& camera_x) {
  drawTextureBox(-size::WIDTH / 2, -size::HEIGHT / 2, size::WIDTH, size::HEIGHT,
    camera_x, 0, 0, 0,
    map_, Color(1, 1, 1),
    0, Vec2f(1, 1), Vec2f(0, 0));
}
