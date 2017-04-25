



/*************************************************************

概述：使用OpenCV对图片文件进行操作，，
包含查找最外矩形边框
利用累计概率霍夫函数擦除边框
调用Tesseract识别ROI

作者：吴新有
日期：20170425
版本：v1.0
**************************************************************/

#include "stdafx.h"
#include "ProcessImage.h"

#include "include\\baseapi.h"
#include "include\\strngs.h"


#pragma  comment(lib,"libtesseract302.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//using namespace std;



ProcessImage::ProcessImage()
{



	srcImage = NULL;
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
void  ProcessImage::WipeSheetBorder()
{
	//利用HoughLinesP擦除单元格边框

	Mat midImage;  //
	Canny(srcImage, midImage, 50, 100, 3);

	//imshow("边缘检测后的图", midImage);

	vector<Vec4i> lines;
	HoughLinesP(midImage, lines, 2, CV_PI / 180, 200, 50, 20);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(srcImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 2, CV_AA);

	}
}


/*************************************************************
说明：查找定位边框，并返回
输入：Mat img 引用
输出：void
备注：测试通过
**************************************************************/
void ProcessImage::FindOutBorder()
{
	vector<vector<Point2i>> contours;
	
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

	outBorder = boundingRect(contours2.back());
	TRACE(_T("LocationBorder = %d,%d,%d,%d\r\n"), outBorder.x, outBorder.y, outBorder.width, outBorder.height);
	
}


/*************************************************************
说明：读入图片文件
输入：const string 文件名
输出：void
备注：
**************************************************************/
void ProcessImage::ReadImage(const string &fileName)
{
	srcImage = imread(fileName);
}

/*************************************************************
说明：读入图片文件
输入：Mat 
输出：void
备注：
**************************************************************/
void ProcessImage::ReadImage(Mat img)
{
	srcImage = img;
}

/*************************************************************
说明：识别图片中指定区域
输入：int x,int y,int width,int height
输出：string
备注：
**************************************************************/
string ProcessImage::RecROI(int x, int y, int width, int height)
{
	Mat sheetCellROI = srcImage(Rect(x, y, width, height));
	Mat gray;
	cvtColor(sheetCellROI, gray, CV_RGB2GRAY);

	tesseract::TessBaseAPI tessOCR;
	// Pass it to Tesseract API  

	tessOCR.Init(NULL, "num", tesseract::OEM_DEFAULT);
	tessOCR.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
	tessOCR.SetImage((uchar*)gray.data, gray.cols, gray.rows, 1, gray.cols);
	



	imshow("sheetCell", gray);

	 string str = tessOCR.GetUTF8Text();
	 TRACE(str.c_str());
	 return str;
}



