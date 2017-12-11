#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QtWidgets>
#include "globalindices.h"

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = 0);
    ~Profile();

private:
    Ui::Profile *ui;
};

#endif // PROFILE_H
