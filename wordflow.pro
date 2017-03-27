TEMPLATE = subdirs

SUBDIRS += \
    translate \
    lib \
    app \
    tests

CONFIG += ordered

translate.SUBDIRS = translate/lib

app.depends = lib
app.depends = translate
tests.depends = lib
