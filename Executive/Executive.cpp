///////////////////////////////////////////////////////////////////////
// Executive.cpp - Manage all Packages of XML Document Model         //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 13.0						         //
// Platform:    Dell Inspiron N5010, Win7 Professional, SP1          //
// Application: Demonstration for CSE 687, Project #2, Spring 2015   //
// Author:      Sunilkumar Lakkad, Syracuse University               //
//              (315) 751-5834, lakkads1@gmail.com                   //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <locale>  
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>      
#include <functional>
#include <Windows.h>
#include "Executive.h"
#include "../XmlDocument/XmlDocument.h"
#include "../Display/Display.h"

using namespace XmlProcessing;

void Executive::xmlOperation(std::string argv,int i)
{
	XmlDocument doc(argv);
	Display dis(doc);
	doc.addElements();			//creating the AST

	testCase1(doc, dis);		//display Element
	testCase2(doc, dis);		//display Elements									
	testCase3(doc, dis);		//display Children
	testCase4(doc, dis);
	testCase5(doc, dis);		//display Descendents By Tag
	testCase6(doc, dis);													
	testCase7(doc, dis);		//display Element By Id
	testCase8(doc, dis);		//display Add Child by Tag
	testCase9(doc, dis);		//display Add child by Id
	testCase10(doc, dis);		//display Remove Child By Tag					
	testCase11(doc, dis);		//display Remove Child By Id
	testCase12(doc, dis);		//display Add Root
	testCase13(doc, dis);		//dispaly Fetched Attributes
	testCase14(doc, dis);		//display Add Attribute	By Tag					
	testCase15(doc, dis);		//display Remove Attribute By Tag
	dis.displayCreateXml(i);	//display Create Xml
	dis.displayMoveConst();
}

void Executive::testCase1(XmlDocument& doc, Display& dis)
{
	string title = "date";
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::vector<sPtr> elem = doc.getElement(title).select();
	dis.displayElement(elem, title);
}

void Executive::testCase2(XmlDocument& doc, Display& dis)
{
	string title = "title";
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::vector<sPtr> elem = doc.getElements(title).select();
	dis.displayElement(elem, title);
}

void Executive::testCase3(XmlDocument& doc, Display& dis)
{
	string tag = "reference";
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::vector<sPtr> elem = doc.getElement(tag).findChildrenByTag().select();
	dis.displayChildrenByTag(elem, tag, "");
}

void Executive::testCase4(XmlDocument& doc, Display& dis)
{
	string tag = "reference";
	string tag1 = "author";
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::vector<sPtr> elem = doc.getElement(tag).findChildrenByTag(tag1).select();
	dis.displayChildrenByTag(elem, tag, tag1);
}

void Executive::testCase5(XmlDocument& doc, Display& dis)
{
	string tag = "reference";
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::vector<sPtr> elem = doc.getElement(tag).findDescendentsByTag().select();
	dis.displayDescendentsByTag(elem, tag, "");
}

void Executive::testCase6(XmlDocument& doc, Display& dis)
{
	string tag = "reference";
	string tag1 = "author";
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::vector<sPtr> elem = doc.getElement(tag).findDescendentsByTag(tag1).select();
	dis.displayDescendentsByTag(elem, tag, tag1);
}

void Executive::testCase7(XmlDocument& doc, Display& dis)
{
	string id = "Wintellect";
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::vector<sPtr> elem = doc.findElementById(id).select();
	dis.displayElementById(elem, id);
}

void Executive::testCase8(XmlDocument& doc, Display& dis)
{
	string parent = "LectureNote";
	string child = "newChild";
	string type = "Tag";
	bool success = doc.addChildrenByTag(parent, child);
	dis.displayAddChildren(success, parent, child, type);
}

void Executive::testCase9(XmlDocument& doc, Display& dis)
{
	string parent = "CSE681";
	string child = "newChild1";
	string type = "ID";
	bool success = doc.addChildrenById(parent, child);
	dis.displayAddChildren(success, parent, child, type);
}

void Executive::testCase10(XmlDocument& doc, Display& dis)
{
	string parent = "LectureNote";
	string child = "newChild";
	string type = "Tag";
	bool success = doc.removeChildrenByTag(parent, child);
	dis.displayRemoveChildren(success, parent, child, type);
}

void Executive::testCase11(XmlDocument& doc, Display& dis)
{
	string parent = "CSE681";
	string child = "newChild1";
	string type = "ID";
	bool success = doc.removeChildrenById(parent, child);
	dis.displayRemoveChildren(success, parent, child, type);
}

void Executive::testCase12(XmlDocument& doc, Display& dis)
{
	string root = "root";
	bool success = doc.addRoot(root);
	dis.displayAddRoot(success, root);
}

void Executive::testCase13(XmlDocument& doc, Display& dis)
{
	string parent = "LectureNote";
	std::vector<std::pair<std::string, std::string>> attr = doc.fetchAttributesByTag(parent);
	dis.displayFetcedAttributesByTag(attr, parent);
}

void Executive::testCase14(XmlDocument& doc, Display& dis)
{
	string parent = "LectureNote";
	std::string key = "key";
	std::string value = "value";
	bool success = doc.getElement(parent).addAttributeByTag(key, value);
	dis.displayAddAttributeByTag(success, parent, key, value);
}

void Executive::testCase15(XmlDocument& doc, Display& dis)
{
	string parent = "LectureNote";
	std::string value = "value";
	bool success = doc.getElement(parent).removeAttributeByTag(value);
	dis.displayRemoveAttributeByTag(success, parent, value);
}
//----<the program starts from this point>------------------------------

#ifdef TEST_EXECUTIVE

int main(int argc, char *  argv[])
{

	if (argc < 2)
	{
		std::cout<< "\n  Please Enter File Name\n\n";
		return 1;
	}
	for (int i = 1; i<argc; ++i)
	{
		std::ifstream f(argv[i]);
		if (!(f.is_open()))
		{
			cout << endl<< "Please Provide correct filename" << endl <<endl;
			break;
		}
		Executive ex;
		ex.xmlOperation(argv[i], i);
	}
	return 0;
}
#endif

