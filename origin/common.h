
#pragma once
#include "../lib/defines.hpp"
#include "../lib/appEnv.hpp"
#include "../lib/font.hpp"
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

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
    WIDTH  = 1024,
    HEIGHT = 768,

    Half_W = WIDTH / 2,
    Half_H = HEIGHT / 2,
  };

  // �Q�[�����̃E�B���h�E�T�C�Y
  enum Window {
    Bottom_W = WIDTH - 20,
    Bottom_H = 140,
    BottomPos_X = -WIDTH / 2 + 10,
    BottomPos_Y = -HEIGHT / 2 + 10,
  };

  // �摜�̐؂���T�C�Y
  enum Cut {
    Unit_W = 32,
    Unit_H = 32,

    World_W = 1024,
    World_H = 1024,

    Logo_W = 256,
    Logo_H = 48,

    Sea_W = 512,
    Sea_H = 512,

    Result_W = 512,
    Result_H = 512,
  };

  // �^�C�g����ʗp
  enum Title {
    LogoPos_Y = HEIGHT / 4,

    Mode_W = 400,
    Mode_H = 80,

    ModePos_Y = -HEIGHT / 8,
  };

  // �Z�[�u���[�h���
  enum DataSelect {
    SlotPos_X = -Half_W + 100,
    SlotPos_Y = HEIGHT / 6,
    Slot_H = 90,

    InfoPos_X = -110,
    InfoPos_Y = SlotPos_Y - Slot_H * 4,
    Info_W = 500,
    Info_H = Slot_H * 4 + 60,
  };

  // �|�[�Y��ʐ�p
  enum Pause {
    PausePos_Y = HEIGHT / 6,
    Attension_Y = HEIGHT / 8,
  };

  // ������ʗp
  enum Politics {
    Command_H = 60,
    CommandPos_X = -WIDTH / 2 + 10,
    CommandPos_Y = HEIGHT / 2 - Command_H - 10,
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

  // ���U���g��ʐ�p
  enum Result {
    Result_Y = HEIGHT / 2 - 150,
  };
}


// �V�X�e���Ŏg���ŗL�l
namespace design {

  // �d�l
  enum System {
    Fps = 60,           // �P�b = 60.frame

    BattleMember = 5,   // �o�������o�[�̏���i�G�������ʁj
    ExpScore = 10,      // �G��|�������̃X�R�A��{�l

    GameStart = 1,      // �Q�[���J�n���̐w�n�̐�
    AllStage  = 12,     // �w�n�̐��F���ׂĂ̐w�n���l������

    NameMaxSize = 5,    // ���O�̍ő啶����

    DefaultPos = 300,   // ������ʃR�}���h�{�^���̏����ʒu
  };

  // �Q�[����Փx
  // TIPS: �G�L�����̃p�����[�^�ɉe��
  enum Difficulty {
    EASY,
    NORMAL,
    HARD,
  };

  enum Weaponprice{
    Fire = 1000,
    Bomb = 2500,
    Trap = 800,
    Poison = 1500,
  };

  // �F�ݒ�
  // TIPS: �F�f�[�^���Ǘ����Ă���z��̗v�f���w�肷��Ƃ��Ɏg��
  enum ColorType {
    White,
    Gray,
    Black,
    Red,
    Pink,
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
    All_Mode,
  };

  // �����ʂ̃R�}���h�`����
  enum CommandState {
    MoveIn,
    Select,
    Blink,
    MoveOut,
    Wait,
  };
}


// �L�����N�^�[�֌W
namespace character {

  // �L�����N�^�[�̃N���X
  // TIPS: �g�p����摜�ɂ��Ή�
  enum Type {
    Fighter,
    Scout,
    Knight,
    Mage,
    Priest,

    Soldier,   // �Ŏ�
    Boss,      // �ŏI�X�e�[�W�̃{�X
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


// ���y�t�@�C���֌W
namespace music {

  // BGM
  enum Music {
    Title,
    Politics,
    DataSelect,
    Result_Win,
    Result_Lose,
    Battle1,
    Battle2,
    Battle3,
    Boss1,
    Boss2,

    All_BGM,
  };

  // SE
  enum SoundEffect {
    Click,
    Click_Menu,

    All_SE,
  };
}


// �L�����N�^�[�̃p�[�\�i���f�[�^
struct sCharacterInfo {
  sCharacterInfo() : level_(1), exp_(0) {}

  bool side_;
  std::string name_;
  u_short type_;
  u_short gender_;

  u_short level_;
  u_short exp_;
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
typedef design::ColorType         paint;
typedef design::Weaponprice       price;

typedef state::SceneMode          scene;
typedef state::SceneState         play;
typedef state::FadeState          fade;
typedef state::BattlePhase        phase;
typedef state::PoliticsMode       mode;
typedef state::CommandState       command;

typedef character::Type           type;
typedef character::DrawAction     action;
typedef character::Gender         gen;
typedef character::ParameterInfo  info;

typedef music::Music              bgm;
typedef music::SoundEffect        se;


//////////////////////////////////////////////////////////////////////
