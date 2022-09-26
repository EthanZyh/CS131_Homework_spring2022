%locations

%{
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


%}


%union {
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
}


/* declare tokens */
%token <raw_int> TOKEN_INTEGER
%token <raw_str> TOKEN_IDENTIFIER
%token <raw_str> TOKEN_STRING
%token <raw_str> TOKEN_IDSTRING
%token <raw_str> TOKEN_TRUE
%token <raw_str> TOKEN_FALSE
%token <raw_str> TOKEN_AND
/* %token <raw_str> TOKEN_BREAK */
%token <raw_str> TOKEN_DEF
%token <raw_str> TOKEN_ELIF
%token <raw_str> TOKEN_ELSE
%token <raw_str> TOKEN_FOR
%token <raw_str> TOKEN_IF
%token <raw_str> TOKEN_NOT
%token <raw_str> TOKEN_OR
%token <raw_str> TOKEN_RETURN
%token <raw_str> TOKEN_WHILE
%token <raw_str> TOKEN_NONE
/* %token <raw_str> TOKEN_AS */
%token <raw_str> TOKEN_CLASS
%token <raw_str> TOKEN_GLOBAL
%token <raw_str> TOKEN_IN
%token <raw_str> TOKEN_IS
%token <raw_str> TOKEN_NONLOCAL
%token <raw_str> TOKEN_PASS
/* For ACC support */
/* %token <raw_str> TOKEN_DECORATOR
%token <raw_str> TOKEN_ACC
%token <raw_str> TOKEN_PARALLEL
%token <raw_str> TOKEN_LOOP
%token <raw_str> TOKEN_VECTOR
%token <raw_str> TOKEN_WORKER */

%token <raw_str> TOKEN_plus
%token <raw_str> TOKEN_minus
%token <raw_str> TOKEN_star
%token <raw_str> TOKEN_slash
%token <raw_str> TOKEN_percent
%token <raw_str> TOKEN_less
%token <raw_str> TOKEN_greater
%token <raw_str> TOKEN_lessequal
%token <raw_str> TOKEN_greaterequal
%token <raw_str> TOKEN_equalequal
%token <raw_str> TOKEN_exclaimequal
%token <raw_str> TOKEN_equal
%token <raw_str> TOKEN_l_paren
%token <raw_str> TOKEN_r_paren
%token <raw_str> TOKEN_l_square
%token <raw_str> TOKEN_r_square
%token <raw_str> TOKEN_comma
%token <raw_str> TOKEN_colon
%token <raw_str> TOKEN_period
%token <raw_str> TOKEN_rarrow
%token TOKEN_INDENT
%token TOKEN_DEDENT
%token TOKEN_NEWLINE

%type <PtrProgram> program
%type <PtrStmt> stmt expr_stmt
%type <PtrIfStmt> elif_list
/* %type <PtrListDecl> top_level_decl declaration_list class_helper */
%type <PtrListDecl> declaration_list class_helper
%type <PtrListStmt> stmt_list block
%type <PtrListTypedVar> typed_var_list
%type <PtrClassDef> class_def
%type <PtrGlobalDecl> global_decl
%type <PtrTypedVar> typed_var
%type <PtrTypeAnnotation> type
/* %type <PtrExpr> expr cexpr optionalRet assign_expr binary_expr */
%type <PtrExpr> expr cexpr assign_expr binary_expr
/* assign_expr: [target =]+ expr */
/* binary_expr: expr [and|or] expr */
%type <PtrIndexExpr> index_expr
%type <PtrMemberExpr> member_expr
%type <PtrListExpr> list_expr
%type <PtrLiteral> literal
%type <PtrIdent> identifier
%type <PtrVarDef> var_def
%type <PtrFuncDef> func_def
%type <PtrNonlocalDecl> nonlocal_decl
/* %type <PtrAssignStmt> assign_stmt */
%type <PtrVarAssignStmt> varAssignStmt
%type <PtrMemberAssignStmt> memberAssignStmt
%type <PtrIndexAssignStmt> indexAssignStmt
%type <PtrVarAssignExpr> varAssignExpr 
%type <PtrMemberAssignExpr> memberAssignExpr
%type <PtrIndexAssignExpr> indexAssignExpr
/* %type <PtrAccOptions> acc_options */


%right TOKEN_IF TOKEN_ELSE
%left TOKEN_OR
%left TOKEN_AND
%left TOKEN_NOT
%nonassoc TOKEN_equalequal TOKEN_exclaimequal TOKEN_greater TOKEN_greaterequal TOKEN_less TOKEN_lessequal TOKEN_IS
%left TOKEN_plus TOKEN_minus
%left TOKEN_star TOKEN_slash TOKEN_percent
%right TOKEN_period TOKEN_comma TOKEN_l_square TOKEN_r_square
%right TOKEN_ELIF

%start program

%%
/* The grammar rules Your Code Here */

/* program: [var_def | func_def | class_def]* stmt* */
program: var_def program {$$=$2;$$->declarations->insert($$->declarations->begin(),$1);$$->location=get_loc(@$);ROOT=$$;}
    | func_def program {$$=$2;$$->declarations->insert($$->declarations->begin(),$1);$$->location=get_loc(@$);ROOT=$$;}
    | class_def program {$$=$2;$$->declarations->insert($$->declarations->begin(),$1);$$->location=get_loc(@$);ROOT=$$;}
    | stmt_list {$$=new parser::Program(get_loc(@$),new std::vector<parser::Decl *>,$1);ROOT=$$;}
    ;

stmt_list: {$$=new std::vector<parser::Stmt *>;}
    | stmt stmt_list {$$=$2; $$->insert($$->begin(),$1);}
    ;

class_def: TOKEN_CLASS identifier TOKEN_l_paren identifier TOKEN_r_paren TOKEN_colon TOKEN_NEWLINE TOKEN_INDENT class_helper TOKEN_DEDENT {
        $$=new parser::ClassDef(get_loc(@$),$2,$4,$9);
    }
    ;

class_helper: TOKEN_PASS TOKEN_NEWLINE {$$=new std::vector<parser::Decl *>; $$->push_back(new parser::PassStmt(get_loc(@$)));}
    | var_def {$$=new std::vector<parser::Decl *>; $$->push_back($1);}
    | func_def {$$=new std::vector<parser::Decl *>; $$->push_back($1);}
    | class_helper var_def {$$=$1; $$->push_back($2);}
    | class_helper func_def {$$=$1; $$->push_back($2);}
    ;

func_def: TOKEN_DEF identifier TOKEN_l_paren typed_var_list TOKEN_r_paren TOKEN_rarrow type TOKEN_colon TOKEN_NEWLINE TOKEN_INDENT declaration_list stmt stmt_list TOKEN_DEDENT{
        $$=new parser::FuncDef(get_loc(@$),$2,$4,$7,$11,$13);
        $$->statements->insert($$->statements->begin(),$12);
    }
    | TOKEN_DEF identifier TOKEN_l_paren typed_var_list TOKEN_r_paren TOKEN_colon TOKEN_NEWLINE TOKEN_INDENT declaration_list stmt stmt_list TOKEN_DEDENT{
        $$=new parser::FuncDef(get_loc(@$),$2,$4,$9,$11);
        $$->statements->insert($$->statements->begin(),$10);
    }
    ;
typed_var_list: {$$=new std::vector<parser::TypedVar*>;}
    | typed_var {$$=new std::vector<parser::TypedVar*>;$$->push_back($1);}
    | typed_var_list TOKEN_comma typed_var {$$=$1;$$->push_back($3);}
    ;
declaration_list: {$$=new std::vector<parser::Decl*>;}
    | declaration_list global_decl {$$=$1;$$->push_back($2);}
    | declaration_list nonlocal_decl {$$=$1;$$->push_back($2);}
    | declaration_list var_def {$$=$1;$$->push_back($2);}
    | declaration_list func_def {$$=$1;$$->push_back($2);}
    ;

typed_var: identifier TOKEN_colon type {$$=new parser::TypedVar(get_loc(@$),$1,$3);}
    ;
identifier: TOKEN_IDENTIFIER {$$=new parser::Ident(get_loc(@$),$1);}

type: identifier {$$=new parser::ClassType(get_loc(@$),string($1->name));}
    | TOKEN_IDSTRING {$$=new parser::ClassType(get_loc(@$),string($1));}
    | TOKEN_l_square type TOKEN_r_square {$$=new parser::ListType(get_loc(@$), $2);}
    ; 

global_decl: TOKEN_GLOBAL identifier TOKEN_NEWLINE {
        $$=new parser::GlobalDecl(get_loc(@$),$2);
    }
    ;

nonlocal_decl: TOKEN_NONLOCAL identifier TOKEN_NEWLINE{
        $$=new parser::NonlocalDecl(get_loc(@$),$2);
    }
    ;

var_def: typed_var TOKEN_equal literal TOKEN_NEWLINE {
        $$=new parser::VarDef(get_loc(@$),$1,$3);
    }
    ;

stmt: expr_stmt TOKEN_NEWLINE {$$=$1;}
    | TOKEN_IF expr TOKEN_colon block elif_list {
        if ($5!=nullptr) $$=new parser::IfStmt(get_loc(@$),$2,$4,$5);
        else $$=new parser::IfStmt(get_loc(@$),$2,$4);}
    | TOKEN_IF expr TOKEN_colon block TOKEN_ELSE TOKEN_colon block {
        $$=new parser::IfStmt(get_loc(@$),$2,$4,$7);}
    | TOKEN_WHILE expr TOKEN_colon block {
        $$=new parser::WhileStmt(get_loc(@$),$2,$4);}
    | TOKEN_FOR identifier TOKEN_IN expr TOKEN_colon block{
        $$=new parser::ForStmt(get_loc(@$),$2,$4,$6);}
    | varAssignStmt TOKEN_NEWLINE {$$=$1;}
    | memberAssignStmt TOKEN_NEWLINE {$$=$1;}
    | indexAssignStmt TOKEN_NEWLINE {$$=$1;}
    ;
elif_list: {$$=nullptr;}
    | TOKEN_ELIF expr TOKEN_colon block elif_list{
        if($5==nullptr)$$=new parser::IfStmt(get_loc(@$),$2,$4);
        else $$=new parser::IfStmt(get_loc(@$),$2,$4,$5);
    }
    | TOKEN_ELIF expr TOKEN_colon block TOKEN_ELSE TOKEN_colon block{
        $$=new parser::IfStmt(get_loc(@$),$2,$4,$7);
    }
    ;

expr_stmt: TOKEN_PASS {$$=new parser::PassStmt(get_loc(@$));}
    | expr {$$=new parser::ExprStmt($1->location,$1);}
    | TOKEN_RETURN {$$=new parser::ReturnStmt(get_loc(@$));}
    | TOKEN_RETURN expr {$$=new parser::ReturnStmt(get_loc(@$),$2);}
    ;

varAssignStmt: identifier TOKEN_equal assign_expr {
        $$=new parser::VarAssignStmt(get_loc(@$),$1,$3);
    }
    | identifier TOKEN_equal expr {
        $$=new parser::VarAssignStmt(get_loc(@$),$1,$3);
    }
    ;
memberAssignStmt: member_expr TOKEN_equal assign_expr {
        $$=new parser::MemberAssignStmt(get_loc(@$),$1,$3);
    }
    | member_expr TOKEN_equal expr {
        $$=new parser::MemberAssignStmt(get_loc(@$),$1,$3);
    }
    ;
indexAssignStmt: index_expr TOKEN_equal assign_expr {
        $$=new parser::IndexAssignStmt(get_loc(@$),$1,$3);
    }
    | index_expr TOKEN_equal expr {
        $$=new parser::IndexAssignStmt(get_loc(@$),$1,$3);
    }
    ;
assign_expr: varAssignExpr {$$=$1;}
    | memberAssignExpr {$$=$1;}
    | indexAssignExpr {$$=$1;}
    ;
varAssignExpr: identifier TOKEN_equal assign_expr{
        $$=new parser::VarAssignExpr(get_loc(@$),$1,$3);
    }
    | identifier TOKEN_equal expr{
        $$=new parser::VarAssignExpr(get_loc(@$),$1,$3);
    }
    ;
memberAssignExpr: member_expr TOKEN_equal assign_expr{
        $$=new parser::MemberAssignExpr(get_loc(@$),$1,$3);
    }
    | member_expr TOKEN_equal expr{
        $$=new parser::MemberAssignExpr(get_loc(@$),$1,$3);
    }
    ;
indexAssignExpr: index_expr TOKEN_equal assign_expr{
        $$=new parser::IndexAssignExpr(get_loc(@$),$1,$3);
    }
    | index_expr TOKEN_equal expr{
        $$=new parser::IndexAssignExpr(get_loc(@$),$1,$3);
    }
    ;

block: TOKEN_NEWLINE TOKEN_INDENT stmt stmt_list TOKEN_DEDENT{$$=$4;$$->insert($$->begin(),$3);}
    ;

literal: TOKEN_NONE {$$=new parser::NoneLiteral(get_loc(@$));}
    | TOKEN_TRUE {$$=new parser::BoolLiteral(get_loc(@$),1);}
    | TOKEN_FALSE {$$=new parser::BoolLiteral(get_loc(@$),0);}
    | TOKEN_INTEGER {$$=new parser::IntegerLiteral(get_loc(@$),yylval.raw_int);}
    | TOKEN_IDSTRING  {$$=new parser::StringLiteral(get_loc(@$), string($1));}
    | TOKEN_STRING {string s($1);$$=new parser::StringLiteral(get_loc(@$),s);}
    ;

expr: cexpr {$$=$1;}
    | TOKEN_NOT expr {$$=new parser::UnaryExpr(get_loc(@$),"not",$2);}
    | binary_expr {$$=$1;}
    | expr TOKEN_IF expr TOKEN_ELSE expr {$$=new parser::IfExpr(get_loc(@$),$3,$1,$5);}
    ;
binary_expr: expr TOKEN_AND expr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("and"),$3);}
    | expr TOKEN_OR expr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("or"),$3);}
    ;

cexpr: identifier {$$=$1;}
    | literal {$$=$1;}
    | TOKEN_l_square list_expr TOKEN_r_square {$$=$2;$$->location=get_loc(@$);}
    | TOKEN_l_paren expr TOKEN_r_paren {$$=$2;$$->location=get_loc(@$);}
    | member_expr {$$=$1;}
    | index_expr {$$=$1;}
    | member_expr TOKEN_l_paren list_expr TOKEN_r_paren {$$=new parser::MethodCallExpr(get_loc(@$),$1,$3->elements);}
    | identifier TOKEN_l_paren list_expr TOKEN_r_paren {$$=new parser::CallExpr(get_loc(@$),$1,$3->elements);}
    | cexpr TOKEN_plus cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("+"),$3);}
    | cexpr TOKEN_minus  cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("-"),$3);}
    | cexpr TOKEN_star cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("*"),$3);}
    | cexpr TOKEN_slash cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("//"),$3);}
    | cexpr TOKEN_percent cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("%"),$3);}
    | cexpr TOKEN_equalequal cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("=="),$3);}
    | cexpr TOKEN_exclaimequal cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("!="),$3);}
    | cexpr TOKEN_lessequal cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("<="),$3);}
    | cexpr TOKEN_greaterequal cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string(">="),$3);}
    | cexpr TOKEN_less cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("<"),$3);}
    | cexpr TOKEN_greater cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string(">"),$3);}
    | cexpr TOKEN_IS cexpr {$$=new parser::BinaryExpr(get_loc(@$),$1,string("is"),$3);}
    | TOKEN_minus cexpr {$$=new parser::UnaryExpr(get_loc(@$),"-",$2);}
    ;
list_expr: {$$=new parser::ListExpr(get_loc(@$),new std::vector<parser::Expr *>);}
    | expr {$$=new parser::ListExpr(get_loc(@$),new std::vector<parser::Expr *>);$$->elements->push_back($1);}
    | list_expr TOKEN_comma expr {$$=$1;$$->elements->push_back($3);$$->location=get_loc(@$);}
    ;

member_expr: cexpr TOKEN_period identifier {$$=new parser::MemberExpr(get_loc(@$),$1,$3);}
    ;

index_expr: cexpr TOKEN_l_square expr TOKEN_r_square {$$=new parser::IndexExpr(get_loc(@$),$1,$3);}
    ;



%%

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
