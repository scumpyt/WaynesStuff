TEMPLATE = subdirs

SUBDIRS += \
    main \
    UnitTests \
    cppSrc

main.depends = cppSrc
UnitTests.depends = cppSrc
