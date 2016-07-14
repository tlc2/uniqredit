#include "bidpage.h"
#include "ui_bidpage.h"
#include "util.h"
#include "guiutil.h"
#include "clientmodel.h"
#include "chainparams.h"
#include "main.h"
#include "net.h"

#include <cstdlib>

#include <fstream>
#include <QMessageBox>
#include <QDesktopServices>

#include <QProcess>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QTimer>

#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

BidPage::BidPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::BidPage)
{
    ui->setupUi(this);

    connect(ui->pushButtonBTCExplorer, SIGNAL(clicked()), this, SLOT(SummonBTCExplorer()));
    connect(ui->pushButtonRefresh, SIGNAL(clicked()), this, SLOT(sendRequests()));
    connect(ui->bImport, SIGNAL(clicked()), this, SLOT(RPC()));

}

void BidPage::setClientModel(ClientModel *model)
{
    clientModel = model;
    if(model)
    {
        //setNumBlocks(model->getNumBlocks());
        //connect(model, SIGNAL(numBlocksChanged(int)), this, SLOT(setNumBlocks(int)));
    }
}

void BidPage::sendRequests()
{
    sendRequest();
    sendRequest2();
}

void BidPage::sendRequest()
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("https://blockchain.info/q/addressbalance/16bi8R4FoDHfjNJ1RhpvcAEn4Cz78FbtZB")));
}

void BidPage::replyFinished(QNetworkReply *reply)
{
    QByteArray data=reply->readAll();
    QString btcassets(data);
    double btcassetsasdouble = btcassets.toDouble();
    QString reserves = QString::number(btcassetsasdouble/COIN, 'f', 8);
    ui->labelReserves->setText(reserves);
}

void BidPage::sendRequest2()
{
    manager2 = new QNetworkAccessManager(this);
    connect(manager2, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished2(QNetworkReply*)));
    manager2->get(QNetworkRequest(QUrl("https://blockchain.info/q/addressbalance/1UniQ1TiDyGbB7KXejnjUAZMEjLCyiEPe")));
}

void BidPage::replyFinished2(QNetworkReply *reply2)
{
    QByteArray data2=reply2->readAll();
    QString bids(data2);
    double bidsasdouble = bids.toDouble();
    QString bids2 = QString::number(bidsasdouble/COIN, 'f', 8);
    ui->labelBids->setText(bids2);
}


void BidPage::GetBids()
{

    
    // get current BTC resrve assets
    //double btcassets = r.getbalance("https://blockchain.info/q/addressbalance/16bi8R4FoDHfjNJ1RhpvcAEn4Cz78FbtZB");
    //QString reserves = QString::number(btcassets/COIN, 'f', 8);
    //ui->labelReserves->setText(reserves);
    
    // get current bids
    //double bids = r.getbalance("https://blockchain.info/q/addressbalance/1BCRbid2i3wbgqrKtgLGem6ZchcfYbnhNu");
    //QString bidz = QString::number(bids/COIN, 'f', 8);
    //ui->labelBids->setText(bidz);    


}

QString BidPage::pathAppend(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

QString BidPage::getDataDirectory()
{
    return GUIUtil::boostPathToQString(GetDataDir());
}

void BidPage::SummonBTCExplorer()
{
    QDesktopServices::openUrl(QUrl("https://btc.blockr.io/address/info/1UniQ1TiDyGbB7KXejnjUAZMEjLCyiEPe", QUrl::TolerantMode));
}

bool BidPage::fileExists(QString path) 
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    return check_file.exists();
}

void BidPage::RPC()
{
    // check there's something to work with
    if (ui->lineEditPassphrase->text() == "" || ui->lineEditPrivkey->text() == "") 
    {
        QMessageBox::information(0, QString("Attention!"), QString("Please enter your wallet passphrase and the private key of the Bitcoin address you sent your bid from."), QMessageBox::Ok);
        return;
    }
  
    // get working data directory
    QString cwd = GUIUtil::boostPathToQString(GetDataDir());

    // check uniqredit-cli and uniqredit-conf exist in cwd
    QString cli = "uniqredit-cli";
    QString clipath = pathAppend(cwd, cli);
    QString conf = "uniqredit.conf";
    QString confpath = pathAppend(cwd, conf);

   if (!fileExists(clipath) || !fileExists(confpath))
    {
        QMessageBox::information(0, QString("Attention!"), QString("Please make sure that uniqredit-cli(.exe) exists in the same directory as the currently loaded wallet.\n\nYou must also have a uniqredit.conf file present, containing the following:\n\nrpcuser=blah\nrpcpassword=blahblah\nrpcallowip=127.0.0.1\nserver=1\n\nOnce these are in place, please restart uniqredit-qt to proceed."), QMessageBox::Ok);
        return; 
    }

    // get password
    QString pwd = ui->lineEditPassphrase->text();

    // build RPC call
    QString callnix = cwd + "/uniqredit-cli --datadir=" + cwd + " walletpassphrase " + pwd + " 60";
    QString callwin = cwd + "/uniqredit-cli.exe --datadir=" + cwd + " walletpassphrase " + pwd + " 60";

    // unlock wallet
    proc2 = new QProcess(this);
    #ifdef __linux
        proc2->start(callnix);
        proc2->waitForFinished();
        //QString output(proc2->readAllStandardOutput()); // check for any output
    #elif _WIN32
        proc2->start(callwin);
        proc2->waitForFinished();
        //QString output(proc2->readAllStandardOutput()); // check for any output       
    #endif

    // reset pwd field
    ui->lineEditPassphrase->setText("");

    // get privkey
    QString privkey = ui->lineEditPrivkey->text();

    // build RPC call
    QString callnix2 = cwd + "/uniqredit-cli --datadir=" + cwd + " importprivkey " + privkey;
    QString callwin2 = cwd + "/uniqredit-cli.exe --datadir=" + cwd + " importprivkey " + privkey;

    // import privkey
    proc3 = new QProcess(this);
    #ifdef __linux
        proc3->start(callnix2);
        proc3->waitForFinished();
        QString output2(proc3->readAllStandardOutput()); // check for any output
    #elif _WIN32
        proc3->start(callwin2);
        proc3->waitForFinished();
        QString output2(proc3->readAllStandardOutput()); // check for any output
    #endif 
    
    // reset privkey field
    ui->lineEditPrivkey->setText("");   
}

BidPage::~BidPage()
{
    delete ui;
}
