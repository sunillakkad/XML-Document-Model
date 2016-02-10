#ifndef DISPLAY_H
#define DISPLAY_H
///////////////////////////////////////////////////////////////////////
// Display.h - display output on console			                 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 13.0						         //
// Platform:    Dell Inspiron N5010, Win7 Professional, SP1          //
// Application: Demonstration for CSE 687, Project #2, Spring 2015   //
// Author:      Sunilkumar Lakkad, Syracuse University               //
//              (315) 751-5834, lakkads1@gmail.com                   //
///////////////////////////////////////////////////////////////////////

/*
* Module Operations :
*== == == == == == == == ==
This  file contains the following class : Display- It outputs the functionality of requirements . 
It contains the declarations of the methods defined in Display.cpp

Public Interface:
=================
public:
Display(XmlDocument& ds);
void displayLine(char lineType);
void displayElement(std::vector<sPtr> elem, std::string title);
void displayChildrenByTag(std::vector<sPtr> elem, std::string tag, std::string tag1);
void displayDescendentsByTag(std::vector<sPtr> elem, std::string tag, std::string tag1);
void displayElementById(std::vector<sPtr> elem, std::string id);
void displayAddChildren(bool success, std::string parent, std::string child, std::string type);
void displayRemoveChildren(bool success, std::string parent, std::string child, std::string type);
void displayAddRoot(bool save, std::string root);
void displayFetcedAttributesByTag(std::vector<std::pair<std::string, std::string>> attr, std::string parent);
void displayAddAttributeByTag(bool success, std::string parent, std::string key, std::string value);
void displayRemoveAttributeByTag(bool success, std::string parent, std::string value);
void displayCreateXml(int counter);
void displayMoveConst();

Required Files:
===============
Tokenizer.h, Display.cpp, XmlDocument.h, XmlElement.h, xmlElementParts.h

Build Command:
==============
cl /EHa /TEST_DISPLAY Display.cpp


Maintenance History:
====================
ver 1.0 : 26 Mar 15
- first release
*/

#include <iostream>
#include<vector>
#include "../XmlDocument/XmlDocument.h"
#include "../XmlElement/XmlElement.h"
using namespace std;

///////////////////////////////////////////////
//Contains Methods for Display

namespace XmlProcessing
{
	class Display{
	public:
		Display(XmlDocument& ds);
		using sPtr = std::shared_ptr < AbstractXmlElement > ;
		void displayLine(char lineType);
		void displayElement(std::vector<sPtr> elem, std::string title);
		void displayChildrenByTag(std::vector<sPtr> elem, std::string tag, std::string tag1);
		void displayDescendentsByTag(std::vector<sPtr> elem, std::string tag, std::string tag1);
		void displayElementById(std::vector<sPtr> elem, std::string id);
		void displayAddChildren(bool success, std::string parent, std::string child, std::string type);
		void displayRemoveChildren(bool success, std::string parent, std::string child, std::string type);
		void displayAddRoot(bool save, std::string root);
		void displayFetcedAttributesByTag(std::vector<std::pair<std::string, std::string>> attr, std::string parent);
		void displayAddAttributeByTag(bool success, std::string parent, std::string key, std::string value);
		void displayRemoveAttributeByTag(bool success, std::string parent, std::string value);
		void displayCreateXml(int counter);
		void displayMoveConst();
	private:
		XmlDocument& store_;
	};
}

#endif