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
    int numero_choix;
    QStringList valeur_choix[5];

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


    void on_listView_color_clicked(const QModelIndex &index);

    void on_pushButton_Conserver_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
