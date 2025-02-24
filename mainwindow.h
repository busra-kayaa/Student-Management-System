#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "ogrenci.h"
#include "notlar.h"
#include "derskaydi.h"
#include "dersler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db;

private slots:
    void on_action_renci_Giri_i_triggered();

    void on_actionDers_Giri_i_triggered();

    void on_actionDers_Kaydi_Olu_tur_triggered();

    void on_actionNot_Giri_i_triggered();

private:
    Ui::MainWindow *ui;
    ogrenci *ogr;
    dersKaydi *dk;
    dersler *ders;
    notlar * nots;
};
#endif // MAINWINDOW_H
