
#pragma once
#include "System/game_manager.h"


int main() {
  win::create();
  GameManager game;
  game.play();
}


// アルファ提出： 12 / 13
/* アルファ版・実装予定リスト

・本編の一部（戦闘パートのみ）
　・プレイヤー、敵　各１
　・順番に行動
　・マウスでコマンド選択：コマンドは３種類程度

・ポーズ画面とリザルト画面
　・ポーズ画面：ゲーム続行、終了
　・リザルト画面：ゲームオーバーに関わらず、リトライ、終了

・
・
・

*/
