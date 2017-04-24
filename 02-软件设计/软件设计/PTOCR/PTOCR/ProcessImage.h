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


	Rect  FindOutBorder2(Mat img);     //查找定位边框
	void  WipeSheetBorder(Mat &img);  //擦除表格所有边框

	




};

