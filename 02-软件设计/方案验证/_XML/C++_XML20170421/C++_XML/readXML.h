
#ifndef READXML_H
#define READXML_H

#include "tinystr.h" 
#include "tinyxml.h" 

#include <iostream>
#include <string>
#include <vector>

using namespace std;


#pragma comment(lib,"tinyxml.lib") 
#pragma comment(lib,"tinyxmlSTL.lib") 


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




string dumpNode(TiXmlNode * pNode, int flag);
void readXML();
void printXML();


#endif