
#include "stage.h"

//
// 本編（実装）
//

// コンストラクタ
Stage::Stage() :
font(Font("res/font/MeiryoConsolas.ttf")) {
  player.own = Texture("res/png/player.png");
  player.hp_max = 10;
  player.wait_time = 0;
  player.attack = 2;
  player.defend = 2;
  player.speed = 11;

  enemy.own = Texture("res/png/enemy.png");
  enemy.hp_max = 9;
  enemy.wait_time = 0;
  enemy.attack = 3;
  enemy.defend = 1;
  enemy.speed = 8;

  bg = Texture("res/png/bg.png");
  turn = true;

  std::string temp_str;

  for (int i = 0; i < 3; ++i) {
    switch (i) {
    case 0: temp_str = "こうげき"; break;
    case 1: temp_str = "ぼうぎょ"; break;
    case 2: temp_str = "かいふく"; break;
    default:;
    }

    button[i] = Button_(
      Vec2f(-WIDTH / 2 + 30, HEIGHT / 2 - 80 * (i + 1)),
      Color(1, 1, 1),
      temp_str);
  }

  font.size(40);
}

// 描画
void Stage::draw() {
  draw_bg();
  draw_player();
  draw_enemy();

  if (turn) { draw_button(); }
  draw_hp();
  //draw_turn_list();
}

// 背景表示
void Stage::draw_bg() {
  drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT,
    0, 0, 1024, 512,
    bg, Color(1, 1, 1));
}

// プレイヤー表示
void Stage::draw_player() {
  drawTextureBox(-WIDTH / 2, -HEIGHT / 2 + 64, 128, 128,
    0, 0, 128, 128,
    player.own, Color(1, 1, 1));
}

// 敵キャラ表示
void Stage::draw_enemy() {
  drawTextureBox(WIDTH / 2 - 128, -HEIGHT / 2 + 64, 128, 128,
    0, 0, 128, 128,
    enemy.own, Color(1, 1, 1));
}

// ボタン表示
void Stage::draw_button() {
  for (int i = 0; i < 3; ++i) {
    drawFillBox(button[i].pos.x(), button[i].pos.y(),
      250, 50, button[i].color);

    font.draw(button[i].str, button[i].pos, Color(0, 0, 0));
  }
}

// 順番の表示
void Stage::draw_turn_list() {
  temp = (player.wait_time > enemy.wait_time)
    ? player.own : enemy.own;

  drawTextureBox(WIDTH / 2 - 64, HEIGHT / 2 - 64, 128, 128,
    0, 0, 128, 128,
    temp, Color(1, 1, 1),
    0, Vec2f(0.5, 0.5), Vec2f(0, 0));
}

// ＨＰの表示
void Stage::draw_hp() {
  // プレイヤー
  num.init_value(player.hp);
  num.disp_value(-WIDTH / 2 + 100, -HEIGHT / 2 + 220);

  // 敵キャラ
  num.init_value(enemy.hp);
  num.disp_value(WIDTH / 2 - 50, -HEIGHT / 2 + 220);
}

// 更新
void Stage::update() {
  /*
  if (!turn) {
  player.count = (10000 - player.wait_time) / player.speed;
  enemy.count = (10000 - enemy.wait_time) / enemy.speed;

  count = (player.count > enemy.count) ? player.count : enemy.count;
  player.wait_time = count * player.speed;
  enemy.wait_time = count * enemy.speed;

  return;
  }
  */

  // プレイヤー
  if (turn) {
    for (int i = 0; i < 3; ++i) {
      button[i].color = Color(1, 1, 1);
      if (box_to_cursor(button[i].pos, Vec2f(250, 50))) {
        button[i].color = Color(1, 0, 0);

        if (win::app->isPushButton(Mouse::LEFT)) {
          turn = false;

          switch (i) {
          case 0:    // こうげき
            enemy.hp += enemy.defend - player.attack;
            break;

          case 1:    // ぼうぎょ（アルファ：何もしない）
            break;

          default:   // かいふく
            player.hp += 2;
          }
        }
      }
    }
  }

  // 敵キャラ
  if (!turn) {
    player.hp += player.defend - enemy.attack;
    turn = true;
  }
}

// リセット
void Stage::reset() {
  player.hp = player.hp_max;
  enemy.hp = enemy.hp_max;
}

// ゲーム終了判定
bool Stage::game_set(int& mode, int& stage) {
  if (!player.hp) { mode = 0; return true; }
  if (!enemy.hp) { mode = 1; stage++; return true; }

  return false;
}
