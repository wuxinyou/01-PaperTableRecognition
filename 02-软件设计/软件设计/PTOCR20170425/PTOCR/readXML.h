
/*************************************************************

概述：读取XML文件，调用TinyXML解析器
	包含遍历XML树，将有效节点数据存储在C++结构体中
作者：吴新有
日期：20170425
版本：v1.0
**************************************************************/

#ifndef READXML_H
#define READXML_H

#include "tinystr.h" 
#include "tinyxml.h" 

#include <iostream>
#include <string>
#include <vector>

using namespace std;




//存放定位边框数据
typedef struct
{
	int x;
	int y;
	int width;
	int height;
}Border;


//存放单元格数据
typedef struct
{
	int x;
	int y;
	int width;
	int height;
	string cellNum;
}Cell;

class ReadXML
{
public:
	ReadXML();
	~ReadXML();

	
	void readXMLFile(const string fileName);
	void print();

private:
	string dumpNode(TiXmlNode * pNode, int flag);

public:
	Border border;     //定义定位边框的边界结构体
	vector<Cell> vecCell;

};






#endif