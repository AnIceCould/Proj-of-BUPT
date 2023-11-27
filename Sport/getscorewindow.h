#ifndef GETSCOREWINDOW_H
#define GETSCOREWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QPushButton>
#include <QFile>
#include <QByteArray>

class GetScoreWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GetScoreWindow(QWidget *parent = nullptr);
    QTextEdit* rankEdit;//编辑框
    QPushButton* reButton;//按钮

signals:

};

#endif // GETSCOREWINDOW_H
