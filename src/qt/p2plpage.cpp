#include "p2plpage.h"
#include "ui_p2plpage.h"

#include <stdio.h>

#include <QMessageBox>

class QSslError;

QT_USE_NAMESPACE

P2PLPage::P2PLPage(QWidget *parent): QWidget(parent), ui(new Ui::P2PLPage)
{
	
    ui->setupUi(this);
    connect(ui->pushButtonRefresh, SIGNAL(clicked()), this, SLOT(sendRequest()));
    connect(ui->tableWidget->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), 
           SLOT(loanRequestSelected(const QItemSelection &, const QItemSelection &)));
}

void P2PLPage::loanRequestSelected(const QItemSelection &, const QItemSelection &)
{
    // pull data from selected row
    QModelIndex currentIndex = ui->tableWidget->currentIndex();
    QString chainid = ui->tableWidget->item(currentIndex.row(), 0)->text();
    QString amount = ui->tableWidget->item(currentIndex.row(), 1)->text();
    QString premium = ui->tableWidget->item(currentIndex.row(), 2)->text();
    QString expiry = ui->tableWidget->item(currentIndex.row(), 3)->text();
    QString period = ui->tableWidget->item(currentIndex.row(), 4)->text();
    QString message = ui->tableWidget->item(currentIndex.row(), 5)->text();
    QString txid = ui->tableWidget->item(currentIndex.row(), 6)->text();

    // do something with it
    QMessageBox::information(0, QString("Loan Request Selected:"), QString("ChainID: " + chainid + "\nAmount: " + amount + "\nPremium: " + premium
                 + "\nExpiry: " + expiry + "\nPeriod: " + period + "\nMessgae: " + message + "\nTxID: " + txid + "\n\nClick OK if you wish to fund this loan request."), QMessageBox::Ok);
}

// get loanrequests.dat from server
void P2PLPage::sendRequest()
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://blockwatch.pw:8000/data/loanrequests.dat")));
}
// initially we'll stick it all in a single string for later choppage
void P2PLPage::replyFinished(QNetworkReply *reply)
{
    QByteArray data=reply->readAll();

    QString loans(data);
    loans.chop(1);

    QStringList rows;
    QStringList items;
    rows.clear();
    items.clear();

    rows << loans.split("\n");

    QString count = QString::number(rows.size());

    if (rows.size() > 0) /* segfault prevention*/ {
        ui->tableWidget->setRowCount(rows.size());
        ui->tableWidget->setColumnCount(8);

        QStringList columns;
        columns <<"CHAIN ID"<<"AMOUNT"<<"PREMIUM"<<"EXPIRY"<<"PERIOD"<<"MESSAGE"<<"TXID"<<"REQID";
        ui->tableWidget->setHorizontalHeaderLabels(columns);
        ui->tableWidget->setItem(2, 2, new QTableWidgetItem("...")); /* segfault prevention*/

	    for (int x = 1; x < rows.size(); x++){
		    items = rows.at(x).split(",");
		    for (int y = 0; y < items.size(); y++){
                ui->tableWidget->setItem(x, y, new QTableWidgetItem(items[y]));
		    }
        }
    }
}

P2PLPage::~P2PLPage()
{
    delete ui;
}
