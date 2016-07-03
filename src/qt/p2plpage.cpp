#include "p2plpage.h"
#include "ui_p2plpage.h"


P2PLPage::P2PLPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::P2PLPage)
{
    ui->setupUi(this);

}


P2PLPage::~P2PLPage()
{
    delete ui;
}

void P2PLPage::importCSVFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("csv File(*.csv)"));
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowData;
    int tempint = 0;
    data.clear();
    rowOfData.clear();
    rowData.clear();
    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        rowData = data.split(";");
        importedCSV.close();
    }
    qDebug() << data;
    for (int x = 0; x < rowOfData.size(); x++)
    {
        for (int y = 0; y < ui->tableWidgetInjectionLocationsExpandedDialog->columnCount(); y++)
        {
            ui->tableWidgetInjectionLocationsExpandedDialog->item(x,y)->setText(rowData[]);
        }
    }
}
