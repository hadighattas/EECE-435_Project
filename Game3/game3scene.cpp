#include "game3scene.h"

Game3Scene::Game3Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("BackgroundGame3.jpg").scaledToHeight(720).scaledToWidth(1280)));
    setSceneRect(0, 0, 1280, 720);
    position1 = -1;
    position2 = -1;

    timerMatch = new QTimer;
    connect(timerMatch, SIGNAL(timeout()), this, SLOT(match()));

    timerNotMatch = new QTimer;
    connect(timerNotMatch, SIGNAL(timeout()), this, SLOT(notMatch()));

    timerEndGame = new QTimer;
    connect(timerEndGame, SIGNAL(timeout()), this, SLOT(endGame()));

    valuesAcquired = new QStringList;
    vicesAcquired = new QStringList;

    endMessage = new QGraphicsTextItem("");
    endMessage->setFont(QFont("asap condensed", 40, QFont::Bold, false));
    endMessage->setDefaultTextColor(QColor(Qt::white));
    endMessage->setZValue(3);

    flip = new QSound("CardFlip.wav");
    fail = new QSound("FailSound.wav");
    win = new QSound("WinningSound.wav");
    correct = new QSound("Correct.wav");
    wrong = new QSound("Wrong.wav");
}

void Game3Scene::placeCards() {
    for(int i =0; i < 18; i++) {
        int y;
        if (i < 6)
            y = 21;
        else if (i < 12)
            y = 247;
        else if (i < 18)
            y = 473;

        int x = 100 + 180 * (i%6);

        cards.insert(i ,new QGraphicsPixmapItem (QPixmap("Card.png").scaled(140, 176, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        cards.at(i)->setPos(x, y);
        stateOfCard.insert(i, CLOSED);// initialize state of all cards as closed
        addItem(cards.at(i));
    }
}

void Game3Scene::setValues() {
    for (int i = 0; i < 18; i++) {
        values.insert(i ,new QGraphicsTextItem);
        values.at(i)->setFont(QFont("asap condensed", 13, QFont::Bold, false));
        values.at(i)->setDefaultTextColor(QColor(Qt::white));
    }

    int maxi, maxj;
    if (difficulty == 0) {
        maxi = 7;
        maxj = 2;
    }
    else if (difficulty == 1) {
        maxi = 6;
        maxj = 3;
    }
    else {
        maxi = 5;
        maxj = 4;
    }

    valuesLeftCount = maxi;

    bool done = false;

    for (int i = 0; i < maxi; i++) {
        done = false;
        while (!done){
            int v1 = rand() % 18;
            int v2 = rand() % 18;
            int random = rand() % (globalValues3.size() - 1);
            if (values.at(v1)->toPlainText() == "" && values.at(v2)->toPlainText() == "" && v1 != v2) {
                values.at(v1)->setPlainText(globalValues3.at(random));
                values.at(v2)->setPlainText(globalValues3.at(random));
                done = true;
            }
        }
    }

    for (int j = 0; j < maxj; j++) {
        done = false;
        while (!done){
            int v1 = rand() % 18;
            int v2 = rand() % 18;
            int random = rand() % (globalVices3.size() - 1);
            if (values.at(v1)->toPlainText() == "" && values.at(v2)->toPlainText() == "" && v1 != v2) {
                values.at(v1)->setDefaultTextColor(QColor(Qt::red));
                values.at(v2)->setDefaultTextColor(QColor(Qt::red));
                values.at(v1)->setPlainText(globalVices3.at(random));
                values.at(v2)->setPlainText(globalVices3.at(random));
                done = true;
            }
        }
    }
    for (int k = 0; k < 18; k++){
        int y;
        if (k < 6)
            y = 95;
        else if (k < 12)
            y = 321;
        else if (k < 18)
            y = 547;

        int x = 113 + 180 * (k%6);

        // centering text in textItem
        values.at(k)->setTextWidth(110);
        QTextBlockFormat format;
        format.setAlignment(Qt::AlignCenter);
        QTextCursor cursor = values.at(k)->textCursor();
        cursor.select(QTextCursor::Document);
        cursor.mergeBlockFormat(format);
        cursor.clearSelection();
        values.at(k)->setTextCursor(cursor);
        values.at(k)->setPos(x, y);
        values.at(k)->setZValue(2);
    }
}

void Game3Scene::setStackedWidget(QStackedWidget *stack, int menuIndex) {
    this->q = stack;
    this->menuIndex = menuIndex;
}

void Game3Scene::setDifficulty(int diff) {
    this->difficulty = diff;
    if (diff == 0 || diff == 1)
        livesCount = 3;
    else
        livesCount = 2;
    placeCards();
    setValues();

    player = new Player;
    player->setDifficulty(difficulty);
    player->setPos(140, 167);
    addItem(player);

    // showing lives
    for(int i = 0; i < livesCount; i++){
        QGraphicsPixmapItem *life = new QGraphicsPixmapItem(QPixmap("Shape10-50.png"));
        life->setPos(0, 150 + 60*i);
        lives.insert(i, life);
        addItem(lives.at(i));
    }
}

void Game3Scene::keyPressEvent(QKeyEvent *event) {
    int row, column;
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        if (player->x() == 140)
            column = 0;
        else
            column = (player->x() - 140) / 180;
        if (player->y() == 167)
            row = 0;
        else
            row = (player->y() - 167) / 226;

        int position = column + 6 * row;
        if (position1 == -1 && stateOfCard.at(position) == CLOSED) {
            flip->play();
            position1 = position;
            stateOfCard.replace(position, OPEN);
            addItem(values.at(position));
            cards.at(position)->setPixmap(QPixmap("CardFront.png").scaled(140, 176, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else if (position2 == -1 && stateOfCard.at(position) == CLOSED) {
            flip->play();
            position2 = position;
            stateOfCard.replace(position, OPEN);
            addItem(values.at(position));
            cards.at(position)->setPixmap(QPixmap("CardFront.png").scaled(140, 176, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            if (values.at(position1)->toPlainText() == values.at(position2)->toPlainText())
                timerMatch->start(1000);
            else
                timerNotMatch->start(1000);
        }

    }
    else
        player->move(event);
}

void Game3Scene::match() {
    timerMatch->stop();

    if (globalValues3.contains(values.at(position1)->toPlainText())) { // value
        correct->play();
        valuesAcquired->append(values.at(position1)->toPlainText());
        valuesLeftCount--;
        if (valuesLeftCount == 0) {
            win->play();
            endMessage->setPlainText("    You won!\nNo values left.");
            endMessage->setPos(640 - endMessage->boundingRect().width()/2, 320);
            addItem(endMessage);
            // flipping remaining cards
            for(int i= 0; i < 18; i++){
                if(stateOfCard.at(i) == CLOSED){
                    addItem(values.at(i));
                    cards.at(i)->setPixmap(QPixmap("CardFront.png").scaled(140, 176, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
            }
            timerEndGame->start(3000);
        }
    }
    else {
        wrong->play();
        vicesAcquired->append(values.at(position1)->toPlainText());
        removeItem(lives.last());
        lives.removeLast();
        livesCount--;
        if (lives.size() == 0) {
            fail->play();
            endMessage->setPlainText("You lost.");
            endMessage->setPos(640 - endMessage->boundingRect().width()/2, 340);
            addItem(endMessage);
            // flipping remaining cards
            for(int i= 0; i < 18; i++){
                if(stateOfCard.at(i) == CLOSED){
                    addItem(values.at(i));
                    cards.at(i)->setPixmap(QPixmap("CardFront.png").scaled(140, 176, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
            }
            timerEndGame->start(3000);
        }
    }
    removeItem(cards.at(position1));
    removeItem(cards.at(position2));
    removeItem(values.at(position1));
    removeItem(values.at(position2));
    stateOfCard.replace(position1, REMOVED);
    stateOfCard.replace(position2, REMOVED);

    position1 = -1;
    position2 = -1;
}

void Game3Scene::notMatch() {
    timerNotMatch->stop();
    flip->play();
    stateOfCard.replace(position1, CLOSED);
    stateOfCard.replace(position2, CLOSED);

    removeItem(values.at(position1));
    removeItem(values.at(position2));

    cards.at(position1)->setPixmap(QPixmap("Card.png").scaled(140, 176, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    cards.at(position2)->setPixmap(QPixmap("Card.png").scaled(140, 176, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    position1 = -1;
    position2 = -1;
}

void Game3Scene::endGame() {
    timerEndGame->stop();
    Game3Score *game3score = new Game3Score;
    game3score->setScore(livesCount, valuesAcquired, vicesAcquired);
    game3score->setStackedWidget(q, this->menuIndex);
    q->addWidget(game3score);
    q->setCurrentWidget(game3score);
}
