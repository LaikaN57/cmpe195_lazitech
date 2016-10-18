%option main noyywrap

%option 8bit always-interactive

%{
%}

%%

  /* General Graphics State */
"w" { } // line width
"J" { } // line cap style
"j" { } // line join style
"M" { } // miter limit
"d" { } // line dash pattern
"gs" { } // EXTERNAL GRAPHICS STATE

  /* Special Graphics State */
"q" { } // push gfx state
"Q" { } // pop gfx state
"cm" { } // modify ctm

  /* Path Construction */
"m" { } // move
"l" { } // line
"c" { } // curve
"h" { } // close
"re" { } // rectangle

  /* Path Painting */
"S" { } // Stroke
"B*" { } // [fill (even-odd) and] Stroke

  /* Color */
"RG" { } // fg
"rg" { } // bg

  /* Number */
(\+|-)?(([[:digit:]]*\.[[:digit:]]+)|([[:digit:]]+\.?)) { }

  /* PDF Array */
\[(.*?)\] { }

  /* PDF Name */
\/[^[:space:]]* { }

  /* Whitespace */
[[:space:]] { }

  /* Save time and eliminate pop/push */
Q[[:space:]]q { }

  /* Other */
. { printf("Unknown char '%s'.\n", yytext); }

%%

