%option noyywrap
%%
.|\n printf("String: \"%s\".\n", yytext);
