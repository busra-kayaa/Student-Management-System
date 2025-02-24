#ifndef DERSLER_H
#define DERSLER_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>

class MainWindow;
namespace Ui {
class dersler;
}

class dersler : public QDialog
{
    Q_OBJECT

public:
    explicit dersler(MainWindow *anasayfa,QWidget *parent = nullptr);
    ~dersler();

private slots:
    void on_ekle_clicked();

private:
    Ui::dersler *ui;
    MainWindow *ans;
    QSqlQuery *sorgu;
};

#endif // DERSLER_H
