//
//  main.cpp
//  compress
//
//  Created by Robin on 10/11/14.
//  Copyright (c) 2014 FRAD. All rights reserved.
//
#include <string.h>
#include <iostream>
using namespace std;


int main(int argc, const char * argv[]) {
	char* path;
	

    // insert code here...
    std::cout << "Hello, World!\n";
	cout<<"type a pathway to a bmp-file to compress or decompress:  ";
	cin>>path;
	cin.ignore();
	
	if(path[sizeof(path)] == 'p')
	{
	}
	else if(path[sizeof(path)] == 'D')
	{
	}

	else cout<<"this ain't no file a kno'"

    return 0;
};
