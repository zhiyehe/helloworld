#-------------------------------------------------
#
# Project created by QtCreator 2019-10-14T21:38:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloworld
TEMPLATE = app

CONFIG += debug_and_release

SOURCES += main.cpp \
    mainwindow.cpp \
    workthread.cpp \
    faceprocess.cpp

HEADERS  += \
    mainwindow.h \
    workthread.h \
    faceprocess.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -O0
#hisisdk
INCLUDEPATH += /data/HISILIB
LIBS += -L/data/HISILIB -lHISI -lsns_imx307_2l -lsns_imx327 -lsns_imx415 -lsns_os04b10 -lsns_ov12870 -lisp -lsns_imx307 -lsns_imx335 -lsns_imx458 -lsns_os05a -lsns_sc4210 \
-lsns_gc2053 -lsns_imx327_2l -lsns_imx335_forcar -lsns_mn34220 -lsns_os08a10
INCLUDEPATH += /home/haisi/Hi3516CV500_SDK_V2.0.2.0/package/mpp/include
LIBS += -L/home/haisi/Hi3516CV500_SDK_V2.0.2.0/package/mpp/lib -lmpi -live -lsecurec -lmd -lnnie -lupvqe -ldnvqe -lVoiceEngine -lhdmi -lisp -l_hiae -l_hiawb -l_hidrc -l_hidehaze -l_hildci -l_hicalcflicker

#opencv
INCLUDEPATH += /data/opencv/include
LIBS += -L/data/opencv/lib -lopencv_stitching -lopencv_superres -lopencv_objdetect -lopencv_dnn -lopencv_ml -lopencv_videostab -lopencv_photo -lopencv_shape -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_video -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core

#algosdk
INCLUDEPATH += /data/zqzn_sdk/sdk_include
LIBS += -L/data/zqzn_sdk/sdk_lib -lzqznfacecore
LIBS += -L/data/zqzn_sdk/depends -lcurl -lssl -lcrypto -lgomp
