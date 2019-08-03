#include <iostream>
#include <string>
#include "unistd.h"
using namespace std;

int main(int argc,char *argv[])
{

// test argv
//=======================================================
//	string a ;
//	cout<<"display the content"<<endl;
//	while(getline(cin,a))
//	{
//	    cout<<"length = "<<a.length()<<endl;
//	    cout<<a<<endl;
//	}
//=======================================================

// test getopt function
//=======================================================
	int options;
	const char * optstring="hs:d:";
	while ((options= getopt(argc, argv, optstring)) != -1)
	{
		switch(options)
		{
			case 'h':
			    cout<<"option is -h"<<endl;	
				break;
			case 's':
				cout<<"option is -s, optarg is "<<optarg<<endl;
				break;
			case 'd':
			    cout<<"option is -d, optarg is "<<optarg<<endl;	
				int num=stoi(optarg);
				cout<<num<<endl;
				break;
		}
	}
//=======================================================

	return 0;
}
