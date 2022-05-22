QT += core network
QT -= gui

SOURCES += src/main.cpp \
           src/contacts_handler.cpp \
           src/contactsworker.cpp \
           src/servermanager.cpp

HEADERS += include/contacts_handler.h \
           include/contactsworker.h \
           include/servermanager.h


INCLUDEPATH += $$_PRO_FILE_PWD_/include
INCLUDEPATH += $$_PRO_FILE_PWD_/../shared/include

#INCLUDEPATH += include/ \
#               ../shared/include

LIBS += -L$$PWD/../shared/lib -lDBManager
LIBS += -L$$PWD/../shared/lib -lNetworkLib

DEFINES += DEBUG_OUTPUT
