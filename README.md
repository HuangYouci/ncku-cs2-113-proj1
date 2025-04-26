# National Cheng Kung University, Computer Science II, 2025 Spring, Project 1

## 專案簡介

這是一個使用 C++ 和 Qt 框架開發的 2D RPG 遊戲，來自於經典的《寶可夢》（Pokémon）系列。本專案為國立成功大學 (NCKU) 113 學年度計算機概論二課程的 Project 1。遊戲包含基本的角色移動、場景切換、NPC 互動、道具系統以及回合制戰鬥系統。

## 開發環境

*   **語言:** C++11
*   **框架:** Qt (版本 Qt 5)
    *   **模組:** QtCore, QtGui, QtWidgets, QtMultimedia
*   **環境:** Qt Creator

## 遊戲特色

*   **多場景設計:** 包含標題畫面、實驗室、城鎮、草地區域、戰鬥畫面和遊戲結束畫面，並實現了場景之間的切換邏輯。
*   **玩家角色:**
    *   可在地圖上進行上、下、左、右移動。
    *   具有移動動畫（基於不同方向顯示不同 Sprite）。
    *   與環境物件進行碰撞檢測。
*   **地圖與實體:**
    *   **Barrier:** 不可通行的區域。
    *   **Ledge:** 只能單向（通常是向下）跳過的特殊地形。
    *   **Tallgrass:** 進入時有一定機率觸發隨機戰鬥。
    *   **NPC:** 可在地圖上存在，部分 NPC 可互動（如實驗室的大木博士）。
    *   **可互動物件:** 如城鎮中的箱子 (TownBox)，互動後可獲得隨機道具。
*   **UI 系統:**
    *   **對話框 (UIdialog):** 用於顯示 NPC 對話或系統提示訊息。
    *   **背包 (UIbag):** 按下 'B' 鍵可開啟，顯示玩家擁有的道具（寶可夢球、傷藥、補藥）和捕捉到的寶可夢列表及其狀態 (等級、HP、屬性)。
    *   **選擇介面 (UIchoose):** 用於初始寶可夢的選擇。
*   **戰鬥系統 (BattleScene):**
    *   **回合制:** 玩家與隨機生成的野生寶可夢進行戰鬥。
    *   **基本指令:** 攻擊、更換寶可夢、使用背包道具、逃跑。
    *   **技能與PP:** 寶可夢擁有技能，使用技能會消耗 PP 值。
    *   **傷害計算:** 考慮寶可夢的攻擊力、防禦力、技能威力、等級以及屬性相剋（實現了火/水/草三種屬性，相剋影響 20% 傷害）。
    *   **道具使用:** 可在戰鬥中使用傷藥回復 HP，補藥回復 PP。
    *   **捕捉機制:** 可使用寶可夢球嘗試捕捉野生寶可夢，成功率基於雙方 HP 計算。
    *   **勝負判定:** 當一方寶可夢 HP 歸零時判定勝負。
    *   **升級與進化:** 戰鬥勝利後，出戰寶可夢可獲得經驗並升級，達到特定等級會進化並學習新技能（目前實作了初代御三家的兩段進化）。
    *   **遊戲結束:** 若玩家所有寶可夢 HP 歸零，則進入遊戲結束畫面。
*   **資源管理 (ResourceManager):**
    *   集中管理遊戲狀態，如玩家道具數量、已獲得的寶可夢列表、遊戲進度標記 (如是否與博士對話、是否已領取初始寶可夢)。
    *   載入並提供全局資源，如像素字體。
*   **音效:** 使用 QtMultimedia 播放背景音樂或音效（如按鈕點擊、戰鬥相關音效）。
*   **資產:** 包含像素風格的寶可夢 Sprite（正反面）、玩家角色 Sprite、地圖元件、UI 圖像、圖標以及音效檔案。

## 專案結構

```
ncku-cs2-113-proj1-main/
│
├── ncku-cs2-113.pro            # Qt 專案檔
├── ncku-cs2-113_zh_TW.ts       # 翻譯檔 (目前為空)
│
├── resources/
│   ├── resources.qrc           # Qt 資源檔 (定義圖像、字體、聲音等)
│   ├── images/                 # 圖像資源
│   │   ├── battle/
│   │   ├── icon/
│   │   ├── other/
│   │   ├── player/
│   │   └── scene/
│   ├── fonts/                  # 字體資源 (unifont.ttf)
│   └── sounds/                 # 音效資源 (.wav)
│
└── src/                        # 原始碼目錄
    │
    ├── GameWindow.cpp          # 主遊戲視窗類別實作
    ├── GameWindow.h            # 主遊戲視窗類別標頭
    ├── main.cpp                # 程式進入點
    │
    ├── core/                   # 核心功能
    │   ├── ResourceManager.cpp
    │   ├── ResourceManager.h   # 管理遊戲資源和狀態
    │   ├── Scene.cpp
    │   └── Scene.h             # 所有場景的基底類別
    │
    ├── entities/               # 遊戲實體 (角色、物件)
    │   ├── Barrier.cpp/.h      # 障礙物
    │   ├── Ledge.cpp/.h        # 平台邊緣
    │   ├── NPC.cpp/.h          # 非玩家角色
    │   ├── Player.cpp/.h       # 玩家角色
    │   ├── Tallgrass.cpp/.h    # 高草叢
    │   └── TownBox.cpp/.h      # 城鎮中的箱子
    │
    ├── scenes/                 # 遊戲場景
    │   ├── BattleScene.cpp/.h  # 戰鬥場景
    │   ├── GameOver.cpp/.h     # 遊戲結束場景
    │   ├── GrasslandScene.cpp/.h # 草地場景
    │   ├── LaboratoryScene.cpp/.h# 實驗室場景
    │   ├── TitleScene.cpp/.h   # 標題畫面場景
    │   └── TownScene.cpp/.h    # 城鎮場景
    │
    ├── ui/                     # 使用者介面元素
    │   ├── UIbag.cpp/.h        # 背包介面
    │   ├── UIchoose.cpp/.h     # 選擇介面 (初始寶可夢)
    │   └── UIdialog.cpp/.h     # 對話框介面
    │
    └── util/                   # 工具類別
        ├── ClickableTextItem.cpp/.h # 可點擊的文字項目
```

## 建置與執行

### 前置需求

1.  **Qt SDK:** 需要安裝 Qt 開發環境 (建議使用 Qt 5.12 或更新版本，或 Qt 6)。可以從 [Qt 官方網站](https://www.qt.io/download) 下載開源版本。安裝時請確保選擇了對應您開發平台的 Desktop 組件 (例如 MinGW, MSVC for Windows, or GCC for Linux/macOS) 以及 Qt Multimedia 模組。
2.  **C++ 編譯器:** 通常會隨 Qt SDK 一併安裝 (如 MinGW, MSVC, GCC/Clang)。

### 建置步驟

1.  **開啟專案:** 使用 Qt Creator 開啟 `ncku-cs2-113.pro` 檔案。
2.  **設定建置套件 (Kit):** Qt Creator 通常會自動偵測已安裝的 Qt 版本和編譯器。如果沒有，請至「工具」->「選項」->「Kits」(或類似路徑) 設定或選擇一個有效的建置套件。
3.  **建置專案:**
    *   點擊 Qt Creator 左下角的「建置」按鈕 (錘子圖示)，或使用快捷鍵 (通常是 `Ctrl+B`)。
    *   或者，選擇「建置」菜單中的「建置專案 "ncku-cs2-113"」。
4.  **等待編譯完成:** Qt Creator 會在「編譯輸出」視窗顯示建置過程。

### 執行步驟

1.  **從 Qt Creator 執行:**
    *   建置成功後，點擊 Qt Creator 左下角的「執行」按鈕 (綠色箭頭圖示)，或使用快捷鍵 (通常是 `Ctrl+R`)。
2.  **直接執行可執行檔:**
    *   建置完成後，可執行檔通常會生成在專案目錄之外的一個建置目錄中 (例如 `build-ncku-cs2-113-proj1-main-Desktop_Qt_...`)。
    *   找到該目錄下的可執行檔並執行。

## 遊戲操作

*   **移動:** 方向鍵 (↑, ↓, ←, →)
*   **互動/確認:** A 鍵
*   **開啟/關閉背包:** B 鍵
*   **進入戰鬥:** P 鍵 (在草地情境中可用，測試用)
*   **重新開始:** Q 鍵 (於遊戲結束畫面可用)
