#pragma once
   
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <vector>

using namespace std;   
using namespace cv;



class ProcessImage
{
public:
	ProcessImage();
	~ProcessImage();


	void  FindOutBorder();     //查找定位边框
	void  WipeSheetBorder();  //擦除表格所有边框
	void  ReadImage(const string &fileName);   //读取文件
	void  ReadImage(Mat img);
	string  RecROI(int x, int y, int width, int height);   //识别图片中指定区域

private:

	Mat srcImage;
	Rect outBorder;




};

