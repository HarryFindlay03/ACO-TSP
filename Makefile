CC = g++

aco_driver.o:
	g++ -c src/aco_driver.cpp -o build/aco_driver.o

pugi_xml_parser.o: 
	g++ -c  src/pugi_xml_parser.cpp -o build/pugi_xml_parser.o

pugixml.o:
	g++ -c ext/pugixml/pugixml.cpp -o build/pugixml.o

aco_driver: aco_driver.o pugi_xml_parser.o pugixml.o
	g++ -o bin/aco_driver build/pugi_xml_parser.o build/pugixml.o