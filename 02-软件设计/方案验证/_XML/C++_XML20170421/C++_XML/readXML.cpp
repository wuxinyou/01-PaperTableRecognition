

#include "stdafx.h"
#include "readXML.h"




Border border;     //定义定位边框的边界结构体
vector<Cell> vecCell;

string dumpNode(TiXmlNode * pNode, int flag)
{
	string msg = "";

	if (pNode == NULL)
	{
		return "";
	}
	TiXmlText * pText = NULL;
	TiXmlNode * pChildNode = NULL;

	int t = pNode->Type();
	if (t == TiXmlText::TINYXML_TEXT)  //节点类型是text节点 
	{

		pText = pNode->ToText();
		string pNodeText = pText->Value();
		string pNodePText = pNode->Parent()->Value();
		string pNodePPText = pNode->Parent()->Parent()->Value();
		string pNodePPPText = pNode->Parent()->Parent()->Parent()->Value();

		//将定位边框数据从XML中解析出来，存放在Border中
		if (pNodePPText == "border")
		{
			if (pNodePText == "x")
				border.x = atoi(pNodeText.c_str());
			else if (pNodePText == "y")
				border.y = atoi(pNodeText.c_str());
			else if (pNodePText == "width")
				border.width = atoi(pNodeText.c_str());
			else if (pNodePText == "height")
				border.height = atoi(pNodeText.c_str());

		}

		//将单元格数据从XML中解析出来，存放在Cell中
		if (pNodePPPText == "cells")
		{
			if (pNodePText == "x")
				vecCell.back().x = atoi(pNodeText.c_str());
			else if (pNodePText == "y")
				vecCell.back().y = atoi(pNodeText.c_str());
			else if (pNodePText == "width")
				vecCell.back().width = atoi(pNodeText.c_str());
			else if (pNodePText == "height")
				vecCell.back().height = atoi(pNodeText.c_str());
			else if (pNodePText == "cellNum")
				vecCell.back().cellNum = pNodeText;

		}


		if (!pNodeText.empty())
		{
			msg = msg + "=" + pNodeText;

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
		string pNodeText = pNode->Value();
		string pNodePText = pNode->Parent()->Value();
		string pNodePPText = pNode->Parent()->Parent()->Value();

		//进入单元格节点
		if (pNodePText == "cells")
		{
			vecCell.push_back(Cell());//插入一个空白的单元格节点

		}

		msg = msg + pNodeText;

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


void readXML()
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


	for (pNode = RootElement->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())  //在同一级别内循环
	{
		dumpNode(pNode, 0);

	}
}

void printXML()
{
	//打印边框数据
	cout << "border" << endl;
	cout << "\t" << "border.x: " << border.x << endl;
	cout << "\t" << "border.y: " << border.y << endl;
	cout << "\t" << "border.width: " << border.width << endl;
	cout << "\t" << "border.height: " << border.height << endl;
	//打印单元格数据
	cout << "cells: " << vecCell.size() << endl;

	for (auto i = 0; i < vecCell.size(); i++)
	{
		cout << "\t" << "cell_" << i << ".x: " << vecCell.at(i).x << endl;
		cout << "\t" << "cell_" << i << ".y: " << vecCell.at(i).y << endl;
		cout << "\t" << "cell_" << i << ".width: " << vecCell.at(i).width << endl;
		cout << "\t" << "cell_" << i << ".height: " << vecCell.at(i).height << endl;
		cout << "\t" << "cell_" << i << ".cellNum: " << vecCell.at(i).cellNum << endl;
		cout << endl;
	}
}