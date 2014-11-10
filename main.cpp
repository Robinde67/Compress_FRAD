//
//  main.cpp
//  compress
//
//  Created by Robin on 10/11/14.
//  Copyright (c) 2014 FRAD. All rights reserved.
//


#include "Compress.h"

#include <string>
#include <iostream>

class Compress;

using namespace std;


int main(int argc, const char * argv[]) {
	string link;
	


    // insert code here...
    std::cout << "Hello, World!\n";
	cout<<"type a pathway to a bmp-file: ";
	getline(cin, link);
	cin.ignore();
	const char* path = link.c_str();
	cout << path << "-" << path[5] << endl;
	unsigned found = link.find_last_of(".");
	std::cout << " type: " << link.substr(found+1) << '\n';
	if (link.substr(found + 1) == "bmp")
	{
		Compress *compress = new Compress(path);
		
		std::cout << "Compressing" << std::endl;
	}
	else if (link.substr(found + 1) == "FRAD" || link.substr(found + 1) == "frad")
	{
		std::cout << "Decompressed" << std::endl;
	}

	else cout << "this ain't no file a kno'";
	getchar();
    return 0;
};
