TEMPLATE = subdirs

SUBDIRS += \
    lib \
    app \
    tests

CONFIG += ordered

app.depends = lib
tests.depends = lib
