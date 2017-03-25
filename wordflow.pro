TEMPLATE = subdirs

SUBDIRS += \
    lib \
    app \
    translate \
    tests

CONFIG += ordered

app.depends = lib
app.depends = translate\lib
tests.depends = lib
