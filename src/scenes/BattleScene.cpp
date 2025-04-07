#include "BattleScene.h"

#include <QGraphicsTextItem>
#include <QRandomGenerator>

BattleScene::BattleScene(QObject *parent, ResourceManager *resourceManager) : Scene(parent, resourceManager)
{
    qDebug() << "[BatleScene] 對戰場景已構建";
    setupScene();
}

void BattleScene::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
    default:
        qDebug() << "[BattleScene] 已按鍵" << event->key();
        break;
    }
}

void BattleScene::setupScene() {
    // 建立戰鬥背景
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(QPixmap(":/images/battle/battle_scene.png").scaled(525, 450, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    addItem(bgItem);
    qDebug() << "[BattleScene] 背景圖片已載入";

    // 建立敵我寶可夢
    myPokemon = new QGraphicsPixmapItem();
    enemyPokemon = new QGraphicsPixmapItem();
    myPokemon->setPos(76, 186);
    enemyPokemon->setPos(326, 51);
    addItem(myPokemon);
    addItem(enemyPokemon);

    myPokemonName = new QGraphicsTextItem();
    enemyPokemonName = new QGraphicsTextItem();
    myPokemonName->setPos(310, 225);
    enemyPokemonName->setPos(45, 55);
    myPokemonName->setFont(resourceManager->getFont(25));
    enemyPokemonName->setFont(resourceManager->getFont(25));
    myPokemonName->setDefaultTextColor(QColor(Qt::black));
    enemyPokemonName->setDefaultTextColor(QColor(Qt::black));
    addItem(myPokemonName);
    addItem(enemyPokemonName);

    myPokemonStat = new QGraphicsTextItem();;
    enemyPokemonStat = new QGraphicsTextItem();
    myPokemonStat->setPos(310, 276);
    enemyPokemonStat->setPos(40, 88);
    myPokemonStat->setFont(resourceManager->getFont(15));
    enemyPokemonStat->setFont(resourceManager->getFont(15));
    myPokemonStat->setDefaultTextColor(QColor(Qt::black));
    enemyPokemonStat->setDefaultTextColor(QColor(Qt::black));
    addItem(myPokemonStat);
    addItem(enemyPokemonStat);

    myPokemonHealthBar0 = new QGraphicsRectItem(380,256,110,18);
    myPokemonHealthBar0->setBrush(QBrush(Qt::white));
    myPokemonHealthBar0->setPen(Qt::NoPen);
    myPokemonHealthBar1 = new QGraphicsRectItem(380,256,110,18);
    myPokemonHealthBar1->setBrush(QBrush(Qt::red));
    myPokemonHealthBar1->setPen(Qt::NoPen);
    enemyPokemonHealthBar0 = new QGraphicsRectItem(112,90,110,18);
    enemyPokemonHealthBar0->setBrush(QBrush(Qt::white));
    enemyPokemonHealthBar0->setPen(Qt::NoPen);
    enemyPokemonHealthBar1 = new QGraphicsRectItem(112,90,110,18);
    enemyPokemonHealthBar1->setBrush(QBrush(Qt::red));
    enemyPokemonHealthBar1->setPen(Qt::NoPen);
    addItem(myPokemonHealthBar0);
    addItem(myPokemonHealthBar1);
    addItem(enemyPokemonHealthBar0);
    addItem(enemyPokemonHealthBar1);

    // 建立選單
    textDescription = new QGraphicsTextItem();
    textDescription->setPlainText(QString("等待系統更新"));
    textDescription->setPos(20, 340);
    textDescription->setFont(resourceManager->getFont(25));
    textDescription->setDefaultTextColor(QColor(Qt::white));
    addItem(textDescription);
    qDebug() << "[TitleScene] 主選單文字已建立";

    // Option
    optionA = new ClickableTextItem("");
    optionA->setPlainText("無動作");
    optionA->setPos(290, 340);
    optionA->setFont(resourceManager->getFont(25));
    optionA->setDefaultTextColor(QColor(Qt::black));
    addItem(optionA);
    optionA->hide();
    qDebug() << "[TitleScene] 主選單文字已建立（選項1）";

    optionB = new ClickableTextItem("");
    optionB->setPlainText("無動作");
    optionB->setPos(290, 390);
    optionB->setFont(resourceManager->getFont(25));
    optionB->setDefaultTextColor(QColor(Qt::black));
    addItem(optionB);
    optionB->hide();
    qDebug() << "[TitleScene] 主選單文字已建立（選項2）";

    optionC = new ClickableTextItem("");;
    optionC->setPlainText("無動作");
    optionC->setPos(400, 340);
    optionC->setFont(resourceManager->getFont(25));
    optionC->setDefaultTextColor(QColor(Qt::black));
    addItem(optionC);
    optionC->hide();
    qDebug() << "[TitleScene] 主選單文字已建立（選項3）";

    optionD = new ClickableTextItem("");
    optionD->setPlainText("無動作");
    optionD->setPos(400, 390);
    optionD->setFont(resourceManager->getFont(25));
    optionD->setDefaultTextColor(QColor(Qt::black));
    addItem(optionD);
    optionD->hide();
    qDebug() << "[TitleScene] 主選單文字已建立（選項4）";

    // 設定音效
    sound = new QSoundEffect(this);
}

void BattleScene::start(){

    // 開始音效
    sound->setSource(QUrl::fromLocalFile(":/sounds/startBattle.wav"));
    sound->play();

    // 生成隨機敵人
    enemy = generateRandomEnemy();

    // 寶可夢（開發測試）
//    Pokemon tempPokemon;
//    PokemonAttack tempAttack;
//    tempPokemon.name = "傑尼龜";
//    tempPokemon.image = QPixmap(":/images/battle/bulbasaur.png");
//    tempPokemon.imageback = QPixmap(":/images/battle/bulbasaur.png");
//    tempPokemon.level = 1;
//    tempPokemon.attack = 5000;
//    tempPokemon.defense = 5;
//    tempPokemon.maxhp = 30;
//    tempPokemon.hp = 30;
//    tempPokemon.pp = 20;
//    tempAttack.name = "戳戳";
//    tempAttack.power = 10;
//    tempPokemon.attacks.append(tempAttack);
//    resourceManager->pokemons.append(tempPokemon);

    // check if there is pokemon can battle
    if (resourceManager->pokemons.isEmpty()) {
        // 沒有寶可夢可以對戰
        textDescription->setPlainText("你沒有寶可夢可以對戰\n去博士實驗室領取一個");
        optionA->hide();
        optionB->hide();
        optionC->hide();
        optionD->show();
        optionD->setPlainText("逃跑");
        optionD->onClick = [=]() {
            sound->setSource(QUrl::fromLocalFile(":/sounds/battleEscape.wav"));
            sound->play();
            qDebug() << "[BattleScene] 點選逃跑";
            switchScene(3);
        };
        return;
    } else {
        // 有寶可夢可以對戰
        myPokemonIndex = 0;
        updateBattleStatus();
        textDescription->setPlainText(QString("戰鬥準備開始!\n\n對手：%2").arg(enemy.name));
        optionA->show();
        optionA->setPlainText("開始");
        optionA->onClick = [=]() {
            sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
            sound->play();
            qDebug() << "[BattleScene] 點選「開始」";
            choosePokemonToStart();
        };
        optionB->hide();
        optionC->hide();
        optionD->show();
        optionD->setPlainText("逃跑");
        optionD->onClick = [=]() {
            sound->setSource(QUrl::fromLocalFile(":/sounds/battleEscape.wav"));
            sound->play();
            qDebug() << "[BattleScene] 點選「逃跑」";
            switchScene(3);
        };
    }
}

void BattleScene::choosePokemonToStart(int current){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    textDescription->setPlainText(QString("請選擇要上場的寶可夢\n目前有 %1 隻寶可夢\n頁 %2/%1").arg(resourceManager->pokemons.size()).arg(current+1));

    if(resourceManager->pokemons.size() > 0){

        optionA->show();
        optionA->setPlainText(QString("[%1]%2[HP:%3]").arg(resourceManager->pokemons[current].level).arg(resourceManager->pokemons[current].name).arg(resourceManager->pokemons[current].hp));
        optionA->onClick = [=]() {
            if (resourceManager->pokemons[current].hp > 0){
                sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
                sound->play();
                qDebug() << "[BattleScene] 上場寶可夢" << resourceManager->pokemons[current].name;
                myPokemonIndex = current;
                updateBattleStatus();
                myround();
            } else {
                qDebug() << "[BattleScene] 寶可夢無法上場 無血量" << resourceManager->pokemons[current].name;
                textDescription->setPlainText(QString("無法選擇 %1\n因為該寶可夢已昏厥\n無血量無法選中").arg(resourceManager->pokemons[current].name));
                optionA->hide();
                optionB->show();
                optionB->setPlainText("重選");
                optionB->onClick = [=]() {
                    sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
                    sound->play();
                    qDebug() << "[BattleScene] 點選「重選」";
                    choosePokemonToStart();
                };
                optionD->show();
                optionD->setPlainText("逃跑");
                optionD->onClick = [=]() {
                    sound->setSource(QUrl::fromLocalFile(":/sounds/battleEscape.wav"));
                    sound->play();
                    qDebug() << "[BattleScene] 點選「逃跑」";
                    switchScene(3);
                };
            }
        };
    }

    if(current > 0){

        optionB->show();
        optionB->setPlainText("←");
        optionB->onClick = [=]() {
            choosePokemonToStart(current-1);
        };
    }

    if(resourceManager->pokemons.size() > current+1){

        optionD->show();
        optionD->setPlainText("→");
        optionD->onClick = [=]() {
            choosePokemonToStart(current+1);
        };
    }
}

Pokemon BattleScene::generateRandomEnemy(){
    Pokemon t1, t2, t3;
    t1.image = QPixmap(":/images/battle/charmander.png");
    t2.image = QPixmap(":/images/battle/bulbasaur.png");
    t3.image = QPixmap(":/images/battle/squirtle.png");
    t1.imageback = QPixmap(":/images/battle/charmander_back.png");
    t2.imageback = QPixmap(":/images/battle/bulbasaur_back.png");
    t3.imageback = QPixmap(":/images/battle/squirtle_back.png");
    t1.name = "小火龍";
    t2.name = "妙蛙種子";
    t3.name = "傑尼龜";
    t1.attack = 5;
    t2.attack = 5;
    t3.attack = 5;
    t1.defense = 5;
    t2.defense = 5;
    t3.defense = 5;
    t1.hp = 30;
    t2.hp = 30;
    t3.hp = 30;
    t1.maxhp = 30;
    t2.maxhp = 30;
    t3.maxhp = 30;
    t1.pp = 20;
    t2.pp = 20;
    t3.pp = 20;
    t1.level = 1;
    t2.level = 1;
    t3.level = 1;
    PokemonAttack at1;
    at1.name = "抓抓";
    at1.power = 10;
    t1.attacks.append(at1);
    t2.attacks.append(at1);
    t3.attacks.append(at1);
    switch(QRandomGenerator::global()->bounded(0, 3)){
    case 0:
        return t1;
        break;
    case 1:
        return t2;
        break;
    default:
        return t3;
    }
}

void BattleScene::updateBattleStatus(){
    qreal percentenemy = static_cast<qreal>(enemy.hp) / enemy.maxhp;
    qreal percentmy = static_cast<qreal>(resourceManager->pokemons[myPokemonIndex].hp) / resourceManager->pokemons[myPokemonIndex].maxhp;

    // Enemy
    enemyPokemon->setPixmap(enemy.image.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enemyPokemonName->setPlainText(QString("%1").arg(enemy.name));
    enemyPokemonStat->setPlainText(QString("%1/20").arg(enemy.pp));
    enemyPokemonHealthBar1->setRect(112,90,110*percentenemy,18);
    // My
    myPokemon->setPixmap(resourceManager->pokemons[myPokemonIndex].imageback.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    myPokemonName->setPlainText(QString("%1").arg(resourceManager->pokemons[myPokemonIndex].name));
    myPokemonStat->setPlainText(QString("PP: %1/20, HP: %2/%3").arg(resourceManager->pokemons[myPokemonIndex].pp).arg(resourceManager->pokemons[myPokemonIndex].hp).arg(resourceManager->pokemons[myPokemonIndex].maxhp));
    myPokemonHealthBar1->setRect(380,256,110*percentmy,18);
}

void BattleScene::myround(){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    textDescription->setPlainText("現在是你的回合！\n請選擇操作");
    optionA->show();
    optionA->setPlainText("攻擊");
    optionA->onClick = [=]() {
        qDebug() << "[BattleScene] 點選「攻擊」";
        myroundFight();
    };
    optionB->show();
    optionB->setPlainText("寶可夢");
    optionB->onClick = [=]() {
        qDebug() << "[BattleScene] 點選「寶可夢」";
        myroundPokemon();
    };
    optionC->show();
    optionC->setPlainText("背包");
    optionC->onClick = [=]() {
        qDebug() << "[BattleScene] 點選「背包」";
        myroundBag();
    };
    optionD->show();
    optionD->setPlainText("逃跑");
    optionD->onClick = [=]() {
        qDebug() << "[BattleScene] 點選「逃跑」";
        switchScene(3);
    };
}

void BattleScene::myroundFight(){

    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    if(resourceManager->pokemons[myPokemonIndex].pp > 0 ){
        textDescription->setPlainText(QString("要使出什麼招數呢？\nPP: %1/20\n補劑: %2").arg(resourceManager->pokemons[myPokemonIndex].pp).arg(resourceManager->getEtherCount()));

        if(resourceManager->pokemons[myPokemonIndex].attacks.size() > 0){
            optionA->show();
            optionA->setPlainText(QString("%1 %2").arg(resourceManager->pokemons[myPokemonIndex].attacks[0].name).arg(resourceManager->pokemons[myPokemonIndex].attacks[0].power));
            optionA->onClick = [=]() {
                qDebug() << "[BattleScene] 使用招數" << resourceManager->pokemons[myPokemonIndex].attacks[0].name;
                myroundFightUse(0);
            };
        }

        if(resourceManager->pokemons[myPokemonIndex].attacks.size() > 1){
            optionB->show();
            optionB->setPlainText(QString("%1 %2").arg(resourceManager->pokemons[myPokemonIndex].attacks[1].name).arg(resourceManager->pokemons[myPokemonIndex].attacks[1].power));
            optionB->onClick = [=]() {
                qDebug() << "[BattleScene] 使用招數" << resourceManager->pokemons[myPokemonIndex].attacks[1].name;
                myroundFightUse(1);
            };
        }

        if(resourceManager->pokemons[myPokemonIndex].attacks.size() > 2){
            optionC->show();
            optionC->setPlainText(QString("%1 %2").arg(resourceManager->pokemons[myPokemonIndex].attacks[2].name).arg(resourceManager->pokemons[myPokemonIndex].attacks[2].power));
            optionC->onClick = [=]() {
                qDebug() << "[BattleScene] 使用招數" << resourceManager->pokemons[myPokemonIndex].attacks[2].name;
                myroundFightUse(2);
            };
        }
        if(resourceManager->pokemons[myPokemonIndex].attacks.size() > 3){
            optionD->show();
            optionD->setPlainText(QString("%1 %2").arg(resourceManager->pokemons[myPokemonIndex].attacks[3].name).arg(resourceManager->pokemons[myPokemonIndex].attacks[3].power));
            optionD->onClick = [=]() {
                qDebug() << "[BattleScene] 使用招數" << resourceManager->pokemons[myPokemonIndex].attacks[3].name;
                myroundFightUse(3);
            };
        }

    } else {
        textDescription->setPlainText(QString("PP不足! 無法攻擊!\nPP: 0/20\n補劑: %1").arg(resourceManager->getEtherCount()));
        optionD->show();
        optionD->setPlainText("返回");
        optionD->onClick = [=]() {
            qDebug() << "[BattleScene] PP 不足，「返回」";
            myround();
        };
    }
}

void BattleScene::myroundFightUse(int methodIndex){

    // pp在選擇時就會計算
    // 計算傷害：(power+attack-enemy defense)*level
    int damage = (resourceManager->pokemons[myPokemonIndex].attacks[methodIndex].power + resourceManager->pokemons[myPokemonIndex].attack - enemy.defense) * resourceManager->pokemons[myPokemonIndex].level;
    enemy.hp -= damage;
    if (enemy.hp < 0) { enemy.hp = 0 ;}

    resourceManager->pokemons[myPokemonIndex].pp--;

    sound->setSource(QUrl::fromLocalFile(":/sounds/battleHit.wav"));
    sound->play();

    myroundConfirm(QString("%1使出了%2\n對手受到%3點傷害!\n對手目前HP%4/%5").arg(resourceManager->pokemons[myPokemonIndex].name).arg(resourceManager->pokemons[myPokemonIndex].attacks[methodIndex].name).arg(damage).arg(enemy.hp).arg(enemy.maxhp));
}

void BattleScene::myroundPokemon(int current){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    textDescription->setPlainText(QString("請選擇要更換的寶可夢\n目前有 %1 隻寶可夢\n頁 %2/%1").arg(resourceManager->pokemons.size()).arg(current+1));

    if(resourceManager->pokemons.size() > 0){

        optionA->show();
        optionA->setPlainText(QString("[%1]%2[HP:%3]").arg(resourceManager->pokemons[current].level).arg(resourceManager->pokemons[current].name).arg(resourceManager->pokemons[current].hp));
        optionA->onClick = [=]() {
            sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
            sound->play();
            qDebug() << "[BattleScene] 更換寶可夢" << resourceManager->pokemons[current].name;
            myPokemonIndex = current;
            myroundConfirm(QString("已更換至 %1\nHP: %2/%3\nPP: %4").arg(resourceManager->pokemons[myPokemonIndex].name).arg(resourceManager->pokemons[myPokemonIndex].hp).arg(resourceManager->pokemons[myPokemonIndex].maxhp).arg(resourceManager->pokemons[myPokemonIndex].pp));
        };
    }

    if(current > 0){

        optionB->show();
        optionB->setPlainText("←");
        optionB->onClick = [=]() {
            sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
            sound->play();
            myroundPokemon(current-1);
        };
    }

    if(resourceManager->pokemons.size() > current+1){

        optionD->show();
        optionD->setPlainText("→");
        optionD->onClick = [=]() {
            sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
            sound->play();
            myroundPokemon(current+1);
        };
    }
}

void BattleScene::myroundBag(){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    textDescription->setPlainText("請選擇要使用的道具\n作用於目前寶可夢\n使用後將輪到對手回合");

    optionA->show();
    optionA->setPlainText(QString("傷藥 %1").arg(resourceManager->getPotionCount()));
    optionA->onClick = [=]() {
        sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
        sound->play();
        qDebug() << "[BattleScene] 點選「傷藥」";
        if (resourceManager->getPotionCount() > 0){
            resourceManager->addPotionCount(-1);
            resourceManager->pokemons[myPokemonIndex].hp += 10;
            if (resourceManager->pokemons[myPokemonIndex].hp > resourceManager->pokemons[myPokemonIndex].maxhp){
                resourceManager->pokemons[myPokemonIndex].hp = resourceManager->pokemons[myPokemonIndex].maxhp;
            }
            myroundConfirm(QString("使用成功!\n%1的HP已增加10\n現在HP %2/%3!").arg(resourceManager->pokemons[myPokemonIndex].name).arg(resourceManager->pokemons[myPokemonIndex].hp).arg(resourceManager->pokemons[myPokemonIndex].maxhp));
        } else {
            myroundBack("無法使用\n你的傷藥不足!");
        }
    };

    optionB->show();
    optionB->setPlainText(QString("補藥 %1").arg(resourceManager->getEtherCount()));
    optionB->onClick = [=]() {
        sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
        sound->play();
        qDebug() << "[BattleScene] 點選「補藥」";
        if (resourceManager->getEtherCount() > 0){
            resourceManager->addEtherCount(-1);
            resourceManager->pokemons[myPokemonIndex].pp = 20;
            myroundConfirm(QString("使用成功!\n%1的PP已回復滿!").arg(resourceManager->pokemons[myPokemonIndex].name));
        } else {
            myroundBack("無法使用\n你的補藥不足!");
        }
    };

    int captureChance = 50 + resourceManager->pokemons[myPokemonIndex].hp - enemy.hp*2 ; // 兩個人的血量相加（％）
    int requiredChance = QRandomGenerator::global()->bounded(0, 101);
    optionC->show();
    optionC->setPlainText(QString("寶可球 %1").arg(resourceManager->getPokeballCount()));
    optionC->onClick = [=]() {
        sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
        sound->play();
        qDebug() << "[BattleScene] 點選「寶可夢球」";
        if (resourceManager->getPokeballCount() > 0){
            resourceManager->addPokeballCount(-1);
            if (captureChance >= requiredChance ){ // 抓獲
                myroundCaptureSuccess();
            } else {
                myroundConfirm(QString("捕捉失敗!\n\n(測試用) %1 < %2").arg(captureChance).arg(requiredChance));
            }
        } else {
            myroundBack("無法使用\n你的寶可夢球不足!");
        }
    };

}

void BattleScene::myroundConfirm(QString message){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    updateBattleStatus();
    textDescription->setPlainText(message);
    optionA->show();
    optionA->setPlainText("好");
    optionA->onClick = [=](){
        if (!judgeVictor()){
            sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
            sound->play();
            // judge 不出來才繼續
            enemyround();
        }
    };
}

void BattleScene::myroundBack(QString message){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    textDescription->setPlainText(message);
    optionA->show();
    optionA->setPlainText("返回");
    optionA->onClick = [=](){
        sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
        sound->play();
        myround();
    };
}

void BattleScene::myroundCaptureSuccess(){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    // 音效(加分項目)捕捉成功
    sound->setSource(QUrl::fromLocalFile(":/sounds/caught.wav"));
    sound->play();

    resourceManager->pokemons.append(enemy);
    textDescription->setPlainText(QString("捕捉成功!恭喜你!\n%1收入囊中了\nHP:%2/%3").arg(enemy.name).arg(enemy.hp).arg(enemy.maxhp));
    optionD->show();
    optionD->setPlainText("離開");
    optionD->onClick = [=](){
        switchScene(3);
    };
}

void BattleScene::enemyround(){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    sound->setSource(QUrl::fromLocalFile(":/sounds/enemyHurt.wav"));
    sound->play();

    if(enemy.pp > 0 ){
        // 使用招數（目前都是「抓抓」）
        int damage = (enemy.attacks[0].power + enemy.attack - resourceManager->pokemons[myPokemonIndex].defense) * 1;
        resourceManager->pokemons[myPokemonIndex].hp -= damage;
        if (resourceManager->pokemons[myPokemonIndex].hp < 0) { resourceManager->pokemons[myPokemonIndex].hp = 0 ;}

        textDescription->setPlainText(QString("%1使出了%2\n你受到了%3點傷害!\n你目前HP%4/%5").arg(enemy.name).arg(enemy.attacks[0].name).arg(damage).arg(resourceManager->pokemons[myPokemonIndex].hp).arg(resourceManager->pokemons[myPokemonIndex].maxhp));

        enemy.pp--;
    } else {
        textDescription->setPlainText(QString("%1的PP值不夠了\n因此無法使用招數").arg(enemy.name));
    }

    updateBattleStatus();

    optionA->show();
    optionA->setPlainText("好");
    optionA->onClick = [=]() {
        if (!judgeVictor()){
            sound->setSource(QUrl::fromLocalFile(":/sounds/buttonSound.wav"));
            sound->play();
            // judge 不出來才繼續
            myround();
        }
    };
}

bool BattleScene::judgeVictor(){
    if (enemy.hp <= 0){
        iWon();
        return true;
    }
    if (resourceManager->pokemons[myPokemonIndex].hp <= 0){
        iLost();
        return true;
    }
    return false;
}

void BattleScene::iWon(){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    sound->setSource(QUrl::fromLocalFile(":/sounds/battleWin.wav"));
    sound->play();

    textDescription->setPlainText(QString("你贏了!\n%1已打敗%2\n你怎麼這麼厲害?").arg(resourceManager->pokemons[myPokemonIndex].name).arg(enemy.name));

    optionA->show();
    optionA->setPlainText("好");
    optionA->onClick = [=](){

        textDescription->setPlainText(iWonLevelup());

        optionA->show();
        optionA->setPlainText("離開");
        optionA->onClick = [=](){
            switchScene(3);
        };
    };

}

void BattleScene::iLost(){
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();

    sound->setSource(QUrl::fromLocalFile(":/sounds/battleLost.wav"));
    sound->play();


    int totalHp = 0;
    for (Pokemon &item : resourceManager->pokemons){
        totalHp += item.hp;
    }

    if (totalHp <= 0 ){
        textDescription->setPlainText(QString("遊戲結束!!\n%1被%2打敗\n所有神奇寶貝都死了").arg(resourceManager->pokemons[myPokemonIndex].name).arg(enemy.name));
        optionA->show();
        optionA->setPlainText("遊戲結束");
        optionA->onClick = [=](){
            switchScene(5);
        };
    } else {
        textDescription->setPlainText(QString("你輸了!\n%1被%2打敗\n菜就多練~繼續加油!").arg(resourceManager->pokemons[myPokemonIndex].name).arg(enemy.name));
        optionA->show();
        optionA->setPlainText("離開");
        optionA->onClick = [=](){
            switchScene(3);
        };
    }
}

QString BattleScene::iWonLevelup(){

    Pokemon &target = resourceManager->pokemons[myPokemonIndex];
    PokemonAttack temp;

    if (target.level < 6){

        // 升級音效
        sound->setSource(QUrl::fromLocalFile(":/sounds/getXP.wav"));
        sound->play();

        // 小火龍 火恐龍 噴火龍
        if (target.name == "小火龍" && target.level == 1){
            target.level = 2;
            temp.name = "吼叫";
            temp.power = 15;
            target.attacks.append(temp);
            return QString("小火龍已升至2級\n習得招式「吼叫 15」");
        }
        if (target.name == "小火龍" && target.level == 2){
            target.level = 3;
            target.name = "火恐龍";
            target.image = QPixmap(":/images/battle/charmeleon.png");
            target.imageback = QPixmap(":/images/battle/charmeleon_back.png");
            target.attack = 10;
            target.defense = 10;
            target.maxhp = 80;
            target.hp += 50;
            target.pp = 15;

            temp.name = "鬼臉";
            temp.power = 20;
            target.attacks.append(temp);
            return QString("小火龍進化為火恐龍\n火恐龍已升至3級\n習得招式「鬼臉 20」");
        }
        if (target.name == "火恐龍" && target.level == 3){
            target.level = 4;
            temp.name = "炙焰";
            temp.power = 25;
            target.pp = 5;
            target.attacks.append(temp);
            return QString("火恐龍已升至4級\n習得招式「炙焰 25」");
        }
        if (target.name == "火恐龍" && target.level == 4){
            target.level = 5;
            target.name = "噴火龍";
            target.image = QPixmap(":/images/battle/charizard.png");
            target.imageback = QPixmap(":/images/battle/charizard_back.png");
            target.attack = 15;
            target.defense = 15;
            target.maxhp = 100;
            target.hp += 20;
            return QString("火恐龍進化為噴火龍\n噴火龍已升至5級");
        }
        if (target.name == "噴火龍" && target.level == 5){
            target.level = 6;
            return QString("噴火龍已升至6級\n已達等級上限");
        }

        // 妙蛙種子 妙蛙草 妙蛙花
        if (target.name == "妙蛙種子" && target.level == 1){
            target.level = 2;
            temp.name = "吼叫";
            temp.power = 15;
            target.attacks.append(temp);
            return QString("妙蛙種子已升至2級\n習得招式「吼叫 15」");
        }
        if (target.name == "妙蛙種子" && target.level == 2){
            target.level = 3;
            target.name = "妙蛙草";
            target.image = QPixmap(":/images/battle/ivysaur.png");
            target.imageback = QPixmap(":/images/battle/ivysaur_back.png");
            target.attack = 10;
            target.defense = 10;
            target.maxhp = 80;
            target.hp += 50;
            target.pp = 15;

            temp.name = "成長";
            temp.power = 20;
            target.attacks.append(temp);
            return QString("妙蛙種子進化為妙蛙草\n妙蛙草已升至3級\n習得招式「成長 20」");
        }
        if (target.name == "妙蛙草" && target.level == 3){
            target.level = 4;
            temp.name = "剃刀葉";
            temp.power = 25;
            target.pp = 5;
            target.attacks.append(temp);
            return QString("妙蛙草已升至4級\n習得招式「剃刀葉 25」");
        }
        if (target.name == "妙蛙草" && target.level == 4){
            target.level = 5;
            target.name = "妙蛙花";
            target.image = QPixmap(":/images/battle/venusaur.png");
            target.imageback = QPixmap(":/images/battle/venusaur_back.png");
            target.attack = 15;
            target.defense = 15;
            target.maxhp = 100;
            target.hp += 20;
            return QString("妙蛙草進化為妙蛙花\n妙蛙花已升至5級");
        }
        if (target.name == "妙蛙花" && target.level == 5){
            target.level = 6;
            return QString("妙蛙花已升至6級\n已達等級上限");
        }
    } else {
        return QString("%1無法再升級了").arg(target.name);
    }


    // 傑尼龜 卡咪龜 水箭龜
    if (target.name == "傑尼龜" && target.level == 1){
        target.level = 2;
        temp.name = "尾鞭";
        temp.power = 15;
        target.attacks.append(temp);
        return QString("傑尼龜已升至2級\n習得招式「尾鞭 15」");
    }
    if (target.name == "傑尼龜" && target.level == 2){
        target.level = 3;
        target.name = "卡咪龜";
        target.image = QPixmap(":/images/battle/wartortle.png");
        target.imageback = QPixmap(":/images/battle/wartortle_back.png");
        target.attack = 10;
        target.defense = 10;
        target.maxhp = 80;
        target.hp += 50;
        target.pp = 15;

        temp.name = "保護";
        temp.power = 20;
        target.attacks.append(temp);
        return QString("傑尼龜進化為卡咪龜\n卡咪龜已升至3級\n習得招式「保護 20」");
    }
    if (target.name == "卡咪龜" && target.level == 3){
        target.level = 4;
        temp.name = "波浪崩潰";
        temp.power = 25;
        target.pp = 5;
        target.attacks.append(temp);
        return QString("卡咪龜已升至4級\n習得招式「波浪崩潰 25」");
    }
    if (target.name == "卡咪龜" && target.level == 4){
        target.level = 5;
        target.name = "水箭龜";
        target.image = QPixmap(":/images/battle/blastoise.png");
        target.imageback = QPixmap(":/images/battle/blastoise_back.png");
        target.attack = 15;
        target.defense = 15;
        target.maxhp = 100;
        target.hp += 20;
        return QString("卡咪龜進化為水箭龜\n水箭龜已升至5級");
    }
    if (target.name == "水箭龜" && target.level == 5){
        target.level = 6;
        return QString("水箭龜已升至6級\n已達等級上限");
    }

    return QString("發生未知錯誤\n無法結算");

}
