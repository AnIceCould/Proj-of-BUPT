#ifndef SETNAMEWINDOW_H
#define SETNAMEWINDOW_H

#include "gameview.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

class SetNameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SetNameWindow(QWidget *parent = nullptr);
private:
    GameView* gameview = NULL;//游戏框架指针
    QLabel* nameLable;//输入提示标签
    QLineEdit* nameEdit;//输入名称框
    QPushButton* backButton;//返回按钮
    QPushButton* nextButton;//继续按钮

signals:

};

#endif // SETNAMEWINDOW_H
