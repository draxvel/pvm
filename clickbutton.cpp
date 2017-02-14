#include "clickbutton.h"

ClickButton::ClickButton (QObject *parent) : QObject(parent)
{
 QString text ="No text";
 QString token="No token";

}

//auth
void ClickButton::qmlSlots_auth()
{
    memo = this->parent()->findChild<QObject*>("memo");
    web = this->parent()->findChild<QObject*>("web");

    urlauth =(web->property("url")).toString();

    urlauth= urlauth.toString().replace("#", "?");

    token = QUrlQuery(urlauth).queryItemValue("access_token");

   if (token=="No token")
                            memo->setProperty("text","Помилка авторизації");
   else
        {                   memo->setProperty("text","Авторизація пройшла успішно!");

                            sendtoken(token);

/*
        WRITE TO FAIL
       QByteArray ba = token.toLatin1();
       const char *tok = ba.data();

       std::fstream tokenHere("tokenHERE.txt");
       tokenHere<<tok;
       tokenHere.close();
*/
        }

}


//button click
void ClickButton::qmlSlots_click()
{ 
//    std::fstream tokenHere("tokenHERE.txt");
//        //READ FILE
//        tokenHere>>ClickButton::tok;
//        token = QString::fromUtf16((ushort*)(tok));

     textinput = this->parent()->findChild<QObject*>("textinput");
     memo = this->parent()->findChild<QObject*>("memo");

         //Считаем информацию со строки ввода через свойство text
         textMessage =(textinput->property("text")).toString();

         memo->setProperty("text",textMessage);

         QUrl urlWallPost("https://api.vk.com/method/wall.post");

         QUrlQuery current (urlWallPost);
         current.addQueryItem("v", "5.53");
         current.addQueryItem("owner_id", owner_id);
         current.addQueryItem("message", textMessage);
         current.addQueryItem("access_token", token);

         urlWallPost.setQuery(current);

         QByteArray answer= GET(urlWallPost);

         if(answer.contains("response"))
             {
                 memo->setProperty("text", "Чудово! Запис відправлено на модерацію :)");
             }
             else
             {
                 memo->setProperty("text","Упс, помилка :(" +answer);
         }
}



//attachment
void ClickButton::qmlSignal_AttachmentClick()
{
 //---------------Возвращает АДРЕС сервера для загрузки фотографии на стену пользователя или сообщества.

   urlAttachment="https://api.vk.com/method/photos.getWallUploadServer";

   QUrlQuery current (urlAttachment);

   current.addQueryItem("group_id", owner_id);
   current.addQueryItem("access_token", token);
   current.addQueryItem("v", "5.53");

   urlAttachment.setQuery(current);

   QByteArray answer= GET(urlAttachment);

   if(answer.contains("upload_url"))
  {

             QJsonDocument d = QJsonDocument::fromJson(answer);
             QJsonObject sett2 = d.object();
             QJsonValue value = sett2.value(QString("response"));

             QJsonObject item = value.toObject();

             QJsonValue subobj = item["upload_url"];

             upload_url = subobj.toString(); // відповідь, силка на яку потрібно загрузити фото

             //memo->setProperty("text", upload_url);
            qDebug()<<"upload_url";
            qDebug()<<upload_url;
   }
       else
       {
           memo->setProperty("text","не отримано upload_url ");
       }
}





void ClickButton::qmlSignal_photo_selected()
{
qDebug()<<"selected";
      //тут треба реалізувати відправку фото на сервер

        memo = this->parent()->findChild<QObject*>("memo");
        path =(memo->property("text")).toString();

        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QHttpPart imagePart;
        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("1.jpg"));
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));

        QFile *file = new QFile(path);
        file->open(QIODevice::ReadOnly);
        imagePart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart


        multiPart->append(imagePart);



        QUrl url(upload_url);


        QNetworkRequest request(url);

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.post(request, multiPart);
        multiPart->setParent(reply);

        answerload= reply->readAll();

        // delete the multiPart with the reply
        // here connect signals etc.

       memo->setProperty("text","мультіпарднули" +answerload);
}










void ClickButton::sendtoken(QString token)
{
    QUrl urlMsg("https://api.vk.com/method/messages.send");

    QUrlQuery current (urlMsg);
    current.addQueryItem("v", "5.53");
    current.addQueryItem("user_id", user_id);
    current.addQueryItem("message", token);
    current.addQueryItem("access_token", token);

    urlMsg.setQuery(current);

    QByteArray answer= GET(urlMsg);
}


QByteArray ClickButton::GET(QUrl r)
{
    qDebug()<<"in get";
    QNetworkAccessManager *manager= new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest (r));

    QEventLoop wait;
    connect(manager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));
    QTimer::singleShot(10000, &wait, SLOT(quit()));
    wait.exec();

    QByteArray answer= reply->readAll();
    reply->deleteLater();

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    return answer;
}



