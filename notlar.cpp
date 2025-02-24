#include "notlar.h"
#include "ui_notlar.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>

notlar::notlar(MainWindow *anasayfa,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notlar)
{
    ui->setupUi(this);
    ans = anasayfa;

    dersListe = new QSqlQuery(ans->db);
    dersmodel = new QSqlQueryModel();

    ogrListe = new QSqlQuery(ans->db);
    ogrmodel = new QSqlQueryModel();

    guncelle = new QSqlQuery(ans->db);

    printer = new QPrinter();
    dialog = new QPrintPreviewDialog(printer);
    connect(dialog, SIGNAL(paintRequested(QPrinter*)),this, SLOT(yazdir()));

    dersleriListele();
    ogrencileriListele(ui->comboBox->currentText());
}

notlar::~notlar()
{
    delete ui;
}

void notlar::dersleriListele()
{
    dersListe->exec("select derskodu from dersler");
    dersmodel->setQuery(*dersListe);
    ui->comboBox->setModel(dersmodel);
}

void notlar::ogrencileriListele(QString derskodu)
{
    ogrListe->prepare("select ogrencino, adi, soyadi from notlar inner join ogrenci on notlar.ogrencino = ogrenci.ogrno where dersno = ?");
    ogrListe->addBindValue(derskodu);
    if (!ogrListe->exec()) {
        QMessageBox::critical(this, "HATA", ogrListe->lastError().text());
    }
    ogrmodel->setQuery(*ogrListe);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(ogrmodel->rowCount());

    QStringList baslik = {"Öğrenci No", "Adı", "Soyadı", "Vize Notu"};
    ui->tableWidget->setHorizontalHeaderLabels(baslik);

    for (int i = 0; i < ogrmodel->rowCount() ; ++i ) {
        ui->tableWidget->setCellWidget(i, 0 , new QLabel(ogrmodel->index(i,0).data().toString()));
        ui->tableWidget->setCellWidget(i, 1 , new QLabel(ogrmodel->index(i,1).data().toString()));
        ui->tableWidget->setCellWidget(i, 2 , new QLabel(ogrmodel->index(i,2).data().toString()));
        ui->tableWidget->setCellWidget(i, 3 , new QLineEdit("-1"));
    }
}

void notlar::on_comboBox_currentIndexChanged(int index)
{
    ogrencileriListele(ui->comboBox->itemText(index));
}


void notlar::yazdir()
{
    QPainter painter(printer);
    painter.drawText(10, 10, "Numarası");
    painter.drawLine(10, 20, 80, 20);
    painter.drawText(100, 10, "Adı");
    painter.drawLine(100, 20, 180, 20);
    painter.drawText(200, 10, "Soyadı");
    painter.drawLine(200, 20, 280, 20);

    int Y = 50;
    for (int i = 0; i < ogrmodel->rowCount(); ++i) {
        painter.drawText(10, Y, ogrmodel->index(i, 0).data().toString());
        painter.drawText(100, Y, ogrmodel->index(i, 1).data().toString());
        painter.drawText(200, Y, ogrmodel->index(i, 2).data().toString());
        Y += 30;
    }
}


void notlar::on_yazdir_clicked()
{
    dialog->exec();
}


void notlar::on_kaydet_clicked()
{
    for (int i = 0; i < ogrmodel->rowCount() ; ++i) {
        guncelle->prepare("update notlar set vize = ? where ogrencino = ? and dersno = ?");
        QLineEdit *ed = (QLineEdit *) ui->tableWidget->cellWidget(i, 3);
        guncelle->addBindValue(ed->text());
        guncelle->addBindValue(((QLabel *) ui->tableWidget->cellWidget(i, 0))->text());
        guncelle->addBindValue(ui->comboBox->currentText());

        if(!guncelle->exec()) {
            QMessageBox::critical(this, "HATA",guncelle->lastError().text());
        }
        else {
            QMessageBox::information(this,"Bilgi","Basariyla guncellendi");
        }
    }
}
