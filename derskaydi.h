#ifndef DERSKAYDI_H
#define DERSKAYDI_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

class MainWindow;
namespace Ui {
class dersKaydi;
}

class dersKaydi : public QDialog
{
    Q_OBJECT

public:
    explicit dersKaydi(MainWindow *anasayfa,QWidget *parent = nullptr);
    ~dersKaydi();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_ogrenciView_clicked(const QModelIndex &index);

    void on_derslerView_clicked(const QModelIndex &index);

private:
    Ui::dersKaydi *ui;
    MainWindow *ans;
    void ogrenciListele(QString param);
    void dersListele(QString dnm);
    void derskaydiListele();

    QSqlQuery *ogrenci, *ders, *derskaydi, *genelsorgu, *combosorgu;
    QSqlQueryModel *ogrmodel, *dersmodel, *kayitmodel, *combomodel;
    QString ogrno, dersno;
};

#endif // DERSKAYDI_H
