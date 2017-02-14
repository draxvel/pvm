#ifndef CLICKBUTTON_H
#define CLICKBUTTON_H
#include <QObject>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QEventLoop>

#include <fstream>
#include <string>

class ClickButton: public QObject
{
    Q_OBJECT
public:
    explicit ClickButton(QObject *parent = 0);

    ClickButton();
    QByteArray GET(QUrl r);


    QString token = "67e066240ec780a2e14067bd83b2e69d4807594336267d7d3598ac1ad77e64f0d20910289b71f9096bcda";
    //char *tok;
    QString owner_id = "-70768705";
    QString upload_url;
    QString user_id="71443393";

    QString path;
    QByteArray answerload;

    QObject* web;
    QObject* memo;
    QObject* textinput;


    void sendtoken(QString);

public slots:
   void qmlSlots_auth();
   void qmlSlots_click();

   void qmlSignal_AttachmentClick();
   void qmlSignal_photo_selected();
private:
    QUrl urlauth;
    QString textMessage;
    QUrl urlAttachment;
};

#endif // CLICKBUTTON_H
