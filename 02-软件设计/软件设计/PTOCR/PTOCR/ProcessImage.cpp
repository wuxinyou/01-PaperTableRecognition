#include "stdafx.h"
#include "ProcessImage.h"


ProcessImage::ProcessImage()
{
}


ProcessImage::~ProcessImage()
{
}



/*************************************************************
说明：擦除原图表格所有的边框
输入：Mat img 引用
输出：void
备注：
**************************************************************/
void  ProcessImage::WipeSheetBorder(Mat &srcImage)
{

	//利用HoughLinesP擦除单元格边框
	//Mat srcImage = imread("1521611168303.jpg");
	Mat midImage;  //
	Canny(srcImage, midImage, 50, 100, 3);

	//imshow("边缘检测后的图", midImage);

	vector<Vec4i> lines;
	HoughLinesP(midImage, lines, 2, CV_PI / 180, 100, 50, 20);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(srcImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 2, CV_AA);

	}
}


/*************************************************************
说明：查找定位边框，并返回
输入：Mat img 引用
输出：Rect
备注：测试通过
**************************************************************/
Rect ProcessImage::FindOutBorder2(Mat srcImage)
{
	vector<vector<Point2i>> contours;
	Rect rect;
	Mat disImage=srcImage.clone();
	Mat srcgray, disgray;
	cvtColor(srcImage, srcgray, COLOR_RGB2GRAY);

	Mat midImage(srcImage.size(), CV_16SC1);
	threshold(srcgray, disgray, 200, 255, CV_THRESH_BINARY_INV);
	findContours(disgray, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	vector<vector<Point2i>> contours2;

	for (int i = 0; i < contours.size(); i++)
	{
		//approxPolyDP(Mat(contours[i]), contours2[i], 3, true);
		if (contours[i].size()>500)
			contours2.push_back(contours[i]);
	}
	
	drawContours(disImage, contours2, -1, Scalar(0), 2);
	imshow("findOutBorder", disImage);

	rect = boundingRect(contours2.back());
	TRACE(_T("LocationBorder = %d,%d,%d,%d\r\n"), rect.x,rect.y,rect.width,rect.height);
	return rect;
}





