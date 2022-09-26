%option noyywrap
%option yylineno

/* The prefix for imports in c syntax */
%{
/* For Indentation */
#include <stack>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#if __cplusplus > 199711L
#define register      // Deprecated in C++11.
#endif  // #if __cplusplus > 199711L

using namespace std;
std::stack<int> stack_indent;

#include <chocopy_parse.hpp>
#include "chocopy.tab.h"

int e1 = 1, e2 = 1,global_leng=0;
string info = "";

#define LITERAL(type) { \
    LOG(DEBUG) << #type << " " <<  yytext << " location: "<< yylloc.first_line<<" " << yylloc.first_column<< " " << (e1 = yylloc.last_line) <<" " << (e2 = yylloc.last_column); \
    return TOKEN_##type; \
}

#define LITERAL_END(type) { \
    LOG(DEBUG) << #type << " " <<  yytext << " location: "<< yylloc.first_line<<" " << yylloc.first_column<< " " << (e1 = yylloc.last_line) <<" " << (e2 = yylloc.last_column); \
    yylloc.last_column=1; yylloc.last_line+=1;  \
    return TOKEN_##type; \
}

int ColNum = 1;
int LineNum = 1;
#define SET_ACTION                                                           \
  yylloc.first_line = LineNum;                                               \
  yylloc.first_column = ColNum;                                              \
  ColNum += yyleng;                                                          \
  yylloc.last_line = LineNum;                                                \
  yylloc.last_column = ColNum;

#define ANOTHER_LINE                                                         \
  ColNum = 1;                                                                \
  LineNum += 1;
#define CLEAR_ONE                                                         \
  ColNum -= 4;                                                                \

#define YY_ANOTHER_TAB                                                       \
  ColNum += 4;
#define YY_ANOTHER_SPACE                                                     \
  ColNum += 1;
#define YY_ANOTHER_STR(i)                                                    \
  ColNum += (i);

char* copy_str(char* a,int strip=0){
  int len=0;while(a[len])++len;
  if(!strip){
    char* b=new char[len+1];
    b[len]=0;
    for(int i=0;i<len;++i)b[i]=a[i];
    return b;
  }
  else{
    char *b=new char[len-1];
    b[len-2]=0;len--;
    for(int i=1;i<len;++i)b[i-1]=a[i];
    return b;
  }
}

bool isAlpha(char c){
  return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
}

int str_cmp(const char* a,const char*b){
  int i=0,j=0;
  while(a[i]&&b[j]){if(a[i]!=b[j])return 0;i++;j++;}
  return !a[i]&&!b[j];
}

int indent_space = 0;
int logical = 0;
#define SL\
  if(!logical){\
    if(indent_space==stack_indent.top());\
    else{\
      yyless(0);\
      if(indent_space>stack_indent.top()){\
        stack_indent.push(indent_space);\
        logical=1;\
        return TOKEN_INDENT;\
      }\
      else{\
        stack_indent.pop();\
        return TOKEN_DEDENT;\
      }\
    }\
  }\
  logical=1;

%}

%x STRING

%%

%{
  /* Init indent stack_indent */
  if (stack_indent.empty()) {
    stack_indent.push(0);
  }

%}

\"     {SET_ACTION; SL; BEGIN(STRING);yymore();}
<STRING>[ \!\#-\[\]-\~]*    {yymore();}
<STRING>\\\\                {yymore();}
<STRING>\\\"                {yymore();}
<STRING>\\t                 {yymore();}
<STRING>\\n                 {yymore();}
<STRING>\"                  {
  int len=strlen(yytext),isid=1;
  for (int i=1;i<len-1;++i)
  {
    char &c = yytext[i];
    if ( !( i==1&&(isAlpha(c) && c=='_') ||
      (isAlpha(c) || c>='0'&&c<='9' || c=='_') ) )
        isid=0;
  }
  yylval.raw_str=copy_str(yytext,1);
  BEGIN(INITIAL);
  if (isid) return TOKEN_IDSTRING;
  else return TOKEN_STRING;
}
<STRING>.                {
        LOG(ERROR) << "Error: Unrecognized token on line " << yylineno << ": " << yytext;
        return 1;
}

[0-9]+                  {SET_ACTION; SL; yylval.raw_int=stoi(yytext); return TOKEN_INTEGER;}

\+    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_plus;}
-     {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_minus;}
\*    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_star;}
"//"  {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_slash;}
"%"   {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_percent;}
\<    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_less;}
\>    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_greater;}
\<=   {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_lessequal;}
\>=   {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_greaterequal;}
==    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_equalequal;}
!=    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_exclaimequal;}
=     {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_equal;}
\(    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_l_paren;}
\)    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_r_paren;}
\[    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_l_square;}
\]    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_r_square;}
,     {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_comma;}
:     {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_colon;}
\.    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_period;}
->    {SET_ACTION; SL; yylval.raw_str=copy_str(yytext); return TOKEN_rarrow;}
"\n"  {SET_ACTION; indent_space=0; ANOTHER_LINE; yylval.raw_str=copy_str(yytext); if(logical){logical=0;return TOKEN_NEWLINE;}}
" "   {SET_ACTION; indent_space++; yylval.raw_str=copy_str(yytext);}
"\t"   {SET_ACTION; indent_space+=4; yylval.raw_str=copy_str(yytext);}


[a-zA-Z_][a-zA-Z_0-9]* {
  SET_ACTION; SL;
  yylval.raw_str=copy_str(yytext);
  if (str_cmp(yytext,"True"))   return TOKEN_TRUE;
  if (str_cmp(yytext,"False"))  return TOKEN_FALSE;
  if (str_cmp(yytext,"and"))  return TOKEN_AND;
  // if (str_cmp(yytext,"break"))  return TOKEN_BREAK;
  if (str_cmp(yytext,"def"))  return TOKEN_DEF;
  if (str_cmp(yytext,"elif"))  return TOKEN_ELIF;
  if (str_cmp(yytext,"else"))  return TOKEN_ELSE;
  if (str_cmp(yytext,"for"))  return TOKEN_FOR;
  if (str_cmp(yytext,"if"))  return TOKEN_IF;
  if (str_cmp(yytext,"not"))  return TOKEN_NOT;
  if (str_cmp(yytext,"or"))  return TOKEN_OR;
  if (str_cmp(yytext,"return"))  return TOKEN_RETURN;
  if (str_cmp(yytext,"while"))  return TOKEN_WHILE;
  if (str_cmp(yytext,"None"))  return TOKEN_NONE;
  // if (str_cmp(yytext,"as"))  return TOKEN_AS;
  if (str_cmp(yytext,"class"))  return TOKEN_CLASS;
  if (str_cmp(yytext,"global"))  return TOKEN_GLOBAL;
  if (str_cmp(yytext,"in"))  return TOKEN_IN;
  if (str_cmp(yytext,"is"))  return TOKEN_IS;
  if (str_cmp(yytext,"nonlocal"))  return TOKEN_NONLOCAL;
  if (str_cmp(yytext,"pass"))  return TOKEN_PASS;
  return TOKEN_IDENTIFIER;
}

\#[^\n]* {
  SET_ACTION;
  // puts("===========================COMMENT");
}

<<EOF>> {
  if(logical){
    logical=0;
    return TOKEN_NEWLINE;
  }
  if(stack_indent.top()>0){
    stack_indent.pop();
    return TOKEN_DEDENT;
  }
  yyterminate();
}


.   {
        LOG(ERROR) << "Error: Unrecognized token on line " << yylineno << ": " << yytext;
        return 1;
    }
%%

/* int main(){
  yylex();
  return 0;
} */

/* 
^(" ")* {
  int len=strlen(yytext);
  if(len==stack_indent.top());
  else{
    if(len>stack_indent.top()){
      stack_indent.push(len);
      return TOKEN_INDENT;
    }
    else{
      stack_indent.pop();
      yyless(0);
      return TOKEN_DEDENT;
    }
  }
}

[" "\t]*

<<EOF>> {
  if(logicalline){
    logicalline=0;
    if(stack_indent.top()>0)yyless(0);
    return TOKEN_NEWLINE;
  }
  logicalline=0;
  if(stack_indent.top()>0){
    stack_indent.pop();
    yyless(0);
    return TOKEN_DEDENT;
  }
}
 */