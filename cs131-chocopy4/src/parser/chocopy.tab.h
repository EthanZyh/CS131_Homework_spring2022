/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_HOME_YEWANDOU_CS131_PA_CS131_CHOCOPY2_SRC_PARSER_CHOCOPY_TAB_H_INCLUDED
# define YY_YY_HOME_YEWANDOU_CS131_PA_CS131_CHOCOPY2_SRC_PARSER_CHOCOPY_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_INTEGER = 258,
    TOKEN_IDENTIFIER = 259,
    TOKEN_STRING = 260,
    TOKEN_IDSTRING = 261,
    TOKEN_TRUE = 262,
    TOKEN_FALSE = 263,
    TOKEN_AND = 264,
    TOKEN_DEF = 265,
    TOKEN_ELIF = 266,
    TOKEN_ELSE = 267,
    TOKEN_FOR = 268,
    TOKEN_IF = 269,
    TOKEN_NOT = 270,
    TOKEN_OR = 271,
    TOKEN_RETURN = 272,
    TOKEN_WHILE = 273,
    TOKEN_NONE = 274,
    TOKEN_CLASS = 275,
    TOKEN_GLOBAL = 276,
    TOKEN_IN = 277,
    TOKEN_IS = 278,
    TOKEN_NONLOCAL = 279,
    TOKEN_PASS = 280,
    TOKEN_plus = 281,
    TOKEN_minus = 282,
    TOKEN_star = 283,
    TOKEN_slash = 284,
    TOKEN_percent = 285,
    TOKEN_less = 286,
    TOKEN_greater = 287,
    TOKEN_lessequal = 288,
    TOKEN_greaterequal = 289,
    TOKEN_equalequal = 290,
    TOKEN_exclaimequal = 291,
    TOKEN_equal = 292,
    TOKEN_l_paren = 293,
    TOKEN_r_paren = 294,
    TOKEN_l_square = 295,
    TOKEN_r_square = 296,
    TOKEN_comma = 297,
    TOKEN_colon = 298,
    TOKEN_period = 299,
    TOKEN_rarrow = 300,
    TOKEN_INDENT = 301,
    TOKEN_DEDENT = 302,
    TOKEN_NEWLINE = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 100 "chocopy.y"

  char * raw_str;
  int raw_int;
  const char *error_msg;
  ::parser::Program *PtrProgram;
  ::parser::Stmt *PtrStmt;
  ::parser::Decl *PtrDecl;
  ::parser::AssignStmt *PtrAssignStmt;
  ::parser::BinaryExpr *PtrBinaryExpr;
  ::parser::BoolLiteral *PtrBoolLiteral;
  ::parser::CallExpr *PtrCallExpr;
  ::parser::ClassDef *PtrClassDef;
  ::parser::ClassType *PtrClassType;
  ::parser::CompilerErr *PtrCompilerErr;
  ::parser::Err *PtrErr;
  ::parser::Expr *PtrExpr;
  ::parser::ExprStmt *PtrExprStmt;
  ::parser::ForStmt *PtrForStmt;
  ::parser::FuncDef *PtrFuncDef;
  ::parser::GlobalDecl *PtrGlobalDecl;
  ::parser::Ident *PtrIdent;
  ::parser::IfExpr *PtrIfExpr;
  ::parser::IndexExpr *PtrIndexExpr;
  ::parser::IntegerLiteral *PtrIntegerLiteral;
  ::parser::ListExpr *PtrListExpr;
  ::parser::ListType *PtrListType;
  ::parser::Literal *PtrLiteral;
  ::parser::MemberExpr *PtrMemberExpr;
  ::parser::MethodCallExpr *PtrMethodCallExpr;
  ::parser::Node *PtrNode;
  ::parser::NoneLiteral *PtrNoneLiteral;
  ::parser::NonlocalDecl *PtrNonlocalDecl;
  ::parser::ReturnStmt *PtrReturnStmt;
  ::parser::StringLiteral *PtrStringLiteral;
  ::parser::TypeAnnotation *PtrTypeAnnotation;
  ::parser::TypedVar *PtrTypedVar;
  ::parser::UnaryExpr *PtrUnaryExpr;
  ::parser::VarDef *PtrVarDef;
  ::parser::WhileStmt *PtrWhileStmt;
  ::parser::IfStmt *PtrIfStmt;
  ::parser::AccOptions *PtrAccOptions;
  ::parser::VarAssignStmt *PtrVarAssignStmt;
  ::parser::MemberAssignStmt *PtrMemberAssignStmt;
  ::parser::IndexAssignStmt *PtrIndexAssignStmt;
  ::parser::VarAssignExpr *PtrVarAssignExpr;
  ::parser::MemberAssignExpr *PtrMemberAssignExpr;
  ::parser::IndexAssignExpr *PtrIndexAssignExpr;
  std::vector<::parser::Decl *> *PtrListDecl;
  std::vector<::parser::Stmt *> *PtrListStmt;
  std::vector<::parser::TypedVar *> *PtrListTypedVar;

#line 158 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_HOME_YEWANDOU_CS131_PA_CS131_CHOCOPY2_SRC_PARSER_CHOCOPY_TAB_H_INCLUDED  */
