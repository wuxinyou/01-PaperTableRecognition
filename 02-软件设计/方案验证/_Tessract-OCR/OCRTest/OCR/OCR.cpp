// OCR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>



#include "include\\baseapi.h"
#include "include\\strngs.h"
#pragma  comment(lib,"libtesseract302.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;





void OCR()
{
	char * str = "test3.jpg";
	tesseract::TessBaseAPI  api;
	api.Init(NULL, "num", tesseract::OEM_DEFAULT);  //初始化，设置语言包，中文简体：chi_sim;英文：eng；也可以自己训练语言包  
	api.SetVariable("tessedit_char_whitelist", "0123456789");    //ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
	STRING text_out;
	if (!api.ProcessPages(str, NULL, 0, &text_out))
	{
		return;
	}

	cout << "result: " << text_out.string() << endl;

}



int _tmain(int argc, _TCHAR* argv[])
{
	OCR();
	system("pause");
	return 0;
}

