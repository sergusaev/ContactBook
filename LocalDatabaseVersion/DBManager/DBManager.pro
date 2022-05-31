QT -= gui
QT += core sql
CONFIG += c++11
TEMPLATE = lib

DESTDIR = $$PWD/../shared/lib

INCLUDEPATH += $$PWD/include

DEFINES +=

HEADERS += \
    include/connectionmanager.h \
    include/dbmapper.h \
    include/executor.h \
    include/dbtypes.h \
    include/manipulator.h \
    include/selector.h \
    include/processor.h


QMAKE_POST_LINK += "$$QMAKE_COPY $$shell_quote($$shell_path($$_PRO_FILE_PWD_/include/processor.h)) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../shared/include/))"
QMAKE_POST_LINK += " & $$QMAKE_COPY $$shell_quote($$shell_path($$_PRO_FILE_PWD_/include/manipulator.h)) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../shared/include/))"
QMAKE_POST_LINK += " & $$QMAKE_COPY $$shell_quote($$shell_path($$_PRO_FILE_PWD_/include/dbtypes.h)) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../shared/include/))"

SOURCES += \
    src/connectionmanager.cpp \
    src/manipulator.cpp \
    src/processor.cpp \
    src/selector.cpp \
    src/executor.cpp


#headers.path = $$PWD/../shared/include
#headers.files =  include/dbtypes.h \
#                 include/processor.h

#INSTALLS += headers
