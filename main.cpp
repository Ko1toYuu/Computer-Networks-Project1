#include <opencv2/opencv.hpp>
#include <iostream>
#include "qrcode.h"

using namespace std;
using namespace cv;

int main()
{
    QRcode qr;
    char test[] = "C:\\Users\\BD\\Desktop\\Project\\test.txt";
    qr.draw_png(test);
}

//debug 改64位
//项目——属性——C/C++——预处理器——预处理器定义——右侧下拉框中“编辑”——在第一个编辑框中添加_CRT_SECURE_NO_WARNINGS——大功告成