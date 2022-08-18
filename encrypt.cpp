#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>

// makeEnctyptFunctions

char * fastEncrypt ( char * str, char * mask )
{
	char * encryptedStr = new char [std::strlen ( str )];
	int maskLength = std::strlen ( mask );

	for (int i = 0, maskIndex = 0; i < std::strlen(str); i++)
	{
		if ( ++maskIndex == maskLength ) maskIndex = 0;

		encryptedStr[i] = str[i] + mask[maskIndex];
	}

	return encryptedStr;
}

// decodingDunctions


char * fastDecode ( char * str, char * mask )
{
	char * decodedStr = new char [std::strlen ( str )];
	int maskLength = std::strlen ( mask );

	for (int i = 0, maskIndex = 0; i < std::strlen(str); i++)
	{
		if ( ++maskIndex == maskLength ) maskIndex = 0;

		decodedStr[i] = str[i] - mask[maskIndex];
	}

	return decodedStr;
}

int main ()
{
	char filename [50];
	char mask [] = "abcdefg";

	//std::strcpy ( filename, "text.txt");
	std::cin.getline ( filename, 49 );

	std::ifstream file;
	file.open ( filename );

	if ( !file.is_open ())
	{
		std::cout << "Error while opening file =(\n";
		std::exit(EXIT_FAILURE);
	}

	char line [1000];

	while ( file.good ())
	{
		file.getline ( line, 999 );
		//std::cout << line;
		//std::cout << "\n";
		std::cout << fastEncrypt ( line, mask );
		std::cout << "\n";
		//std::cout << fastDecode ( fastEncrypt (line, mask), mask );
	}
	
	return 0;
}
