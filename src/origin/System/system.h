
#pragma once
#include "../common.h"
#include <fstream>

//
// �V�X�e���f�[�^
// TIPS: �O���ɕۑ����Ȃ��f�[�^��
//     : �f�[�^�̊Ǘ��� cDataManager �N���X�ōs��
//

class cSystem {
public:
  cSystem() = default;

  // �Z�[�u�f�[�^�̏��
  // TIPS: �g�p��Ԃ݂̂��Ǘ�����f�[�^��ǂݍ���ŃQ�[���ɔ��f����
  bool slot_state_[3];

  // �|�[�Y��ʔ���
  bool isPause_;

  // �`��V�[���̏��
  // TIPS: �N�����̏������� cGameManager �N���X�ōs��
  // * �ȍ~�� scene_manager �N���X���ŊǗ�
  // * play::Now, Last, Next �Ŋe�i�K�̕`���Ԃ��Q�Ƃ���
  state::SceneMode scene_[3];

  // �����ʂ̃R�}���h�I�����
  state::PoliticsMode poli_mode_;

  // �X�e�[�W�Z���N�g�őI�������X�e�[�W��ID
  // TIPS: �}�b�v���ǂݍ��݂̏����Ŏg��
  u_short stage_id_;

  // �퓬�V�[���̏��
  // TIPS: �퓬�A���U���g�̊e�V�[�����ŏ�����؂�ւ���
  // *
  // * phase::Win, Lose �Ń��U���g�̏�����؂�ւ���
  state::BattlePhase phase_;
};