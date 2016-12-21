%option noyywrap

%{
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

%%

{DIGIT}+ {
	printf( "An integer: %s (%d)\n", yytext, atoi( yytext ) );
}

{DIGIT}+"."{DIGIT}* {
	printf( "A float: %s (%g)\n", yytext, atof( yytext ) );
}

if|then|begin|end|procedure|function {
	printf( "A keyword: %s\n", yytext );
}

{ID}	printf( "An identifier: %s\n", yytext );

"+"|"-"|"*"|"/"	printf( "An operator: %s\n", yytext );

"{"[^{}\n]*"}"	/* eat up one-line comments */

[ \t\n]+	/* eat up whitespace */

.	printf( "Unrecognized character: %s\n", yytext );

%%

int main( int argc, char **argv ) {
	FILE * pFile;
	int c;
	char bytes[1];

	++argv, --argc;  /* skip over program name */
	if ( argc > 0 )
		pFile = fopen( argv[0], "r" );
	else
		pFile = stdin;

	if (pFile==NULL)
		perror ("Error opening file");
	else {
		do {
			c = fgetc (pFile);

			if(c != EOF)
				break;

			bytes[0] = (char) c;
			printf("in: %c\n", bytes[0]);
			
			yy_scan_bytes(bytes, 1);
			yylex();
		} while (1);
		
		fclose (pFile);
	}
}

