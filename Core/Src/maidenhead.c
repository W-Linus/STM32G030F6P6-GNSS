/*
 *@filename: maidenhead.c 
 *@Description: Convert latitude and longitude information to Maidenhead grid
 *@version: 1.0
 *@Author: BH8PHG W_Linus
 *@Date: 2022/04/25
 */
#include <maidenhead.h>

/*
 *@name: gnss_getMaidenhead
 *@brief: Convert latitude and longitude information to Maidenhead grid
 *@param: latitude,longitude,destString
 *@return: none
 */
void gnss_getMaidenhead(float latitude,float longitude,uint8_t* destString){
	float	tempNumber;					// Used in the intermediate computations
	int	index;						// Determines character to display

/*
 *	First compute the first 2 characters:
 */

	
	longitude += 180;					// 360 degrees starting from middle of the Pacific
	tempNumber = longitude / 20;			// Each major square is 20 degrees wide
	index = (int) tempNumber;			// The index to upper case letters
	destString[0] = index + 'A';				// Set first character
	longitude = longitude - ( index * 20 );			// Remainder for step 2

	latitude += 90;					// 180 degrees starting from the South pole
	tempNumber = latitude / 10;				// Each major square is 10 degrees high
	index = (int) tempNumber;			// The index to upper case letters
	destString[1] = index + 'A';				// Set second character
	latitude = latitude - ( index * 10 );			// Remainder for step 2


/*
 *	Now the 2nd two digits:
 */

	tempNumber = longitude / 2;				// Remainder from step 1 divided by 2
	index = (int) tempNumber;			// Index to digits
	destString[2] = index + '0';				// Set third character
	longitude = longitude - ( index * 2 );			// Remainder for step 3

	tempNumber = latitude;				// Remainder from step 1 divided by 1
	index = (int) tempNumber;			// Index to digits
	destString[3] = index + '0';				// Set fourth character
	latitude = latitude - index;				// Remainder for step 3


/*
 *	Now the third two characters:
 */

	tempNumber = longitude / 0.0833333;			// Remainder from step 2 divided by 0.083333
	index = (int) tempNumber;			// The index to lower case letters
	destString[4] = index  + 'a';				// Set fifth character

	tempNumber = latitude / 0.0416667;			// Remainder from step 2 divided by 0.0416667
	index = (int) tempNumber;			// The index to lower case letters
	destString[5] = index + 'a';				// Set fifth character

	destString[6] = '\0';					// Null terminator
}