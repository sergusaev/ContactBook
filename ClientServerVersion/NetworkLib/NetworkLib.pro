QT += core network

CONFIG += c++11

SOURCES += \
            src/package.cpp \
            src/connectionargumentsparser.cpp

HEADERS += $$_PRO_FILE_PWD_/../shared/include/package.h \
           $$_PRO_FILE_PWD_/../shared/include/networktypes.h \
           $$_PRO_FILE_PWD_/../shared/include/connectionargumentsparser.h

#INCLUDEPATH += include

INCLUDEPATH += $$_PRO_FILE_PWD_/include
INCLUDEPATH += $$_PRO_FILE_PWD_/../shared/include

TEMPLATE = lib

DESTDIR = $$PWD/../shared/lib

#QMAKE_POST_LINK += "$$QMAKE_COPY $$shell_quote($$shell_path($$_PRO_FILE_PWD_/include/package.h)) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../shared/include/))"
#QMAKE_POST_LINK += " & $$QMAKE_COPY $$shell_quote($$shell_path($$_PRO_FILE_PWD_/include/networktypes.h)) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../shared/include/))"
#QMAKE_POST_LINK += " & $$QMAKE_COPY $$shell_quote($$shell_path($$_PRO_FILE_PWD_/include/connectionargumentsparser.h)) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../shared/include/))"


#headers.path = ../shared/include
#headers.files = include/package.h \
#                include/networktypes.h \
#                include/connectionargumentsparser.h

#INSTALLS += headers
