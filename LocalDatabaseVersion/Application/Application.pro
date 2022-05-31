QT += quick sql
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        src/contact.cpp \
        main.cpp \
        src/contacts_handler.cpp \
        src/contacts_model.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/qml
QML2_IMPORT_PATH += $$PWD/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/../shared/include
INCLUDEPATH += $$PWD/../DBManager/include

LIBS += -L$$PWD/../shared/lib/ -lDBManager

HEADERS += \
    include/contact.h \
    include/contacts_handler.h \
    include/contacts_model.h

