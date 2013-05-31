#include "res/ResourceManager.h"

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <algorithm>

#include <UnitTest++.h>

using namespace std;

TEST(GetListFromSpacedStringReturnsCorrect)
{
	srand(time(0));
	int amountOfNums = 10000;

	vector<float> checkVec;
	for (float i = 0; i < amountOfNums / 10; i += 0.1f)
	{
		checkVec.push_back(i);
	}

	stringstream ss;
	ss << 'c';
	for (float i = 0; i < amountOfNums / 10;)
	{
		int r = rand() % 5;
		switch (r)
		{
		case 0:
		case 1:
		case 2:
			break;
		case 3:
		case 4:
			ss << ' ';
			ss << i;
			ss << ' ';
			i += 0.1;
			break;
		}
		char c = (rand() % 93) + 33;
		if ((c < 48 || c > 57) && (c != 43 && c != 45 && c != 46)) // the character is not a digit and the character != '+', '-', '.'
		{
			ss << c;
		};
	}

	vector<float> funcVec = scim::ResourceManager::GetListFromSpacedString<float>(ss.str());

	CHECK_EQUAL(funcVec.size(), checkVec.size());
	CHECK_ARRAY_CLOSE(funcVec.data(), checkVec.data(), checkVec.size(), 0.001f);
}

TEST(TryGetFileContents)
{
	std::stringstream filename;
	filename << "test/" << "TestResourceManager" << ".txt";
	std::string fileConents = scim::ResourceManager::GetFileContents(filename.str());
}
