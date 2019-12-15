#include "faceprocess.h"
#include <HISI.h>
#include <stdio.h>
#include <unistd.h>  //包含了Linux C 中的函数getcwd()
#include <opencv2/opencv.hpp>
#include <zqzn_sdk.h>
#include <zqzn_sdk_helper.h>

#define FILEPATH_MAX (100)
string root_path = "";
string serial_no = "YMA6-JA8B-4D78-ER97";
string vis_face_file = "vis_test.jpg";
string nir_face_file = "nir_test.jpg";
string video_file = "test.mp4";
string db_file = "person.db";
using namespace cv;
#define TAG "ZqznSDK"

int test_detect_vis_image(SDK_HANDLE sdk_handle, vector<FaceData> &out_face_datas, Mat &img_mat) {
    img_mat = imread(vis_face_file, IMREAD_COLOR);
    int ret = detect_face(sdk_handle, img_mat.data, img_mat.cols, img_mat.rows, out_face_datas);
    if (ret == PROCESS_OK) {
        // string facedata_str=print_facedata(out_face_datas[0]);
        // LOGD(TAG,"detect_face ok,first facedata:\n%s", facedata_str.c_str());
        LOGD(TAG, "detect_face ok, facedata size:%d", (int)out_face_datas.size());
    } else {
        LOGE(TAG, "detect_face failed,ret:%d", ret);
        return 1;
    }
    return ret;
}
int test_detect_vis_image_maxface(SDK_HANDLE sdk_handle, FaceData &out_face_data, Mat &img_mat) {
    img_mat = imread(vis_face_file, IMREAD_COLOR);
    int ret = detect_max_face(sdk_handle, img_mat.data, img_mat.cols, img_mat.rows, out_face_data);
    if (ret == PROCESS_OK) {
        // string facedata_str=print_facedata(out_face_data);
        // LOGD(TAG,"detect_max_face ok,max facedata:\n%s", facedata_str.c_str());
        LOGD(TAG, "detect_max_face ok");
    } else {
        LOGE(TAG, "detect_max_face failed,ret:%d", ret);
        return 1;
    }
    return ret;
}
int test_quality_detect(SDK_HANDLE sdk_handle, Mat &img_mat, FaceData &faceData) {
    int ret =
        quality_detect(sdk_handle, img_mat.data, img_mat.cols, img_mat.rows, faceData, true, true, true, true, true);
    if (ret == PROCESS_OK) {
        // string facedata_str=print_facedata(faceData);
        // LOGD(TAG,"qulity_detect ok, facedata:\n%s", facedata_str.c_str());
        LOGD(TAG, "quality_detect ok");
    } else {
        LOGE(TAG, "quality_detect failed,ret:%d", ret);
        return 1;
    }
    return ret;
}
int test_extract_feature(SDK_HANDLE sdk_handle, Mat &img_mat, FaceData &faceData) {
    int ret = extract_feature(sdk_handle, img_mat.data, img_mat.cols, img_mat.rows, faceData);
    if (ret == PROCESS_OK) {
        // string facedata_str=print_facedata(faceData);

        // LOGD(TAG,"test_extract_feature ok, feature_len=%d,facedata:\n%s",
        // maxFaceData.features.size(),facedata_str.c_str());
        LOGD(TAG, "extract_feature ok,feature size:%d", (int)faceData.features.size());
    } else {
        LOGE(TAG, "extract_feature failed,ret:%d", ret);
        return 1;
    }
    return ret;
}
int test_safetyhelmet_detect(SDK_HANDLE sdk_handle, Mat &img_mat, FaceData &faceData) {
    int ret = safetyhelmet_detect(sdk_handle, img_mat.data, img_mat.cols, img_mat.rows, faceData);
    if (ret == PROCESS_OK) {
        LOGD(TAG, "safetyhelmet_detect ok,safetyhelmet score:%d", (int)faceData.safetyhelmet_on);
    } else {
        LOGE(TAG, "safetyhelmet_detect failed,ret:%d", ret);
        return 1;
    }
    return ret;
}

int test_add_and_search_person(SDK_HANDLE sdk_handle, FaceData &faceData, PERSONID personid, string &person_code) {
    FaceData emptyFaceData;
    int ret = put_person_by_face(sdk_handle, personid, person_code, "{}", 0, faceData, emptyFaceData);
    if (ret != PROCESS_OK) {
        LOGE(TAG, "put_person_by_face failed,ret:%d", ret);
        return 1;
    }
    LOGD(TAG, "add_person_by_face ok");

    vector<SearchPerson> search_persons;
    ret = search_person_by_face(sdk_handle, faceData, 1, search_persons);
    if (ret != PROCESS_OK) {
        LOGD(TAG, "search_person_by_face failed,ret:%d", ret);
        return 1;
    } else {
        for (int i = 0; i < search_persons.size(); i++) {
            SearchPerson search_person = search_persons[i];
            LOGD(TAG, "search_person ok,person_id=%lld,face_id=%lld,sim=%f,person_code=%s", search_person.person_id,
                 search_person.face_id, search_person.similarity, search_person.person_code.c_str());
        }
    }
    string code, data;
    int group;
    ret = get_person_info(sdk_handle, personid, code, data, &group);
    if (ret == PROCESS_OK) {
        LOGD(TAG, "get_person_info ok,person_code:%s", code.c_str());
    } else {
        LOGE(TAG, "get_person_info failed,ret:%d", ret);
    }
    return ret;
}

int test_visliveness_detect(SDK_HANDLE sdk_handle, Mat &img_mat, FaceData &faceData) {
    int ret = visliveness_detect(sdk_handle, img_mat.data, img_mat.cols, img_mat.rows, faceData, true);
    if (ret == PROCESS_OK) {
        // string facedata_str=print_facedata(faceData);
        // LOGD(TAG,"visliveness_detect ok, facedata:\n%s", facedata_str.c_str());
    } else {
        LOGE(TAG, "visliveness_detect failed,ret:%d", ret);
        return 1;
    }
    return ret;
}
void test_read_nir_image(Mat &nir_image_mat) { nir_image_mat = imread(vis_face_file, IMREAD_COLOR); }

int test_nirliveness_detect(SDK_HANDLE sdk_handle, Mat &img_mat, Mat &nir_image_mat, FaceData &vis_facedata,
                            FaceData &nirFaceData) {
    straw_hat::Point delt;
    delt.y = 0;
    delt.x = 0;
    int ret = nirliveness_detect(sdk_handle, img_mat.data, img_mat.cols, img_mat.rows, nir_image_mat.data,
                                 nir_image_mat.cols, nir_image_mat.rows, vis_facedata, nirFaceData, delt, true, true);
    LOGD(TAG, "face time:%s", print_time(vis_facedata.face_time).c_str());
    if (ret == PROCESS_OK) {
        // string facedata_str=print_facedata(vis_facedata);
        // LOGD(TAG,"nirliveness_detect ok,  facedata:\n%s", facedata_str.c_str());
        LOGD(TAG, "nirliveness_detect ok,liveness_score=%f", vis_facedata.liveness_score);

    } else {
        LOGE(TAG, "nirliveness_detect failed,ret:%d", ret);
        return 1;
    }
    return ret;
}
int test_face_compare(SDK_HANDLE sdk_handle, Mat &img_mat, Mat &nir_image_mat, double &sim) {
    int ret = face_compare(sdk_handle, img_mat.data, img_mat.cols, img_mat.rows, nir_image_mat.data, nir_image_mat.cols,
                           nir_image_mat.rows, sim);
    if (ret == PROCESS_OK) {
        LOGD(TAG, "face_compare ok,  sim:%f", sim);

    } else {
        LOGE(TAG, "face_compare failed,ret:%d", ret);
        return 1;
    }
    return ret;
}

int test_person_face_count(SDK_HANDLE sdk_handle) {
    int count = 0;
    int ret = get_persons_count(sdk_handle, count);
    if (ret == 0) {
        LOGD(TAG, "get_persons_count ok,  persons count:%d", count);
    } else {
        LOGE(TAG, "get_persons_count failed,ret:%d", ret);
        return 1;
    }
    ret = get_faces_count(sdk_handle, count);
    if (ret == 0) {
        LOGD(TAG, "get_faces_count ok,  faces count:%d", count);
    } else {
        LOGE(TAG, "get_faces_count failed,ret:%d", ret);
        return 1;
    }
    return ret;
}
int test_update_remove_clear_person(SDK_HANDLE sdk_handle, PERSONID personid, float *feature, int len) {
    int ret = update_person(sdk_handle, personid, "tony ma", "{aa}", 1);
    if (ret != PROCESS_OK) {
        LOGE(TAG, "update_person failed,ret:%d", ret);
    }
    LOGD(TAG, "%s", "update_person ok");
    ret = update_person_face(sdk_handle, personid, feature, len, nullptr, 0);
    if (ret != PROCESS_OK) {
        LOGE(TAG, "update_person failed,ret:%d", ret);
        return ret;
    }
    LOGD(TAG, "%s", "update_person_face ok");
    ret = remove_person_face2(sdk_handle, personid);
    if (ret != PROCESS_OK) {
        LOGE(TAG, "remove_person_face failed,ret:%d", ret);
    }
    LOGD(TAG, "%s", "remove_person_face ok");
    ret = remove_person(sdk_handle, personid);
    if (ret != PROCESS_OK) {
        LOGE(TAG, "remove_person failed,ret:%d", ret);
        return ret;
    }
    LOGD(TAG, "%s", "remove_person ok");
    ret = clear_persons(sdk_handle);
    if (ret != PROCESS_OK) {
        LOGE(TAG, "clear_persons failed,ret:%d", ret);
        return ret;
    }
    LOGD(TAG, "%s", "clear_persons ok");
    return ret;
}

SDK_HANDLE init_for_evaluate(const char* a)
{
   return 0;
}

int test_image() {
    char deviceId[1024];
    int len = 0;
    if (get_device_id(deviceId, &len)) {
        LOGD(TAG, "device_id:%s", deviceId);
    }
    SDK_HANDLE sdk_handle = init_for_evaluate(root_path.c_str());
    if (sdk_handle > 0) {
        LOGD(TAG, "algos version:%s", print_algos_version(sdk_handle).c_str());
        int ret = 0;
        vector<FaceData> out_face_datas;
        FaceData maxFaceData;
        Mat vis_img_mat;
        ret = test_detect_vis_image(sdk_handle, out_face_datas, vis_img_mat);
        if (ret != 0) return ret;
        ret = test_detect_vis_image_maxface(sdk_handle, maxFaceData, vis_img_mat);
        if (ret != 0) return ret;
        ret = test_safetyhelmet_detect(sdk_handle, vis_img_mat, maxFaceData);
        if (ret != 0) return ret;
        ret = test_quality_detect(sdk_handle, vis_img_mat, maxFaceData);
        if (ret != 0) return ret;
        ret = test_extract_feature(sdk_handle, vis_img_mat, maxFaceData);
        if (ret != 0) return ret;
        PERSONID personid = 0;
        string person_code = "jackey ma";
        ret = test_add_and_search_person(sdk_handle, maxFaceData, personid, person_code);
        if (ret != 0) return ret;
        ret = test_visliveness_detect(sdk_handle, vis_img_mat, maxFaceData);
        if (ret != 0) return ret;
        Mat nir_img_mat;
        test_read_nir_image(nir_img_mat);
        FaceData nirFaceData;
        ret = test_nirliveness_detect(sdk_handle, vis_img_mat, nir_img_mat, maxFaceData, nirFaceData);
        if (ret != 0) return ret;
        double sim = 0.0;
        ret = test_face_compare(sdk_handle, vis_img_mat, nir_img_mat, sim);
        if (ret != 0) return ret;
        ret = test_person_face_count(sdk_handle);
        if (ret != 0) return ret;
        float *nir_feature = (float *)malloc(nirFaceData.features.size() * sizeof(float));
        convert_vector_to_array_float(nirFaceData.features, nir_feature);
        ret = test_update_remove_clear_person(sdk_handle, personid, nir_feature, nirFaceData.features.size());
        free(nir_feature);
        release_sdk(sdk_handle);
        return ret;
    } else {
        LOGE(TAG, "init_for_evaluate failed,sdk_handle:%lld", sdk_handle);
        return 1;
    }
}

string read_serial_no(string file_path) {
    FILE *file = fopen(file_path.c_str(), "r");
    if (file != NULL) {
        char buf[20];
        int len = fread(buf, 1, sizeof(buf), file);
        fclose(file);
        return string(buf, len);
    }
    return "";
}

void initfaceprocess(void)
{
    SAMPLE_VIO_Rotate(0);
    return;
}

bool isProduct;
int faceprocess(void) {
    isProduct = true;
    LOGD(TAG, "Usage:%s",
         "zqzn_face_test [env] [option] [root_path],env default value is 0(test),option default value is "
         "0(image),root_path default value is current dir");
    LOGD(TAG, "sdk version:%s", get_sdk_version().c_str());
    int option = 0;
    char root_path_dir[FILEPATH_MAX] = {0};
    getcwd(root_path_dir, FILEPATH_MAX);
#if 0
    if (argc > 1) {
        isProduct = argv[1][0] == '1';
    }
    if (argc > 2) {
        option = argv[2][0] - '0';
    }
    if (argc > 3) {
        memset(root_path_dir, 0, sizeof(root_path_dir));
        memcpy(root_path_dir, argv[3], strlen(argv[3]));
    }
#endif
    root_path = string(root_path_dir, strlen(root_path_dir));
    string sn = read_serial_no(string(root_path).append("/serial_no.txt"));
    if (sn.length() > 0) serial_no = sn;
    if (option == 0) {
        vis_face_file = string(root_path).append("/").append(vis_face_file);
        nir_face_file = string(root_path).append("/").append(nir_face_file);
        test_image();
    }
    return 0;
}
