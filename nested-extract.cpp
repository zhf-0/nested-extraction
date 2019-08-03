#include <iostream>
#include <fstream>
#include <string>
#include "unistd.h"
#include <vector>

struct Node
{
    int begin=0,end=0;
	Node * parent = NULL;
	Node * left = NULL;
	Node * right = NULL;
};

class Tree
{
public:
	Node * root;
	Node * header;

	Tree()
	{
		root = NULL;
		header = NULL;
	}

	Tree(std::string str, char l, char r)
	{
        int len = str.length();
		root = new Node;
		root->begin = 0;
		root->end = len;
		header = root;
		for(int i=0;i<len;i++)
		{
			if(str[i] == l)
			{
				if(header->end == 0)
				{
					header->left = new Node;
					header->left->begin = i;
					header->left->parent = header;
					header = header->left;
				}
				else
				{
					header->right = new Node;
					header->right->begin = i;
					header->right->parent = header;
					header = header->right;
				}

			}
			if(str[i] == r)
			{
				if(header->end == 0)
					header->end = i;
				else
				{
					while(header->end != 0)
						header = header->parent;

					header->end = i;
				}
			}
		}
	}

	void select(int num,int *index)
	{
		header = root;
		for(int i=0;i<num;i++)
		{
           if(i%2 == 0)
		   {
		      for(int j=0;j<index[i];j++)
			  {
				  if(header->right != NULL)
				  {
					  header = header->right;
				  }
				  else
				  {
					  header->begin = 0;
					  header->end = 1;
					  //std::cerr<<"index is out of range"<<std::endl;
					  return ;
				  }
			  }
		   }
		   else
		   {
		      for(int j=0;j<index[i];j++)
			  {
				  if(header->left != NULL)
				  {
					  header = header->left;
				  }
				  else
				  {
					  header->begin = 0;
					  header->end = 1;
					  //std::cerr<<"index is out of range"<<std::endl;
					  return ;
				  }
			  }
		   }
		}
		//std::cout<<"begin="<<header->begin<<"  end="<<header->end<<std::endl;
	}



	void destroy(Node *point)
	{
		if(point == NULL)
			return ;
		destroy(point->left);
		destroy(point->right);
		delete point;
	}


	~Tree()
	{
		destroy(root);
		root = NULL;
		header = NULL;
    }
};


void split(std::string & input,std::vector<std::string> &output,char d)
{
    int start=0;
	int len=input.length();
	for(int i=0;i<len;i++)
	{
		if(input[i] == d)
		{
			output.push_back(input.substr(start,i-start));
			start = i+1;
		}
	}
	output.push_back(input.substr(start,len-start));
}

struct Config
{
	char left='{';
	char right='}';
	char delimiter=':';

	bool pflag=0;
	std::string pcache;

	int fileflag=0;
	std::string filename;

	int rflag=0;
	std::string rcache;

	std::string input;
};

Config result;

void  display_oneline(Tree& tree)
{
	if(result.pflag == 1)
	{
		std::vector<std::string> first_split;
		split(result.pcache,first_split,';');
		std::vector<std::string> second_split;
		for(unsigned long  i=0;i<first_split.size();i++)
		{
			split(first_split[i],second_split,'-');
			int temp[10];
			int n = second_split.size();
			for(int j=0;j<n;j++)
				temp[j]=stoi(second_split[j]);

			tree.select(n,temp);
			std::cout<<result.input.substr(tree.header->begin+1,tree.header->end - tree.header->begin -1);
			if(i == first_split.size()-1)
				std::cout<<std::endl;
			else
				std::cout<<result.delimiter;

			second_split.clear();
		}
	}
	else
	{
		std::cout<<result.input<<std::endl;
	}
}


void replace_oneline(Tree & tree)
{
	std::vector<std::string> first_split;
	split(result.rcache,first_split,';');
	std::vector<std::string> second_split;
	int start=0;
	for(unsigned long i =0;i<first_split.size();i=i+2)
	{
		split(first_split[i],second_split,'-');
		int temp[10];
		int layer=second_split.size();
		for(int j=0;j<layer;j++)
			temp[j]=stoi(second_split[j]);

		tree.select(layer,temp);
		if(result.rflag == 1)
		{
			std::cout<<result.input.substr(start,tree.header->begin+1-start);
			std::cout<<first_split[i+1];
		    start = tree.header->end;
		}
		else if(result.rflag == 2)
		{
			std::cout<<result.input.substr(start,tree.header->begin-start);
			std::cout<<first_split[i+1];
		    start = tree.header->end+1;
		}

		second_split.clear();
	}

	std::cout<<result.input.substr(start,result.input.size() - start)<<std::endl;

}


void display_help()
{
	std::cout<<"Options:"<<std::endl;
	std::cout<<" -h	display help information"<<std::endl;
	std::cout<<" -a	the string that needed to be dealt with"<<std::endl;
	std::cout<<" -s	using which pair of symbol to split the string, default symbols are '{}'"<<std::endl;
	std::cout<<" -f	the name of file that needed to be dealt with"<<std::endl;
	std::cout<<" -p	print which part of string, default behavior is printing the whole string"<<std::endl;
	std::cout<<" -d	using which delimiter to seperate the output, default symbol is ':'"<<std::endl;
	std::cout<<" -r	replace the selected content with new content, exclude the pair of symbol"<<std::endl;
	std::cout<<" -R	replace the selected content with new content, include the pair of symbol"<<std::endl;
}


void final_output()
{
	Tree a(result.input,result.left,result.right);
	if(result.rflag == 0)
		display_oneline(a);
	else
		replace_oneline(a);
}


int main(int argc, char* argv[])
{


	int options;
	const char * optstring="hs:d:p:f:a:r:R:";
	while ((options= getopt(argc, argv, optstring)) != -1)
	{
		switch(options)
		{
			case 'h':
				display_help();
				return 0;
			case 's':
				result.left = optarg[0];
				result.right = optarg[1];
				break;
			case 'd':
				result.delimiter = optarg[0];
				break;
			case 'p':
				result.pflag = 1;
				result.pcache = optarg;
				break;
			case 'f':
				result.fileflag =1;
				result.filename = optarg;
				break;
			case 'a':
				result.fileflag = 2;
				result.input = optarg;
				break;
			case 'r':
				result.rflag = 1;
				result.rcache = optarg;
				break;
            case 'R':
				result.rflag = 2;
				result.rcache = optarg;
				break;
		}
	}


    if(result.fileflag == 0) // pipeline input
	{
		while(getline(std::cin,result.input))
			final_output();
	}
	else if(result.fileflag == 1) // file input
	{
		std::ifstream ifs(result.filename);
		if(!ifs)
		{
            std::cout<<"can't open the file"<<std::endl;
			return 0;
		}
		else
		{
			while(getline(ifs,result.input))
				final_output();
		}
	}
	else // single command input
	{
		final_output();
	}

	return 0;
}
