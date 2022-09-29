TEMPLATE = subdirs

SUBDIRS = \
    Client \
    Player \
    Engine \
    Maps \
    ExchangeLib

unix {
    SOURCES += Maps
}

win32 {
}
