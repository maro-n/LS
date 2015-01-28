
#pragma once
#include "win_manager.h"
#include "../System/system.h"
#include "../System/user.h"
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
  static std::vector<cCharacter>::iterator it;

  static cSystem system;
  static cUser   user;
  static Random  random;

  static void sceneInit(const state::SceneMode&);
  static void bugProof();

  static void slotCheck();
  static bool saveUserData(const short&);
  static bool loadUserData(const short&);

  static short getTerritory();
};

typedef cDataManager  data;
