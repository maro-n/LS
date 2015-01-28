
#pragma once
#include "../lib/defines.hpp"
#include "../lib/appEnv.hpp"
#include "../lib/font.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

//
// �V�X�e������
//

/* �}�N���A�萔 */
//////////////////////////////////////////////////////////////////////

#define FONT_   "res/font/arare.ttf"


// �摜�ȂǁA�T�C�Y�Ɋւ�����
namespace size {

  // �A�v���̃E�B���h�E�T�C�Y
  enum GameWindow {
    WIDTH = 1024,
    HEIGHT = 766,
  };

  // �Q�[�����̃E�B���h�E�T�C�Y
  enum Window {
    Message_W = WIDTH,
    Message_H = 128,
  };

  // �摜�̐؂���T�C�Y
  enum Cut {
    Chip_W = 32,
    Chip_H = 32,

    Unit_W = 32,
    Unit_H = 32,
  };

  // ��ʏ�̕\���T�C�Y
  enum Disp {
  };

  // �퓬��ʐ�p
  enum Battle {
    UnitInfo_W = WIDTH / 5,
    UnitInfo_H = 128,

    Gauge_W = 164,
    Gauge_H = 18,
    GaugePos_X = 20,
    GaugePos_Y = 20,

    NamePos_X = 20,
    NamePos_Y = 90,
  };
}


// �V�X�e���Ŏg���ŗL�l
namespace design {

  // �d�l
  enum System {
    Fps = 60,           // �P�b = 60.frame

    BattleMember = 5,   // �o�������o�[�̏���i�G�������ʁj
    BonusPoint = 10,    // ���x���A�b�v�������̃{�[�i�X�l

    GameStart = 1,      // �Q�[���J�n���̐w�n�̐�
    AllStage  = 12,     // �w�n�̐��F���ׂĂ̐w�n���l������

    NameMaxSize = 5,    // ���O�̍ő啶����
  };

  // �Q�[����Փx
  // TIPS: �G�L�����̃p�����[�^�ɉe��
  enum Difficulty {
    EASY,
    NORMAL,
    HARD,
  };

  // �{�^���̑I�����
  enum CommandState {
    Out,
    OnMouse,
    Clicked,
  };

  // �F�ݒ�
  // TIPS: �F�f�[�^���Ǘ����Ă���z��̗v�f���w�肷��Ƃ��Ɏg��
  enum ColorType {
    White,
    Gray,
    Black,
    Red,
    Purple,
    Blue,
    SkyBlue,
    Green,
    Yellow,
    Orange,
    Brown,

    // TIPS: �z��p�f�[�^
    // * �ォ��F��ǉ����Ă��A������w�肵�Ă���Ώ���ɔz��̃T�C�Y���ς��
    ColorVariation,
    // DANGER: ���̉��ɂ͐F�f�[�^�����Ȃ�����
  };
}


// �e�V�[���̏������
namespace state {

  // �`�悷��V�[��
  enum SceneMode {
    None,
    Exit,       // �Q�[���I��
    Save,
    Load,

    Title,
    Politics,   // �Ґ��A������
    Battle,
    Result,
  };

  // �e�i�K�̕`����
  enum SceneState {
    Now,    // ���݂̕`��V�[��
    Last,   // ���O�̕`��V�[��
    Next,   // ���̕`��V�[���̏���
  };

  // �t�F�[�h�C���A�t�F�[�h�A�E�g�̏��
  enum FadeState {
    FadeOut,
    FadeIn,
    Stop,
  };

  // �퓬��ʂ̏��
  enum BattlePhase {
    Standby,
    Fight,
    Win,
    Lose,
  };

  // �����ʂ̑I���R�}���h
  enum PoliticsMode {
    Funds,
    Armaments,
    Strategy,
    Invasion,
    DataSelect,

    Neutral,   // �����I�����Ă��Ȃ����
  };
}


// �L�����N�^�[�֌W
namespace character {

  // �L�����N�^�[�̃N���X
  // TIPS: �g�p����摜�ɂ��Ή�
  enum Type {
    Fighter,
    Scout,
    Armor,
    Mage,
    Priest,

    Noob,   // �Ŏ�
    Boss,   // �ŏI�X�e�[�W�̃{�X
  };

  // �`�悷��s��
  enum DrawAction {
    Stand,
    Damage,
    Danger,
    Move,
    Avoid,
    Dead,
    Attack,
  };

  // �s���̏��
  enum ActionState {
    Now,
    Next,   // ���̃A�j���̏��
    Last,   // �_���[�W���󂯂钼�O�̏��
  };

  // �L�����N�^�[�̐���
  // TIPS: �摜�؂���ʒu��ύX���邽�߂����Ɏg��
  enum Gender {
    Male,
    Female,
  };

  // �L�����N�^�[�̑���
  // TIPS: �`�悷����W�̌v�Z�ɂ��g��
  enum Lane {
    Front,
    Back,
  };

  // �L�����N�^�[�̃p�����[�^���
  enum ParameterLimit {
    UNIT_TURN = 10000,
    LEVEL_LIMIT = 99,
    HP_LIMIT = 9999,
    PARAM_LIMIT = 255,
  };

  // �p�����[�^�̏���m�F�p�̏��
  enum ParameterInfo {
    Pow,
    Vit,
    Mag,
    Spd,
    Dex,
    Luk,
  };
}


// �L�����N�^�[�̃p�[�\�i���f�[�^
struct sCharacterInfo {
  bool side_;
  std::string name_;
  u_short type_;
  u_short gender_;
};


// �L�����N�^�[�̃p�����[�^
struct sParameter {
  sParameter() :
    pow_(10), vit_(10), mag_(10), spd_(10), dex_(10), luk_(10) {}

  sParameter(short n) :
    pow_(n), vit_(n), mag_(n), spd_(n), dex_(n), luk_(n) {}

  u_short pow_;    // power: �����U���͂ɉe��
  u_short vit_;    // vitality: �����h��́A���R�񕜑��x�ɉe��
  u_short mag_;    // magica: ���@�̈З́A�h��͂ɉe��
  u_short spd_;    // speed: �s�����x�A����ɉe��
  u_short dex_;    // dexterity: �����A��S���ɉe��
  u_short luk_;    // luck: �����A����A��S���ɉe��
};


/* ��` */
//////////////////////////////////////////////////////////////////////

typedef unsigned short            u_short;
typedef std::stringstream         sstream;

typedef design::Difficulty        dif;
typedef design::CommandState      button;
typedef design::ColorType         paint;

typedef state::SceneMode          scene;
typedef state::SceneState         play;
typedef state::FadeState          fade;
typedef state::BattlePhase        phase;
typedef state::PoliticsMode       mode;

typedef character::Type           type;
typedef character::DrawAction     action;
typedef character::Gender         gen;
typedef character::ParameterInfo  info;


//////////////////////////////////////////////////////////////////////
