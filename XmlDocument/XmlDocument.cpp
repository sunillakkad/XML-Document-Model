/////////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes               //
// Ver 1.3                                                         //
// Language:    C++, Visual Studio 13.0						       //
// Platform:    Dell Inspiron N5010, Win7 Professional, SP1        //
// Application: Demonstration for CSE 687, Project #2, Spring 2015 //
// Author:      Sunilkumar Lakkad, Syracuse University             //
//              (315) 751-5834, lakkads1@gmail.com                 //
// Source:      Jim Fawcett, CST 4-187, Syracuse University        //
//              (315) 443-3948, jfawcett@twcny.rr.com              //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "XmlDocument.h"

using namespace XmlProcessing;

//----<Constructor for XmlDocument>---------------------------------------------------

XmlProcessing::XmlDocument::XmlDocument(const std::string& fileName)
{
	xmFileName = fileName;
}
//----<Move Assignment for XmlDocument>----------------------------------------------------------

XmlDocument& XmlDocument:: operator=(XmlDocument&& other)
{
	if (this != &other)
	{
		pDocElement_.reset();
		std::cout << "\n Move Assignment operator Called" << std::endl;
		pDocElement_ = other.pDocElement_;
		other.pDocElement_ = nullptr;
	}
	return *this;
}
//----<Parsing XML tags and inserting elements in AST>-------------------------------------------

void XmlDocument::addElements()
{
	Toker toker(xmFileName);
	toker.setMode(Toker::xml);
	XmlParts parts(&toker);
	pDocElement_ = makeDocElement();
	std::string text;
	int counter = 0;
	while (parts.get())
	{
		if (parts.length() <= 1 && counter == 0)
			return;
		counter++;
		bool success = false;
		bool success1 = false;
		std::string line = parts.show();
		success = parsingDeclareElement(line);
		success = parsingProcInstrElement(line);
		success = parsingCommentElement(line);
		success1 = parsingTaggedElement(line);
		if (!success && !success1)
		{
			text = line;
			if (!temporaryStack.empty())
			{
				sPtr sp = temporaryStack.top();
				sp->addChild(makeTextElement(text));
			}
		}
	}
}

bool XmlDocument::parsingDeclareElement(std::string line)
{
	int temp = line.find("? xml");
	int temp1 = line.find("? xml -");
	if (temp != -1 && temp1 == -1)
	{
		sPtr sp = makeXmlDeclarElement();
		temp = line.find("=");
		if (temp != -1)
			attributesFillByTag(sp, line);

		pDocElement_->addChild(sp);
		return true;
	}
	return false;
}

bool XmlDocument::parsingProcInstrElement(std::string line)
{
	int temp = line.find("? xml -");
	int temp1 = line.find(" = ");
	if (temp != -1)
	{
		int ext;
		std::string insert;
		for (unsigned int i = 6; i < line.size(); i++)
		{
			if (line[i] == '=' || line[i] == '?')
				break;
			if (line[i - 1] == ' ')
				ext = i - 1;
			insert.push_back(line[i]);
		}
		std::string str = insert.substr(0, (ext - 6));
		insert.clear();
		for (unsigned int i = 0; i < str.size(); i++)
		{
			if (str[i] != ' ')
				insert.push_back(str[i]);
		}
		sPtr sp = makeProcInstrElement(insert);
		if (temp1 != -1)
			attributesFillByTag(sp, line);

		pDocElement_->addChild(sp);
		return true;
	}
	return false;
}
bool XmlDocument::parsingCommentElement(std::string line)
{
	int temp = line.find("!");
	if (temp != -1)
	{
		int temp = line.find("-");
		std::string str;
		for (unsigned int i = temp + 3; i < line.size(); i++)
		{
			str.push_back(line[i]);
			if (line[i + 2] == '-')
				break;
		}
		sPtr sp = makeCommentElement(str);
		pDocElement_->addChild(sp);
		return true;
	}
	return false;
}

bool XmlDocument::parsingTaggedElement(std::string line)
{
	int temp = line.find("? xml");
	int temp1 = line.find("? xml -");
	int temp2 = line.find(" = ");
	int temp3 = line.find("!");
	int temp4 = line.find("<");
	int temp5 = line.find("< /");
	int temp6 = line.find("/ >");
	bool success = false;
	if ((temp == -1) && (temp2 != -1 || temp4 != -1 || temp6 != -1) && (temp3 == -1) && (temp5 == -1) && (temp1 == -1))
	{
		std::string insert;
		for (unsigned int i = 4; i < line.size(); i++)
		{
			if (line[i] == ' ')
				break;
			insert.push_back(line[i]);
		}
		sPtr sp = makeTaggedElement(insert);
		if (temp2 != -1)
			attributesFillByTag(sp, line);
		if (temporaryStack.empty())
			pDocElement_->addChild(sp);
		else{
			sPtr a = temporaryStack.top();
			a->addChild(sp);
		}
		temporaryStack.push(sp);
		success = true;
	}
	if (temp5 != -1)
	{
		if (!temporaryStack.empty())
		{
			temporaryStack.pop();
			success = true;
		}
	}
	return success;
}
//----<Fill Atributes in AST Tags>----------------------------------------------------------

void XmlDocument::attributesFillByTag(std::shared_ptr < AbstractXmlElement >& element, std::string line)
{
	std::string attr;
	std::string temp;
	std::string value;
	for (unsigned int ins = 0; ins < line.size(); ins++)
	{
		if (line[ins] == '=')
		{
			attr.clear();
			value.clear();
			temp.clear();
			for (unsigned int i = ins - 2; i > 0; i--)
			{
				temp.push_back(line[i]);
				if (line[i] == ' ')
					break;
			}
			for (unsigned int j = temp.size() - 2; j >= 0; j--)
			{
				attr.push_back(temp[j]);
				if (j == 0)
					break;
			}
			for (unsigned int k = ins + 3; k < line.size(); k++)
			{
				if (line[k] == '\"' || line[k] == '\'')
					break;
				value.push_back(line[k]);
			}
			element->addAttrib(attr, value);
		}
	}
}
//----<Find Element using Tag from the AST>-----------------------------------------------

XmlDocument& XmlDocument::getElement(const std::string& tag)
{
	found_.clear();
	std::vector<sPtr> children;
	if (pDocElement_ != nullptr)
	{
		children = pDocElement_->children();
		for (std::vector<sPtr>::iterator iter = children.begin(); iter != children.end(); ++iter)
			DFSWithTag(*iter, tag);

		if (found_.size() > 0)
			found_.erase(found_.begin() + 1, found_.begin() + found_.size());
	}
	return *this;
}
//----<Find Elements using Tag from the AST>------------------------------------------------

XmlDocument& XmlDocument::getElements(const std::string& tag)
{
	found_.clear();
	std::vector<sPtr> children;
	if (pDocElement_ != nullptr)
	{
		children = pDocElement_->children();
		for (std::vector<sPtr>::iterator iter = children.begin(); iter != children.end(); ++iter)
			DFSWithTag(*iter, tag);
	}
	return *this;
}
//----<Return Vector of sPtrs from AST>--------------------------------------------------------

std::vector<std::shared_ptr < AbstractXmlElement >> XmlDocument::select()
{
	return found_;
}
//----<Depth first Search over AST>-----------------------------------------------------------------

void XmlDocument::DFSWithTag(sPtr pNode, std::string tag)
{
	if (pNode->value() == tag)
	{
		found_.push_back(pNode);
		for (auto pChild : pNode->children())
			DFSWithTag(pChild, "");
	}

	if (tag == "" && dynamic_cast<TextElement*>(pNode.get()) == nullptr)
		found_.push_back(pNode);
	for (auto pChild : pNode->children())
		DFSWithTag(pChild, tag);
}
//----<Finding Children in AST using Parent's Tag>---------------------------------------------------

XmlDocument& XmlDocument::findChildrenByTag(const std::string& tag)
{
	std::vector<sPtr> children = found_;
	if (found_.size() <= 0)
		return *this;

	sPtr sp = found_[0];
	found_.clear();
	children = sp->children();
	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i]->value() == tag || tag == "")
		{
			if (dynamic_cast<TextElement*>(children[i].get()) == nullptr)
				found_.push_back(children[i]);
		}
	}
	return *this;
}
//----<Finding Descendents in AST of Partucular Element by Tag >----------------------------------

XmlDocument& XmlDocument::findDescendentsByTag(const std::string& tag)
{
	std::vector<sPtr> children = found_;
	if (found_.size() <= 0)
		return *this;

	sPtr sp = found_[0];
	found_.clear();
	children = sp->children();

	for (std::vector<sPtr>::iterator iter = children.begin(); iter != children.end(); ++iter)
		DFSWithTag(*iter, tag);
	return *this;
}
//----<Find Element using ID from the AST>----------------------------------------------

XmlDocument& XmlDocument::findElementById(const std::string& id)
{
	found_.clear();
	std::vector<sPtr> children;
	if (pDocElement_ != nullptr)
	{
		children = pDocElement_->children();
		for (std::vector<sPtr>::iterator iter = children.begin(); iter != children.end(); ++iter)
			DFSWithTag(*iter, "");

		children = found_;
		found_.clear();
		for (std::vector<sPtr>::iterator iter = children.begin(); iter != children.end(); ++iter)
		{
			if (dynamic_cast<TaggedElement*>((*iter).get()) != nullptr || dynamic_cast<ProcInstrElement*>((*iter).get()) != nullptr || dynamic_cast<XmlDeclarElement*>((*iter).get()) != nullptr)
			{
				std::vector<std::pair<std::string, std::string>> attr = (*iter)->returnAttrib();
				for (std::vector<std::pair<std::string, std::string>>::iterator iter1 = attr.begin(); iter1 != attr.end(); ++iter1)
				{
					if ((iter1->second) == id)
						found_.push_back((*iter));
				}
			}
		}
	}
	return *this;
}
//----<Depth First Search over AST to Search ID>--------------------------------------------

void XmlDocument::DFSWithId(sPtr pNode, std::string id)
{

	if (dynamic_cast<TaggedElement*>(pNode.get()) != nullptr || dynamic_cast<ProcInstrElement*>(pNode.get()) != nullptr || dynamic_cast<XmlDeclarElement*>(pNode.get()) != nullptr)
	{
		std::vector<std::pair<std::string, std::string>> attr = pNode->returnAttrib();
		for (std::vector<std::pair<std::string, std::string>>::iterator iter = attr.begin(); iter != attr.end(); ++iter)
		{
			if ((iter->second) == id)
			{
				found_.push_back(pNode);
				for (auto pChild : pNode->children())
					DFSWithTag(pChild, id);
			}
		}

	}

	for (auto pChild : pNode->children())
		DFSWithTag(pChild, id);
}
//----<Add Children in AST using Parent's Tag>------------------------------------------------

bool XmlDocument::addChildrenByTag(const std::string& parent, const std::string& child)
{
	std::vector<std::shared_ptr < AbstractXmlElement >> root = getElement(parent).select();
	if (root.size() <= 0)
		return false;

	sPtr taggedElement = makeTaggedElement(child);
	root[0]->addChild(taggedElement);
	return true;
}
//----<Add Children in AST by ID>---------------------------------------------------------

bool XmlDocument::addChildrenById(const std::string& parent, const std::string& child)
{
	std::vector<std::shared_ptr < AbstractXmlElement >> root = findElementById(parent).select();
	sPtr taggedElement = makeTaggedElement(child);
	if (root.size() > 0)
	{
		root[0]->addChild(taggedElement);
		return true;
	}
	return false;
}
//----<Remove Children in AST By Tag>-------------------------------------------------

bool XmlDocument::removeChildrenByTag(const std::string& parent, const std::string& child)
{
	bool success = false;
	std::vector<std::shared_ptr < AbstractXmlElement >> root = getElement(parent).select();
	if (root.size() <= 0)
		return false;
	std::vector<std::shared_ptr < AbstractXmlElement >> children = root[0]->children();
	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i]->value() == child)
		{
			root[0]->removeChild(children[i]);
			success = true;
			break;
		}
	}
	return true;
}
//----<Remove Children in AST by ID>--------------------------------------------

bool XmlDocument::removeChildrenById(const std::string& parent, const std::string& child)
{
	bool success = false;
	std::vector<std::shared_ptr < AbstractXmlElement >> root = findElementById(parent).select();
	if (root.size()>0)
	{
		std::vector<std::shared_ptr < AbstractXmlElement >> children = root[0]->children();
		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children[i]->value() == child)
			{
				root[0]->removeChild(children[i]);
				return true;
			}
		}
	}
	return false;
}
//----<add root in an empty tree>--------------------------------------------

bool XmlDocument::addRoot(std::string root)
{
	auto save = getElement("").select();
	DocElement* de = dynamic_cast<DocElement*> (pDocElement_.get());
	if (de != NULL){
		if ((de->hasXmlRoot()))
		{
			return false;
		}
		else
		{
			sPtr taggedElement = makeTaggedElement(root);
			pDocElement_->addChild(taggedElement);
			return true;
		}
	}
	else
	{
		pDocElement_ = makeDocElement();
		sPtr taggedElement = makeTaggedElement(root);
		pDocElement_->addChild(taggedElement);
		return true;
	}
}
//----<Fetch Attributes from AST by Tag>------------------------------------------------

std::vector<std::pair<std::string, std::string>> XmlDocument::fetchAttributesByTag(std::string tag)
{
	std::vector<std::shared_ptr < AbstractXmlElement >> root = getElement(tag).select();
	std::vector<std::pair<std::string, std::string>> attr;
	if (root.size() > 0)
		attr = root[0]->returnAttrib();
	return attr;
}
//----<Add Attributes to AST by Tag>----------------------------------------------------

bool XmlDocument::addAttributeByTag(const std::string& name, const std::string& value)
{
	std::vector<sPtr> children = found_;
	if (found_.size() <= 0)
		return false;
	sPtr sp = found_[0];
	for (auto pElement : children)
	{
		if (dynamic_cast<TaggedElement*>(sp.get()) != nullptr || dynamic_cast<ProcInstrElement*>(sp.get()) != nullptr || dynamic_cast<XmlDeclarElement*>(sp.get()) != nullptr)
		{
			pElement->addAttrib(name, value);
			return true;
		}
	}
	return false;
}
//----<Remove Attributes from AST by Tag>----------------------------------------------------------------

bool XmlDocument::removeAttributeByTag(const std::string& name)
{
	std::vector<sPtr> children = found_;
	if (found_.size() <= 0)
		return false;

	bool success = false;
	for (auto pElement : children)
	{
		if (dynamic_cast<TaggedElement*>(pElement.get()) != nullptr || dynamic_cast<ProcInstrElement*>(pElement.get()) != nullptr || dynamic_cast<XmlDeclarElement*>(pElement.get()) != nullptr)
		{
			std::vector<std::pair<std::string, std::string>> p = pElement->returnAttrib();
			for (auto save : p)
			{
				if (save.second == name)
				{
					success = pElement->removeAttrib(name);
					success = true;
					return success;
				}
			}
		}
	}
	return success;
}

#ifdef TEST_XMLDOCUMENT

int main()
{
	title("Testing XmlDocument class");
	XmlDocument doc("LectureNote.xml");
	using sPtr = std::shared_ptr < AbstractXmlElement > ;
	std::cout << "\n\n";
	doc.addElements();
	auto save = doc.getElement("reference").findDescendentsByTag().select();
	auto savee = doc.getElement("reference").findChildrenByTag().select();
	auto ele = doc.findElementById("Wintellect").select();
	auto save1 = doc.getElements("title").select();
	auto save2 = doc.addChildrenByTag("LectureNote", "newChild");
	auto save21 = doc.addChildrenById("CSE681", "newChild");
	auto save3 = doc.removeChildrenByTag("LectureNote", "newChild");
	auto save31 = doc.removeChildrenById("CSE681", "newChild");
	auto save4 = doc.addRoot("root");
	auto save5 = doc.fetchAttributesByTag("LectureNote");
	auto save6 = doc.getElement("LectureNote").addAttributeByTag("dlsn", "sdksj");
	auto save7 = doc.getElement("LectureNote").removeAttributeByTag("dlsn");
	std::cout << std::endl << doc.docElementReturn()->toString() << std::endl;
	std::ofstream outfile("test.xml");
	outfile << doc.docElementReturn()->toString() << std::endl;
	outfile.close();
	std::cout << std::endl << "The File Created: test.xml" << std::endl;

	std::cout << "\nDemonstrating move constructor" << std::endl;
	XmlDocument doc2 = std::move(doc);
	XmlDocument doc3(" ");
	doc3 = std::move(doc2);
	std::cout << "\n\n";
}
#endif
