TEMPLATE = subdirs

SUBDIRS = \
    Client \
    Player \
    Engine \
    ExchangeLib

unix {
    SOURCES += Maps
}

win32 {
}
