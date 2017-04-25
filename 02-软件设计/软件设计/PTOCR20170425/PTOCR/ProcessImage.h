

/*************************************************************

概述：使用OpenCV对图片文件进行操作，，
	包含查找最外矩形边框
	利用累计概率霍夫函数擦除边框
	调用Tesseract识别ROI

作者：吴新有
日期：20170425
版本：v1.0
**************************************************************/
#pragma once
   

#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <vector>


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
	

public:
	Rect outBorder;




};

