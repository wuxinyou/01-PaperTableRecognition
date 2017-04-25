

#include "stdafx.h"
#include "recognizeBar.h"


void RecBar::recBar(Mat img)
{
	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	Mat imageGray;
	cvtColor(img, imageGray, CV_RGB2GRAY);
	int width = imageGray.cols;
	int height = imageGray.rows;
	uchar *raw = (uchar *)imageGray.data;
	Image imageZbar(width, height, "Y800", raw, width * height);
	scanner.scan(imageZbar); //扫描条码      
	Image::SymbolIterator symbol = imageZbar.symbol_begin();
	if (imageZbar.symbol_begin() == imageZbar.symbol_end())
	{
		cout << "查询条码失败，请检查图片！" << endl;
		return;
	}
	//for (; symbol != imageZbar.symbol_end(); ++symbol)
	//{
	//	cout << "类型：" << endl << symbol->get_type_name() << endl << endl;
	//	cout << "条码：" << endl << symbol->get_data() << endl << endl;

	//	TRACE(_T("\r\n"));
	//	TRACE(_T("BarTypeName = %s\r\n"), symbol->get_type_name().c_str());
	//	TRACE(_T("\r\n"));
	//	TRACE(symbol->get_data().c_str());
	//	TRACE(_T("\r\n"));
	//	TRACE(_T("BarDataLen = %d\r\n"), sizeof(symbol->get_data()));
	//}



	typeName = symbol->get_type_name();
	data = symbol->get_data();

	imageZbar.set_data(NULL, 0);
}