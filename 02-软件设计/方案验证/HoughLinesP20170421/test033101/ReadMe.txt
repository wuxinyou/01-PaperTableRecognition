
RecognizeRectange
20170414
1.本实例测试识别图片中的矩形框。
2.在实际应用是只需要检测最外面的边框即可，所以cvFindContours(gray, storage, &contours, sizeof(CvContour),
				CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));  //CV_RETR_CCOMP
	然而在检测最外边框时，总是会把图片边框给检测出来，这不是我们想要的，我们要检测定位边框，
	所以cvThreshold(tgray, gray, (l + 1) * 255 / N, 255, CV_THRESH_BINARY_INV); //CV_THRESH_BINARY_INV

HoughLinesP
20170419
1.利用累计概率霍夫变换，擦除表格图片中所有的单元格边框
2.可以去除单元格边框，调整相关参数可以取得比较好的效果。
3.擦除单元格边框后可以可以根据《单元格对应尺寸表》来标识ROI。

HoughLinesP20170421
1.添加xml识别。
2.添加成功，可以识别XML，并提取单元格ROI。
3.功能模块化。
