#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Busra/okul.db");
    if(!db.open()) {
        QMessageBox::critical(this,"Veri Tabanina Baglanamadi", db.lastError().text());
    }
    ogr = new ogrenci(this);
    ders = new dersler(this);
    dk = new dersKaydi(this);
    nots = new notlar(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_renci_Giri_i_triggered()
{
    ogr->show();
}


void MainWindow::on_actionDers_Giri_i_triggered()
{
    ders->show();
}


void MainWindow::on_actionDers_Kaydi_Olu_tur_triggered()
{
    dk->show();
}


void MainWindow::on_actionNot_Giri_i_triggered()
{
    nots->show();
}
