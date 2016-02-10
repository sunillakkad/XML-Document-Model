#ifndef EXECUTIVE_H
#define EXECUTIVE_H
///////////////////////////////////////////////////////////////////////
// Executive.h - Manage all Packages of XML Document Model           //
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
* This module is the heart of the project, it controls the flow of the application

Public Interface:
=================
public:

void xmlOperation(std::string argv, int i);
void testCase1(XmlDocument& doc, Display& dis);
void testCase2(XmlDocument& doc, Display& dis);
void testCase3(XmlDocument& doc, Display& dis);
void testCase4(XmlDocument& doc, Display& dis);
void testCase5(XmlDocument& doc, Display& dis);
void testCase6(XmlDocument& doc, Display& dis);
void testCase7(XmlDocument& doc, Display& dis);
void testCase8(XmlDocument& doc, Display& dis);
void testCase9(XmlDocument& doc, Display& dis);
void testCase10(XmlDocument& doc, Display& dis);
void testCase11(XmlDocument& doc, Display& dis);
void testCase12(XmlDocument& doc, Display& dis);
void testCase13(XmlDocument& doc, Display& dis);
void testCase14(XmlDocument& doc, Display& dis);
void testCase15(XmlDocument& doc, Display& dis);

Required Files:
===============
Tokenizer.h, Display.h, Executive.cpp, XmlDocument.h, XmlElement.h, xmlElementParts.h

Build Command:
==============
devenv Project2.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 26 Mar 15
- first release
*/

#include <iostream>
#include<vector>
#include<regex>
#include "../XmlDocument/XmlDocument.h"
#include "../Display/Display.h"

////////////////////////////////////////////////////////////
// Manage whole application

namespace XmlProcessing
{
	class  Executive
	{
	public:
		void xmlOperation(std::string argv, int i);
		void testCase1(XmlDocument& doc, Display& dis);
		void testCase2(XmlDocument& doc, Display& dis);
		void testCase3(XmlDocument& doc, Display& dis);
		void testCase4(XmlDocument& doc, Display& dis);
		void testCase5(XmlDocument& doc, Display& dis);
		void testCase6(XmlDocument& doc, Display& dis);
		void testCase7(XmlDocument& doc, Display& dis);
		void testCase8(XmlDocument& doc, Display& dis);
		void testCase9(XmlDocument& doc, Display& dis);
		void testCase10(XmlDocument& doc, Display& dis);
		void testCase11(XmlDocument& doc, Display& dis);
		void testCase12(XmlDocument& doc, Display& dis);
		void testCase13(XmlDocument& doc, Display& dis);
		void testCase14(XmlDocument& doc, Display& dis);
		void testCase15(XmlDocument& doc, Display& dis);
	private:

	};
}
#endif
