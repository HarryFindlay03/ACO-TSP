CC = g++

pugi_xml_parser.o: 
	g++ -c  src/pugi_xml_parser.cpp -o build/pugi_xml_parser.o

pugixml.o:
	g++ -c ext/pugixml/pugixml.cpp -o build/pugixml.o

pugi_xml_parser: pugi_xml_parser.o pugixml.o
	g++ -o bin/pugi_xml_parser build/pugi_xml_parser.o build/pugixml.o