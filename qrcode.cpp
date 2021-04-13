#include "qrcode.h"
void QRcode::draw_png(char* input_file_name)
{
	input_file = fopen(input_file_name, "rb");
	if (!input_file)
		cout << "�ļ���ʧ��" << endl;
	Mat frame;
	char test_str[MAX_CHAR + 2] = { 0 };
	char png_name[10] = { 0 };
	bool* bin_str;
	int count = 0;//ͳ��ͼƬ��Ŀ
	while (!feof(input_file))
	{
		bin_str = new bool[MAX_CHAR + no_of_frame];
		memset(test_str, 0, MAX_CHAR);
		count++;
		//����ͼƬ��Ϣ
		int temp = count;
		int t = 0;
		while (temp > 0)   //ѭ�����̵�ʼ�գ��ж�n�Ƿ��ܱ�2����
		{
			if (temp % 2 == 1)   //������洢ÿ�γ���2֮������������϶���ż�ԣ���Ӧ������λ����ֵ
				bin_str[t] = false;
			else
				bin_str[t] = true;
			t++;
			temp /= 2;
		}
		sprintf(png_name, "%d.png", count);
		fread(test_str, MAX_CHAR + 1, 1, input_file);
		int length = strlen(test_str);
		char_to_bool(test_str, length, bin_str);
		frame = bin_to_png(bin_str, length + no_of_frame);//ͼƬ����
		bool result = imwrite(png_name, frame);
		if (!result)
			cout << "�ļ����ʧ��" << endl;
		else
			cout << "��" << count << "�Ŷ�ά������ɹ�" << endl;
		delete[]bin_str;
		memset(png_name, 0, sizeof(png_name));
		memset(test_str, 0, MAX_CHAR);
	}
}


Mat QRcode::draw_pure_white(int a, int b)
{
	Mat image(a, b, CV_8UC3, Scalar(255, 255, 255));
	rectangle(image, Point(0, 0), Point(a, b), Scalar(255, 255, 255), FILLED, LINE_8);
	return image;
}

void QRcode::draw_anchors(Mat& image)
{
	//��λ��1
	rectangle(image, Point(left_blank, left_blank), Point(anchor_size + left_blank - anchor_blank, anchor_size + left_blank - anchor_blank), Scalar(0), FILLED, LINE_8);//��������(���붨λ���С)
	rectangle(image, Point(left_blank + anchor_blank, left_blank + anchor_blank), Point(left_blank + anchor_size - anchor_blank * 2, left_blank + anchor_size - anchor_blank * 2), Scalar(255, 255, 255), FILLED, LINE_8);
	rectangle(image, Point(left_blank + anchor_blank * 2, left_blank + anchor_blank * 2), Point(left_blank + anchor_size - anchor_blank * 3, left_blank - anchor_blank * 3 + anchor_size), Scalar(0), FILLED, LINE_8);
	//��λ��2
	rectangle(image, Point(left_blank, IMG_X - anchor_size + left_blank + anchor_blank), Point(anchor_size + left_blank - anchor_blank, IMG_X + left_blank), Scalar(0), FILLED, LINE_8);//��������
	rectangle(image, Point(left_blank + anchor_blank, IMG_X - anchor_size + left_blank + anchor_blank * 2), Point(left_blank + anchor_size - anchor_blank * 2, IMG_X + left_blank - anchor_blank), Scalar(255, 255, 255), FILLED, LINE_8);
	rectangle(image, Point(left_blank + anchor_blank * 2, IMG_X - anchor_size + left_blank + anchor_blank * 3), Point(left_blank + anchor_size - anchor_blank * 3, IMG_X + left_blank - anchor_blank * 2), Scalar(0), FILLED, LINE_8);
	//��λ��3
	rectangle(image, Point(IMG_Y - anchor_size + left_blank + anchor_blank, left_blank), Point(IMG_Y + left_blank, anchor_size + left_blank - anchor_blank), Scalar(0), FILLED, LINE_8);//��������(���붨λ���С)
	rectangle(image, Point(IMG_Y - anchor_size + left_blank + anchor_blank * 2, left_blank + anchor_blank), Point(IMG_Y + left_blank - anchor_blank, left_blank + anchor_size - anchor_blank * 2), Scalar(255, 255, 255), FILLED, LINE_8);
	rectangle(image, Point(IMG_Y - anchor_size + left_blank + anchor_blank * 3, left_blank + anchor_blank * 2), Point(IMG_Y + left_blank - anchor_blank * 2, left_blank + anchor_size - anchor_blank * 3), Scalar(0), FILLED, LINE_8);

	//ͼƬ��Ϣ

}

Mat QRcode::bin_to_png(bool* str, int size)//����ֵΪ�������ַ������ַ�������
{
	Mat image = draw_pure_white(IMG_Y + 2 * left_blank, IMG_X + 2 * left_blank);
	draw_anchors(image);

	int count = 0;//ͳ���������Ŀ
	for (int p = 0; p < anchor_size / one_block_width; p++)//1��2��λ��֮��Ķ�ά��
	{
		for (int q = 0; q < (IMG_X / one_block_width) - (2 * anchor_size / one_block_width); q++)
		{
			rectangle(image, Point(anchor_size + one_block_width * q + left_blank, 0 + one_block_width * p + left_blank), Point(anchor_size + one_block_width * (q + 1) + left_blank, 0 + one_block_width * (p + 1) + left_blank), Scalar(255 * str[count], 255 * str[count], 255 * str[count]), FILLED, LINE_8);//0Ϊ�ף�1Ϊ��
			count++;
			if (count > size)
			{
				return image;			//�������Ϊ�հ�
			}
		}
	}

	for (int p = 0; p < IMG_Y / one_block_width - 2 * anchor_size / one_block_width; p++)//�м䲿�ֶ�ά��
	{
		for (int q = 0; q < IMG_X / one_block_width; q++)
		{
			rectangle(image, Point(0 + one_block_width * q + left_blank, anchor_size + one_block_width * p + left_blank), Point(0 + one_block_width * (q + 1) + left_blank, anchor_size + one_block_width * (p + 1) + left_blank), Scalar(255 * str[count], 255 * str[count], 255 * str[count]), FILLED, LINE_8);
			count++;
			if (count > size)
			{
				return image;
			}
		}
	}
	for (int p = 0; p < anchor_size / one_block_width; p++)//3��λ���ұߵĶ�ά��
	{
		for (int q = 0; q < IMG_X / one_block_width - (anchor_size / one_block_width); q++)
		{
			rectangle(image, Point(anchor_size + one_block_width * q + left_blank, IMG_Y - anchor_size + one_block_width * p + left_blank), Point(anchor_size + one_block_width * (q + 1) + left_blank, IMG_Y - anchor_size + one_block_width * (p + 1) + left_blank), Scalar(255 * str[count], 255 * str[count], 255 * str[count]), FILLED, LINE_8);
			count++;
			if (count > size)
			{
				return image;
			}
		}

	}
	return image;
}

void QRcode::char_to_bool(char* c, int length, bool* b)
{
	int j = 0;
	for (int i = no_of_frame - 1; j < length; i++)
	{
		if (c[j] == '1')
			b[i] = false;
		else
			b[i] = true;
		j++;
	}
}