#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <string> //delete this include while rebuild programm and // imeToStr line

// SETTINGS

#define MAXTITLELENGTH 50
#define MAXBODYLENGTH 10000

// global variables

//unsigned int numberOfTasks = 0;

// basic functons

char * getPassword ()
{
	char input [51];
	// remake getline to correct input method
	
	std::cout << "Enter the password: ";
	std::cin.getline ( input, 50 );

	char * password = new char [std::strlen(input)];
	std::strcpy ( password, input );

	return password;
}

std::string timeToStr ( int time )
{
	if ( time < 60 )
	{
		return std::to_string ( time ) + " sec ago";
	}
	if ( time < 3600 )
	{
		return std::to_string ( time / 60 ) + " min ago";
	}
	if ( time < 216000 )
	{
		return std::to_string ( time / 3600 ) + " h. ago";
	}
	return std::to_string ( time / 216000 ) + " d. ago";
}


// EnctyptFunctions

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

// clases


struct Task
{
	char * title;
	char * body;
	std::time_t appendTime;
};

struct Tasks
{
	Task ** tasks;
	unsigned int length = 0;
};

Task * getTask ( char * title, char * body )
{
	return new Task { title, body, std::time (0) };
}

Task * getTask (void)
{
	char title [MAXTITLELENGTH];
	char body [MAXBODYLENGTH] = "\0";
	char bodyLine [MAXBODYLENGTH];
	char * pointerTitle;// new char [MAXTITLELENGTH];
	char * pointerBody;// new char [MAXBODYLENGTH];
	
	// entering body
	std::cout << "Please enter the body:\n";
	
	while ( true )
	{	
		std::cin.getline ( bodyLine, MAXBODYLENGTH - 1 );

		if ( int( std::strlen ( body ) + std::strlen(bodyLine) ) >= int (MAXBODYLENGTH))
		{
			std::cout << "[ERROR] Input stream full\nDeleting last line...\n";
			break;
		}
		
		std::strcpy ( body, std::strcat ( body, bodyLine ));
		//std::strcpy ( pointerBody, body );
		
		if ( body [ std::strlen ( body ) - 1] == '\\' )
		{
			body[std::strlen (body) - 1] = '\n';
			continue;
		}
		break;

	}
	
	pointerBody = new char [std::strlen ( body )];
	std::strcpy ( pointerBody, body );
	
	// add backword to clear the task body...	

	// creating title
	
	std::cout << "Please enter the title:\n";

	// append function if title == " " make title by first 2-4 words

	std::cin.getline ( title, MAXTITLELENGTH - 1 );
	
	pointerTitle = new char [std::strlen( title )];
	std::strcpy ( pointerTitle, title );

	//std::cin.getline (  );
	return getTask ( pointerTitle, pointerBody );
}

int encryptFile ( char * filename, char * mask )
{
	//std::strcpy ( filename, "text.txt");
	std::ifstream fileIn;
	fileIn.open ( filename );

	if ( !fileIn.is_open ())
	{
		std::cout << "Error while opening file =(\n";
		std::exit(EXIT_FAILURE);
	}

	char line [1000];

	while ( fileIn.good ())
	{
		fileIn.getline ( line, 999 );
		//std::cout << line;
		//std::cout << "\n";
		std::cout << fastEncrypt ( line, mask );
		//std::cout << "\n";
		//std::cout << fastDecode ( fastEncrypt (line, mask), mask );
	}
	
	return 0;
}

int dump ( Tasks * tasks, char * mask )
{
	char filename [] = ".tasks";
	
	std::ofstream outFile;
	outFile.open (filename);

	for ( int i = 0; i < tasks->length; i++ )
	{
		char * taskText = new char [std::strlen( tasks->tasks[i]->body ) + 1 + std::strlen(  tasks->tasks[i]->title )];
		std::strcpy ( taskText, tasks->tasks[i]->title );
		taskText [std::strlen(  tasks->tasks[i]->title )] = '\\';
		std::strcpy ( taskText, std::strcat ( taskText, tasks->tasks[i]->body  ) );
		//std::cout << "Mask : \"" <<  mask << "\"\n";
		//std::cout << fastEncrypt ( taskText, mask ) << "\n" << taskText;
		outFile << fastEncrypt ( taskText, mask ); 
		//outFile << "|";
		//outFile << fastEncrypt ( tasks->tasks[i]->body, mask );
		outFile << "\n<--new-->\n";
		delete [] taskText;
	}
	
	//std::cout << tasks << "\n";
	//std::cout << tasks->tasks[0]->title;
	outFile.close();
	return 0;	
}

Tasks * load ( char * filename, char * mask )
{
	std::ifstream inputFile;
	inputFile.open ( filename );

	if ( !fileIn.is_open ())
	{
		std::cout << "Error while opening file =(\n";
		std::exit(EXIT_FAILURE);
	}

	char line [ MAXBODYLENGTH + MAXTITLELENGTH ];
	
	while ( fileIn.good ())
	{
		fileIn.getline ( line, ( MAXBODYLENGTH + MAXTITLELENGTH ) );	
		line = fastDecode ( line, mask );
		
		for ( int i = 0; i < std::strlen ( line ) );

		std::cout << fastEncrypt ( line, mask );
	}	
}

void printTasksArr ( Task ** tasks, unsigned int length )
{
	std::cout << "Total tasks: " << length << "\n";
	for ( int i = 0; i < length; i++ )	
	{
		std::cout << i << ". task:\n";
		std::cout << tasks[i]->title << "\n" << tasks[i]->body << "\n";
	}
}

void printTasksArr ( Tasks * tasks )
{
	printTasksArr ( tasks->tasks, tasks->length );	
}

int main ()
{
	char * password = getPassword ();
	Tasks * tasks = new Tasks { new Task * [2], 2}; 
	//Task **  = new Task * [2];
	tasks->tasks[0] = getTask ();
	tasks->tasks[1] = getTask ();
		
	std::cout << "Mask: " << password;
	dump ( tasks, password );
	//printTasksArr ( tasks->tasks, tasks->length );
	//Task * task = getTask ();
	//std::cout << task->title << "\n" << task->body << "\n";
	delete [] password;
	delete tasks;
	return 0;
}
