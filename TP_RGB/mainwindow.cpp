#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_Red_valueChanged(int value)
{
    QPalette palette;
    ui->spinBox_Red->setAutoFillBackground(true);
    palette.setColor(QPalette::Base, QColor(QColor(ui->spinBox_Red->value(), 0, 0)));
    if (ui->spinBox_Red->value() <= 200)
        palette.setColor(QPalette::Text, Qt::white);
    else
        palette.setColor(QPalette::Text, Qt::black);
    ui->spinBox_Red->setPalette(palette);
    ui->verticalSlider_Red->setValue(value);
}

void MainWindow::on_verticalSlider_Red_valueChanged(int value)
{
    ui->spinBox_Red->setValue(value);
}

void MainWindow::on_spinBox_Green_valueChanged(int value)
{
    QPalette palette;
    ui->spinBox_Green->setAutoFillBackground(true);
    palette.setColor(QPalette::Base, QColor(QColor(0, ui->spinBox_Green->value(), 0)));
    if (ui->spinBox_Green->value() <= 190)
        palette.setColor(QPalette::Text, Qt::white);
    else
        palette.setColor(QPalette::Text, Qt::black);
    ui->spinBox_Green->setPalette(palette);
    ui->verticalSlider_Green->setValue(value);
}

void MainWindow::on_verticalSlider_Green_valueChanged(int value)
{
    ui->spinBox_Green->setValue(value);
}

void MainWindow::on_spinBox_Blue_valueChanged(int value)
{
    QPalette palette;
    ui->spinBox_Blue->setAutoFillBackground(true);
    palette.setColor(QPalette::Base, QColor(QColor(0, 0, ui->spinBox_Blue->value())));
    palette.setColor(QPalette::Text, Qt::white);
    ui->spinBox_Blue->setPalette(palette);
    ui->verticalSlider_Blue->setValue(value);
}

void MainWindow::on_verticalSlider_Blue_valueChanged(int value)
{
    ui->spinBox_Blue->setValue(value);
}

void MainWindow::RGB_Adjust()
{
    QPalette palette;
    ui->label_Color->setAutoFillBackground(true);
    palette.setColor(QPalette::Window, QColor(QColor(ui->spinBox_Red->value(), ui->spinBox_Green->value(), ui->spinBox_Blue->value())));
    ui->label_Color->setPalette(palette);
}

void MainWindow::init()
{
    ui->verticalSlider_Red->setStyleSheet("QSlider::handle:veritcal { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop:1 red); border: 1px solid #999999; border-radius: 5px;}");
    ui->verticalSlider_Green->setStyleSheet("QSlider::handle:veritcal { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop:1 green); border: 1px solid #999999; border-radius: 5px;}");
    ui->verticalSlider_Blue->setStyleSheet("QSlider::handle:veritcal { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop:1 blue); border: 1px solid #999999; border-radius: 5px;}");

    ui->verticalSlider_Red->setRange(0, 255);
    ui->verticalSlider_Green->setRange(0, 255);
    ui->verticalSlider_Blue->setRange(0, 255);

    ui->spinBox_Red->setRange(0, 255);
    ui->spinBox_Green->setRange(0, 255);
    ui->spinBox_Blue->setRange(0, 255);

    connect(ui->spinBox_Red, SIGNAL(valueChanged(int)), this, SLOT(RGB_Adjust()));
    connect(ui->spinBox_Green, SIGNAL(valueChanged(int)), this, SLOT(RGB_Adjust()));
    connect(ui->spinBox_Blue, SIGNAL(valueChanged(int)), this, SLOT(RGB_Adjust()));

    ui->spinBox_Red->setValue(255);
    ui->spinBox_Green->setValue(255);
    ui->spinBox_Blue->setValue(255);

}

