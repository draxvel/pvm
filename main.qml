import QtQuick 2.0
import QtWebView 1.1
import QtQuick.Window 2.2
import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick 2.2
import QtQuick.Dialogs 1.0

Window
{

    width:  960
    height: 640
    visible: true

    signal qmlSignalClick()
    signal qmlSignalAttachmentClick()
    signal qmlSignal()
    signal qmlSignalPhotoselected()

                WebView
                {
                anchors.fill: parent
                    id: web
                    objectName: "web"
                    visible: true
                    url: "http://oauth.vk.com/authorize?client_id=5521014&v=5.53&scope=messages,wall,photos&redirect_uri=https://oauth.vk.com/blank.html&display=mobile&response_type=token"
                onUrlChanged:
                {
                var url_string = url.toString()
                if (url_string.indexOf("access_token") !== -1)
                {
                     qmlSignal()
                    web.visible=false
                }
                }
                }

                Rectangle
                   {
                   id:backround
                   anchors.fill: parent
                   color: "#F5F5F5"
                      visible: true
                   }

                FileDialog {
                        id: fileDialogLoad
                        folder: shortcuts.home
                        title: "Choose a file to open"
                        selectMultiple: false
                        nameFilters: [ "Image files (*.png *.jpg)", "All files (*)" ]
                        onAccepted:
                        {
                        memo.text =fileUrl
                        qmlSignalPhotoselected()
                        }
                    }



                   Text
               {
                       id:textup
                       text:"Введіть текст і натисніть кнопку"
                       anchors.top: backround.top
                       color:"#B0C4DE"
                       horizontalAlignment : Text.AlignHCenter
                       //x:10
                       width: parent.width
                       height: 40
                       font.pixelSize: 30
               }

//ПОЛЕ ДЛЯ ВВОДУ
                                    Rectangle
                                   {
                                           id: input
                                           x:5
                                           width: parent.width-20
                                           height: parent.height/2
                                           color: "#FFFAF0"
                                           visible:true
                                           anchors.top: textup.bottom
                                           clip: true
                                    }

                                           TextInput
                                   {
                                               id: textinput
                                               objectName: "textinput"
                                               x:10
                                               maximumLength:400000
                                               font.pixelSize: 35
                                               anchors.fill: input
                                               visible:true
                                               color: "#BEBEBE"
                                               wrapMode: "Wrap"
                                   }

//ПРИКРІПИТИ ЗОБРАЖЕННЯ

                               Rectangle
                       {
                                   id: buttonattachment
                                   x:200
                                   objectName: button2
                                  anchors.top:textinput.bottom
                                  width: parent.width-400
                                  height: parent.width/15
                                   visible:true
                                   enabled: false
                                   radius: 10
                                   color:"#F5F5F5"
                       }

                               Text
                       {
                               id:buttonattachmenttext
                               text:"Прикріпити зображення"
                               anchors.fill:buttonattachment
                               font.pixelSize: 20
                               color: "#A9A9A9"

                               horizontalAlignment : Text.AlignHCenter
                               verticalAlignment: Text.AlignVCenter
                       }


                               MouseArea
                                   {
                                   anchors.fill: buttonattachment
                                   onClicked:
                                   {
                                      buttonattachmenttext.color ="#808080"
                                      qmlSignalAttachmentClick()
                                      fileDialogLoad.open();
                                   }
                                   }


//Кнопка
                   Rectangle {
                       id: button
                       objectName: button1
                       x:100
                       y:+50
                       anchors.top:buttonattachment.bottom
                       width: parent.width-200
                       height: parent.width/8
                       visible:true
                       radius: 30

                       Text
                       {
                       text:"Надіслати"
                       anchors.fill:button
                       font.pixelSize: 35
                       color: "#FFDAB9"

                       horizontalAlignment : Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                       }
                       MouseArea
                           {
                           anchors.fill: button
                           onClicked:
                           {
                               button.border.color= "#B0C4DE"
                               button.border.width= 5
                               qmlSignalClick()

                               textinput.clear()
                           }
                           }
                      }

//ПОЛЕ ВИВОДУ
                       Rectangle
                       {
                           id: memoRect
                           anchors.top:button.bottom
                           x:25
                           width: parent.width-50
                           height: 100
                           color: "#F5F5F5"

                           TextEdit
                           {
                           id: memo
                           horizontalAlignment : Text.AlignHCenter
                           font.pixelSize: 30
                           color: "#40E0D0"
                           objectName: "memo"
                           width:parent.width;
                           height:parent.width;
                           readOnly:true
                           }
                       }


 //НАДПИС ЗНИЗУ
                       Text
                       {
                       text:"©2016 Підслухано в Миколаєві"
                       anchors.bottom:backround.bottom
                       horizontalAlignment : Text.AlignHCenter
                       width: parent.width
                       font.pixelSize: 30
                       color:"#B0C4DE"
                       }
}






















