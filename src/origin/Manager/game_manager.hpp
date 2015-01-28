
#pragma once
#include "win_manager.h"
#include "data_manager.h"
#include "scene_manager.h"
#include "../Resource/image.h"

//
// �Q�[���Ǘ��N���X
// TIPS:
// * ���̃N���X�̃R���X�g���N�^�͍Ō�Ɏ��s�����悤�Ȃ̂ŁA
// * �����������ꍇ�̓V�[�h�l�̐ݒ�ォ�A�X�V�����̓����ōs������
//

class cGameManager {
  cSceneManager scene_;

public:
  // TIPS: �N�����A�K�v�ȏ��������s��
  cGameManager() {
    // CAUTION:
    // * �V�[�h�l�������̃^�C�~���O���킩��Ȃ��Ȃ�̂ŁA
    // * ���̏ꏊ����ړ������Ȃ�����
    data::random.setSeed(u_int(time(nullptr)));

    // TIPS: �`��J�n����V�[�����w��
    data::sceneInit(scene::Title);

    //data::system.slotCheck();
    //win::app->bgColor(win::color(paint::Green, 0.5f));
  }

  // �Q�[�����s
  // CAUTION: ���̊֐��ȊO�� while ���[�v�����Ȃ�
  void run() {
    while (win::app->isOpen() && !scene_.exit()) {
      //scene_.init();
      scene_.update();
      scene_.draw();
    }
  }
};
