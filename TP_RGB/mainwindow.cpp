#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QStringListModel>
#include <QMessageBox>
#include <QFile>
#include <qfiledialog.h>

#include <QDebug>

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
    palette.setColor(QPalette::Base, QColor(QColor(value, 0, 0)));
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
    palette.setColor(QPalette::Base, QColor(QColor(0, value, 0)));
    if (value <= 190)
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
    palette.setColor(QPalette::Base, QColor(QColor(0, 0, value)));
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
    QColor color = QColor(ui->spinBox_Red->value(), ui->spinBox_Green->value(), ui->spinBox_Blue->value());
    QString colorHex = color.name(QColor::HexRgb);
    ui->label_Color->setAutoFillBackground(true);
    palette.setColor(QPalette::Window, color);
    ui->label_Color->setPalette(palette);
    ui->label_Color->setText(colorHex);
}

void MainWindow::init()
{
    // change le style des sliders
    ui->verticalSlider_Red->setStyleSheet("QSlider::handle:veritcal { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop:1 red); border: 1px solid #999999; border-radius: 5px;}");
    ui->verticalSlider_Green->setStyleSheet("QSlider::handle:veritcal { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop:1 green); border: 1px solid #999999; border-radius: 5px;}");
    ui->verticalSlider_Blue->setStyleSheet("QSlider::handle:veritcal { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop:1 blue); border: 1px solid #999999; border-radius: 5px;}");

    // definie la limite des sliders
    ui->verticalSlider_Red->setRange(0, 255);
    ui->verticalSlider_Green->setRange(0, 255);
    ui->verticalSlider_Blue->setRange(0, 255);

    // definie la limite des spinboxs
    ui->spinBox_Red->setRange(0, 255);
    ui->spinBox_Green->setRange(0, 255);
    ui->spinBox_Blue->setRange(0, 255);

    // connect les signaux aux slots pour changer la couleur du label "color"
    connect(ui->spinBox_Red, SIGNAL(valueChanged(int)), this, SLOT(RGB_Adjust()));
    connect(ui->spinBox_Green, SIGNAL(valueChanged(int)), this, SLOT(RGB_Adjust()));
    connect(ui->spinBox_Blue, SIGNAL(valueChanged(int)), this, SLOT(RGB_Adjust()));

    // definie les valeur de depart des spinboxs
    ui->spinBox_Red->setValue(255);
    ui->spinBox_Green->setValue(255);
    ui->spinBox_Blue->setValue(255);

    // affiche la liste complete des couleurs de QT
    QStringList listeCouleurs = QColor::colorNames();
    QStringListModel *modeleCouleurs = new QStringListModel(listeCouleurs);
    ui->listView_color->setModel(modeleCouleurs);

    // initialise la valeur de depart pour les choix
    this->numero_choix = 1;

    for (int i = 0; i < 6; i++)
    {
        QString nom_label = "label_Choix" + QString::number(i+1);
        label[i] = this->findChild<QLabel*>(nom_label);
    }
}

void MainWindow::on_listView_color_clicked(const QModelIndex &index)
{
    QVariant nom = index.data(Qt::DisplayRole);
    int red = nom.value<QColor>().red();
    int green = nom.value<QColor>().green();
    int blue = nom.value<QColor>().blue();

    ui->spinBox_Red->setValue(red);
    ui->spinBox_Green->setValue(green);
    ui->spinBox_Blue->setValue(blue);
}

void MainWindow::on_pushButton_Conserver_clicked()
{
    QString nom_label = "label_Choix" + QString::number(this->numero_choix);
    QLabel *label = this->findChild<QLabel*>(nom_label);
    QPalette palette;
    palette.setColor(QPalette::Window, ui->label_Color->text());
    label->setAutoFillBackground(true);
    label->setText(ui->label_Color->text());
    label->setPalette(palette);

    if (this->numero_choix<6)
        this->numero_choix++;
    else
        this->numero_choix = 1;
}


void MainWindow::on_actionNew_triggered()
{
    QString name_file = "";
    name_file = QFileDialog::getSaveFileName(this, "New File", "D:/fauret.SNIRW/deuxieme annee/TP CP/TP_RGB/TP_RGB", "Text files (*.pal)");
    if (name_file != "")
    {
        QFile file(name_file);
        file.open(QIODeviceBase::NewOnly);
        file.close();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString name_file = "";
    name_file = QFileDialog::getOpenFileName(this, "Open file", "D:/fauret.SNIRW/deuxieme annee/TP CP/TP_RGB/TP_RGB", "Text files (*.pal)");
    if (name_file != "")
    {
        QFile file(name_file);
        if (!file.open(QIODeviceBase::ReadOnly | QIODeviceBase::Text))
        {
            return;
        }

        QTextStream flux(&file);
        QString valeur = flux.readAll();
        QStringList couleur = valeur.split("\n");

        for (int i = 0; i < 6; i++)
        {
            if (couleur[i] != "")
            {
                QPalette palette;
                this->label[i]->setText(couleur[i]);
                palette.setColor(QPalette::Window, this->label[i]->text());
                this->label[i]->setAutoFillBackground(true);
                this->label[i]->setPalette(palette);
            }
        }
        file.close();
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString name_file = "";
    name_file = QFileDialog::getSaveFileName(this, "Save file", "D:/fauret.SNIRW/deuxieme annee/TP CP/TP_RGB/TP_RGB" ,"Text files (*.pal)");
    if (name_file != "")
    {
        QFile file(name_file);
        if (!file.open(QIODeviceBase::WriteOnly | QIODeviceBase::Text))
        {
            return;
        }

        QTextStream flux(&file);
        flux << this->formatage_fichier();
        file.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString name_file = "";
    name_file = QFileDialog::getSaveFileName(this, "New File", "D:/fauret.SNIRW/deuxieme annee/TP CP/TP_RGB/TP_RGB", "Text files (*.pal)");
    if (name_file != "")
    {
        QFile file(name_file);
        if (!file.open(QIODeviceBase::NewOnly | QIODeviceBase::Text))
        {
            return;
        }
        QTextStream flux(&file);
        flux << this->formatage_fichier();
        file.close();
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_the_app_triggered()
{
    QMessageBox::about(this, "About this app", "This application is designe to learn QT and the c++");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

QString MainWindow::formatage_fichier()
{
    QString listCouleur = "";
    for (int  i = 0; i < 6; i++)
    {
        if (this->label[i]->text() != "Choix " + QString::number(i+1))
            listCouleur += this->label[i]->text() + "\n";
        else
            listCouleur += "\n";
    }
    return listCouleur;
}
