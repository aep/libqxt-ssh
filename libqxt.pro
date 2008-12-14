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

#write the paths to prf file
unix:system((echo QXTbase=$${QXTINSTALLDIR}; echo QXTinclude=$${include.path}; echo QXTbin=$${bin.path}; echo QXTlib=$${target.path}; cat deploy/qt/qxt.prf.m) > deploy/qt/qxt.prf)

#windows supports similar syntax
win32:system((echo QXTbase=$${QXTINSTALLDIR}& echo QXTinclude=$${include.path} & echo QXTbin=$${bin.path} & echo QXTlib=$${target.path} & type deploy\qt\qxt.prf.m) > deploy\qt\qxt.prf)

docs.files = deploy/docs/*
#docs.commands = assistant -addContentFile $${docs.path}/index.dcf
docs.commands = $$qxtNativeSeparators(tools/doqsy/doqsy)

features.path = $$[QT_INSTALL_DATA]/mkspecs/features
features.files = deploy/qt/qxt.prf

docs.path = $${QXTINSTALLDIR}/docs
docs.CONFIG = no_default_install

INSTALLS += features docs

SUBDIRS += tools/doqsy
QMAKE_EXTRA_TARGETS += docs

contains( QXT_BUILD, core ){
    message( building core module )
    sub_core.subdir = src/core
    SUBDIRS += sub_core	
}


contains( QXT_BUILD, gui ){
    message( building gui module )
    sub_gui.subdir = src/gui
    sub_gui.depends = sub_core
    SUBDIRS += sub_gui
    contains( QXT_BUILD, designer ){
        sub_designer.subdir = src/designer
        sub_designer.depends = sub_core sub_gui
        SUBDIRS += sub_designer
    }
}

contains( QXT_BUILD, network ){
    message( building network module )
    sub_network.subdir = src/network
    sub_network.depends = sub_core
    SUBDIRS += sub_network

}

contains( QXT_BUILD, sql ){
    message( building sql module )
    sub_sql.subdir = src/sql
    sub_sql.depends = sub_core
    SUBDIRS += sub_sql

}

contains(DEFINES,HAVE_DB){
contains( QXT_BUILD, berkeley ){
    message( building berkeley module )
    sub_berkeley.subdir = src/berkeley
    sub_berkeley.depends = sub_core
    SUBDIRS += sub_berkeley

}
}

contains( QXT_BUILD, web ){
    message( building web module )
    sub_web.subdir = src/web
    sub_web.depends = sub_core sub_network
    SUBDIRS += sub_web

}
contains( QXT_BUILD, crypto ){
    message( building crypto module )
    sub_crypto.subdir = src/crypto
    sub_crypto.depends = sub_core
    SUBDIRS += sub_crypto
}

contains(DEFINES,HAVE_VIRAL){
contains( QXT_BUILD, viral ){
    message( building viral module )
    sub_viral.subdir = src/viral
    sub_viral.depends = sub_core
    SUBDIRS += sub_viral
}
}

style.CONFIG = recursive
style.recurse = $$SUBDIRS
style.recurse -= tools/doqsy
style.recurse_target = astyle
QMAKE_EXTRA_TARGETS += style









