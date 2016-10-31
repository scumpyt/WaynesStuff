TEMPLATE = subdirs

SUBDIRS += \
    main \
    CppSrc \
    UnitTests

main.depends = CppSrc
#UnitTests.depends = CppSrc
