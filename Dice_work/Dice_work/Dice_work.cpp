#include <iostream>
#include <string>
#include <ctime>
using namespace std;


int roll(string str)
{
	string data = "";                                                       
	int num = 0, DiceType = 0, mod = 1, sum = 0, pos = 0;
	bool modif = false;
	while (pos < str.size())                                                 
	{
		if (str[pos] == 'd')                                                 
		{                                                                   
			num = stoi(data);
			data = "";
		}
		else if (str[pos] == '+' || str[pos] == '-')                          
		{                                                                  
			modif = true;                                                  
			DiceType = stoi(data);
			data = "";
			if (str[pos] == '-') mod = -1;                                  
		}
		else if (str[pos] == ' ')                                            
		{
			if (modif) {
				mod *= stoi(data);
			}else
			{
				mod = 0;
				DiceType = stoi(data);
			}
			for (int i = 0; i < num; i++) sum += rand() % DiceType + 1;     
			sum += mod;
			modif = false;                                                 
			mod = 1;
			data = "";
			num = 0;
			DiceType = 0;
		}
		else data += str[pos];
		pos++;
	}
	return sum;
}

void main()
{
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 1000; i++) cout << roll("3d10 ") << endl;
}