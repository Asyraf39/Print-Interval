#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main()
{
	int slide_per_page, total_slide, stage = 1, pos = 0;
	string pages, temp, choice;
	stringstream front, back;
	bool push = false, range = false;
	vector<int> print;
	vector<int> stage1;
	vector<int> stage2;
	vector<int> exclude;
	
	do
	{
		cout << "Enter the total number of slides : ";
		getline(cin, temp);
		total_slide = atoi(temp.c_str());
		
		cout << "Enter the number of slides per page : ";
		getline(cin, temp);
		slide_per_page = atoi(temp.c_str());
		
		cout << "Please enter exception pages, '0' if none : ";
		getline(cin, pages);
		
		for(int i = 0; i < total_slide; i++)
		{
			print.push_back(i+1);
		}
		
		for(int j = 0; j < pages.length(); j++)
		{
			if(isdigit(pages[j]) && push == true)
			{
				pos = j;
				push = false;
			}
			
			if((!isdigit(pages[j]) && !isspace(pages[j])) || j == pages.length() - 1)
			{
				temp = pages.substr(pos, j + 1 - pos);
				
				if(range == true)
				{
					for(int k = exclude[exclude.size() - 1]; k < atoi(temp.c_str()); k++)
					{
						exclude.push_back(exclude[exclude.size() - 1] + 1);
					}
					range = false;
				}
				else
				{
					exclude.push_back(atoi(temp.c_str()));	
				}
				push = true;
				
				if(pages[j] == '-')
				{
					range = true;
				}
			}
		}
		
		sort(exclude.begin(),exclude.end());
		exclude.erase(unique(exclude.begin(), exclude.end()), exclude.end());
		
		for(int l = 0; l < exclude.size(); l++)
		{
			for(int m = 0; m < print.size(); m++)
			{
				if(exclude[l] == print[m])
				{
					for(int n = m + 1; n < print.size(); n++)
					{
						print[n-1] = print[n];
					}
					print.pop_back();
				}
			}
		}
		
		for(int o = 0; o < print.size(); o++)
		{
			if(o % (slide_per_page * 2) < slide_per_page)
			{
				stage1.push_back(print[o]);
			}
			else
			{
				stage2.push_back(print[o]);
			}
		}
		
		for(int p = 0; p < stage1.size(); p++)
		{
			if(stage1[p] != stage1[stage1.size() - 1])
			{
				if(stage1[p+1] - stage1[p] != 1)
				{
					if(p != 0)
					{
						if(stage1[p] - stage1[p-1] == 1)
						{
							front << "-";
						}
					}
					front << stage1[p] << ", ";
				}
				else
				{
					if(p == 0)
					{
						front << stage1[p];
					}
					else if(stage1[p] - stage1[p-1] != 1)
					{
						front << stage1[p];
					}
				}
			}
			else
			{
				if(p != 0)
				{
					if(stage1[p] - stage1[p-1] == 1)
					{
						front << "-";
					}
				}
				front << stage1[p];
			}
		}
		
		for(int q = 0; q < stage2.size(); q++)
		{
			if(stage2[q] != stage2[stage2.size() - 1])
			{
				if(stage2[q+1] - stage2[q] != 1)
				{
					if(q != 0)
					{
						if(stage2[q] - stage2[q-1] == 1)
						{
							back << "-";
						}
					}
					back << stage2[q] << ", ";
				}
				else
				{
					if(q == 0)
					{
						back << stage2[q];
					}
					else if(stage2[q] - stage2[q-1] != 1)
					{
						back << stage2[q];
					}
				}
			}
			else
			{
				if(q != 0)
				{
					if(stage2[q] - stage2[q-1] == 1)
					{
						back << "-";
					}
				}
				back << stage2[q];
			}
		}

		ofstream myfile;
		myfile.open("Print interval.txt");
		myfile << front.str() << endl;
		myfile << back.str();
		myfile.close();
		
		stage = 1;
		pos = 0;
		pages = "";
		temp = "";
		front.str("");
		back.str("");
		while(print.size() != 0)
		{
			print.pop_back();
		}
		while(stage1.size() != 0)
		{
			stage1.pop_back();
		}
		while(stage2.size() != 0)
		{
			stage2.pop_back();
		}
		while(exclude.size() != 0)
		{
			exclude.pop_back();
		}
		
		cout << "Do you want to start over? ('Y' if yes, any other key if no)" << endl << ">";
		getline(cin, choice);
		cout << endl;
	}
	while(choice == "Y" || choice == "y");
	
	//system("PAUSE");
	return 0;
}
