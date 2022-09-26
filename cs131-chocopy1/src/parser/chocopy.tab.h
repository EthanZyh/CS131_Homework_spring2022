/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_CHOCOPY_TAB_H_INCLUDED
# define YY_YY_CHOCOPY_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_INTEGER = 258,           /* TOKEN_INTEGER  */
    TOKEN_IDENTIFIER = 259,        /* TOKEN_IDENTIFIER  */
    TOKEN_STRING = 260,            /* TOKEN_STRING  */
    TOKEN_TRUE = 261,              /* TOKEN_TRUE  */
    TOKEN_FALSE = 262,             /* TOKEN_FALSE  */
    TOKEN_AND = 263,               /* TOKEN_AND  */
    TOKEN_BREAK = 264,             /* TOKEN_BREAK  */
    TOKEN_DEF = 265,               /* TOKEN_DEF  */
    TOKEN_ELIF = 266,              /* TOKEN_ELIF  */
    TOKEN_ELSE = 267,              /* TOKEN_ELSE  */
    TOKEN_FOR = 268,               /* TOKEN_FOR  */
    TOKEN_IF = 269,                /* TOKEN_IF  */
    TOKEN_NOT = 270,               /* TOKEN_NOT  */
    TOKEN_OR = 271,                /* TOKEN_OR  */
    TOKEN_RETURN = 272,            /* TOKEN_RETURN  */
    TOKEN_WHILE = 273,             /* TOKEN_WHILE  */
    TOKEN_NONE = 274,              /* TOKEN_NONE  */
    TOKEN_AS = 275,                /* TOKEN_AS  */
    TOKEN_CLASS = 276,             /* TOKEN_CLASS  */
    TOKEN_GLOBAL = 277,            /* TOKEN_GLOBAL  */
    TOKEN_IN = 278,                /* TOKEN_IN  */
    TOKEN_IS = 279,                /* TOKEN_IS  */
    TOKEN_NONLOCAL = 280,          /* TOKEN_NONLOCAL  */
    TOKEN_PASS = 281,              /* TOKEN_PASS  */
    TOKEN_DECORATOR = 282,         /* TOKEN_DECORATOR  */
    TOKEN_ACC = 283,               /* TOKEN_ACC  */
    TOKEN_PARALLEL = 284,          /* TOKEN_PARALLEL  */
    TOKEN_LOOP = 285,              /* TOKEN_LOOP  */
    TOKEN_VECTOR = 286,            /* TOKEN_VECTOR  */
    TOKEN_WORKER = 287,            /* TOKEN_WORKER  */
    TOKEN_plus = 288,              /* TOKEN_plus  */
    TOKEN_minus = 289,             /* TOKEN_minus  */
    TOKEN_star = 290,              /* TOKEN_star  */
    TOKEN_slash = 291,             /* TOKEN_slash  */
    TOKEN_percent = 292,           /* TOKEN_percent  */
    TOKEN_less = 293,              /* TOKEN_less  */
    TOKEN_greater = 294,           /* TOKEN_greater  */
    TOKEN_lessequal = 295,         /* TOKEN_lessequal  */
    TOKEN_greaterequal = 296,      /* TOKEN_greaterequal  */
    TOKEN_equalequal = 297,        /* TOKEN_equalequal  */
    TOKEN_exclaimequal = 298,      /* TOKEN_exclaimequal  */
    TOKEN_equal = 299,             /* TOKEN_equal  */
    TOKEN_l_paren = 300,           /* TOKEN_l_paren  */
    TOKEN_r_paren = 301,           /* TOKEN_r_paren  */
    TOKEN_l_square = 302,          /* TOKEN_l_square  */
    TOKEN_r_square = 303,          /* TOKEN_r_square  */
    TOKEN_comma = 304,             /* TOKEN_comma  */
    TOKEN_colon = 305,             /* TOKEN_colon  */
    TOKEN_period = 306,            /* TOKEN_period  */
    TOKEN_rarrow = 307,            /* TOKEN_rarrow  */
    TOKEN_INDENT = 308,            /* TOKEN_INDENT  */
    TOKEN_DEDENT = 309,            /* TOKEN_DEDENT  */
    TOKEN_NEWLINE = 310            /* TOKEN_NEWLINE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 74 "chocopy.y"

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
  std::vector<::parser::Decl *> *PtrListDecl;
  std::vector<::parser::Stmt *> *PtrListStmt;
  std::vector<::parser::TypedVar *> *PtrListTypedVar;

#line 165 "chocopy.tab.h"

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

#endif /* !YY_YY_CHOCOPY_TAB_H_INCLUDED  */
