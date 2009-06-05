#
# Qxt main project file
#
# Do not edit this file.
# Use config.pri to specify compile options.
#
unix:!macx:include(features/unix/qxtbuild.prf)
win32:include(features/win32/qxtbuild.prf)
macx:include(features/macx/qxtbuild.prf)

TEMPLATE = subdirs
DESTDIR  = deploy/libs

#check Qt version
QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")
QT_VER_MAJ = $$member(QT_VERSION, 0)
QT_VER_MIN = $$member(QT_VERSION, 1)

lessThan(QT_VER_MAJ, 4) | lessThan(QT_VER_MIN, 2) {
   error(LibQxt requires Qt 4.2 or newer but Qt $$[QT_VERSION] was detected.)
}

win32:!win32-g++ {
    unixstyle = false
} else :win32-g++:isEmpty(QMAKE_SH) {
    unixstyle = false
} else {
    unixstyle = true
}

$$unixstyle {
    QDOC = QXTDIR=$$PWD $$PWD/tools/3rdparty/qdoc3/qdoc3
} else {
    QDOC = set QXTDIR=$$PWD&& $$PWD/tools/3rdparty/qdoc3/qdoc3.exe
    QDOC = $$replace(QDOC, "/", "\\\\")
}

SUBDIRS += tools/3rdparty/qdoc3

adp_docs.commands = ($$QDOC -DQXT_DOXYGEN_RUN $$PWD/doc/src/qxt.qdocconf)
adp_docs.depends += sub-tools-3rdparty-qdoc3
docs.depends = adp_docs
QMAKE_EXTRA_TARGETS += qdoc adp_docs docs

docs.files = doc/html/*
docs.path = $${QXTINSTALLDIR}/doc
docs.CONFIG = no_default_install

features.path = $$[QT_INSTALL_DATA]/mkspecs/features
features.files = deploy/qt/qxt.prf

INSTALLS += features

exists( modules.prf ) {
    unix:system(rm -f modules.prf)
    win32:system(del modules.prf)
}

contains( QXT_BUILD, core ){
    message( building core module )
    sub_core.subdir = src/core
    SUBDIRS += sub_core
    system(echo QXT_MODULES+=core >> modules.prf)
}

contains( QXT_BUILD, gui ){
    message( building gui module )
    sub_gui.subdir = src/gui
    sub_gui.depends = sub_core
    SUBDIRS += sub_gui
    system(echo QXT_MODULES+=gui >> modules.prf)
    contains( QXT_BUILD, designer ){
        sub_designer.subdir = src/designer
        sub_designer.depends = sub_core sub_gui
        SUBDIRS += sub_designer
        system(echo QXT_MODULES+=designer >> modules.prf)
    }
}

contains( QXT_BUILD, network ){
    message( building network module )
    sub_network.subdir = src/network
    sub_network.depends = sub_core
    SUBDIRS += sub_network
    system(echo QXT_MODULES+=network >> modules.prf)
}

contains( QXT_BUILD, sql ){
    message( building sql module )
    sub_sql.subdir = src/sql
    sub_sql.depends = sub_core
    SUBDIRS += sub_sql
    system(echo QXT_MODULES+=sql >> modules.prf)
}

contains(DEFINES,HAVE_DB){
contains( QXT_BUILD, berkeley ){
    message( building berkeley module )
    sub_berkeley.subdir = src/berkeley
    sub_berkeley.depends = sub_core
    SUBDIRS += sub_berkeley
    system(echo QXT_MODULES+=berkeley >> modules.prf)
}
}

contains(DEFINES,HAVE_ZEROCONF){
contains( QXT_BUILD, zeroconf ){
    message( building zeroconf module )
    sub_zeroconf.subdir = src/zeroconf
    sub_zeroconf.depends = sub_network
    SUBDIRS += sub_zeroconf
}
}

contains( QXT_BUILD, web ){
    message( building web module )
    sub_web.subdir = src/web
    sub_web.depends = sub_core sub_network
    SUBDIRS += sub_web
    system(echo QXT_MODULES+=web >> modules.prf)
}

QMAKE_CLEAN += modules.prf

#write the paths to prf file
unix:system((echo QXTbase=$${QXTINSTALLDIR}; echo QXTinclude=$${include.path}; echo QXTbin=$${bin.path}; echo QXTlib=$${target.path}; cat modules.prf; cat deploy/qt/qxt.prf.m) > deploy/qt/qxt.prf)

#windows supports similar syntax
win32:system((echo QXTbase=$${QXTINSTALLDIR}& echo QXTinclude=$${include.path} & echo QXTbin=$${bin.path} & echo QXTlib=$${target.path} & type modules.prf & type deploy\qt\qxt.prf.m) > deploy\qt\qxt.prf)

style.CONFIG = recursive
style.recurse = $$SUBDIRS
style.recurse_target = astyle
QMAKE_EXTRA_TARGETS += style

sub-examples.commands += cd examples && $(QMAKE) examples.pro && $(MAKE)
QMAKE_EXTRA_TARGETS += sub-examples

sub-tests.commands += cd tests && $(QMAKE) tests.pro && $(MAKE)
QMAKE_EXTRA_TARGETS += sub-tests

runtests.depends += sub-tests
runtests.commands += cd tests && $(MAKE) test
QMAKE_EXTRA_TARGETS += runtests

cov_zerocounters.CONFIG += recursive
cov_zerocounters.recurse = $$SUBDIRS
cov_zerocounters.recurse -= sub_designer
cov_zerocounters.recurse_target = zerocounters
QMAKE_EXTRA_UNIX_TARGETS += cov_zerocounters

cov_capture.CONFIG += recursive
cov_capture.recurse = $$SUBDIRS
cov_capture.recurse -= sub_designer
cov_capture.recurse -= sub_sql # TODO: write unit tests for these!
cov_capture.recurse_target = capture
QMAKE_EXTRA_UNIX_TARGETS += cov_capture

cov_genhtml.CONFIG += recursive
cov_genhtml.recurse = $$SUBDIRS
cov_genhtml.recurse -= sub_designer
cov_genhtml.recurse -= sub_sql # TODO: write unit tests for these!
cov_genhtml.recurse_target = genhtml
QMAKE_EXTRA_UNIX_TARGETS += cov_genhtml

coverage.depends += first cov_zerocounters runtests cov_capture cov_genhtml
QMAKE_EXTRA_UNIX_TARGETS += coverage
