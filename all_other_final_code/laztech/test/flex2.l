/* scanner for a toy Pascal-like language */

%option noyywrap

%{
/* need this for the call to atof() below */
#include <math.h>

#define YY_INPUT(buf,result,max_size) { \
  int c = getchar(); \
  result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
}
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

%%

{DIGIT}+    {
            printf( "int: %s (%d)\n", yytext,
                    atoi( yytext ) );
            }

{DIGIT}+"."{DIGIT}*        {
            printf( "flt: %s (%g)\n", yytext,
                    atof( yytext ) );
            }

if|then|begin|end|procedure|function        {
            printf( "key: %s\n", yytext );
            }

{ID}        printf( "idn: %s\n", yytext );

"+"|"-"|"*"|"/"   printf( "opt: %s\n", yytext );

"{"[^{}\n]*"}"     /* eat up one-line comments */

[ \t\n]+          /* eat up whitespace */

.           printf( "unk: %s\n", yytext );

%%

int main( int argc, char **argv ) {
    FILE * fd;
    int c;
    char bytes[3];

    bytes[2] = '\0';

    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            fd = fopen( argv[0], "r" );
    else
            fd = stdin;

    while(1) {
            c = fgetc(fd);
            if ( c == EOF ) break;
            bytes[0] = (char) c;

            c = fgetc(fd);
            if ( c == EOF ) break;
            bytes[1] = (char) c;

            printf( "in: \"%s\": ", bytes );
            yy_scan_bytes( bytes, 2 );
            yylex();
    }
}

