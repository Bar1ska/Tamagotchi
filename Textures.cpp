#include <iostream>
#include <stdlib.h>
#include "Textures.h"


void Textures::read(string path)
{
	ifstream file(path);
	if (file.is_open())
	{
		while (getline(file, line, '\n'))
		{
			tamagotchi.push_back(line);
		}
	}
	file.close();
}
void Textures::print()
{
	system("CLS");
	for (int i = 0; i < tamagotchi.size(); ++i)
	{
		cout << tamagotchi[i] << endl;
	}
}
