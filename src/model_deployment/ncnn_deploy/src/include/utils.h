#pragma once
#include "YOLO_ncnn.h"


//��ʾncnn::Mat�е�����
void pretty_print(const ncnn::Mat& m);

//sigmoid�����
float sigmoid(float x);

//���������
void draw_box(cv::Mat& ori_img, const vector<Detect_YOLO::BBoxRect>& results, 
	const vector<string>&class_name, const vector<cv::Scalar>& color, const vector<int>& input_shape);