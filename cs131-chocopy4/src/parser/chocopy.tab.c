/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "chocopy.y"

#include <cstdio>
#include <cstdarg>
#include <vector>
#include <string>
#include <iostream>
#include <chocopy_parse.hpp>
#include <chocopy_ast.hpp>


/** external functions from lex */
extern void yyrestart(FILE*);
extern int yylex();
extern int yyparse();
extern FILE* yyin;
parser::Program *ROOT = new parser::Program(new int[4]{1, 1, 1, 1});

typedef struct yyltype {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

/** Error reporting */
void yyerror(const char *s);


/** Return a mutable list initially containing the single value ITEM. */
template<typename T>
std::vector<T *>* single(T *item) {
    std::vector<T *> *list=new std::vector<T *>();
    list->push_back(item);
    return list;
}

/* If ITEM is non-null, appends it to the end of LIST.  Then returns LIST. Generic is deprecated */
template<typename T>
std::vector<parser::Decl *>* combine(std::vector<parser::Decl *>* list, T *item) {
    list->push_back(item);
    return list;
}


std::vector<parser::Stmt *>* combine(std::vector<parser::Stmt *>* list, parser::Stmt *item) {
    list->push_back(item);
    return list;
}

parser::ListExpr* combine(parser::ListExpr *list, parser::Expr *item) {
    list->elements->push_back(item);
    return list;
}

std::vector<parser::TypedVar *>* combine(std::vector<parser::TypedVar *>* list, parser::TypedVar *item) {
    list->push_back(item);
    return list;
}

std::vector<parser::IfStmt *>* combine(std::vector<parser::IfStmt *>* list, parser::IfStmt *item) {
    list->push_back(item);
    return list;
}

template<typename T>
T* get_right (std::vector<T*> *item){
    return item->at(0);
}

int* link_loc(int* a, int *b){
    int* loc = new int[4];
    loc[0]=a[0];loc[1]=a[1];
    loc[2]=b[2];loc[3]=b[3];
    return loc;
}

// int* get_loc(auto yylloc){
//     int* loc = new int[4];
//     loc[0] = yylloc.first_line;
//     loc[1] = yylloc.first_column;
//     loc[2] = yylloc.last_line;
//     loc[3] = yylloc.last_column;
//     printf("=========get_loc %d %d %d %d\n",loc[0],loc[1],loc[2],loc[3]);
//     return loc;
// }

int* get_loc(auto a){
    int *b = (int*)&a;
    int *c = new int[4];
    c[0]=b[0];c[1]=b[1];c[2]=b[2];c[3]=b[3]-1;
    return c;
}



#line 166 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 319 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"

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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   440

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

#define YYUNDEFTOK  2
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   260,   260,   261,   262,   263,   266,   267,   270,   275,
     276,   277,   278,   279,   282,   286,   291,   292,   293,   295,
     296,   297,   298,   299,   302,   304,   306,   307,   308,   311,
     316,   321,   326,   327,   330,   332,   334,   336,   337,   338,
     340,   341,   345,   350,   351,   352,   353,   356,   359,   363,
     366,   370,   373,   377,   378,   379,   381,   384,   388,   391,
     395,   398,   403,   406,   407,   408,   409,   410,   411,   414,
     415,   416,   417,   419,   420,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   445,   446,   447,   450,
     453
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_INTEGER", "TOKEN_IDENTIFIER",
  "TOKEN_STRING", "TOKEN_IDSTRING", "TOKEN_TRUE", "TOKEN_FALSE",
  "TOKEN_AND", "TOKEN_DEF", "TOKEN_ELIF", "TOKEN_ELSE", "TOKEN_FOR",
  "TOKEN_IF", "TOKEN_NOT", "TOKEN_OR", "TOKEN_RETURN", "TOKEN_WHILE",
  "TOKEN_NONE", "TOKEN_CLASS", "TOKEN_GLOBAL", "TOKEN_IN", "TOKEN_IS",
  "TOKEN_NONLOCAL", "TOKEN_PASS", "TOKEN_plus", "TOKEN_minus",
  "TOKEN_star", "TOKEN_slash", "TOKEN_percent", "TOKEN_less",
  "TOKEN_greater", "TOKEN_lessequal", "TOKEN_greaterequal",
  "TOKEN_equalequal", "TOKEN_exclaimequal", "TOKEN_equal", "TOKEN_l_paren",
  "TOKEN_r_paren", "TOKEN_l_square", "TOKEN_r_square", "TOKEN_comma",
  "TOKEN_colon", "TOKEN_period", "TOKEN_rarrow", "TOKEN_INDENT",
  "TOKEN_DEDENT", "TOKEN_NEWLINE", "$accept", "program", "stmt_list",
  "class_def", "class_helper", "func_def", "typed_var_list",
  "declaration_list", "typed_var", "identifier", "type", "global_decl",
  "nonlocal_decl", "var_def", "stmt", "elif_list", "expr_stmt",
  "varAssignStmt", "memberAssignStmt", "indexAssignStmt", "assign_expr",
  "varAssignExpr", "memberAssignExpr", "indexAssignExpr", "block",
  "literal", "expr", "binary_expr", "cexpr", "list_expr", "member_expr",
  "index_expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF (-159)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     290,  -159,  -159,  -159,  -159,  -159,  -159,    35,    35,   344,
     344,   344,   344,  -159,    35,  -159,   361,   344,   344,     4,
    -159,   290,   290,   -27,   155,   290,   318,   -18,    -2,     3,
      57,  -159,   169,  -159,   377,    26,    90,    93,   111,   106,
      44,   123,  -159,  -159,   169,    86,   125,   140,   110,   169,
      51,  -159,  -159,  -159,   115,   344,   344,     7,  -159,  -159,
     117,  -159,  -159,  -159,  -159,   344,   344,   344,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     344,    35,   344,   344,   344,    35,   344,   141,   141,    35,
    -159,  -159,   344,   147,   139,  -159,  -159,  -159,  -159,   169,
     162,   137,   -23,  -159,     7,  -159,  -159,  -159,   116,   188,
     396,   140,   140,    63,    63,    63,   396,   396,   396,   396,
     396,   396,    27,  -159,  -159,   169,    71,  -159,   169,   133,
    -159,   158,    92,   159,   126,  -159,    10,   169,  -159,   344,
     344,   344,  -159,   166,   344,  -159,  -159,    11,    35,   141,
     318,   344,   173,  -159,   176,  -159,   169,  -159,   169,  -159,
     169,  -159,   169,   174,     7,  -159,  -159,   318,   100,   141,
     177,   180,   184,   182,   141,  -159,   187,  -159,   189,  -159,
     198,    40,   238,   190,   192,  -159,   191,     5,  -159,  -159,
      35,    35,  -159,  -159,  -159,  -159,   318,  -159,   141,  -159,
    -159,  -159,  -159,   201,   202,   200,   238,  -159,  -159,  -159,
    -159,   318,   207,  -159
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,    66,    25,    68,    67,    64,    65,     0,     0,     0,
       0,    45,     0,    63,     0,    43,     0,     0,    96,     0,
       5,     6,     6,     0,    75,     6,     6,     0,     0,     0,
       0,    76,    44,    71,    69,    79,    80,     0,     0,    75,
       0,    79,    80,    70,    46,     0,     0,    95,     0,    97,
       0,     1,     4,     3,     0,     0,    96,     0,     2,     7,
      75,    32,    37,    38,    39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,     0,    16,     0,     0,     0,     0,
      78,    77,     0,     0,    75,    47,    53,    54,    55,    48,
      79,    80,     0,    27,     0,    26,    24,    73,     0,    74,
      94,    83,    84,    85,    86,    87,    92,    93,    90,    91,
      88,    89,     0,    99,    49,    50,     0,    51,    52,     0,
      17,     0,     0,     0,    40,    35,     0,    98,    31,     0,
       0,     0,    82,     0,     0,   100,    81,     0,     0,     0,
       0,     0,     0,    33,     0,    56,    57,    58,    59,    60,
      61,    28,    72,     0,     0,    18,    36,     6,     0,     0,
       0,     0,     0,     0,     0,    34,     0,    19,     0,    62,
      40,     0,     0,     0,     0,    41,     0,     0,    11,    10,
       0,     0,    23,    20,    21,    22,     6,    19,     0,     9,
       8,    13,    12,     0,     0,     0,     0,    42,    29,    30,
      15,     6,     0,    14
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,   199,   -25,  -159,  -159,  -158,  -159,    41,   -65,     0,
    -102,  -159,  -159,   -70,  -147,    78,  -159,  -159,  -159,  -159,
     -42,  -159,  -159,  -159,   -83,   206,   148,  -159,     1,   -38,
       6,    12
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,   187,    22,   129,   182,    23,    39,
     106,   193,   194,    25,    26,   153,    27,    28,    29,    30,
      95,    96,    97,    98,   134,    31,    32,    33,    34,    50,
      41,    42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      24,    59,   143,   167,    51,   135,    35,    37,    38,     2,
      54,     2,    36,   103,    46,     7,   142,    47,   102,    92,
     130,    24,    24,   188,   192,    24,    60,    35,    35,   201,
      61,    35,    35,    36,    36,   196,    65,    36,    36,     2,
     124,    66,   127,    67,     2,   126,    62,   104,   192,   154,
       7,    63,   200,    65,   163,    94,   164,   105,    66,   211,
      67,   100,   172,    82,    83,   186,   166,   101,   145,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   123,    94,   165,    94,   131,   175,    87,   100,   136,
     100,   180,    91,    92,   101,    65,   101,   155,   157,   159,
      66,    65,    67,    80,   105,    64,    66,    81,    67,    65,
     146,   189,   195,    92,    66,   207,    67,   202,     1,    65,
       3,     4,     5,     6,    66,    65,    67,    84,   144,    88,
      66,    85,    67,    86,    13,   149,   195,   151,   152,    94,
      94,    94,   173,   174,    56,   100,   100,   100,   131,    90,
      60,   101,   101,   101,    55,    56,    35,    40,    43,    44,
      45,    83,    36,    89,   105,    48,    49,    60,    71,    72,
      73,   205,   147,    35,   141,   148,   139,    56,    65,    36,
      80,   131,    24,    66,    81,    67,   212,   131,    35,   133,
     203,   204,    55,    56,    36,   138,    60,    65,    57,   140,
      83,    57,    35,    99,    49,   150,    24,   161,    36,   151,
     184,    60,    35,   107,   108,   109,   169,    35,    36,   170,
      52,    53,   171,    36,    58,   176,   177,   178,   122,   179,
     125,    49,   128,   181,   132,   198,   197,   183,   206,   199,
     137,     1,     2,     3,     4,     5,     6,   210,     7,   208,
     209,     8,     9,    10,   213,    11,    12,    13,   185,   190,
      93,     0,   191,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,    18,     0,
       0,     0,     0,     0,     0,     0,     0,   156,   158,   160,
       0,     0,   162,     1,     2,     3,     4,     5,     6,   168,
       7,     0,     0,     8,     9,    10,     0,    11,    12,    13,
      14,     0,     0,     0,     0,    15,     0,    16,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     0,    17,     0,
      18,     8,     9,    10,     0,    11,    12,    13,     0,     0,
       0,     0,     0,    15,     0,    16,     0,     1,     2,     3,
       4,     5,     6,     0,     0,     0,    17,     0,    18,    10,
       0,     0,     0,    13,     1,     2,     3,     4,     5,     6,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
      13,     0,    17,     0,    18,     0,     0,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      68,    18,     0,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,     0,     0,     0,    80,     0,    -1,
       0,    81,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,     0,     0,     0,    80,     0,     0,     0,
      81
};

static const yytype_int16 yycheck[] =
{
       0,    26,   104,   150,     0,    88,     0,     7,     8,     4,
      37,     4,     0,     6,    14,    10,    39,    16,    56,    42,
      85,    21,    22,   181,   182,    25,    26,    21,    22,   187,
      48,    25,    26,    21,    22,   182,     9,    25,    26,     4,
      82,    14,    84,    16,     4,    83,    48,    40,   206,    39,
      10,    48,    47,     9,    43,    55,    45,    57,    14,   206,
      16,    55,   164,    37,    38,    25,   149,    55,    41,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    81,    82,   148,    84,    85,   169,    43,    82,    89,
      84,   174,    41,    42,    82,     9,    84,   139,   140,   141,
      14,     9,    16,    40,   104,    48,    14,    44,    16,     9,
      39,   181,   182,    42,    14,   198,    16,   187,     3,     9,
       5,     6,     7,     8,    14,     9,    16,    37,    12,    43,
      14,    38,    16,    22,    19,    43,   206,    11,    12,   139,
     140,   141,   167,    43,    38,   139,   140,   141,   148,    39,
     150,   139,   140,   141,    37,    38,   150,     9,    10,    11,
      12,    38,   150,    38,   164,    17,    18,   167,    28,    29,
      30,   196,    39,   167,    37,    42,    37,    38,     9,   167,
      40,   181,   182,    14,    44,    16,   211,   187,   182,    48,
     190,   191,    37,    38,   182,    48,   196,     9,    43,    37,
      38,    43,   196,    55,    56,    46,   206,    41,   196,    11,
      12,   211,   206,    65,    66,    67,    43,   211,   206,    43,
      21,    22,    48,   211,    25,    48,    46,    43,    80,    47,
      82,    83,    84,    46,    86,    43,    46,    48,   197,    48,
      92,     3,     4,     5,     6,     7,     8,    47,    10,    48,
      48,    13,    14,    15,    47,    17,    18,    19,   180,    21,
      54,    -1,    24,    25,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,   140,   141,
      -1,    -1,   144,     3,     4,     5,     6,     7,     8,   151,
      10,    -1,    -1,    13,    14,    15,    -1,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    38,    -1,
      40,    13,    14,    15,    -1,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    38,    -1,    40,    15,
      -1,    -1,    -1,    19,     3,     4,     5,     6,     7,     8,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    -1,    38,    -1,    40,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      23,    40,    -1,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,    23,
      -1,    44,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    10,    13,    14,
      15,    17,    18,    19,    20,    25,    27,    38,    40,    50,
      51,    52,    54,    57,    58,    62,    63,    65,    66,    67,
      68,    74,    75,    76,    77,    79,    80,    58,    58,    58,
      75,    79,    80,    75,    75,    75,    58,    77,    75,    75,
      78,     0,    50,    50,    37,    37,    38,    43,    50,    51,
      58,    48,    48,    48,    48,     9,    14,    16,    23,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      40,    44,    37,    38,    37,    38,    22,    43,    43,    38,
      39,    41,    42,    74,    58,    69,    70,    71,    72,    75,
      79,    80,    78,     6,    40,    58,    59,    75,    75,    75,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    75,    58,    69,    75,    78,    69,    75,    55,
      57,    58,    75,    48,    73,    73,    58,    75,    48,    37,
      37,    37,    39,    59,    12,    41,    39,    39,    42,    43,
      46,    11,    12,    64,    39,    69,    75,    69,    75,    69,
      75,    41,    75,    43,    45,    57,    73,    63,    75,    43,
      43,    48,    59,    51,    43,    73,    48,    46,    43,    47,
      73,    46,    56,    48,    12,    64,    25,    53,    54,    62,
      21,    24,    54,    60,    61,    62,    63,    46,    43,    48,
      47,    54,    62,    58,    58,    51,    56,    73,    48,    48,
      47,    63,    51,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    50,    50,    51,    51,    52,    53,
      53,    53,    53,    53,    54,    54,    55,    55,    55,    56,
      56,    56,    56,    56,    57,    58,    59,    59,    59,    60,
      61,    62,    63,    63,    63,    63,    63,    63,    63,    63,
      64,    64,    64,    65,    65,    65,    65,    66,    66,    67,
      67,    68,    68,    69,    69,    69,    70,    70,    71,    71,
      72,    72,    73,    74,    74,    74,    74,    74,    74,    75,
      75,    75,    75,    76,    76,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    78,    78,    78,    79,
      80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     0,     2,    10,     2,
       1,     1,     2,     2,    14,    12,     0,     1,     3,     0,
       2,     2,     2,     2,     3,     1,     1,     1,     3,     3,
       3,     4,     2,     5,     7,     4,     6,     2,     2,     2,
       0,     5,     7,     1,     1,     1,     2,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     5,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     5,     3,     3,     1,     1,     3,     3,     1,
       1,     4,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     0,     1,     3,     3,
       4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 260 "chocopy.y"
                         {(yyval.PtrProgram)=(yyvsp[0].PtrProgram);(yyval.PtrProgram)->declarations->insert((yyval.PtrProgram)->declarations->begin(),(yyvsp[-1].PtrVarDef));(yyval.PtrProgram)->location=get_loc((yyloc));ROOT=(yyval.PtrProgram);}
#line 1806 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 3:
#line 261 "chocopy.y"
                       {(yyval.PtrProgram)=(yyvsp[0].PtrProgram);(yyval.PtrProgram)->declarations->insert((yyval.PtrProgram)->declarations->begin(),(yyvsp[-1].PtrFuncDef));(yyval.PtrProgram)->location=get_loc((yyloc));ROOT=(yyval.PtrProgram);}
#line 1812 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 4:
#line 262 "chocopy.y"
                        {(yyval.PtrProgram)=(yyvsp[0].PtrProgram);(yyval.PtrProgram)->declarations->insert((yyval.PtrProgram)->declarations->begin(),(yyvsp[-1].PtrClassDef));(yyval.PtrProgram)->location=get_loc((yyloc));ROOT=(yyval.PtrProgram);}
#line 1818 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 5:
#line 263 "chocopy.y"
                {(yyval.PtrProgram)=new parser::Program(get_loc((yyloc)),new std::vector<parser::Decl *>,(yyvsp[0].PtrListStmt));ROOT=(yyval.PtrProgram);}
#line 1824 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 6:
#line 266 "chocopy.y"
           {(yyval.PtrListStmt)=new std::vector<parser::Stmt *>;}
#line 1830 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 7:
#line 267 "chocopy.y"
                     {(yyval.PtrListStmt)=(yyvsp[0].PtrListStmt); (yyval.PtrListStmt)->insert((yyval.PtrListStmt)->begin(),(yyvsp[-1].PtrStmt));}
#line 1836 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 8:
#line 270 "chocopy.y"
                                                                                                                                          {
        (yyval.PtrClassDef)=new parser::ClassDef(get_loc((yyloc)),(yyvsp[-8].PtrIdent),(yyvsp[-6].PtrIdent),(yyvsp[-1].PtrListDecl));
    }
#line 1844 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 9:
#line 275 "chocopy.y"
                                       {(yyval.PtrListDecl)=new std::vector<parser::Decl *>; (yyval.PtrListDecl)->push_back(new parser::PassStmt(get_loc((yyloc))));}
#line 1850 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 10:
#line 276 "chocopy.y"
              {(yyval.PtrListDecl)=new std::vector<parser::Decl *>; (yyval.PtrListDecl)->push_back((yyvsp[0].PtrVarDef));}
#line 1856 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 11:
#line 277 "chocopy.y"
               {(yyval.PtrListDecl)=new std::vector<parser::Decl *>; (yyval.PtrListDecl)->push_back((yyvsp[0].PtrFuncDef));}
#line 1862 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 12:
#line 278 "chocopy.y"
                           {(yyval.PtrListDecl)=(yyvsp[-1].PtrListDecl); (yyval.PtrListDecl)->push_back((yyvsp[0].PtrVarDef));}
#line 1868 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 13:
#line 279 "chocopy.y"
                            {(yyval.PtrListDecl)=(yyvsp[-1].PtrListDecl); (yyval.PtrListDecl)->push_back((yyvsp[0].PtrFuncDef));}
#line 1874 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 14:
#line 282 "chocopy.y"
                                                                                                                                                                               {
        (yyval.PtrFuncDef)=new parser::FuncDef(get_loc((yyloc)),(yyvsp[-12].PtrIdent),(yyvsp[-10].PtrListTypedVar),(yyvsp[-7].PtrTypeAnnotation),(yyvsp[-3].PtrListDecl),(yyvsp[-1].PtrListStmt));
        (yyval.PtrFuncDef)->statements->insert((yyval.PtrFuncDef)->statements->begin(),(yyvsp[-2].PtrStmt));
    }
#line 1883 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 15:
#line 286 "chocopy.y"
                                                                                                                                                         {
        (yyval.PtrFuncDef)=new parser::FuncDef(get_loc((yyloc)),(yyvsp[-10].PtrIdent),(yyvsp[-8].PtrListTypedVar),(yyvsp[-3].PtrListDecl),(yyvsp[-1].PtrListStmt));
        (yyval.PtrFuncDef)->statements->insert((yyval.PtrFuncDef)->statements->begin(),(yyvsp[-2].PtrStmt));
    }
#line 1892 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 16:
#line 291 "chocopy.y"
                {(yyval.PtrListTypedVar)=new std::vector<parser::TypedVar*>;}
#line 1898 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 17:
#line 292 "chocopy.y"
                {(yyval.PtrListTypedVar)=new std::vector<parser::TypedVar*>;(yyval.PtrListTypedVar)->push_back((yyvsp[0].PtrTypedVar));}
#line 1904 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 18:
#line 293 "chocopy.y"
                                           {(yyval.PtrListTypedVar)=(yyvsp[-2].PtrListTypedVar);(yyval.PtrListTypedVar)->push_back((yyvsp[0].PtrTypedVar));}
#line 1910 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 19:
#line 295 "chocopy.y"
                  {(yyval.PtrListDecl)=new std::vector<parser::Decl*>;}
#line 1916 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 20:
#line 296 "chocopy.y"
                                   {(yyval.PtrListDecl)=(yyvsp[-1].PtrListDecl);(yyval.PtrListDecl)->push_back((yyvsp[0].PtrGlobalDecl));}
#line 1922 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 21:
#line 297 "chocopy.y"
                                     {(yyval.PtrListDecl)=(yyvsp[-1].PtrListDecl);(yyval.PtrListDecl)->push_back((yyvsp[0].PtrNonlocalDecl));}
#line 1928 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 22:
#line 298 "chocopy.y"
                               {(yyval.PtrListDecl)=(yyvsp[-1].PtrListDecl);(yyval.PtrListDecl)->push_back((yyvsp[0].PtrVarDef));}
#line 1934 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 23:
#line 299 "chocopy.y"
                                {(yyval.PtrListDecl)=(yyvsp[-1].PtrListDecl);(yyval.PtrListDecl)->push_back((yyvsp[0].PtrFuncDef));}
#line 1940 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 24:
#line 302 "chocopy.y"
                                       {(yyval.PtrTypedVar)=new parser::TypedVar(get_loc((yyloc)),(yyvsp[-2].PtrIdent),(yyvsp[0].PtrTypeAnnotation));}
#line 1946 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 25:
#line 304 "chocopy.y"
                             {(yyval.PtrIdent)=new parser::Ident(get_loc((yyloc)),(yyvsp[0].raw_str));}
#line 1952 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 26:
#line 306 "chocopy.y"
                 {(yyval.PtrTypeAnnotation)=new parser::ClassType(get_loc((yyloc)),string((yyvsp[0].PtrIdent)->name));}
#line 1958 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 27:
#line 307 "chocopy.y"
                     {(yyval.PtrTypeAnnotation)=new parser::ClassType(get_loc((yyloc)),string((yyvsp[0].raw_str)));}
#line 1964 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 28:
#line 308 "chocopy.y"
                                         {(yyval.PtrTypeAnnotation)=new parser::ListType(get_loc((yyloc)), (yyvsp[-1].PtrTypeAnnotation));}
#line 1970 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 29:
#line 311 "chocopy.y"
                                                   {
        (yyval.PtrGlobalDecl)=new parser::GlobalDecl(get_loc((yyloc)),(yyvsp[-1].PtrIdent));
    }
#line 1978 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 30:
#line 316 "chocopy.y"
                                                      {
        (yyval.PtrNonlocalDecl)=new parser::NonlocalDecl(get_loc((yyloc)),(yyvsp[-1].PtrIdent));
    }
#line 1986 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 31:
#line 321 "chocopy.y"
                                                     {
        (yyval.PtrVarDef)=new parser::VarDef(get_loc((yyloc)),(yyvsp[-3].PtrTypedVar),(yyvsp[-1].PtrLiteral));
    }
#line 1994 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 32:
#line 326 "chocopy.y"
                              {(yyval.PtrStmt)=(yyvsp[-1].PtrStmt);}
#line 2000 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 33:
#line 327 "chocopy.y"
                                                {
        if ((yyvsp[0].PtrIfStmt)!=nullptr) (yyval.PtrStmt)=new parser::IfStmt(get_loc((yyloc)),(yyvsp[-3].PtrExpr),(yyvsp[-1].PtrListStmt),(yyvsp[0].PtrIfStmt));
        else (yyval.PtrStmt)=new parser::IfStmt(get_loc((yyloc)),(yyvsp[-3].PtrExpr),(yyvsp[-1].PtrListStmt));}
#line 2008 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 34:
#line 330 "chocopy.y"
                                                                   {
        (yyval.PtrStmt)=new parser::IfStmt(get_loc((yyloc)),(yyvsp[-5].PtrExpr),(yyvsp[-3].PtrListStmt),(yyvsp[0].PtrListStmt));}
#line 2015 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 35:
#line 332 "chocopy.y"
                                         {
        (yyval.PtrStmt)=new parser::WhileStmt(get_loc((yyloc)),(yyvsp[-2].PtrExpr),(yyvsp[0].PtrListStmt));}
#line 2022 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 36:
#line 334 "chocopy.y"
                                                          {
        (yyval.PtrStmt)=new parser::ForStmt(get_loc((yyloc)),(yyvsp[-4].PtrIdent),(yyvsp[-2].PtrExpr),(yyvsp[0].PtrListStmt));}
#line 2029 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 37:
#line 336 "chocopy.y"
                                  {(yyval.PtrStmt)=(yyvsp[-1].PtrVarAssignStmt);}
#line 2035 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 38:
#line 337 "chocopy.y"
                                     {(yyval.PtrStmt)=(yyvsp[-1].PtrMemberAssignStmt);}
#line 2041 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 39:
#line 338 "chocopy.y"
                                    {(yyval.PtrStmt)=(yyvsp[-1].PtrIndexAssignStmt);}
#line 2047 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 40:
#line 340 "chocopy.y"
           {(yyval.PtrIfStmt)=nullptr;}
#line 2053 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 41:
#line 341 "chocopy.y"
                                                 {
        if((yyvsp[0].PtrIfStmt)==nullptr)(yyval.PtrIfStmt)=new parser::IfStmt(get_loc((yyloc)),(yyvsp[-3].PtrExpr),(yyvsp[-1].PtrListStmt));
        else (yyval.PtrIfStmt)=new parser::IfStmt(get_loc((yyloc)),(yyvsp[-3].PtrExpr),(yyvsp[-1].PtrListStmt),(yyvsp[0].PtrIfStmt));
    }
#line 2062 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 42:
#line 345 "chocopy.y"
                                                                    {
        (yyval.PtrIfStmt)=new parser::IfStmt(get_loc((yyloc)),(yyvsp[-5].PtrExpr),(yyvsp[-3].PtrListStmt),(yyvsp[0].PtrListStmt));
    }
#line 2070 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 43:
#line 350 "chocopy.y"
                      {(yyval.PtrStmt)=new parser::PassStmt(get_loc((yyloc)));}
#line 2076 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 44:
#line 351 "chocopy.y"
           {(yyval.PtrStmt)=new parser::ExprStmt((yyvsp[0].PtrExpr)->location,(yyvsp[0].PtrExpr));}
#line 2082 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 45:
#line 352 "chocopy.y"
                   {(yyval.PtrStmt)=new parser::ReturnStmt(get_loc((yyloc)));}
#line 2088 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 46:
#line 353 "chocopy.y"
                        {(yyval.PtrStmt)=new parser::ReturnStmt(get_loc((yyloc)),(yyvsp[0].PtrExpr));}
#line 2094 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 47:
#line 356 "chocopy.y"
                                                  {
        (yyval.PtrVarAssignStmt)=new parser::VarAssignStmt(get_loc((yyloc)),(yyvsp[-2].PtrIdent),(yyvsp[0].PtrExpr));
    }
#line 2102 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 48:
#line 359 "chocopy.y"
                                  {
        (yyval.PtrVarAssignStmt)=new parser::VarAssignStmt(get_loc((yyloc)),(yyvsp[-2].PtrIdent),(yyvsp[0].PtrExpr));
    }
#line 2110 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 49:
#line 363 "chocopy.y"
                                                      {
        (yyval.PtrMemberAssignStmt)=new parser::MemberAssignStmt(get_loc((yyloc)),(yyvsp[-2].PtrMemberExpr),(yyvsp[0].PtrExpr));
    }
#line 2118 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 50:
#line 366 "chocopy.y"
                                   {
        (yyval.PtrMemberAssignStmt)=new parser::MemberAssignStmt(get_loc((yyloc)),(yyvsp[-2].PtrMemberExpr),(yyvsp[0].PtrExpr));
    }
#line 2126 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 51:
#line 370 "chocopy.y"
                                                    {
        (yyval.PtrIndexAssignStmt)=new parser::IndexAssignStmt(get_loc((yyloc)),(yyvsp[-2].PtrIndexExpr),(yyvsp[0].PtrExpr));
    }
#line 2134 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 52:
#line 373 "chocopy.y"
                                  {
        (yyval.PtrIndexAssignStmt)=new parser::IndexAssignStmt(get_loc((yyloc)),(yyvsp[-2].PtrIndexExpr),(yyvsp[0].PtrExpr));
    }
#line 2142 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 53:
#line 377 "chocopy.y"
                           {(yyval.PtrExpr)=(yyvsp[0].PtrVarAssignExpr);}
#line 2148 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 54:
#line 378 "chocopy.y"
                       {(yyval.PtrExpr)=(yyvsp[0].PtrMemberAssignExpr);}
#line 2154 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 55:
#line 379 "chocopy.y"
                      {(yyval.PtrExpr)=(yyvsp[0].PtrIndexAssignExpr);}
#line 2160 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 56:
#line 381 "chocopy.y"
                                                 {
        (yyval.PtrVarAssignExpr)=new parser::VarAssignExpr(get_loc((yyloc)),(yyvsp[-2].PtrIdent),(yyvsp[0].PtrExpr));
    }
#line 2168 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 57:
#line 384 "chocopy.y"
                                 {
        (yyval.PtrVarAssignExpr)=new parser::VarAssignExpr(get_loc((yyloc)),(yyvsp[-2].PtrIdent),(yyvsp[0].PtrExpr));
    }
#line 2176 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 58:
#line 388 "chocopy.y"
                                                     {
        (yyval.PtrMemberAssignExpr)=new parser::MemberAssignExpr(get_loc((yyloc)),(yyvsp[-2].PtrMemberExpr),(yyvsp[0].PtrExpr));
    }
#line 2184 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 59:
#line 391 "chocopy.y"
                                  {
        (yyval.PtrMemberAssignExpr)=new parser::MemberAssignExpr(get_loc((yyloc)),(yyvsp[-2].PtrMemberExpr),(yyvsp[0].PtrExpr));
    }
#line 2192 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 60:
#line 395 "chocopy.y"
                                                   {
        (yyval.PtrIndexAssignExpr)=new parser::IndexAssignExpr(get_loc((yyloc)),(yyvsp[-2].PtrIndexExpr),(yyvsp[0].PtrExpr));
    }
#line 2200 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 61:
#line 398 "chocopy.y"
                                 {
        (yyval.PtrIndexAssignExpr)=new parser::IndexAssignExpr(get_loc((yyloc)),(yyvsp[-2].PtrIndexExpr),(yyvsp[0].PtrExpr));
    }
#line 2208 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 62:
#line 403 "chocopy.y"
                                                             {(yyval.PtrListStmt)=(yyvsp[-1].PtrListStmt);(yyval.PtrListStmt)->insert((yyval.PtrListStmt)->begin(),(yyvsp[-2].PtrStmt));}
#line 2214 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 63:
#line 406 "chocopy.y"
                    {(yyval.PtrLiteral)=new parser::NoneLiteral(get_loc((yyloc)));}
#line 2220 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 64:
#line 407 "chocopy.y"
                 {(yyval.PtrLiteral)=new parser::BoolLiteral(get_loc((yyloc)),1);}
#line 2226 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 65:
#line 408 "chocopy.y"
                  {(yyval.PtrLiteral)=new parser::BoolLiteral(get_loc((yyloc)),0);}
#line 2232 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 66:
#line 409 "chocopy.y"
                    {(yyval.PtrLiteral)=new parser::IntegerLiteral(get_loc((yyloc)),yylval.raw_int);}
#line 2238 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 67:
#line 410 "chocopy.y"
                      {(yyval.PtrLiteral)=new parser::StringLiteral(get_loc((yyloc)), string((yyvsp[0].raw_str)));}
#line 2244 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 68:
#line 411 "chocopy.y"
                   {string s((yyvsp[0].raw_str));(yyval.PtrLiteral)=new parser::StringLiteral(get_loc((yyloc)),s);}
#line 2250 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 69:
#line 414 "chocopy.y"
            {(yyval.PtrExpr)=(yyvsp[0].PtrExpr);}
#line 2256 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 70:
#line 415 "chocopy.y"
                     {(yyval.PtrExpr)=new parser::UnaryExpr(get_loc((yyloc)),"not",(yyvsp[0].PtrExpr));}
#line 2262 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 71:
#line 416 "chocopy.y"
                  {(yyval.PtrExpr)=(yyvsp[0].PtrExpr);}
#line 2268 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 72:
#line 417 "chocopy.y"
                                         {(yyval.PtrExpr)=new parser::IfExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),(yyvsp[-4].PtrExpr),(yyvsp[0].PtrExpr));}
#line 2274 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 73:
#line 419 "chocopy.y"
                                 {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("and"),(yyvsp[0].PtrExpr));}
#line 2280 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 74:
#line 420 "chocopy.y"
                         {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("or"),(yyvsp[0].PtrExpr));}
#line 2286 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 75:
#line 423 "chocopy.y"
                  {(yyval.PtrExpr)=(yyvsp[0].PtrIdent);}
#line 2292 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 76:
#line 424 "chocopy.y"
              {(yyval.PtrExpr)=(yyvsp[0].PtrLiteral);}
#line 2298 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 77:
#line 425 "chocopy.y"
                                              {(yyval.PtrExpr)=(yyvsp[-1].PtrListExpr);(yyval.PtrExpr)->location=get_loc((yyloc));}
#line 2304 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 78:
#line 426 "chocopy.y"
                                       {(yyval.PtrExpr)=(yyvsp[-1].PtrExpr);(yyval.PtrExpr)->location=get_loc((yyloc));}
#line 2310 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 79:
#line 427 "chocopy.y"
                  {(yyval.PtrExpr)=(yyvsp[0].PtrMemberExpr);}
#line 2316 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 80:
#line 428 "chocopy.y"
                 {(yyval.PtrExpr)=(yyvsp[0].PtrIndexExpr);}
#line 2322 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 81:
#line 429 "chocopy.y"
                                                        {(yyval.PtrExpr)=new parser::MethodCallExpr(get_loc((yyloc)),(yyvsp[-3].PtrMemberExpr),(yyvsp[-1].PtrListExpr)->elements);}
#line 2328 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 82:
#line 430 "chocopy.y"
                                                       {(yyval.PtrExpr)=new parser::CallExpr(get_loc((yyloc)),(yyvsp[-3].PtrIdent),(yyvsp[-1].PtrListExpr)->elements);}
#line 2334 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 83:
#line 431 "chocopy.y"
                             {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("+"),(yyvsp[0].PtrExpr));}
#line 2340 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 84:
#line 432 "chocopy.y"
                               {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("-"),(yyvsp[0].PtrExpr));}
#line 2346 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 85:
#line 433 "chocopy.y"
                             {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("*"),(yyvsp[0].PtrExpr));}
#line 2352 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 86:
#line 434 "chocopy.y"
                              {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("//"),(yyvsp[0].PtrExpr));}
#line 2358 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 87:
#line 435 "chocopy.y"
                                {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("%"),(yyvsp[0].PtrExpr));}
#line 2364 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 88:
#line 436 "chocopy.y"
                                   {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("=="),(yyvsp[0].PtrExpr));}
#line 2370 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 89:
#line 437 "chocopy.y"
                                     {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("!="),(yyvsp[0].PtrExpr));}
#line 2376 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 90:
#line 438 "chocopy.y"
                                  {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("<="),(yyvsp[0].PtrExpr));}
#line 2382 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 91:
#line 439 "chocopy.y"
                                     {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string(">="),(yyvsp[0].PtrExpr));}
#line 2388 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 92:
#line 440 "chocopy.y"
                             {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("<"),(yyvsp[0].PtrExpr));}
#line 2394 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 93:
#line 441 "chocopy.y"
                                {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string(">"),(yyvsp[0].PtrExpr));}
#line 2400 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 94:
#line 442 "chocopy.y"
                           {(yyval.PtrExpr)=new parser::BinaryExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),string("is"),(yyvsp[0].PtrExpr));}
#line 2406 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 95:
#line 443 "chocopy.y"
                        {(yyval.PtrExpr)=new parser::UnaryExpr(get_loc((yyloc)),"-",(yyvsp[0].PtrExpr));}
#line 2412 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 96:
#line 445 "chocopy.y"
           {(yyval.PtrListExpr)=new parser::ListExpr(get_loc((yyloc)),new std::vector<parser::Expr *>);}
#line 2418 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 97:
#line 446 "chocopy.y"
           {(yyval.PtrListExpr)=new parser::ListExpr(get_loc((yyloc)),new std::vector<parser::Expr *>);(yyval.PtrListExpr)->elements->push_back((yyvsp[0].PtrExpr));}
#line 2424 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 98:
#line 447 "chocopy.y"
                                 {(yyval.PtrListExpr)=(yyvsp[-2].PtrListExpr);(yyval.PtrListExpr)->elements->push_back((yyvsp[0].PtrExpr));(yyval.PtrListExpr)->location=get_loc((yyloc));}
#line 2430 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 99:
#line 450 "chocopy.y"
                                           {(yyval.PtrMemberExpr)=new parser::MemberExpr(get_loc((yyloc)),(yyvsp[-2].PtrExpr),(yyvsp[0].PtrIdent));}
#line 2436 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;

  case 100:
#line 453 "chocopy.y"
                                                     {(yyval.PtrIndexExpr)=new parser::IndexExpr(get_loc((yyloc)),(yyvsp[-3].PtrExpr),(yyvsp[-1].PtrExpr));}
#line 2442 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"
    break;


#line 2446 "/home/yewandou/CS131/PA/cs131-chocopy2/src/parser/chocopy.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 458 "chocopy.y"


/** The error reporting function. */
void yyerror(const char *s) {
    /** TO STUDENTS: This is just an example.
     * You can customize it as you like. */
    info = "Parser error near token ";
    info += yylval.error_msg;
    int *loc = new int[4]{0};
    loc[0] = yylloc.first_line;
    loc[1] = yylloc.first_column;
    loc[2] = yylloc.last_line;
    loc[3] = yylloc.last_column - 1;

    parser::CompilerErr *test = new parser::CompilerErr(loc, info, true);
    ROOT->errors->compiler_errors = new vector<parser::CompilerErr *>();
    ROOT->has_compiler_errors = true;
    ROOT->errors->compiler_errors->push_back(test);
    ((parser::Node *)ROOT)->location[2] = e1;
    ((parser::Node *)ROOT)->location[3] = e2;
}

parser::Program * parse(const char* input_path) {
    if (input_path != NULL) {
        if (!(yyin = fopen(input_path, "r"))) {
            fprintf(stderr, "[ERR] Open input file %s failed.\n", input_path);
            exit(EXIT_FAILURE);
        }
    } else {
        yyin = stdin;
    }
    /** Uncomment to see the middle process of bison*/
    /* yydebug = 1; */
    yyrestart(yyin);
    /* puts("------yyparse start---------"); */
    yyparse();
    /* puts("----------yyparse end------------"); */
    return ROOT;
}
