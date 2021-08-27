#include <iostream>
#include "../RapidXML/rapidxml.hpp"
#include "../RapidXML/rapidxml_utils.hpp"
#include "../RapidXML/rapidxml_ext.hpp"
#include "../RapidXML/RapidXMLSTD.hpp"

void ReadXML();
void WriteXML();

int main()
{
    std::cout << "Hello Example!\n";

    ReadXML();
    WriteXML();

	int ret = getchar();
}

void ReadXML()
{
	//load file
	XMLDocument* xml = ::CreateXMLFromFile("ReadExample.xml");
	if (!xml)
	{
		std::cout << "XML object not created" << std::endl;
		return;
	}

	//find root
	XMLElement* root = ::FindNodeInRoot(xml, "RootElement");
	if (!root)
	{
		std::cout << "Could not find root." << std::endl;
		::FreeXML(xml);
		return;
	}

	//Reading an attribute
	auto xml_RootAttrib = root->first_attribute("Attribute");
	if (!xml_RootAttrib)
	{
		std::cout << "Could not find attribute in root." << std::endl;
		::FreeXML(xml);
		return;
	}

	char* valueAsStr = xml_RootAttrib->value();
	int valueAsNumber = atoi(valueAsStr);

	//Reading an array of elements
	XMLElement* xml_ElmentArray = root->first_node("ElementArray");
	if (!xml_ElmentArray)
	{
		std::cout << "Could not find ElmentArray xml element." << std::endl;
		::FreeXML(xml);
		return;
	}
	
	//Loops through all the elements with the name "Element"
	for (XMLElement* xml_Element = xml_ElmentArray->first_node("Element"); xml_Element; xml_Element = xml_Element->next_sibling())
	{
		if (!xml_Element)
		{
			printf("Element is not valid.\n");
			continue;
		}

		std::cout << xml_Element->value() << std::endl;
	}

	::FreeXML(xml);
}

void WriteXML()
{
	auto doc = ::CreateXML(1, "utf-8");

	auto root = ::CreateNode(doc, "ROOT", "");
	if (!::AddNodeToDocument(doc, root))
	{
		std::cout << "Could not add root" << std::endl;
		::FreeXML(doc);
		return;
	}

	if (!SetNodeDefaultNamespaces(doc, root))
	{
		std::cout << "Could not set namespaces" << std::endl;
		::FreeXML(doc);
		return;
	}

	for (size_t i = 0; i < 5; i++)
	{
		auto x = ::CreateNode(doc, "Node", "");
		auto a = ::CreateAttribute(doc, "ID", std::to_string(i));		
		::AddAttributeToNode(x, a);
		::AddNodeToNode(root, x);
	}	

	if (!::SaveXML(*doc, "test.xml"))
	{
		std::cout << "Could not create file" << std::endl;
	}
	::FreeXML(doc);
}