///////////////////////////////////////////////////////////////////////
// Display.cpp - display output on console			                 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 13.0						         //
// Platform:    Dell Inspiron N5010, Win7 Professional, SP1          //
// Application: Demonstration for CSE 687, Project #2, Spring 2015   //
// Author:      Sunilkumar Lakkad, Syracuse University               //
//              (315) 751-5834, lakkads1@gmail.com                   //
///////////////////////////////////////////////////////////////////////

#include "Display.h"
#include <Windows.h>

using namespace XmlProcessing;

//----<Constructor for Display>------------------------------------------------

Display::Display(XmlDocument& ds) : store_(ds)
{

}

void Display::displayLine(char lineType)
{
	cout << endl << std::string(79, lineType)<<endl;
}
//----<Display Element/Elements with particular Tag>----------------------------------------

void Display::displayElement(std::vector<sPtr> elem, std::string title)
{
	displayLine('=');
	cout << "Demonstrating: Get Element/Elements with particular Tag";
	displayLine('=');
	if (elem.size() <= 0)
	{
		cout << "Elements with Tag " <<title <<" not found";
		displayLine('-');
	}
	else
	{
		cout << "Elements with Tag: " << title;
		displayLine('-');

		for (auto pChild : elem)
			cout << pChild->toString() << endl;
	}
	displayLine('-');
}
//----<Display Children of Parents with particular Parent Tag>-----------------------------------

void Display::displayChildrenByTag(std::vector<sPtr> elem, std::string tag, std::string tag1)
{
	displayLine('=');
	cout << "Demonstrating: Get Childrens of Parents with particular Parent Tag";
	displayLine('=');

	if (elem.size() <= 0)
	{
		cout << "Elements with tag: " << tag << "and children" << tag1 << " not found";
		displayLine('-');
	}
	else
	{
		cout << "Parent Tag: " << tag;
		displayLine('-');

		if (tag1 != "")
			cout << " Particular Element \"" << tag1 << "\" :"<< endl;
		for (auto pChild : elem)
			cout << pChild->toString() << endl;
	}
	displayLine('-');
}
//----<Display Descendents of particular Element by Tag>-----------------------------------

void Display::displayDescendentsByTag(std::vector<sPtr> e, std::string tag, std::string tag1)
{
	displayLine('=');
	cout << "Demonstrating: Get Descendents of particular Element by Tag";
	displayLine('=');
	if (e.size() <= 0)
	{
		cout << "Elements with tag: " << tag << "and children" << tag1 << " not found";
		displayLine('-');
	}
	else
	{
		cout << "Elements with tag: " << tag;
		if (tag1 != "")
			cout <<endl<< "Elements with descend: " << tag1;
		displayLine('-');
		for (auto pChild : e)
			cout << pChild->toString() << endl;
	}
	displayLine('-');
}
//----<Display Element/Elements with particular ID>-------------------------------------------

void Display::displayElementById(std::vector<sPtr> e, std::string id)
{
	displayLine('=');
	cout << "Demonstrating: Get Element/Elements with particular ID";
	displayLine('=');
	if (e.size() <= 0)
	{
		cout << "Elements with id " << id << " not found";
		displayLine('-');
	}
	else
	{
		cout << "Elements with id: " << id;
		displayLine('-');
		for (auto pChild : e)
			cout << pChild->toString() << endl;
	}
	displayLine('-');
}
//----<Display Add Children to Tree by Tag/ID>-------------------------------------------

void Display::displayAddChildren(bool success, std::string parent, std::string child, std::string type)
{
	displayLine('=');
	cout << "Demonstrating: Add Children to Tree by Parent's "<< type;
	displayLine('=');

	cout << "Parent's "<<type<<": " << parent << endl;
	cout << "Children: " << child;
	displayLine('-');

	if (success)
	{
		cout << "The Children added Successfully by "<<type;
		displayLine('-');
		sPtr elements = store_.docElementReturn();
		cout << elements->toString();
	}
	else
		cout << "Add Opreation Fails!!";
	displayLine('-');

}
//----<Display Remove Children to Tree by Tag/ID>--------------------------------------------------

void Display::displayRemoveChildren(bool success, std::string parent, std::string child, std::string type)
{
	displayLine('=');
	cout << "Demonstrating: Remove Children to Tree by Parent's "<<type;
	displayLine('=');

	cout << "Parent's" << type <<": " << parent << endl;
	cout << "Children: " << child;
	displayLine('-');

	if (success)
	{
		cout << "The children Removed successfully by "<< type <<endl;
		displayLine('-');
		sPtr elements = store_.docElementReturn();
		cout << elements->toString();
	}
	else
		cout << "Remove Opreation Fails!!";
	displayLine('-');

}
//----<Display Add Root element to empty Tree>------------------------------------

void Display::displayAddRoot(bool success, std::string root)
{
	displayLine('=');
	cout << "Demonstrating: Add Root element to empty Tree ";
	displayLine('=');

	cout << "The Tag of the root to be added: " << root;
	displayLine('-');
	if (success)
	{
		cout << "The root has been added successfully";
		displayLine('-');
		sPtr elements = store_.docElementReturn();
		cout << elements->toString();
	}
	else
		cout << "Tree contains root already, Operation Fail!!";
	displayLine('-');
}
//----<Display Attributes for a tag>-------------------------------------------

void Display::displayFetcedAttributesByTag(std::vector<std::pair<std::string, std::string>> attr, std::string elem)
{
	displayLine('=');
	cout << "Demonstrating: Get Attributes for a tag ";
	displayLine('=');

	cout << "The Attributes of the tag to be fetched: " << elem;
	displayLine('-');

	if (attr.size() > 0)
	{
		cout << endl;
		for (auto pair : attr)
			cout << pair.first << "=" << pair.second << endl;
	}
	else
		cout << "No attributes fetched";
	displayLine('-');
}
//----<display add Attributes for a tag>-----------------------------------------

void Display::displayAddAttributeByTag(bool success, std::string parent, std::string key, std::string value)
{
	displayLine('=');
	cout << "Demonstrating: Add Attributes for a tag ";
	displayLine('=');

	cout << "Attributes to be added: " << key << "=" <<value << endl;
	cout << "The Tag for which its added: " << parent;
	displayLine('-');

	if (success)
	{
		cout << endl;
		cout << "The Attributes has been added successfully to Tree"<<endl;
		displayLine('-');
		sPtr elements = store_.docElementReturn();
		cout << elements->toString();
	}
	else
		cout << "Add Attributes Operation Fails!!";
	displayLine('-');
}
//----<Display Remove Attributes for a tag>-----------------------------------

void Display::displayRemoveAttributeByTag(bool success, std::string parent, std::string value)
{
	displayLine('=');
	cout << "Demonstrating: Remove Attributes for a tag ";
	displayLine('=');

	cout << "Attributes to be removed: " << value << endl;
	cout << "The Tag for which its removed: " << parent;
	displayLine('-');

	if (success)
	{
		cout << endl;
		cout << "The Attributes has been removed successfully to Tree" << endl;
		displayLine('-');
		sPtr elements = store_.docElementReturn();
		cout << elements->toString();
	}
	else
		cout << "Remove Attributes Operation Fails!!";
	displayLine('-');
}
//----<Creating and storing an XML file>---------------------------------

void Display:: displayCreateXml(int counter)
{
	displayLine('=');
	cout << "Demonstrating: Creating XML";
	displayLine('=');

	std::string s = std::to_string(counter);
	string xmFileName = "xml" + s + ".xml";
	std::ofstream outfile(xmFileName);
	if (store_.docElementReturn() != nullptr)
	{
		outfile << store_.docElementReturn()->toString() << std::endl;
		cout << endl;
		cout << "The file Created: " << xmFileName << endl;
	}
	outfile.close();
	displayLine('-');
}
//----<Display Move Constructors Operation>---------------------------

void Display:: displayMoveConst()
{
	displayLine('=');
	cout << "Demonstrating: Move Constructor";
	displayLine('=');
	cout << endl;
	XmlDocument doc2 = std::move(store_);
	XmlDocument doc3(" ");
	doc3 = std::move(doc2);
	displayLine('-');
}
//----<Test Stub>-------------------------------------------------

#ifdef TEST_DISPLAY

void main()
{
	using sPtr = std::shared_ptr < AbstractXmlElement >;

	XmlDocument doc("LectureNote.xml"); Display d(doc);
	string parent = "LectureNote"; string child = "newChild"; string parent1 = "LectureNote"; string child1 = "newChild1";
	string root = "root"; std::string key = "key"; std::string value = "value"; string title = "title";	string tag = "reference"; string tag1 = "author"; string id = "Wintellect";
	doc.addElements();												//creating the AST
	std::vector<sPtr> a = doc.getElement(title).select();
	d.displayElement(a, title);										//display Element
	std::vector<sPtr> b = doc.getElements(title).select();
	d.displayElement(b, title);									//display Elements
	std::vector<sPtr> c = doc.getElement(tag).findChildrenByTag().select();
	d.displayChildrenByTag(c, tag, "");									//display Children
	std::vector<sPtr> save = doc.getElement(tag).findDescendentsByTag().select();
	d.displayDescendentsByTag(save, tag, "");										//display Descendents
	std::vector<sPtr> childsearch = doc.getElement(tag).findChildrenByTag(tag1).select();
	d.displayChildrenByTag(childsearch, tag, tag1);
	std::vector<sPtr> dsearch = doc.getElement(tag).findDescendentsByTag(tag1).select();
	d.displayDescendentsByTag(dsearch, tag, tag1);
	std::vector<sPtr> ele = doc.findElementById(id).select();
	d.displayElementById(ele, id);												//display ElementById
	bool save2 = doc.addChildrenByTag(parent, child);
	d.displayAddChildren(save2, parent, child, "Tag");									//display AddChildren
	bool save21 = doc.addChildrenById(parent1, child1);
	d.displayAddChildren(save21, parent1, child1, "ID");							//display AddchilbyId
	bool save3 = doc.removeChildrenByTag(parent, child);
	d.displayRemoveChildren(save3, parent, child, "Tag");								//display RemoveChildren
	bool save31 = doc.removeChildrenById(parent1, child1);
	d.displayRemoveChildren(save31, parent1, child1, "ID");						//displayRemoveChildrenById
	bool save4 = doc.addRoot(root);
	d.displayAddRoot(save4, root);												//displayAddRoot
	std::vector<std::pair<std::string, std::string>> save5 = doc.fetchAttributesByTag(parent);
	d.displayFetcedAttributesByTag(save5, parent);
	bool save6 = doc.getElement(parent).addAttributeByTag(key, value);
	d.displayAddAttributeByTag(save6, parent, key, value);							//display AddAttribute
	bool save7 = doc.getElement(parent).removeAttributeByTag(value);
	d.displayRemoveAttributeByTag(save7, parent, value);								//displayRemoveAttribute
	d.displayCreateXml(1);												//displayCreateXml
	d.displayMoveConst();
}

#endif
