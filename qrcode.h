#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

//��ά���С
#define one_block_width 10
#define left_blank 0
#define IMG_X 100 * one_block_width//��������ά��߿�
#define IMG_Y 100 * one_block_width
#define anchor_size 10 * one_block_width
#define anchor_blank 1 * one_block_width//��Ĵ�ϸ
#define no_of_frame 10//��ÿ�Ŷ�ά��ǰ�����ǵڼ�֡
//ÿ����ά��������������
#define MAX_CHAR (IMG_X / one_block_width * IMG_Y / one_block_width) - 3 * (anchor_size / one_block_width * anchor_size / one_block_width) - no_of_frame
#pragma once
class QRcode
{
	FILE* input_file;

public:
	void draw_png(char* input_file_name);
	Mat draw_pure_white(int a, int b);
	Mat bin_to_png(bool* str, int size);
	void draw_anchors(Mat& image);
	void char_to_bool(char* a, int length, bool* b);
};

