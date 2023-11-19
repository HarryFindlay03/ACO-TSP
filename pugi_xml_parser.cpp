#include <iostream>
#include "pugixml.hpp"

int main()
{
    pugi::xml_document doc;
    if(!doc.load_file("burma14.xml")) return -1;

    pugi::xml_node nodes = doc.child("travellingSalesmanProblemInstance").child("graph");
    std::cout << nodes.name() << std::endl;

    for(pugi::xml_node node = nodes.first_child(); node; node = node.next_sibling())
    {
        std::cout << node.name() << std::endl;
        for(pugi::xml_node cost = node.first_child(); cost; cost = cost.next_sibling())
        {
            // converting to a double
            double d;
            const char* s = cost.attribute("cost").value();
            sscanf(s, "%lf", &d);
            std::cout << d << std::endl;
        }
    }
    return 0;
}



