#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <clickbutton.h>
#include <fstream>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


 //  std:: ofstream tokenHere("tokenHERE.txt"); //создать
// std::  fstream tokenHere( QString("tokenHERE.txt").toLatin1().constData() );
//    // создаём объект для чтения файла
//    std::ifstream tokenHereR("tokenHere.txt");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//-----------
        //находим корневой объект в QML модели
        QObject* root = engine.rootObjects()[0];

        //экземпляр нашего класса
        ClickButton *click = new ClickButton(root);


        //связываем наш слот из класса и сигнал из qml файла

//        if(!(tokenHere.eof()))
//           {
        QObject::connect(root, SIGNAL(qmlSignal()),click,SLOT(qmlSlots_auth()));
//           }


        QObject::connect(root,SIGNAL(qmlSignalClick()),click,SLOT(qmlSlots_click()));

        QObject::connect(root,SIGNAL(qmlSignalAttachmentClick()),click,SLOT(qmlSignal_AttachmentClick()));

        QObject::connect(root,SIGNAL(qmlSignalPhotoselected()),click, SLOT (qmlSignal_photo_selected()));


//-----------

    return app.exec();
}
