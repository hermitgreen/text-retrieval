#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "line.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void buttonIsClicked();
    void CLRbuttonIsClicked();
    void closeButtonIsClicked();
    void queryNoButtonIsClicked();
    void backButtonIsClicked();

    void print(std::string name);
    void query(std::string word);
};

#endif // MAINWINDOW_H
