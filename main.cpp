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

//debug ��64λ
//��Ŀ�������ԡ���C/C++����Ԥ����������Ԥ���������塪���Ҳ��������С��༭�������ڵ�һ���༭�������_CRT_SECURE_NO_WARNINGS�����󹦸��