// test033101.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include "readXML.h"

using namespace std;
using namespace cv;

int thresh = 50;
IplImage* img = NULL;
IplImage* img0 = NULL;
CvMemStorage* storage = NULL;
const char * wndname = "正方形检测 demo";

int offSetX = 0;
int offSetY = 0;


//angle函数用来返回（两个向量之间找到角度的余弦值）
double angle(CvPoint* pt1, CvPoint* pt2, CvPoint* pt0)
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;
	double dx2 = pt2->x - pt0->x;
	double dy2 = pt2->y - pt0->y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// 返回图像中找到的所有轮廓序列，并且序列存储在内存存储器中

CvSeq* findSquares4(IplImage* img, CvMemStorage* storage)
{
	imshow("img", Mat(img));
	CvSeq* contours;
	int i, c, l, N = 11;
	CvSize sz = cvSize(img->width & -2, img->height & -2);

	IplImage* timg = cvCloneImage(img);
	IplImage* gray = cvCreateImage(sz, 8, 1);
	IplImage* pyr = cvCreateImage(cvSize(sz.width / 2, sz.height / 2), 8, 3);
	IplImage* tgray;
	CvSeq* result;
	double s, t;
	// 创建一个空序列用于存储轮廓角点
	CvSeq* squares = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvPoint), storage);

	cvSetImageROI(timg, cvRect(0, 0, sz.width, sz.height));
	// 过滤噪音
	cvPyrDown(timg, pyr, 7);
	cvPyrUp(pyr, timg, 7);
	tgray = cvCreateImage(sz, 8, 1);

	// 红绿蓝3色分别尝试提取
	for (c = 0; c < 1; c++)
	{
		// 提取 the c-th color plane
		cvSetImageCOI(timg, c + 1);
		cvCopy(timg, tgray, 0);
		imshow("timg", Mat(timg));

		// 尝试各种阈值提取得到的（N=11）
		for (l = 9; l < 10; l++)
		{
			// apply Canny. Take the upper threshold from slider
			// Canny helps to catch squares with gradient shading  
			if (l == 0)
			{
				cvCanny(tgray, gray, 0, thresh, 3);
				
				//使用任意结构元素膨胀图像
				//cvDilate(gray, gray, 0, 1);
			}
			else
			{
				// apply threshold if l!=0:
				cvThreshold(tgray, gray, (l + 1) * 255 / N, 255, CV_THRESH_BINARY_INV);
				imshow("gray", Mat(gray));
			}
			

			// 找到所有轮廓并且存储在序列中
			int contours_num =cvFindContours(gray, storage, &contours, sizeof(CvContour),
				CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
			
			cout << "contours_num: " << contours_num << endl;

			// 继续查找下一个轮廓
			//contours = contours->h_next;
			cout << "contours->total: " << contours->total<<endl;
			// 遍历找到的每个轮廓contours
			while (contours)
			{
				//用指定精度逼近多边形曲线
				result = cvApproxPoly(contours, sizeof(CvContour), storage,
					CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.08, 0);


				if (result->total == 4 &&
					fabs(cvContourArea(result, CV_WHOLE_SEQ)) > 10000/*  &&
					fabs(cvContourArea(result, CV_WHOLE_SEQ)) < 100000*/&&
					cvCheckContourConvexity(result))
				{
					s = 0;

					for (i = 0; i < 5; i++)
					{
						// find minimum angle between joint edges (maximum of cosine)
						if (i >= 2)
						{
							t = fabs(angle(
								(CvPoint*)cvGetSeqElem(result, i),
								(CvPoint*)cvGetSeqElem(result, i - 2),
								(CvPoint*)cvGetSeqElem(result, i - 1)));
							s = s > t ? s : t;
						}
					}

					// if 余弦值 足够小，可以认定角度为90度直角
					//cos0.1=83度，能较好的趋近直角
					if (s < 0.051)
						for (i = 0; i < 4; i++)
							cvSeqPush(squares,
							(CvPoint*)cvGetSeqElem(result, i));
				}

				// 继续查找下一个轮廓
				contours = contours->h_next;
			}
		}
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&pyr);
	cvReleaseImage(&tgray);
	cvReleaseImage(&timg);

	return squares;
}

//drawSquares函数用来画出在图像中找到的所有正方形轮廓
void drawSquares(IplImage* img, CvSeq* squares)
{
	CvSeqReader reader;
	IplImage* cpy = cvCloneImage(img);
	int i;
	cvStartReadSeq(squares, &reader, 0);
	
	cout <<"squares->total: " <<squares->total<<endl;

	// read 4 sequence elements at a time (all vertices of a square)
	for (i = 0; i < squares->total; i += 4)
	{
		CvPoint pt[4], *rect = pt;
		int count = 4;

		// read 4 vertices
		CV_READ_SEQ_ELEM(pt[0], reader);
		CV_READ_SEQ_ELEM(pt[1], reader);
		CV_READ_SEQ_ELEM(pt[2], reader);
		CV_READ_SEQ_ELEM(pt[3], reader);

		cout << "pt[3].x= " << pt[3].x<< endl;
		cout << "pt[3].y= " << pt[3].y<< endl;
		cout << "pt[1].x= " << pt[1].x << endl;
		cout << "pt[1].y= " << pt[1].y << endl;

		offSetX = pt[0].x;
		offSetY = pt[0].y;

		// draw the square as a closed polyline
		cvPolyLine(cpy, &rect, &count, 1, 1, CV_RGB(0, 255, 0), 1, CV_AA, 0);
	}
	
	cvShowImage(wndname, cpy);
	cvReleaseImage(&cpy);
}

//读取XML，并在图中绘制单元格边框
void drawCell(Mat img)
{
	int num = 0;
	readXML();
	rectangle(img, Rect(border.x + offSetX, border.y + offSetY, border.width, border.height), Scalar(0, 0, 255), 1);
	for (auto i : vecCell)
	{
		rectangle(img, Rect(i.x + offSetX, i.y + offSetY, i.width, i.height), Scalar(0, 255, 0), 1);

		//提取ROI
		Mat imageROI = img(Rect(i.x + offSetX, i.y + offSetY, i.width, i.height));
		char  win[10];
		_itoa(num++, win, 10);
		imshow(win, imageROI);
	}
}
//找到所有的单元格边框，并擦除
void findAllBorder()
{
	//利用HoughLinesP擦除单元格边框
	Mat srcImage = imread("1521611168303.jpg");
	Mat midImage, dstImage;  //
	Canny(srcImage, midImage, 50, 100, 3);

	imshow("边缘检测后的图", midImage);

	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

	vector<Vec4i> lines;
	HoughLinesP(midImage, lines, 2, CV_PI / 180, 100, 50, 20);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(srcImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 2, CV_AA);

	}

	drawCell(srcImage);

	imshow("AfterHoughLinesP", srcImage);
}




char* names[] = { "1521611168303.jpg",  0 };

int main(int argc, char** argv)
{
	int i, c;
	storage = cvCreateMemStorage(0);

	for (i = 0; names[i] != 0; i++)
	{
		img0 = cvLoadImage(names[i], 1);
		if (!img0)
		{
			cout << "不能载入" << names[i] << "继续下一张图片" << endl;
			continue;
		}
		img = cvCloneImage(img0);
		cvNamedWindow(wndname, 1);

		// find and draw the squares
		drawSquares(img, findSquares4(img, storage));
		findAllBorder();



		c = cvWaitKey(0);
		cvReleaseImage(&img);
		cvReleaseImage(&img0);

		cvClearMemStorage(storage);

		if ((char)c == 27)
			break;
	}

	cvDestroyWindow(wndname);
	return 0;
}
