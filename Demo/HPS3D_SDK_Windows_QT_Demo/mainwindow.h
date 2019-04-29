#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
     void timerUpDate();

    void on_Connect_clicked();

    void on_DisConnect_clicked();

    void on_SingleMeasure_clicked();

    void on_Start_clicked();

    void on_Stop_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
