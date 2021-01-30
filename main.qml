import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "ImageGallery"

    Connections {
        target: galleryclient
        function onImageReceived() {
            localstorage.insertRecord(galleryclient.image);
            dst.entry = galleryclient.image;
        }
    }


    TabView {
        id: tabs
        anchors.fill: parent

        onCurrentIndexChanged: { if (tabs.currentIndex == 1) galleryclient.onEntry(); else galleryclient.onExit() }

        Tab {
            id: src
            title: "GalleryServer"

            ColumnLayout {
                anchors.fill:parent

                ComboBox {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                    id: selector
                    textRole: "title"
                    model: gallery.titles;

                    onCurrentIndexChanged: { galleryserver.onItemChanged(selector.currentText) }
                }
            }
        }

        Tab {
            id: dst
            title: "GalleryClient"
            property var entry: galleryclient.noimage;

            ColumnLayout {
                anchors.fill: parent

                TextField {
                    Layout.fillWidth: true
                    id: titleinput
                    placeholderText: "Enter image title"

                    function titleEntered(title) {
                        if (localstorage.hasRecord(title)) {
                            dst.entry = localstorage.getRecord(title);
                        }
                        else {
                            galleryclient.onTitleEntered(title);
                        }
                    }

                    onAccepted: { console.log("edited " + text); titleEntered(text) }
                }

                ColumnLayout {
                    Layout.fillWidth: true

                    Image {
                        id: content
                        fillMode: Image.PreserveAspectFit
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        source: dst.entry.url
                    }
                }

                Label {
                    Layout.alignment: Qt.AlignCenter
                    id: title
                    text: dst.entry.title
                }

                Button {
                    Layout.alignment: Qt.AlignCenter
                    id: action
                    text: "Delete Local Record"

                    function recordDeleted(entry) {
                        localstorage.deleteRecord(entry);

                        if (!localstorage.isEmpty()) {
                            dst.entry = localstorage.getRandomRecord();
                        }
                        else {
                            dst.entry = galleryclient.noimage;
                        }
                    }

                    onClicked: recordDeleted(entry.title)
                }
            }
        }
    }
}
