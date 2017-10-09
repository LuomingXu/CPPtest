#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<string>
#include<ctime>
using namespace std;

int numberOFpeople = 0;

double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

template<class T>
void convertFromStringToInt(T &value, const std::string &s)
{
	std::stringstream ss(s);
	ss >> value;
}

std::vector<std::string> Split(const std::string& s, const std::string& delim)
{//#include string vector algorithm
	std::vector<std::string> v;

	if (!delim.empty())
	{
		auto b = s.begin();
		auto i = s.end();
		while ((i = std::search(b, s.end(), delim.begin(), delim.end())) != s.end())
		{
			if (i - b > 0) // token can't be empty string
			{
				v.emplace_back(std::string(b, i));
			}

			b = i + delim.length();
		}

		if (b != s.end())
		{
			v.emplace_back(std::string(b, s.end()));
		}
	}
	else
	{
		throw "Delimiter can't be empty string";
	}

	return v;
}

class People
{
public:
	~People();
	int pwd = 0;
	int originIndex;
};

People::~People()
{

}

int main()
{
	srand(unsigned(time(0)));//time seed

	#pragma region testCode
			//for study
			/*std::string s("0,10");
			auto v = Split(s, ",");
			std::cout << v[0] << endl;
			double temp = 0;
			convertFromStringToInt(temp, v[0]);
			std::cout << temp << endl;
			for each (auto var in v)
			{
			std::cout << var << endl;
			}*/
	#pragma endregion

	std::cout << "Please input the number of people" << endl;
	std::cin >> numberOFpeople;

	People people[10];

	std::cout << "Please input the password's range which belong to people" << endl;
	std::cout << "LIKE: 1,10" << endl;
	string str;
	int pwdStart = 0, pwdEnd = 0;
	std::cin >> str;
	auto v = Split(str, ",");
	convertFromStringToInt(pwdStart,v[0]);
	convertFromStringToInt(pwdEnd, v[1]);

	for (int i = 0; i < numberOFpeople; i++)
	{
		people[i].pwd = (int)random(pwdStart, pwdEnd);//the random range is "[start, end)"
		people[i].originIndex = i;
	}//for--assign the pwd
	std::cout << "Has assigned pwd..." << endl;

	for (int i = 0; i < numberOFpeople; i++)
	{
		std::cout << i << "  " << people[i].originIndex << "  " << people[i].pwd << endl;
	}//for--display all data

	int cycle = 0;
	std::cout << "Please input the first cycling times" << endl;
	std::cin >> cycle;

	int firstPeople = 0;
	std::cout << "Please input the first people" << endl;
	std::cin >> firstPeople;

	while (people[0].pwd > 0)
	{
		firstPeople--;
		if (cycle > numberOFpeople)
			cycle %= numberOFpeople;
		std::cout << "cycle : " << cycle << endl;

		if (cycle == 0)//if the cycle == 0, the firstPeople which should be deleted is the last people
		{
			firstPeople = numberOFpeople;
		}
		else
		{
			for (int i = 0; i < cycle; i++)
			{
				if (++firstPeople > numberOFpeople)
				{
					firstPeople = 1;
				}
			}//for--confirm the first cycle people
		}
		
		std::cout << "firstPeople: " << firstPeople<< endl;
		std::cout << "The deleted people is " << people[firstPeople - 1].originIndex + 1 << "  His pwd is " << people[firstPeople - 1].pwd << endl;

		cycle = people[firstPeople - 1].pwd;
		People temp;
		for (int i = (firstPeople - 1); i < numberOFpeople; i++)
		{
			temp = people[++i];
			people[--i] = temp;
		}//for--delete the rubbish data

		if (--numberOFpeople == 0)//if numberOFpeople == 0 break this WHILE
			break;

		for (int i = 0; i < numberOFpeople; i++)
		{
			std::cout << people[i].originIndex + 1 << "   " << people[i].pwd << endl;
		}//for--display the rest data

		std::cout << "-----------------------" << endl;
	}

	std::cout << endl << "The cycle is ended..." << endl;
	std::cout << "Please input any key to exit..." << endl;
	getchar();
	getchar();
	return 0;
}