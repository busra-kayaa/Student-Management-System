#include "derskaydi.h"
#include "ui_derskaydi.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlError>

dersKaydi::dersKaydi(MainWindow *anasayfa,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dersKaydi)
{
    ui->setupUi(this);
    ans = anasayfa;

    derskaydi = new QSqlQuery(ans->db);
    kayitmodel = new QSqlQueryModel();

    genelsorgu = new QSqlQuery(ans->db);

    combosorgu = new QSqlQuery(ans->db);
    combomodel = new QSqlQueryModel();

    combosorgu->exec("select distinct donem from dersler order by donem");
    combomodel->setQuery(*combosorgu);
    ui->comboBox->setModel(combomodel);

    ogrenciListele("");
    dersListele(ui->comboBox->currentText());
}

dersKaydi::~dersKaydi()
{
    delete ui;
}

void dersKaydi::on_pushButton_clicked()
{
    genelsorgu->prepare("insert into notlar (ogrencino, dersno) values (?,?)");
    genelsorgu->addBindValue(ogrno);
    genelsorgu->addBindValue(dersno);

    if(!genelsorgu->exec()) {
        QMessageBox::critical(this,"Ekleme Hatasi",genelsorgu->lastError().text());
    }
    derskaydiListele();
}


void dersKaydi::on_lineEdit_textChanged(const QString &arg1)
{
    ogrenciListele(ui->lineEdit->text());
}


void dersKaydi::on_comboBox_currentIndexChanged(int index)
{
    dersListele(ui->comboBox->itemText(index));
}


void dersKaydi::on_ogrenciView_clicked(const QModelIndex &index)
{
    ogrno = ogrmodel->index(index.row(),0).data().toString();
    derskaydiListele();
}


void dersKaydi::on_derslerView_clicked(const QModelIndex &index)
{
    dersno = dersmodel->index(index.row(),0).data().toString();
}

void dersKaydi::ogrenciListele(QString param)
{
    ogrenci = new QSqlQuery(ans->db);
    ogrmodel = new QSqlQueryModel();

    if(param.isEmpty()) {
        ogrenci->exec("select * from ogrenci");
    } else {
        ogrenci->exec("select * from ogrenci where adi like '" + param + " % '" );
    }

    ogrmodel->setQuery(*ogrenci);
    ui->ogrenciView->setModel(ogrmodel);
}

void dersKaydi::dersListele(QString dnm)
{
    ders = new QSqlQuery(ans->db);
    dersmodel = new QSqlQueryModel();

    ders->prepare("select * from dersler where donem = ?");
    ders->addBindValue(dnm);

    if(!ders->exec()) {
        QMessageBox::critical(this, " Ders Listeleme Hatası", ders->lastError().text());
    }
    dersmodel->setQuery(*ders);
    ui->derslerView->setModel(dersmodel);
}

void dersKaydi::derskaydiListele()
{
    derskaydi->prepare("select * from notlar where ogrencino = ?");
    derskaydi->addBindValue(ogrno);
    if(!derskaydi->exec()) {
        QMessageBox::critical(this, "Ders Kaydi Listeleme Hatasi",derskaydi->lastError().text());
    }
    kayitmodel->setQuery(*derskaydi);
    ui->dersKaydiView->setModel(kayitmodel);
}
/*

SQL'de `LIKE` operatörüyle yapılabilecek farklı filtreleme türleri vardır. İşte birkaç örnek, farklı filtreleme yöntemlerini açıklayan kullanımlar:

### 1. Başlangıçla Eşleşen Değerler
Eğer bir sütunda belirli bir değeri baştan aramak istiyorsanız, `%` operatörünü kullanabilirsiniz. Örneğin:

ogrenci->exec("select * from ogrenci where adi like '" + param + "%'");
Bu, "adi" sütununda `param` ile başlayan tüm satırları döndürecektir.

### 2. Bitişle Eşleşen Değerler
Bir değerin sonunda belirli bir kelimeyi aramak için `_` (alt çizgi) kullanabilirsiniz. Örneğin:

ogrenci->exec("select * from ogrenci where adi like '%" + param + "'");
Bu, "adi" sütununda `param` ile biten tüm satırları döndürecektir.

### 3. Belirli Bir Desene Uyan Değerler
`LIKE` ile belirli bir desene göre filtreleme yapabilirsiniz. Örneğin, bir karakterin belli bir konumda olup olmadığını kontrol etmek için `_` kullanabilirsiniz.

ogrenci->exec("select * from ogrenci where adi like '_a%'");
Bu, "adi" sütununda ilk harfi herhangi bir karakter olan ve ardından "a" harfi gelen tüm kayıtları döndürecektir.

### 4. Birden Fazla Koşul ile Eşleşme
Birden fazla koşul kullanarak filtreleme yapmak mümkündür. Örneğin, hem başlangıç hem de bitişe dayalı filtreleme yapmak isterseniz:

ogrenci->exec("select * from ogrenci where adi like '" + param1 + "%' and adi like '%" + param2 + "'");
Bu, "adi" sütununda `param1` ile başlayıp, `param2` ile biten tüm satırları döndürecektir.

### 5. Harflerin Büyük/Küçük Olmasına Duyarsız Filtreleme
`LIKE` operatörü genellikle büyük/küçük harf duyarlıdır. Ancak bazı veritabanlarında büyük/küçük harf duyarsızlık sağlamak için `ILIKE` operatörü veya `COLLATE` ifadesi kullanılabilir (örneğin, PostgreSQL). Eğer SQL server'ınız büyük/küçük harfe duyarsızsa şu şekilde kullanabilirsiniz:

ogrenci->exec("select * from ogrenci where adi like '" + param + "%' collate nocase");

### 6. Birden Fazla Terimi İçeren Filtreleme
Eğer bir sütunda belirli kelimeleri içeren satırları arıyorsanız, `IN` operatörünü kullanabilirsiniz. Bu, çoklu değerlerle filtreleme yapmanıza imkan tanır.

ogrenci->exec("select * from ogrenci where adi in ('" + param1 + "', '" + param2 + "')");
Bu, "adi" sütununda `param1` veya `param2` ile eşleşen tüm kayıtları döndürecektir.

### 7. Daha Esnek Filtreleme
Daha esnek ve gelişmiş filtreleme için `AND` ve `OR` gibi mantıksal operatörleri kullanabilirsiniz:

ogrenci->exec("select * from ogrenci where adi like '" + param1 + "%' and soyadi like '%" + param2 + "'");
Bu, "adi" sütununda `param1` ile başlayıp, "soyadi" sütununda `param2` ile biten tüm satırları döndürecektir.

### 8. Eşleşmeyen Değerler
Eğer bir değerin eşleşmediği durumları görmek isterseniz, `NOT LIKE` kullanabilirsiniz:

ogrenci->exec("select * from ogrenci where adi not like '" + param + "%'");
Bu, "adi" sütununda `param` ile başlamayan tüm satırları döndürecektir.

### 9. Sayısal ve Tarihsel Filtrelemeler
Eğer sayısal veya tarihsel veri üzerinde filtreleme yapmak istiyorsanız, bu durumda `=` veya `BETWEEN` gibi operatörler kullanabilirsiniz:

ogrenci->exec("select * from ogrenci where notel between " + startParam + " and " + endParam);
Bu, "notel" (öğrencinin not ortalaması gibi) sütununda belirtilen aralıkta olan tüm kayıtları döndürecektir.

*/
