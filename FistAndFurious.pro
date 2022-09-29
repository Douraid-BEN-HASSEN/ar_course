TEMPLATE = subdirs

SUBDIRS = \
    Client \
    Player \
    Engine \
    ExchangeLib \
    Maps \

unix {
    SOURCES += Maps
}

win32 {
}
