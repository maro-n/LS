
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
  short dif_;

  // �ǂݍ��ރ}�b�v�f�[�^�Ɗl���ςݔ���
  // TIPS: �V�K�Q�[���J�n�������̂݁A�����_���ɒl��ݒ�
  struct {
    bool flag_;
    u_short id_;
  } map_info[design::AllStage];

  // �e��J�E���g�f�[�^
  // TIPS: �G���f�B���O�̕]����ʂŎg���i�\��j
  struct {
    u_short clear_;     // �Q�[���̃N���A��
    u_short battle_;    // �퓬��
    u_short command_;   // �헪�R�}���h�����s������
  } count;

  // ����R�}���h���s�p�f�[�^
  u_int money_;   // ����

  // �퓬�R�}���h���s�p�f�[�^
  // TIPS: �|�[�Y��ʂŎg�p����
  struct {
    u_short fire_;
    u_short cannon_;
    u_short trap_;
    u_short poison_;
    bool spy_;
  } strategy;

  // �퓬�ς݂̃}�b�v�t���O
  bool wasInvasion[design::AllStage];

  // ���j�b�g���
  std::vector<cCharacter> player;   // �v���C���[
};
