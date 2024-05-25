#include "hsbs/app/M5StickCPlust2App.h"
#include "seamonsue/activity/DebugActivity.h"
#include "seamonsue/activity/clean/CleanActivity.h"
#include "seamonsue/activity/common/BackgroundActivity.h"
#include "seamonsue/activity/common/HappyActivity.h"
#include "seamonsue/activity/dead/DeadActivity.h"
#include "seamonsue/activity/food/FoodActivity.h"
#include "seamonsue/activity/game/GameActivity1.h"
#include "seamonsue/activity/home/HomeActivity.h"
#include "seamonsue/activity/info/InfoActivity1.h"
#include "seamonsue/activity/info/InfoActivity2.h"
#include "seamonsue/activity/menu/MenuCleanActivity.h"
#include "seamonsue/activity/menu/MenuFoodActivity.h"
#include "seamonsue/activity/menu/MenuGameActivity.h"
#include "seamonsue/activity/menu/MenuInfoActivity.h"
#include "seamonsue/activity/reset/ResetActivity.h"
#include "seamonsue/activity/title/TitleActivity.h"
#include "seamonsue/activity/clock/ClockActivity.h"
#include "seamonsue/activity/clock/ClockEditActivity.h"
#include "seamonsue/data/MonsData.h"
#include "seamonsue/global.h"
#include <Arduino.h>

hsbs::M5StickCPlust2App app;

void setup() {
  //---------------------------------------------------
  // セットアップ
  //---------------------------------------------------
  Serial.begin(115200);
  app.setup();

  // FPS を設定
  // オフスクリーンレンダリングのスプライトをスクリーンに焼く処理が 12ms
  // 加えてアプリの描画処理の負荷が 18ms 程度。
  // ゲームロジックは 1ms 程度。
  // 最大で 30fps くらいのパフォーマンスなので余裕をもって 24fps に設定
  app.setFps(24);

  // 30秒の操作なしで自動ディープスリープ
  app.setAutoSleepTime(30000);

  //---------------------------------------------------
  // アクティビティ（画面）を追加
  //---------------------------------------------------
  app.add("/", new seamonsue::BackgroundActivity()); // 背景とバッテリー

  app.add("/title", new seamonsue::TitleActivity()); // タイトル画面

  app.add("/home", new seamonsue::HomeActivity());            // ホーム画面
  app.add("/home/info", new seamonsue::MenuInfoActivity());   // 情報アイコンフォーカス時
  app.add("/home/food", new seamonsue::MenuFoodActivity());   // 食事アイコンフォーカス時
  app.add("/home/game", new seamonsue::MenuGameActivity());   // ゲームアイコンフォーカス時
  app.add("/home/clean", new seamonsue::MenuCleanActivity()); // 掃除アイコンフォーカス時
  
  app.add("/clock", new seamonsue::ClockActivity()); // 時計画面
  app.add("/clock/edit", new seamonsue::ClockEditActivity()); // 時計編集画面

  app.add("/info", new seamonsue::MenuInfoActivity());    // 情報アイコン
  app.add("/info/page1", new seamonsue::InfoActivity1()); // 年齢・食事
  app.add("/info/page2", new seamonsue::InfoActivity2()); // ゲーム・掃除

  app.add("/food", new seamonsue::MenuFoodActivity());    // 食事アイコン
  app.add("/food/page1", new seamonsue::FoodActivity());  // 食事
  app.add("/food/page2", new seamonsue::HappyActivity()); // 食事の喜ぶ演出

  app.add("/game", new seamonsue::MenuGameActivity());    // ゲームアイコン
  app.add("/game/page1", new seamonsue::GameActivity1()); // ミニゲーム
  app.add("/game/page2", new seamonsue::HappyActivity()); // ゲームの喜ぶ演出

  app.add("/clean", new seamonsue::MenuCleanActivity());   // 掃除アイコン
  app.add("/clean/page1", new seamonsue::CleanActivity()); // 掃除演出
  app.add("/clean/page2", new seamonsue::HappyActivity()); // 掃除の喜ぶ演出

  app.add("/dead", new seamonsue::DeadActivity()); // お墓

  app.add("/reset", new seamonsue::ResetActivity()); // リセット画面

  //---------------------------------------------------
  // イベントハンドリング
  //---------------------------------------------------
  // ディープスリープの直前のイベントでデータを保存
  app.registerEvent(hsbs::EVENT_BEFORE_SLEEP, []() {
    timeStore.save();
    gameStore.save();
    petStore.save();
  });

  // Aボタン長押しでミュート切り替え
  app.registerEvent(hsbs::EVENT_BUTTON_LONG_PRESS_A, []() {
    if (app.getPath().equals("/home/") || app.getPath().equals("/clock/")) {// ホーム画面
      gameStore.toggleMute();// トグルミュート
      soundUtil.muted = gameStore.getMuted();
      soundUtil.pressButton();
    }
  });

  // Bボタン長押しでリセット画面
  app.registerEvent(hsbs::EVENT_BUTTON_LONG_PRESS_B, []() {
    if (app.getPath().equals("/clock/edit/")) {// 時計編集画面
      return;
    }
    soundUtil.pressButton();
    app.go("/reset");
  });

  // フレーム更新時のメインロジック
  app.registerEvent(hsbs::EVENT_ENTER_FRAME, []() {
    soundUtil.update();
    globalTicker.update();
    if (app.getPath().indexOf("/home") == 0) {
      // ホーム画面の時に更新
      timeStore.update();
      petStore.updateEvolutionCount(timeStore.getTotalSec());
      if (timeStore.getElapsedSec() > 60) { // 60 秒ごとに消化する
        // パラメータを更新
        petStore.updatePetParams(timeStore.getElapsedSec());
        timeStore.resetElapsedSec();
        // しんでたらお墓画面へ
        if (petStore.isDead()) {
          gameStore.dead();
          app.go("/dead");
        }
      }
    }
  });

  //---------------------------------------------------
  // デバッグ機能
  //---------------------------------------------------
  // seamonsue::DebugActivity *debugActivity = new seamonsue::DebugActivity();
  // debugActivity->stage.visible = false;
  // app.add("/", debugActivity);
  // // Aボタン長押しでデバッグテキスト表示
  // app.registerEvent(hsbs::EVENT_BUTTON_LONG_PRESS_A, [debugActivity]() {
  //   debugActivity->stage.visible = !debugActivity->stage.visible;
  // });

  //---------------------------------------------------
  // データを復元とアプリの開始
  //---------------------------------------------------
  gameStore.restore();
  timeStore.restore();
  petStore.restore();
  petStore.updateEvolutionCount(timeStore.getTotalSec()); // 総時間から進化
  petStore.updatePetParams(timeStore.getElapsedSec());    // スリープ中の経過時間を消化
  timeStore.resetElapsedSec();
  if (gameStore.getGameState() == seamonsue::PLAY && petStore.isDead()) {
    gameStore.dead();
  }
  soundUtil.muted = gameStore.getMuted();// ミュートの状態を反映
  // 画面を切り替えてアプリを開始
  switch (gameStore.getGameState()) {
  case seamonsue::TITLE: app.go("/title"); break; // タイトル画面
  case seamonsue::PLAY: app.go(gameStore.getClockMode() ? "/clock" : "/home"); break;   // 育成画面
  case seamonsue::DEAD: app.go("/dead"); break;   // お墓画面
  }
}


/**
 * @brief デバッグ用のコマンド
 * 
 * @param str 
 */
void applyDebugCommand(String str) {
  int spaceIndex = str.indexOf(' ');
  String command = str.substring(0, spaceIndex);
  String value = str.substring(spaceIndex + 1);

  if (command.equals("add_age")) {
    // 総時間を追加（day）
    timeStore.appendAge(value.toFloat());
    return;
  }
  if (command.equals("add_elapsed")) {
    // 経過時間を追加（day）
    timeStore.appendElapsed(value.toFloat());
    return;
  }
  if (command.equals("add_time")) {
    // 総時間と経過時間を追加（day）
    timeStore.appendAge(value.toFloat());
    timeStore.appendElapsed(value.toFloat());
    return;
  }
  if (command.equals("path")) {
    // 画面遷移を強制実行
    app.go(value);
    return;
  }
  if (command.equals("exec_food")) {
    // 食事を強制実行
    petStore.execFood();
    return;
  }
  if (command.equals("exec_game")) {
    // ゲームを強制実行
    petStore.execGame();
    return;
  }
  if (command.equals("exec_clean")) {
    // 掃除を強制実行
    petStore.execClean();
    return;
  }
}

void loop() {
  app.update();
  // デバッグ用にシリアル経由でコマンドを受け付ける
  if (Serial.available()) {
    app.resetSleepTimestamp();
    applyDebugCommand(Serial.readString());
  }
}
