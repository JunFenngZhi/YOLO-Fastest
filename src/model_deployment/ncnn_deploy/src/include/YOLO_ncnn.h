#pragma once
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

#include "benchmark.h"
#include "cpu.h"
#include "datareader.h"
#include "net.h"
#include "gpu.h"

using namespace std;


//cpu num threads
#define NUMTHREADS 8

class Detect_YOLO
{
public:
	struct BBoxRect
	{
		float cls_score; //������
		float conf; //Ŀ�����Ŷ�
		int xmin;
		int ymin;
		int xmax;
		int ymax;
		int label;  //����ǩ
	};

public:
	Detect_YOLO(const char* paramPath, const char* binPath, const vector<int>&img_size,
		int num_class, float conf_thres, float nms_thres, const vector<vector<float>>&anchors);
	~Detect_YOLO();
	void detect(const cv::Mat& ori_img, vector<BBoxRect>& all_bbox_rects, 
		float& infer_time, float& post_process_time) const;  //��������ͼƬ�����ش����ļ����
	
public:
	ncnn::Net net;
	vector<vector<float>>anchors;//ÿ��ͷ��Ӧһ�У�ÿ������Ϊ��w_1,h_1,w_2,h_2...��
	vector<int> img_size; //(w,h,c)
	float conf_thres;
	float nms_thres;
	int num_anchors;
	int num_class;
	
private:
	int decode_bbox(const vector<ncnn::Mat>& pred, vector<BBoxRect>& all_bbox_rects) const;//�Լ�������н��룬�ָ�Ϊ��ʵ����
	void qsort_descent(vector<BBoxRect>& datas, int left, int right) const; //����conf��������
	void non_maxium_supression(vector<BBoxRect>& bbox_rects) const; //���������bbox���зǼ���ֵ����
	float cal_IOU(const BBoxRect& box_1, const BBoxRect& box_2) const;

};

