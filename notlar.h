#ifndef NOTLAR_H
#define NOTLAR_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPrintPreviewDialog>

class MainWindow;
namespace Ui {
class notlar;
}

class notlar : public QDialog
{
    Q_OBJECT

public:
    explicit notlar(MainWindow *anasayfa,QWidget *parent = nullptr);
    ~notlar();
    void dersleriListele();
    void ogrencileriListele(QString derskodu);

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void yazdir();

    void on_yazdir_clicked();

    void on_kaydet_clicked();

private:
    Ui::notlar *ui;
    MainWindow *ans;

    QSqlQuery *dersListe, *ogrListe, *guncelle;
    QSqlQueryModel *dersmodel, *ogrmodel;

    QPrinter *printer;
    QPrintPreviewDialog *dialog;
};

#endif // NOTLAR_H
