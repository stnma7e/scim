#include <UnitTest++.h>

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		printf("USAGE: test_scim\n");
		for (int i = 1; i < argc; ++i)
		{
			printf("\tinvalid arg: \"%s\"\n", argv[i]);
		}
		return 1;
	}

	return UnitTest::RunAllTests();
}
