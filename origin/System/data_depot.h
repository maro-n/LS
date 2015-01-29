
#pragma once
#include "draw_window.h"
#include "system.hpp"
#include "user.hpp"
#include "../Resource/music.hpp"
#include "../../lib/random.hpp"
#include <ctime>
#include <fstream>

//
// データ管理クラス
//

class cDataManager {
  cDataManager() = delete;

  static std::string file_;

  static bool getFilePass(const short&);

public:
  static cSystem system;
  static cUser   user;
  static Random  random;

  static cMusicResource music;

  static void bugProof();
  static void sceneInit(const state::SceneMode&);
  static void newGame(const dif&);

  static void slotCheck();
  static bool saveUserData(const short&);
  static bool loadUserData(const short&);

  static short getTerritory();
};

typedef cDataManager  data;
