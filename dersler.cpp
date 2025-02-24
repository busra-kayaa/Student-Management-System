#include "dersler.h"
#include "ui_dersler.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlError>

dersler::dersler(MainWindow *anasayfa,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dersler)
{
    ui->setupUi(this);
    ans = anasayfa;
}

dersler::~dersler()
{
    delete ui;
}

void dersler::on_ekle_clicked()
{
    sorgu = new QSqlQuery(ans->db);
    sorgu->prepare("insert into dersler values (?,?,?,?)");
    sorgu->addBindValue(ui->kodu->text());
    sorgu->addBindValue(ui->adi->text());
    sorgu->addBindValue(ui->donem->text());
    sorgu->addBindValue(ui->kredi->text());

    if(!sorgu->exec()) {
        QMessageBox::critical(this,"Ders Ekleme Sorgu Hatasi",sorgu->lastError().text());
    } else {
        QMessageBox::information(this,"Bilgi","Ders Başarıyla Eklendi");
    }
}

