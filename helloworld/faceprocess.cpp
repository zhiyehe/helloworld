#include "faceprocess.h"
#include <QDebug>
#include <stdio.h>
#include <unistd.h>  //包含了Linux C 中的函数getcwd()
#include "mainwindow.h"
#ifdef FORARM
#include <opencv2/opencv.hpp>
#include <zqzn_sdk.h>
#include <zqzn_sdk_helper.h>
#include <HISI.h>
extern MainWindow *w_ptr;
#define FILEPATH_MAX (100)

extern bool bGetData;
extern int bmpSize;
extern unsigned char bmpData[];
using namespace cv;
#define TAG "ZqznSDK"

SDK_HANDLE sdk_handle = 0 ;
void initfaceprocess(void)
{
    SAMPLE_VIO_ViDoublePipeRouteToGetVPSS(0);

    LOGD(TAG, "sdk version:%s", get_sdk_version().c_str());
    string root_path = "/data/run";
    char deviceId[1024];
    int len = 0;

    if (get_device_id(deviceId, &len)) {
        LOGD(TAG, "device_id:%s", deviceId);
    }

    sdk_handle = init_for_evaluate(root_path.c_str());
    if (sdk_handle > 0)
    {
        LOGE(TAG, "init_for_evaluate OK,sdk_handle:%lld", sdk_handle);
    }
    else
    {
        LOGE(TAG, "init_for_evaluate failed,sdk_handle:%lld", sdk_handle);
    }

    return;
}

extern "C" {
void callback(unsigned char* rgb_ptr, int size)
{
    //qDebug()<<"in c++ callback, size"<<size;
    //LOGD(TAG, "sdk version:%s\n", get_sdk_version().c_str());
    if(bGetData and sdk_handle)
    {
       memcpy(bmpData, rgb_ptr, size);
       bmpSize = size;
    }

    if (sdk_handle > 0) {
        LOGD(TAG, "algos version:%s\n", print_algos_version(sdk_handle).c_str());
        int ret = 0;
        vector<FaceData> out_face_datas;
        FaceData maxFaceData;
        Mat vis_img_mat;
        Mat img_mat(360, 640, CV_8UC1, rgb_ptr);
        ret = detect_face(sdk_handle, img_mat.data, img_mat.cols, img_mat.rows, out_face_datas);
        if (ret == PROCESS_OK) {
            // string facedata_str=print_facedata(out_face_datas[0]);
            // LOGD(TAG,"detect_face ok,first facedata:\n%s", facedata_str.c_str());
            w_ptr->showfacedectetresult(1);
            LOGD(TAG, "detect_face ok, facedata size:%d", (int)out_face_datas.size());
        } else {
            w_ptr->showfacedectetresult(0);
            LOGE(TAG, "detect_face failed,ret:%d", ret);
            return;
        }
    }
}

}
#endif
