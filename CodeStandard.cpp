/*----------------------------------------------------------------------------------------------
-- DATE: 		February 17, 2015
--
-- Source File:	CodeStandard.cpp
--
-- REVISIONS: 	(Date and Description)
--
-- DESIGNER:	Jeff Bayntun and Calvin Rempel
--
-- PROGRAMMER:	Jeff Bayntun
--
--
-- INTERFACE:
--	void LineUp::addCustomer( Customer* cust, string time, size_t complainDelay )
--	void LineUp::increaseMorale( string time )
--
--
-- NOTES: 	This file defines and displays the code standard for the COMP 4981 Linux Game
			project.  Functions should only be commented in the cpp file, not the header.
			All rules are defined in below, in this comment.  There is a sample 
			class below to show how these rules are used.  If something is unclear, or you
			feel that more rules should be added, let Calvin or I know.
			
			RULES:
			
			1) 	Headers - All source files and functions should be commented with 'Aman style' 
				headers. This includes a main header at the top of the file and one for each 
				function.
				
			2)	Class Names - CamelCase with the first letter of each word capitalized.
			
			3)	Variable/Function Names - camelCase with very first letter lower case.  
				Constants should be all capitals.
			
			4)	Code Blocks - Curly braces should be own their own unindented (from the previous
				block) line for each code block.  This applies to both opening and closing 
				braces.
				
			5)	Magic numbers are bad.
			
			6)	Comments - Wherever it improves readability or understanding of the code
			
-----------------------------------------------------------------------------------------------*/
#include <deque>
#include <string>
#include "CodeStandard.h"

using namespace std;

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		LineUp::AddCustomer
--
-- DATE:			February 10, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Jeff Bayntun
--
-- PROGRAMMER:		Jeff Bayntun
--
-- INTERFACE:		void LineUp::addCustomer( Customer* cust, string time, size_t complainDelay )
--	cust:			pointer to the customer to add
--	time:			formatted string with the current time
--	complainDelay:	delay incurred when a complaint is made
--
-- RETURNS: 		void
--
-- NOTES:			Adds a Customer to the lineup, outputs this info to the console.
-----------------------------------------------------------------------------------------------*/
void LineUp::addCustomer( Customer* cust, string time, size_t complainDelay )
{
	line.push_back( cust );
	cout << time << "Customer ID: " << cust->getId() << " Has Joined Queue ID: " << id << endl;
	if( line.size() == 1 ) // this is the only customer in the line
	{
		serveCustomer( 0, complainDelay, time );
	}
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION:	LineUp::increaseMorale
--
-- DATE:		February 10, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Jeff Bayntun
--
-- PROGRAMMER:	Jeff Bayntun
--
-- INTERFACE:	void LineUp::increaseMorale( string time)
--	time:		formatted string with the current time
--
-- RETURNS: 	void
--
-- NOTES: 		increases the morale of all customers in the line
-----------------------------------------------------------------------------------------------*/
void LineUp::increaseMorale( string time )
{
	for( unsigned int i = 0; i < line.size(); i++ )
	{
		line[i]->increaseMorale( time );
	}
}
