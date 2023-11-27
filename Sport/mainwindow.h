#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "setnamewindow.h"
#include "getscorewindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SetNameWindow* setwindow = NULL;//设置名字窗口
    GetScoreWindow* getwindow = NULL;//排行榜窗口
};
#endif // MAINWINDOW_H
