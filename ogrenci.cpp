#include "ogrenci.h"
#include "ui_ogrenci.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlError>

ogrenci::ogrenci(MainWindow *anasayfa,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ogrenci)
{
    ui->setupUi(this);
    ans = anasayfa;
}

ogrenci::~ogrenci()
{
    delete ui;
}

void ogrenci::on_vazgec_clicked()
{
    this->close();  // Formu kapat
}

void ogrenci::on_ekle_clicked()
{
    sorgu = new QSqlQuery(ans->db);

    sorgu->prepare("insert into ogrenci values (?,?,?)");
    sorgu->addBindValue(ui->no->text());
    sorgu->addBindValue(ui->adi->text());
    sorgu->addBindValue(ui->soyadi->text());

    if(!sorgu->exec()){
        QMessageBox::critical(this, " Öğrenci Ekleme Sorgu Hatasi",sorgu->lastError().text());
    } else {
        QMessageBox::information(this,"Bilgi","Öğrenci Başarılı Bir Şekilde Eklendi");
    }
}
