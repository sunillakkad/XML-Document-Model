#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
/////////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes                 //
// Ver 1.3                                                         //
// Language:    C++, Visual Studio 13.0						       //
// Platform:    Dell Inspiron N5010, Win7 Professional, SP1        //
// Application: Demonstration for CSE 687, Project #2, Spring 2015 //
// Author:      Sunilkumar Lakkad, Syracuse University             //
//              (315) 751-5834, lakkads1@gmail.com                 //
// Source:      Jim Fawcett, CST 4-187, Syracuse University        //
//              (315) 443-3948, jfawcett@twcny.rr.com              //
/////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to help students in CSE687 - Object Oriented Design
* get started with Project #2 - XML Document Model.  It uses C++11 constructs,
* most noteably std::shared_ptr.  The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
*
* Abstract Syntax Trees, defined in this package, are unordered trees with 
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
*
* Required Files:
* ---------------
*   - XmlDocument.h, XmlDocument.cpp, 
	  Tokenizer.h, Tokenizer.cpp
	  xmlElementParts.h, xmlElementParts.cpp
*     XmlElement.h, XmlElement.cpp
*
Public Interface:
=================
void addElements();
bool XmlDocument::parsingDeclareElement(std::string line);
bool XmlDocument::parsingProcInstrElement(std::string line);
bool XmlDocument::parsingCommentElement(std::string line);
bool XmlDocument::parsingTaggedElement(std::string line);
void attributesFillByTag(std::shared_ptr < AbstractXmlElement >& element, std::string check);
XmlDocument& getElement(const std::string& tag);           
XmlDocument& getElements(const std::string& tag);          
std::vector<sPtr> select();                            
void DFSWithTag(sPtr pNode, std::string tag);
XmlDocument& findChildrenByTag(const std::string& tag = "");     
XmlDocument& findDescendentsByTag(const std::string& tag = "");  
XmlDocument& findElementById(const std::string& id);
void DFSWithId(sPtr pNode, std::string id);
bool addChildrenByTag(const std::string& parent, const std::string& child);
bool addChildrenById(const std::string& parent, const std::string& child);
bool removeChildrenByTag(const std::string& parent, const std::string& child);
bool removeChildrenById(const std::string& parent, const std::string& child);
bool addRoot(std::string root);
std::vector<std::pair<std::string, std::string>> fetchAttributesByTag(std::string tag);
bool addAttributeByTag(const std::string& name, const std::string& value);
bool removeAttributeByTag(const std::string& name);
void createDocElement(sPtr docElemnt){ pDocElement_ = docElemnt; }
sPtr docElementReturn(){ return pDocElement_; }


* Build Process:
* --------------
cl /EHa /TEST_XMLDOCUMENT XmlDocument.cpp
*
* Maintenance History:
* --------------------
* ver 1.3 : 25 Mar 15
* added required functionalities
* ver 1.2 : 23 Feb 15
* - modified these comments
* ver 1.1 : 20 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
*/

#include <memory>
#include <string>
#include <stack>
#include "../XmlElement/XmlElement.h"
#include "../XmlElementParts/Tokenizer.h"
#include "../XmlElementParts/xmlElementParts.h"

///////////////////////////////////////////////
//used to create AST and perform operations on it

namespace XmlProcessing
{
  class XmlDocument
  {
  public:
    using sPtr = std::shared_ptr < AbstractXmlElement > ;

    enum sourceType { string, filename };

    XmlDocument(const std::string& src);
	XmlDocument(XmlDocument& other) = delete;
	XmlDocument(XmlDocument&& other) : pDocElement_(other.pDocElement_){other.pDocElement_ = nullptr;
		std::cout << " Move Constructor Called";}
	XmlDocument& operator=(XmlDocument&& other);

	void addElements();
	bool XmlDocument::parsingDeclareElement(std::string line);
	bool XmlDocument::parsingProcInstrElement(std::string line);
	bool XmlDocument::parsingCommentElement(std::string line);
	bool XmlDocument::parsingTaggedElement(std::string line);
	void attributesFillByTag(std::shared_ptr < AbstractXmlElement >& element, std::string check);
	XmlDocument& getElement(const std::string& tag);           // found_[0] contains first element (DFS order) with tag
	XmlDocument& getElements(const std::string& tag);          // found_ contains all elements with tag
	std::vector<sPtr> select();                            // return reference to found_.  Use std::move(found_) to clear found_
	void DFSWithTag(sPtr pNode, std::string tag);
	XmlDocument& findChildrenByTag(const std::string& tag = "");     // found_ contains sPtrs to children of prior found_[0] 
	XmlDocument& findDescendentsByTag(const std::string& tag = "");  // found_ contains sPtrs to descendents of prior found_[0]
	XmlDocument& findElementById(const std::string& id);
	void DFSWithId(sPtr pNode, std::string id);
	bool addChildrenByTag(const std::string& parent, const std::string& child);
	bool addChildrenById(const std::string& parent, const std::string& child);
	bool removeChildrenByTag(const std::string& parent, const std::string& child);
	bool removeChildrenById(const std::string& parent, const std::string& child);
	bool addRoot(std::string root);
	std::vector<std::pair<std::string, std::string>> fetchAttributesByTag(std::string tag);
	bool addAttributeByTag(const std::string& name, const std::string& value);
	bool removeAttributeByTag(const std::string& name);
	void createDocElement(sPtr docElemnt){ pDocElement_ = docElemnt; }
	sPtr docElementReturn(){ return pDocElement_; }

  private:
    sPtr pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
    std::vector<sPtr> found_;  // query results
	std::stack<sPtr> temporaryStack;
	std :: string xmFileName;	
  };
}
#endif
