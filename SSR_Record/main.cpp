#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<time.h>
#include<fstream>

using namespace std;

struct people
{
	char name[20];
	int timeLen;
	int timeList[30];
	
};

people People[20];
int PeopleSum = 0;



void AddPeople(const char *name)
{
	strcpy(People[PeopleSum].name,name);
	PeopleSum++;
}

void ShowAllPeople()
{
	cout << "name\ttime\n";
	
	for(int i=0;i<PeopleSum;i++)
	{
		cout << People[i].name << "\t";
		for (int j = 0; j < People[i].timeLen; j++)
		{
			cout << People[i].timeList[j] << "\t";
		}
		cout << endl;
	}
	if (PeopleSum == 0)
	{
		cout << "\tno result" << endl;
	}
}

void AddTime(const char* name,int timedata)
{
	for (int i = 0; i < PeopleSum; i++)
	{
		if (strcmp(name, People[i].name) == 0)
		{
			if (timedata == 0)
			{
				time_t timeNow = time(0);

				tm *timeNow1 = localtime(&timeNow);
				timedata =(( timeNow1->tm_year+1900) * 100 + timeNow1->tm_mon+1)*100+timeNow1->tm_mday+1;
				cout << "timeData " << timedata << endl;
			}
			People[i].timeList[People[i].timeLen] = timedata;
			People[i].timeLen++;
		}
	}
}

void DelPeople(const char *name)
{

	for (int i = 0; i < PeopleSum; i++)
	{
		if (strcmp(People[i].name, name) == 0)
		{
			cout << "233" << endl;
			for (int j = i; j <PeopleSum-1; j++)
			{
				People[j] = People[j + 1];
			}
			memset((void*)&People[PeopleSum - 1], 0, sizeof(People[PeopleSum - 1]));
			
			PeopleSum--;
		}
	}

}



void save()
{
	ofstream outfile;
	outfile.open("savedata.txt",ios::binary);

	outfile.write((char*)&PeopleSum, sizeof(PeopleSum));
	for (int i = 0; i < PeopleSum; i++)
	{
		outfile.write((char*)&People[i], sizeof(People[i]));
	}
	outfile.close();
}

void load()
{
	ifstream infile;
	infile.open("savedata.txt",ios::binary);

	infile.read((char*)&PeopleSum, sizeof(PeopleSum));
	
	for (int i = 0; i < PeopleSum; i++)
	{
		infile.read((char*)&People[i], sizeof(People[i]));
	}
}

int main()
{
	load();
	cout << "SSR_Record" << endl;
	cout << "__________________________________________" << endl;
	while (1)
	{
		cout << "1.show 2.add people 3.add time 4.del people 5.quit" << endl;
		int index;
		cin >> index;
		if (index == 1)
		{
			ShowAllPeople();
		}
		else if (index == 2)
		{
			cout << "name?";
			char name[20];
			cin >> name;
			AddPeople(name);
		}
		else if (index == 3)
		{
			cout << "name?";
			char name[20];
			cin >> name;
			cout << "time?(input 0 is today)";
			int time;
			cin >> time;
			AddTime(name, time);
		}
		else if (index == 4)
		{
			cout << "name?";
			char name[20];
			cin >> name;
			DelPeople(name);
		}
		else if (index == 5)
		{
			save();
			break;
		}
	}

	return 0;
}