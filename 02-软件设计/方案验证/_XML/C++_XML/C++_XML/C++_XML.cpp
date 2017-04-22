// C++_XML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tinystr.h" 
#include "tinyxml.h" 
#include <iostream>
#include <string>

using namespace std;


#pragma comment(lib,"tinyxml.lib") 
#pragma comment(lib,"tinyxmlSTL.lib") 


int count123 = 0;

string dumpNode(TiXmlNode * pNode, int flag);


int  _tmain(int argc, _TCHAR* argv[])
{


	TiXmlDocument *myDocument = new TiXmlDocument("1521611168303.xml");
	myDocument->LoadFile();

	//获得xml的头，即声明部分 
	TiXmlDeclaration* decl = myDocument->FirstChild()->ToDeclaration();

	cout << "xml文件的版本是:" << decl->Version() << endl;
	cout << "xml的编码格式是：" << decl->Encoding() << endl;

	//获得根元素 
	TiXmlElement *RootElement = myDocument->RootElement();

	//输出根元素名称 
	cout << RootElement->Value() << endl;
	TiXmlNode* pNode = NULL;
	string msg = "";
	
	for (pNode = RootElement->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())  //在同一级别内循环
	{
		msg = dumpNode(pNode, 0);
		cout << msg << endl;
	}	

	system("pause");

	return 0;
}



string dumpNode(TiXmlNode * pNode, int flag)
{
	string msg = "";

	if (pNode == NULL)
	{
		return "";
	}
	TiXmlText * pText = NULL;
	TiXmlNode * pChildNode = NULL;
	count123++;
	int t = pNode->Type();
	if (t == TiXmlText::TINYXML_TEXT)  //节点类型是text节点 
	{
		pText = pNode->ToText();
		string text = pText->Value();
		if (!text.empty())
		{
			msg = msg + "=" + text;
			
		}

		
	}
	else if (t == TiXmlText::TINYXML_ELEMENT) //节点类型是Element 
	{
		msg = msg + "\r\n";
		int num = flag;
		while (num >= 1)
		{
			msg = msg + "\t";
			num--;
		}
		msg = msg + pNode->Value();		

		//输出属性 
		TiXmlElement * pElement = pNode->ToElement();
		TiXmlAttribute * pAttr = pElement->FirstAttribute();
		TiXmlAttribute * pNextAttr = NULL;
		string tmpAttrMsg = "[";
		if (pAttr != NULL)
		{
			string tmpAttrVal = "";
			string tmpAttrName = "";
			do
			{
				tmpAttrVal = pAttr->Value();
				tmpAttrName = pAttr->Name();
				tmpAttrMsg += tmpAttrName + "=" + tmpAttrVal + ","; //各个属性之间用逗号分隔 

			} while (pAttr = pAttr->Next());
			tmpAttrMsg = tmpAttrMsg.erase(tmpAttrMsg.find_last_of(","));
		}
		tmpAttrMsg += "]";
		msg += tmpAttrMsg;
	}

	//循环访问它的每一个元素 
	for (pChildNode = pNode->FirstChild(); pChildNode != 0; pChildNode = pChildNode->NextSibling())  //在同一级别内循环
	{
		msg = msg + dumpNode(pChildNode, flag + 1);
	}

	return msg;
}