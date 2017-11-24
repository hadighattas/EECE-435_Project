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

    bool done = false;

    for (int i = 0; i < maxi; i++) {
        done = false;
        while (!done){
            int v1 = rand() % 18;
            int v2 = rand() % 18;
            int random = rand() % globalValues3.size();
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
            int random = rand() % globalVices3.size();
            if (values.at(v1)->toPlainText() == "" && values.at(v2)->toPlainText() == "" && v1 != v2) {
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
    }
}

void Game3Scene::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
}

void Game3Scene::setDifficulty(int diff) {
    this->difficulty = diff;
    placeCards();
    setValues();

    player = new Player;
    player->setDifficulty(difficulty);
    player->setPos(140, 167);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    addItem(player);
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
        if (position1 == position)
            return ;
        else if (position1 == -1) {
            position1 = position;
            stateOfCard.replace(position, OPEN);
            addItem(values.at(position));
            cards.at(position)->setPixmap(QPixmap("CardFront.png"));
        }
        else if (position2 == -1) {
            position2 = position;
            stateOfCard.replace(position, OPEN);
            addItem(values.at(position));
            cards.at(position)->setPixmap(QPixmap("CardFront.png"));
            if (values.at(position1)->toPlainText() == values.at(position2)->toPlainText()) {
                player->clearFocus();
                timerMatch->start(1000);
            }
            else {
                player->clearFocus();
                timerNotMatch->start(1000);
            }
        }

    }
}

void Game3Scene::match() {
    removeItem(cards.at(position1));
    removeItem(cards.at(position2));
    removeItem(values.at(position1));
    removeItem(values.at(position1));
    stateOfCard.replace(position1, REMOVED);
    stateOfCard.replace(position2, REMOVED);

    player->setFocus();

    position1 = -1;
    position2 = -1;
}

void Game3Scene::notMatch() {
    stateOfCard.replace(position1, CLOSED);
    stateOfCard.replace(position2, CLOSED);

    cards.at(position1)->setPixmap(QPixmap("Card.png"));
    cards.at(position2)->setPixmap(QPixmap("Card.png"));

    player->setFocus();

    position1 = -1;
    position2 = -1;
}
