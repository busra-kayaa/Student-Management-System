#ifndef OGRENCI_H
#define OGRENCI_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

class MainWindow; /////////////

namespace Ui {
class ogrenci;
}

class ogrenci : public QDialog
{
    Q_OBJECT

public:
    explicit ogrenci(MainWindow *anasayfa, QWidget *parent = nullptr);
    ~ogrenci();

private slots:
    void on_vazgec_clicked();
    void on_ekle_clicked();

private:
    Ui::ogrenci *ui;
    MainWindow *ans;
    QSqlQuery *sorgu;
};

#endif // OGRENCI_H
