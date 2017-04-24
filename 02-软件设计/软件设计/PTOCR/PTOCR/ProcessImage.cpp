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
备注：还有问题，有待改善
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

	return rect;
}

/*

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
				cvCanny(tgray, gray, 0, 50, 3);

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
			int contours_num = cvFindContours(gray, storage, &contours, sizeof(CvContour),
				CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

			cout << "contours_num: " << contours_num << endl;

			// 继续查找下一个轮廓
			//contours = contours->h_next;
			cout << "contours->total: " << contours->total << endl;
			// 遍历找到的每个轮廓contours
			while (contours)
			{
				//用指定精度逼近多边形曲线
				result = cvApproxPoly(contours, sizeof(CvContour), storage,
					CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.08, 0);


				if (result->total == 4 &&
					fabs(cvContourArea(result, CV_WHOLE_SEQ)) > 10000&&
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

	cout << "squares->total: " << squares->total << endl;

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

		cout << "pt[3].x= " << pt[3].x << endl;
		cout << "pt[3].y= " << pt[3].y << endl;
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




*/