#ifndef P2PLPAGE_H
#define P2PLPAGE_H

#include "clientmodel.h"

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QCoreApplication>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QStringList>
#include <QTimer>
#include <QUrl>

namespace Ui
{
    class P2PLPage;
}

class P2PLPage: public QWidget
{
    Q_OBJECT

public:
    P2PLPage(QWidget *parent = 0);
    ~P2PLPage();

    void setClientModel(ClientModel *model);

private:
    Ui::P2PLPage *ui;
    ClientModel *clientModel;
    
    QNetworkAccessManager *manager;

private Q_SLOTS:
	//void importCSVFile();
    void sendRequest();
    void replyFinished(QNetworkReply *reply);
    void loanRequestSelected(const QItemSelection &, const QItemSelection &);
};

#endif // P2PLPAGE_H
