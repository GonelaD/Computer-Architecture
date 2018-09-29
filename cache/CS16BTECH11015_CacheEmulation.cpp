#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

  
 

bool search(vector<string> v, int numelem , string tmp)
{
	for(int i=0;i<numelem;i++)
	{
		if(v[i]==tmp)return true;
	}
	return false;
}
int search2(string tmp, string cache[] , int size)
{
	for(int i=0;i<size;i++)
	{
		if(cache[i]==tmp)return i;
	}
	return -1;
}
void FIFO(string input,int NOE,string end)
{
	string tmp;

	int misses=0;
	int compulsory=0;
	int capacity=0;
	int accesses=0;
	std::string a="CS16BTECH11015_FIFO_";
	for(int i=0;i<input.length()-4;i++)
	{
		a = a+input[i];
	}
	a= a+"_"+end+".txt";

	const char* c=a.c_str();
	const char* in=input.c_str();
	vector<string> v,final; // v keeps track of elements present in the cache
	deque<string> q; //queue takes  care of order

	ifstream myfile;
	ofstream outfile;
	myfile.open(in);
	outfile.open(c);


	
	int i=0;
	int hits=0;

	while(myfile>>tmp)
	{

		
		if(find(q.begin(),q.end(),tmp)!=q.end())
		{
			
			final.push_back("HIT");
			i--;
			hits++;
			accesses++;
		}
		else if(q.size()<NOE && find(q.begin(),q.end(),tmp)==q.end())
		{
			final.push_back("MISS");
			accesses++;
			if(search(v,v.size(),tmp))
			{
				capacity++;
			}
			else
			{
				compulsory++;
			}
			
			v.push_back(tmp);
			misses++;
			q.push_back(tmp);
		}
		else 
		{
			if(search(v,v.size(),tmp))
			{
				capacity++;
			}
			else
			{
				compulsory++;
			}
			final.push_back("MISS");
			q.pop_front();
			accesses++;
			v.push_back(tmp);
			misses++;
			q.push_back(tmp);
		}

		i++;

	}
	



	outfile<<"TOTAL_ACCESSES="<<accesses<<endl;

	outfile<<"TOTAL_MISSES="<<misses<<endl;

	outfile<<"COMPULSORY_MISSES="<<compulsory<<endl;
	outfile<<"CAPACITY_MISSES="<<capacity<<endl;
	for(vector<string>::const_iterator i = final.begin(); i != final.end(); ++i) {
    outfile << *i << endl;}
}





void OPTIMAL(string input,int NOE,string end)
{
	
	string address[50000];
	string cache[1024];
	string tmp;
	int counter[1024];
	vector<string> final;
	int cache_size=0;
	int hits=0;
	std::string a="CS16BTECH11015_OPTIMAL_";
	for(int i=0;i<input.length()-4;i++)
	{
		a = a+input[i];
	}
	a= a+"_"+end+".txt";

	const char* c=a.c_str();
	const char* in=input.c_str();
	int misses=0;
	int accesses=0;
	int total_size=0;
	int capacity=0;
	int compulsory=0;
	

	ifstream myfile;
	ofstream outfile;
	myfile.open(in);
	outfile.open(c);

	while(myfile >> tmp)
	{
		address[total_size]=tmp;
		total_size++;
		
	}

	
	int i;
	for( i=0; i<total_size ; i++)
	{
		
		tmp = address[i];
		
		if(search2(tmp,cache,cache_size)!=-1){
			final.push_back("HIT");
			hits++;
			
			accesses++;
		}
		else
        {
            final.push_back("MISS");
            misses++;
            accesses++;
            if(search2(tmp,address,i)!= -1)capacity++;
            else compulsory++;
            
            if(cache_size == NOE)
            {
           		int replacement;

			

			int flag;
			for(int j =0 ; j<cache_size ; j++){
				string val=cache[j];
				flag=0;
				for(int k=i;k<total_size;k++){

					
					if(val==address[k]){
						
						counter[j]=k;

						flag=1;
						break;
					}
				}

				if(flag==0)
				{
				 replacement=j;
				 break;
				}
			}

			
			if(flag==1)
			{
				int max = counter[0];
				replacement=0; 
				for(int m=0;m<cache_size;m++)
				{
					
					if(counter[m]>max){
						max=counter[m];
						replacement=m;
					}
				}
				
				
			}

			cache[replacement]=tmp;     

           
               
            }
            else
            {   
                cache[cache_size]=tmp;
                cache_size=(cache_size+1);
               

            }
               
        }
		


			

	}

	outfile<<"TOTAL_ACCESSES="<<accesses<<endl;

	outfile<<"TOTAL_MISSES="<<misses<<endl;

	outfile<<"COMPULSORY_MISSES="<<compulsory<<endl;
	outfile<<"CAPACITY_MISSES="<<capacity<<endl;

	for(vector<string>::const_iterator i = final.begin(); i != final.end(); ++i) {
    outfile << *i << endl;}
}


void LRU( string input, int NOE,string end)
{
	string tmp;
	//string add1="LRU";
	int misses=0;
	int accesses=0;
	int capacity=0;
	int compulsory=0;
	vector<string> final;
	std::string a="CS16BTECH11015_LRU_";
	for(int i=0;i<input.length()-4;i++)
	{
		a = a+input[i];
	}



	list<string> list1;
	vector<string> v;
	a= a+"_"+end+".txt";

	const char* c=a.c_str();
	const char* in=input.c_str();

	ifstream myfile;
	ofstream outfile;
	myfile.open(in);
	outfile.open(c);
	int i=0;
	


	while(myfile>>tmp)
	{


		if(find(list1.begin(),list1.end(),tmp) == list1.end() && list1.size()<NOE )
		{
			final.push_back("MISS");
			misses++;
			if(search(v,v.size(),tmp))
			{
				capacity++;
			}
			else
			{
				compulsory++;
			}
			accesses++;
			v.push_back(tmp);
			list1.push_front(tmp);
		}

		else if(find(list1.begin(),list1.end(),tmp) == list1.end() && list1.size()>NOE-1 )
		{
			final.push_back("MISS");
			misses++;
			if(search(v,v.size(),tmp))
			{
				capacity++;
			}
			else
			{
				compulsory++;
			}
			accesses++;
			v.push_back(tmp);
			list1.pop_back();
			list1.push_front(tmp);

		}

		else 
		{
			final.push_back("HIT");
			accesses++;
			list1.remove(tmp);
			list1.push_front(tmp);
		}

		i++;
	}


	outfile<<"TOTAL_ACCESSES="<<accesses<<endl;

	outfile<<"TOTAL_MISSES="<<misses<<endl;

	outfile<<"COMPULSORY_MISSES="<<compulsory<<endl;
	outfile<<"CAPACITY_MISSES="<<capacity<<endl;
	for(vector<string>::const_iterator i = final.begin(); i != final.end(); ++i) {
    outfile << *i << endl;}
}




int main(int argc, char *argv[])
{


	if(strcmp(argv[1],"OPTIMAL") == 0)
	{
		int entries = atoi(argv[3]);
		OPTIMAL(argv[2],entries,argv[3]);
	}

	if(strcmp(argv[1],"FIFO")==0)
	{
		int entries = atoi(argv[3]);
		FIFO(argv[2],entries,argv[3]);
	}

	if(strcmp(argv[1],"LRU")==0)
	{
		int entries = atoi(argv[3]);
		LRU(argv[2],entries,argv[3]);
	}

}