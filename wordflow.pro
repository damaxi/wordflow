TEMPLATE = subdirs

SUBDIRS += \
    lib \
    app \
    translate \
    tests

CONFIG += ordered

app.depends = lib
app.depends = translate
tests.depends = lib
