#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_Red_valueChanged(int value);

    void on_verticalSlider_Red_valueChanged(int value);

    void on_spinBox_Green_valueChanged(int value);

    void on_verticalSlider_Green_valueChanged(int value);

    void on_spinBox_Blue_valueChanged(int value);

    void on_verticalSlider_Blue_valueChanged(int value);

    void RGB_Adjust();

    void init();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
