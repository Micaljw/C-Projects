%{
#include <stdio.h>
#include "y.tab.h"

%}

%%
go|move|walk|run 				return MOTION;
north|south|east|west 				yylval = strdup(yytext); return DIRECTION;
take|look|inventory|open|grab|search|examine	yylval = strdup(yytext); return ACTION;	
drink|use					return DRINK;
small|medium					yylval = strdup(yytext); return POTION;									
attack|stab|trip|lunge				yylval = strdup(yytext); return FIGHT;	
talk|speak					return CONVERSE;
equip						return EQUIP;
iron|chest|boots|gloves|steel			yylval = strdup(yytext); return ITEM;
equipped					return EQUIPPED;
stats						return STATS;
exit|quit|leave|terminate|finished 		return EXIT;
help						return HELP;
start						return START;
\n                     
[ \t]+    
.             
%%
