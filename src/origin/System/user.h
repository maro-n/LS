
#pragma once
#include "../common.h"
#include "../Object/character.h"
#include <vector>

//
// ���[�U�[�f�[�^
// TIPS: �O���ɕۑ�����f�[�^��
//     : �f�[�^�̊Ǘ��� cDataManager �N���X�ōs��
//

class cUser {
public:
  cUser() = default;

  // �Q�[���̓�Փx
  // TIPS: �V�K�Q�[���J�n�������̂ݒl��ݒ�
  design::Difficulty dif_;

  // �ǂݍ��ރ}�b�v�f�[�^�Ɗl���ςݔ���
  // TIPS: �V�K�Q�[���J�n�������̂݁A�����_���ɒl��ݒ�
  struct {
    bool flag_;
    u_short id_;
  } map_info[design::AllStage];

  // �e��J�E���g�f�[�^
  struct {
    u_short clear_;    // �Q�[���̃N���A��
    u_short battle_;   // �퓬��
    u_short turn_;     // ����R�}���h�����s������
  } count;

  // ����R�}���h���s�p�f�[�^
  struct {
    u_int money_;    // ����
    u_short food_;   // ����
  } assets;

  // �퓬�R�}���h���s�p�f�[�^
  struct {
    u_short poison_;
    u_short fire_;
    u_short cannon_;
    bool side_attack_;
    bool spy_;
  } strategy;

  std::vector<cCharacter> player;
  std::vector<cCharacter> enemy;
};
