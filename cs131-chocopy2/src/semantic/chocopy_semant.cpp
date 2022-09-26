//
// Created by yiwei yang on 2/18/21.
//

#include "FunctionDefType.hpp"
#include "ValueType.hpp"
#include <chocopy_semant.hpp>
#include <fmt/format.h>
#include <list>
#include <map>
#include <regex>
#include <set>
#include <utility>

using std::map;
using std::set;

bool is_lambda_pass = false;
bool is_rvalue = false;
vector<string> lambda_params;
template <class Key, class T> set<string> key_to_set(const std::map<Key, T> &map, std::set<Key> &set) {
    set.clear();
    auto itr = map.begin();
    while (map.end() != itr) {
        set.insert((itr++)->first);
    }
    return set;
}

namespace semantic {
cJSON *FunctionDefType::toJSON() const {
    cJSON *d = cJSON_CreateObject();

    cJSON_AddStringToObject(d, "kind", "FuncType");
    auto param = cJSON_CreateArray();

    if (!this->params->empty())
        for (auto &parameter : *this->params) {
            auto type_name = parameter->get_type().c_str();
            auto tmp_param = cJSON_CreateObject();

            if (dynamic_cast<ListValueType *>(parameter)) {
                cJSON_AddStringToObject(tmp_param, "kind", type_name);
                cJSON_AddItemToObject(tmp_param, "elementType",
                                      parser::add_inferred_type(((ListValueType *)parameter)->element_type));
                cJSON_AddItemToArray(param, tmp_param);
            } else {
                auto param_name = ((ClassValueType *)parameter)->class_name.c_str();
                cJSON_AddStringToObject(tmp_param, "kind", type_name);
                cJSON_AddStringToObject(tmp_param, "className", param_name);
                cJSON_AddItemToArray(param, tmp_param);
            }
        }
    cJSON_AddItemToObject(d, "parameters", param);

    auto class_name = ((ClassValueType *)this->return_type)->class_name.c_str();
    auto tmp_return = cJSON_CreateObject();
    cJSON_AddStringToObject(tmp_return, "kind", "ClassValueType");
    cJSON_AddStringToObject(tmp_return, "className", class_name);
    cJSON_AddItemToObject(d, "returnType", tmp_return);
    return d;
}
void FunctionDefType::set_name(string_view className) { ((ClassValueType *)this->return_type)->class_name = className; }
template <typename Ty> bool SymbolType::eq(const Ty &Value) {
    if (this->is_list_type()) {
        if (dynamic_cast<ListValueType *>(Value))
            return ((ListValueType *)this)->element_type->eq(((ListValueType *)Value)->element_type);
        else
            return false;
    } else if (this->is_value_type()) {
        if (dynamic_cast<ClassValueType *>(Value))
            return ((ClassValueType *)this)->get_name() == ((ClassValueType *)Value)->get_name();
        else
            return false;
    }
    return false;
}
template <typename Ty> bool SymbolType::neq(const Ty &Value) { return !(this->eq(Value)); }

void DeclarationAnalyzer::debug_sym() {
    for (const auto &x : *sym->tab) {
        if ((x.second)->is_list_type()) {
            LOG(INFO) << x.first << " : [" << ((ClassValueType *)((ListValueType *)x.second)->element_type)->get_name()
                      << "]\n";
        } else if ((x.second)->is_func_type()) {
            if (dynamic_cast<FunctionDefType *>(x.second))
                LOG(INFO) << "Function " << x.first << " : "
                          << dynamic_cast<FunctionDefType *>(x.second)->return_type->get_name() << "\nparam\n";
            for (const auto y : *dynamic_cast<FunctionDefType *>(x.second)->params)
                if (!y->is_list_type())
                    LOG(INFO) << "      : " << ((ClassValueType *)y)->get_name() << "\n";
                else
                    LOG(INFO) << "      : " << ((ClassValueType *)((ListValueType *)y)->element_type)->get_name()
                              << "\n";
        } else if ((x.second)->is_value_type()) {
            LOG(INFO) << x.first << " : " << ((ClassValueType *)x.second)->get_name() << "\n";
        }
    }
}


#define DEBUG 0
#define print(x) if(DEBUG)cerr<<#x<<"="<<x<<'\n';
using namespace parser;

void DeclarationAnalyzer::visit(parser::VarDef &varDef) {
    if(DEBUG)cerr<<"--VarDef--\n";
    // type
    auto tp = varDef.var->type;
    auto tp2 = dynamic_cast<ListType*>(tp);
    while(tp2){
        tp = tp2->elementType;
        tp2 = dynamic_cast<ListType*>(tp);
    }
    if (dynamic_cast<parser::ClassType *>(tp) &&
        globals->get<SymbolType *>(((parser::ClassType *)tp)->className) == nullptr &&
        classNames.find(((ClassType*)tp)->className)==classNames.end() &&
        !(((parser::ClassType *)tp)->className == curr_class)) {
        errors->emplace_back(
            new SemanticError(varDef.var->type, fmt::format("Invalid type annotation; there is no class named: {}",
                                                            ((parser::ClassType *)varDef.var->type)->get_name())));
    }
    this->passing_type = ValueType::annotate_to_val(varDef.var->type);
    // name
    if(sym->tab->count(varDef.var->identifier->name)){
        errors->emplace_back(
            new SemanticError(varDef.var->identifier, 
                fmt::format("Invalid Var name; re-define: {}",
                    varDef.var->identifier->name)));
    }
    else if(classNames.find(varDef.var->identifier->name)!=classNames.end()){
        errors->emplace_back(
            new SemanticError(varDef.var->identifier, 
                fmt::format("Invalid Var name; it is a class name: {}",
                    varDef.var->identifier->name)));
    }
    else if(varDef.var->identifier->name=="int"||varDef.var->identifier->name=="str"||varDef.var->identifier->name=="bool"||varDef.var->identifier->name=="list"||varDef.var->identifier->name=="object"){
        errors->emplace_back(
            new SemanticError(varDef.var->identifier, 
                fmt::format("Invalid Var name; it is pre-defined: {}",
                    varDef.var->identifier->name)));
    }
    else if(curr_class!=""&&curr_func==""&&sym->get<SymbolType*>(varDef.var->identifier->name)){
        errors->emplace_back(
            new SemanticError(varDef.var->identifier, 
                fmt::format("Invalid Var name; re-define: {}",
                    varDef.var->identifier->name)));
    }
    // add into symbol table
    if(dynamic_cast<ClassType*>(varDef.var->type))
        sym->put(varDef.var->identifier->name, new ClassValueType((ClassType*)varDef.var->type));
    else sym->put(varDef.var->identifier->name, new ListValueType((ListType*)varDef.var->type));
}
/* The Declaration check rules Your Code Here */

void DeclarationAnalyzer::visit(parser::ClassDef &node) {
    if(DEBUG)cerr<<"--ClassDef "<<node.name->name<<'\n';
    curr_class = node.name->name;
    // name
    if(sym->get<SymbolType*>(node.name->name)){
        errors->emplace_back(
            new SemanticError(node.name, 
                fmt::format("Invalid Class name; re-define: {}",
                    node.name->name)));
    }
    // super class
    bool found_super = 1;
    auto super = sym->get<ClassDefType*>(node.superClass->name);
    if(!super){
        errors->emplace_back(
            new SemanticError(node.superClass, 
                fmt::format("Invalid superClass name; no such class: {}",
                    node.superClass->name)));
        found_super = 0;
    }
    else if(super->class_name=="int"||super->class_name=="str"||super->class_name=="bool"||super->class_name=="list"){
        errors->emplace_back(
            new SemanticError(node.superClass, 
                fmt::format("Invalid superClass name; cannot inherit: {}",
                    node.superClass->name)));
        found_super = 0;
    }
    // create symboltable
    if(found_super)
        sym = new SymbolTable(globals->get<ClassDefType*>(node.superClass->name)->current_scope);
    else sym = new SymbolTable(sym);
    auto bar = new ClassDefType(node.superClass->name, node.name->name);
    bar->class_name = node.name->name;
    bar->super_class = node.superClass->name;
    bar->current_scope = sym;
    // enumerate
    for(auto& decl: *node.declaration){
        if(dynamic_cast<VarDef*>(decl)){
            decl->accept(*this);
            curr_class = node.name->name;
        }
    }
    for(auto& decl: *node.declaration){
        if(!dynamic_cast<VarDef*>(decl)){
            decl->accept(*this);
            curr_class = node.name->name;
        }
    }
    // add into symbol table
    globals->put(node.name->name, bar);
    // exit
    sym = globals;
}
void DeclarationAnalyzer::visit(parser::ClassType &node) {}
void DeclarationAnalyzer::visit(parser::IfStmt &node) {
    if(DEBUG)cerr<<"--IfStmt "<<'\n';
    // condition
    node.condition->accept(*this);
    // then
    bool has_return_then=0, has_return_elif=1, has_return_else=0;
    for(auto &stmt: *node.thenBody){
        has_return=0;
        stmt->accept(*this);
        has_return_then|=has_return;
    }
    // elif
    if(node.el==node.cond::THEN_ELIF){
        has_return_elif=0;
        has_return=0;
        node.elifBody->accept(*this);
        has_return_elif|=has_return;
    }
    // else
    if(node.el==node.cond::THEN_ELSE){
        for(auto& stmt: *node.elseBody){
            has_return=0;
            stmt->accept(*this);
            has_return_else|=has_return;
        }
    }
    has_return = has_return_then & has_return_elif & has_return_else;
}
void DeclarationAnalyzer::visit(parser::FuncDef &node) {
    if(DEBUG)cerr<<"--FuncDef "<<node.name->name<<'\n';
    curr_func = node.name->name;
    // name
    auto name = sym->get<SymbolType*>(node.name->name);
    if(sym->tab->count(node.name->name)){   // same scope re-define
        errors->emplace_back(
            new SemanticError(node.name, 
                fmt::format("Invalid Func name; re-define: {}",
                    node.name->name)));
    }
    if(node.name->name=="int"||node.name->name=="str"||node.name->name=="bool"||node.name->name=="list"||node.name->name=="object"){
        errors->emplace_back(
            new SemanticError(node.name, 
                fmt::format("Invalid Func name; it is pre-defined: {}",
                    node.name->name)));
    }
    // create symboltable
    sym = new SymbolTable(sym);
    auto bar = new FunctionDefType();
    bar->func_name = node.name->name;
    bar->params = new std::vector<SymbolType *>();
    bar->current_scope = sym;
    // params
    for(auto& param:*node.params){
        param->accept(*this);
        bar->params->emplace_back((*sym->tab)[param->identifier->name]);
    }
    if(curr_class!=""){ // self
        if(!bar->params->size()){
            errors->emplace_back(
                new SemanticError(&node, 
                    fmt::format("Invalid Method params; at least one params")));
        }
        else{
            auto self_type = (*bar->params)[0];
            if(self_type->get_name()!=curr_class){
                errors->emplace_back(
                    new SemanticError((*node.params)[0], 
                        fmt::format("Invalid Method params; the first param must have type:{}",
                        curr_class)));
            }
        }
    }
    // return type
    if(node.returnType==nullptr)
        bar->return_type = new ClassValueType("<None>");
    else{
        auto tp = node.returnType;
        auto tp2 = dynamic_cast<ListType*>(tp);
        while(tp2){
            tp = tp2->elementType;
            tp2 = dynamic_cast<ListType*>(tp);
        }
        if (dynamic_cast<parser::ClassType *>(tp) &&
            globals->get<SymbolType *>(((parser::ClassType *)tp)->className) == nullptr &&
            classNames.find(((ClassType*)tp)->className)==classNames.end() &&
            !(((parser::ClassType *)tp)->className == curr_class)) {
                errors->emplace_back(
                    new SemanticError(node.returnType, fmt::format("Invalid return type; there is no class named: {}",
                                                                    ((parser::ClassType *)node.returnType)->get_name())));
        }
        bar->return_type = new ClassValueType((ClassType*)node.returnType);
    }
    // inherited override
    if(curr_class!="" && name){
        auto father_func = dynamic_cast<FunctionDefType*>(name);
        bool is_error = 0;
        if(!father_func) is_error=1;
        else if(father_func->return_type->neq(bar->return_type)) is_error=1;
        else if(father_func->params->size()!=bar->params->size()) is_error=1;
        else{
            int i=0;
            for(auto& param: *father_func->params){
                if(i && param->neq((*bar->params)[i]))
                    is_error=1;
                i++;
            }
        }
        if(is_error)
            errors->emplace_back(
                new SemanticError(node.name, 
                    fmt::format("Invalid override; method: {}",
                        node.name->name)));
    }
    // add into symbol table
    sym->parent->put(node.name->name, bar);
    auto parent = sym->parent;
    if(curr_class!=""){
        sym->parent = globals;
    }
    // enumerate
    bool has_return_here = 0;
    for(auto& decl: *node.declarations){
        if(dynamic_cast<VarDef*>(decl)){
            decl->accept(*this);
            curr_func = node.name->name;
        }
    }
    for(auto& decl: *node.declarations){
        if(!dynamic_cast<VarDef*>(decl)){
            decl->accept(*this);
            curr_func = node.name->name;
        }
    }
    for(auto& stmt: *node.statements){
        has_return=0;
        stmt->accept(*this);
        has_return_here |= has_return;
    }
    // judge return
    auto ret = dynamic_cast<parser::ClassType *>(node.returnType);
    if(ret&&(ret->className=="int"||ret->className=="str"||ret->className=="bool")&&!has_return){
        errors->emplace_back(
            new SemanticError(node.returnType, 
                fmt::format("Invalid return; not all paths have return")));
    }
    // exit
    sym = parent;
}
void DeclarationAnalyzer::visit(parser::GlobalDecl &node) {
    if(DEBUG)cerr<<"--GlobalDecl "<<node.variable->name<<'\n';
    // name
    if(sym->tab->count(node.variable->name)){
        errors->emplace_back(
            new SemanticError(node.variable, 
                fmt::format("Invalid global; re-define: {}",
                    node.variable->name)));
    }
    else{
        auto glb = globals->get<ClassValueType*>(node.variable->name);
        if(!glb)
            errors->emplace_back(
                new SemanticError(node.variable,
                    fmt::format("Invalid global; no global var named: {}",
                        node.variable->name)));
        else 
            sym->put(node.variable->name, glb);
    }
}
void DeclarationAnalyzer::visit(parser::NonlocalDecl &node) {
    if(DEBUG)cerr<<"--NonlocalDecl "<<node.variable->name<<'\n';
    // name
    if(sym->tab->count(node.variable->name)){
        errors->emplace_back(
            new SemanticError(node.variable, 
                fmt::format("Invalid nonlocal; re-define: {}",
                    node.variable->name)));
    }
    else{
        auto sym_tab = sym->parent;
        bool found=0;
        ClassValueType* nlc;
        while(sym_tab!=globals){
            if(sym_tab->tab->count(node.variable->name)){
                nlc=sym_tab->get<ClassValueType*>(node.variable->name);
                if(nlc)found=1;
                else break;
            }
            sym_tab = sym_tab->parent;
        }
        if(!found){
            errors->emplace_back(
                new SemanticError(node.variable, 
                    fmt::format("Invalid nonlocal; no nonlocal var named: {}",
                        node.variable->name)));
        }
        else 
            sym->put(node.variable->name, nlc);
    }
}
void DeclarationAnalyzer::visit(parser::TypedVar &node) {
    if(DEBUG)cerr<<"--TypedVar "<<node.identifier->name<<":"<<node.type->get_name()<<'\n';
    // type
    auto tp = node.type;
    auto tp2 = dynamic_cast<ListType*>(tp);
    while(tp2){
        tp = tp2->elementType;
        tp2 = dynamic_cast<ListType*>(tp);
    }
    if (dynamic_cast<parser::ClassType *>(tp) &&
        globals->get<SymbolType *>(((parser::ClassType *)tp)->className) == nullptr &&
        classNames.find(((ClassType*)tp)->className)==classNames.end() &&
        !(((parser::ClassType *)tp)->className == curr_class)) {
        errors->emplace_back(
            new SemanticError(node.type, fmt::format("Invalid type annotation; there is no class named: {}",
                                                            ((parser::ClassType *)node.type)->get_name())));
    }
    // name
    if(sym->tab->count(node.identifier->name)){
        errors->emplace_back(
            new SemanticError(node.identifier, 
                fmt::format("Invalid Var name; re-define: {}",
                    node.identifier->name)));
    }
    if(classNames.find(node.identifier->name)!=classNames.end()){
        errors->emplace_back(
            new SemanticError(node.identifier, 
                fmt::format("Invalid Var name; it is a class name: {}",
                    node.identifier->name)));
    }
    if(node.identifier->name=="int"||node.identifier->name=="str"||node.identifier->name=="bool"||node.identifier->name=="list"||node.identifier->name=="object"){
        errors->emplace_back(
            new SemanticError(node.identifier, 
                fmt::format("Invalid Var name; it is pre-defined: {}",
                    node.identifier->name)));
    }
    this->passing_type = ValueType::annotate_to_val(node.type);
    if(dynamic_cast<ClassType*>(node.type))
        sym->put(node.identifier->name, new ClassValueType((ClassType*)node.type));
    else sym->put(node.identifier->name, new ListValueType((ListType*)node.type));
}
void DeclarationAnalyzer::visit(parser::ReturnStmt &node){
    if(curr_func=="__init__" && node.value){
        errors->emplace_back(
            new SemanticError(node.value, 
                fmt::format("Invalid return; __init__ cannot have return value")));
    }
    if(curr_func==""){
        errors->emplace_back(
            new SemanticError(node.value, 
                fmt::format("Invalid return; not in a function")));
    }
    has_return=1;
}
void DeclarationAnalyzer::visit(parser::VarAssignStmt &node){
    if(DEBUG)cerr<<"--VarAssignStmt"<<'\n';
    // name
    if(!sym->tab->count(node.var->name)){
        errors->emplace_back(
            new SemanticError(node.var, fmt::format("Invalid assign; no such var: {}",
                                            node.var->name)));
    }
    node.value->accept(*this);
}
void DeclarationAnalyzer::visit(parser::VarAssignExpr &node){
    if(DEBUG)cerr<<"--VarAssignExpr"<<'\n';
    // name
    if(!sym->tab->count(node.var->name)){
        errors->emplace_back(
            new SemanticError(node.var, fmt::format("Invalid assign; no such var: {}",
                                            node.var->name)));
    }
    node.value->accept(*this);
}
void DeclarationAnalyzer::visit(parser::ForStmt &node) {
    // iterable
    node.iterable->accept(*this);
    // identifier
    node.identifier->accept(*this);
    // enter
    sym = new SymbolTable(sym);
    for(auto& stmt: *node.body){
        stmt->accept(*this);
    }
    // exit
    sym = sym->parent;
}
void DeclarationAnalyzer::visit(parser::Program &program) {
    curr_func = "";
    curr_class = "";
    if(DEBUG)cerr<<"--Program--\n";
    for(auto& decl: *program.declarations){
        ClassDef* d = dynamic_cast<ClassDef *>(decl);
        if(d){
            // printf("pre: classdef: \n");
            // auto foo = new ClassDefType(d->superClass->name, d->name->name);
            // sym->tab->insert({d->name->name, foo});
            if(DEBUG)cerr<<"pre:"<<d->name->name<<'\n';
            classNames.insert(d->name->name);
        }
    }
    for(auto& decl: *program.declarations){
        if(dynamic_cast<VarDef*>(decl)){
            decl->accept(*this);
            curr_func = "";
            curr_class = "";
        }
    }
    for(auto& decl: *program.declarations){
        if(!dynamic_cast<VarDef*>(decl)){
            decl->accept(*this);
            curr_func = "";
            curr_class = "";
        }
    }
    for(auto& stmt: *program.statements){
        stmt->accept(*this);
    }
}

template <typename... Args> void TypeChecker::typeError(parser::Node *node, const string &message, Args... rest) {
    node->semError(rest...);
    node->semError(message);
}
void TypeChecker::typeError(parser::Node *node, const string &message) {
    if (!node->has_type_err()) {
        node->typeError = message;
    } else {
        node->typeError += "\t" + message;
    }
}
#define DEBUGTYPE 0
#define test(x) if(DEBUGTYPE) typeError(&node, x)
#define out(x) if(DEBUGTYPE) std::cout<<(x)<<'\n'
#define debug(x) if(DEBUGTYPE) std::cerr<<(x)<<'\n'
using namespace semantic;

void TypeChecker::visit(parser::Program &program) {
    father.clear();
    childs.clear();
    for(auto Decl : *globals->tab)
    {
        if(dynamic_cast<ClassDefType*>(Decl.second))
        {
            string fa = ((ClassDefType*)Decl.second)->super_class;
            string child = ((ClassDefType*)Decl.second)->class_name;
            father.insert({child, fa});
            if(childs.find(fa) != childs.end())
                childs[fa].push_back(child);
            else
            {
                vector<string> tmp;
                tmp.push_back(child);
                childs.insert({fa, tmp});
            }
        }
    }
    // std::cerr<<father["int"]<<'\n';
    // std::cerr<<father[":asdjklafjgl"]<<'\n';
    if(father.find("int") != father.end())
    {
        father["int"] = "object";
        // std::cerr<<father[(string)"int"]<<'\n';
    }
    else
    {
        father.insert({"int", "object"});
    }
    if(father.find("bool") == father.end())
    {
        father.insert({"bool", "object"});
    }
    else {
        father["bool"] = "object";
    }
    if(father.find("str") == father.end())
        father.insert({"str", "object"});
    else {
        father["str"] = "object";
    }
    if(father.find("<None>") == father.end())
        father.insert({"<None>", "object"});
    else {
        father["<None>"] = "object";
    }
    for (auto& decl : *program.declarations) {
        decl->accept(*this);
        // std::cout<<decl->get_id()->name<<'\n';
    }
    for (auto& stmt : *program.statements) {
        stmt->accept(*this);
        // out(stmt->kind);
    }
}
/* The Type check rules Your Code Here */
/*  
    Expression 
    f(x,y,z) // para type and number
    return type?
    x = ?
*/

bool TypeChecker::IsInherit(string a, string b){
    // a is b's subclass
    auto it = father.find(a);
    auto nowstr = a;
    // std::cerr<<a<<'\n'<<b<<'\n';
    while(it != father.end())
    {
        if(nowstr == b){
            return true;
        }
        nowstr = father[nowstr];
        it = father.find(nowstr);
    }
    // std::cerr<<"FALSE"<<'\n';
    return false;
}
bool TypeChecker::le(string a, string b){
    // a <= b
    if(IsInherit(a, b)) return true;
    if(a == b) return true;
    if(a == "<None>" && b == "object") return true;
    if(a == "<Empty>" && b == "object") return true;
    return false;
}
SymbolType* TypeChecker::LCA(SymbolType* a, SymbolType* b){
    if(a==nullptr) return new ClassValueType(b->get_name());
    if(b==nullptr) return new ClassValueType(a->get_name());
    if(a->is_list_type() || b->is_list_type()) {
        return new ClassValueType("object");
    }
    // std::cerr<<fmt::format("LCA: {} {}", a->get_name(), b->get_name())<<'\n';
    
    if(IsInherit(a->get_name(), b->get_name())) return b;
    if(IsInherit(b->get_name(), a->get_name())) return a;
    vector<string> a_pa;
    vector<string> b_pa;
    string nowstr = a->get_name();
    // std::cerr<<nowstr<<'\n';
    // std::cerr<<"fa: "<<father[nowstr]<<'\n';
    while(nowstr != "object")
    {
        // std::cerr<<nowstr<<'\n';
        a_pa.push_back(nowstr);
        nowstr = father[nowstr];
    }
    // std::cerr<<"1\n";
    nowstr = b->get_name();
    while(nowstr != "object")
    {
        b_pa.push_back(nowstr);
        nowstr = father[nowstr];
    }
    std::reverse(a_pa.begin(), a_pa.end());
    std::reverse(b_pa.begin(), b_pa.end());
    string now = "object";
    for(int i=0; i<std::min(a_pa.size(), b_pa.size()); ++i)
    {
        if(a_pa[i] == b_pa[i])
        {
            now = a_pa[i];
        }
        else
        {
            break;
        }
    }
    return new ClassValueType(now);
}

bool TypeChecker::CouldBeAssign(SymbolType* T_2, SymbolType* T_1){
    if(le(T_1->get_name(), T_2->get_name())) return true;
    if(T_1->is_list_type()){
        if(T_2->get_name() == "object")
            return true;
    }
    if(T_1->get_name() == "<None>"){
        if(T_2->get_name() != "int" && T_2->get_name() != "bool" && T_2->get_name() != "str")
            return true;
    }
    if(T_1->get_name() == "<Empty>"){
        if(T_2->is_list_type())
            return true;
    }
    if(T_2->is_list_type() && !((ListValueType*)T_2)->element_type->is_list_type()){
        if(T_1->get_name() == "[<None>]")
            return true;
    }
    return false;
}
void TypeChecker::visit(parser::BinaryExpr &node) {
    // std::cerr<<"BEGIN BINARY EXPR"<<'\n';
    node.left->accept(*this);
    node.right->accept(*this);
    
    // std::cerr<<"TEST!\n";
    // if(node.left->inferredType == nullptr){
    //     std::cerr<<"left is null"<<'\n';
    // }
    // if(node.right->inferredType == nullptr){
    //     std::cerr<<"right is null"<<'\n';
    // }
    auto l = node.left->inferredType->get_name();
    auto r = node.right->inferredType->get_name();
    // std::cerr<<"EDN!\n";
    if(node.operator_=="+")
    {
        // std::cerr<<"BEGIN +\n";
        if(l == "int" && r == "int")
            node.inferredType = new ClassValueType("int");
        else if(l == "str" && r == "str")
            node.inferredType = new ClassValueType("str");
        else if(node.left->inferredType->is_list_type() && node.right->inferredType->is_list_type())
        {
            // std::cerr<<"651:\n";
            node.inferredType = LCA(node.left->inferredType, node.right->inferredType);
            // std::cerr<<"END";
        }
        else {
            node.inferredType = new ClassValueType("object");
            typeError(&node, "Type Error: + could not be applied to types " + l + " and " + r);
        }
    }
    if(node.operator_ == "==" || node.operator_ == "!=")
    {
        if(l == "int" && r == "int")
            node.inferredType = new ClassValueType("bool");
        else if(l == "str" && r == "str")
            node.inferredType = new ClassValueType("bool");
        else if(l == "bool" && r == "bool")
            node.inferredType = new ClassValueType("bool");
        else
        {
            typeError(&node, "Type Error: " + node.operator_ + " could not be applied to types " + l + " and " + r);
            node.inferredType == new ClassValueType("bool");
        }
    }
    if(node.operator_ == "and" || node.operator_ == "or")
    {
        if(l == "bool" && r == "bool")
            node.inferredType = new ClassValueType("bool");
        else
        {
            typeError(&node, "Type Error: " + node.operator_ + " could not be applied to types " + l + " and " + r);
            node.inferredType = new ClassValueType("bool");
        }
    }
    if(node.operator_ == "-" || node.operator_ == "//" || node.operator_ == "*" || node.operator_ == "%")
    {
        if(l == "int" && r == "int")
            node.inferredType = new ClassValueType("int");
        else
        {
            typeError(&node, "Type Error: " + node.operator_ + " could not be applied to types " + l + " and " + r);
            node.inferredType = new ClassValueType("int");
        }
    }
    if(node.operator_ == "<" || node.operator_ == ">" || node.operator_ == "<=" || node.operator_ == ">=")
    {
        if(l == "int" && r == "int")
            node.inferredType = new ClassValueType("bool");
        else
        {
            typeError(&node, "Type Error: " + node.operator_ + " could not be applied to types " + l + " and " + r);
            node.inferredType = new ClassValueType("bool");
        }
    }
    if(node.operator_ == "is")
    {
        if(l == "int" || l == "bool" || l == "str" || r == "int" || r == "bool" || r == "str") {
            typeError(&node, "Type Error: " + node.operator_ + " could not be applied to types " + l + " and " + r);
        }
        node.inferredType = new ClassValueType("bool");
    }
}
void TypeChecker::visit(parser::BoolLiteral &node) {
    node.inferredType = new ClassValueType("bool");
}
void TypeChecker::visit(parser::CallExpr &node) {
    auto func = sym->get<SymbolType*>(node.function->name);
    if(func == nullptr) {
        typeError(&node, "Function " + node.function->name + " is not defined");
        node.inferredType = new ClassValueType("object");
        node.function->inferredType = new ClassValueType("object");
        if(node.has_args) {
            for(auto& arg : *node.args) {
                arg->accept(*this);
            }
        }
    }
    else if(dynamic_cast<FunctionDefType*>(func)){
        auto func_type = (FunctionDefType*)func;
        node.function->inferredType = func_type;
        if(node.has_args) {
            for(auto& arg : *node.args) {
                arg->accept(*this);
            }
            if(node.args->size() != func_type->params->size()) {
                typeError(&node, fmt::format("Error! Expected {} arguments, but got {}", func_type->params->size(), node.args->size()));
            }
            else {
                for(int i=0; i<node.args->size(); ++i) {
                    if(func_type->params->at(i)->get_name() != node.args->at(i)->inferredType->get_name()) {
                        typeError(&node, fmt::format("Error! Expected '{}', got '{}'", func_type->params->at(i)->get_name(), node.args->at(i)->inferredType->get_name()));
                    }
                }
            }
        }
        node.inferredType = func_type->return_type;
    }
    else if(dynamic_cast<ClassDefType*>(func)){
        node.function->inferredType = func;
        if(node.has_args)
        {
            for(auto& arg : *node.args)
            {
                arg->accept(*this);
            }
            // typeError(&node, "Error! Class method cannot have arguments");
        }
        node.inferredType = new ClassValueType(func->get_name());
    }
    else{
        typeError(&node, "Error! " + node.function->name + " is not a function");
        node.inferredType = new ClassValueType("object");
        node.function->inferredType = func;
        if(node.has_args) {
            for(auto& arg : *node.args) {
                arg->accept(*this);
            }
        }
    }

}
void TypeChecker::visit(parser::ClassDef &node) {
    auto curscope = sym;
    auto tmp = sym->get<ClassDefType*>(node.name->name);
    sym = tmp->current_scope;
    for(auto& decl: *node.declaration){
        decl->accept(*this);
    }
    sym = curscope;
}
void TypeChecker::visit(parser::ExprStmt &node) {
    node.expr->accept(*this);
}
void TypeChecker::visit(parser::ForStmt &node) {
    node.identifier->accept(*this);
    node.iterable->accept(*this);
    for(auto& stmt: *node.body) {
        stmt->accept(*this);
    }
    auto Idtype = node.identifier->inferredType->get_name();
    bool f = 0;
    ListValueType* ptr = (ListValueType*)node.iterable->inferredType;
    if(node.iterable->inferredType->is_list_type()){
        f = 1;
    }
    if(f) {
        auto listType = ptr->element_type->get_name();
        if(!le(listType, Idtype)) {
            typeError(&node, fmt::format("Error! List type expected '{0}' <= '{1}'", listType , Idtype));
        }
    }
    else {
        if(!le("str", Idtype)) {
            typeError(&node, fmt::format("Error! Expected 'str' <= '{}'", Idtype));
        }
    }
}
void TypeChecker::visit(parser::FuncDef &node) {
    auto curscope = sym;
    auto tmp = sym->get<FunctionDefType*>(node.name->name);
    auto curtype = passing_type;
    sym = tmp->current_scope;
    passing_type = tmp->return_type;
    for(auto& param: *node.params) {
        param->accept(*this);
    }
    for(auto& decl: *node.declarations) {
        decl->accept(*this);
    }
    for(auto& stmt: *node.statements) {
        stmt->accept(*this);
    }
    sym = curscope;
    passing_type = curtype;
}
void TypeChecker::visit(parser::Ident &node) {
    if(globals->get<ValueType*>(node.name) == nullptr)
    {
        typeError(&node, "Error! " + node.name + "is not a variable.");
        node.inferredType = new ClassValueType("object");
    }
    else if(globals->get<ClassDefType*>(node.name))
    {
        typeError(&node, "Error! " + node.name + "is a Class.");
        node.inferredType = new ClassValueType(node.name);
    }
    else 
        node.inferredType = globals->get<ValueType*>(node.name);

}
void TypeChecker::visit(parser::IfExpr &node) {
    node.condition->accept(*this);
    node.thenExpr->accept(*this);
    node.elseExpr->accept(*this);
    if(node.condition->inferredType->get_name() != "bool") {
        typeError(&node, fmt::format("Error! Expected 'bool', got '{}'", node.condition->inferredType->get_name()));
    }
    // std::cerr<<"844\n";
    // std::cerr<<fmt::format("LCA844: {}, {}", node.thenExpr->inferredType->get_name(), node.elseExpr->inferredType->get_name())<<"\n";
    node.inferredType = LCA(node.thenExpr->inferredType, node.elseExpr->inferredType);
    // std::cerr<<"FINISH\n";
}
void TypeChecker::visit(parser::IndexExpr &node) {
    node.list->accept(*this);
    node.index->accept(*this);
    if(node.list->inferredType->is_list_type()) {
        if(node.index->inferredType->get_name() != "int") {
            typeError(&node, fmt::format("Error! Expected 'int', got '{}'", node.index->inferredType->get_name()));
        }
        // std::cerr<<"BEGIN\n";
        node.inferredType = new ClassValueType(((ListValueType*)node.list->inferredType)->element_type->get_name());
        // std::cerr<<"END\n";
    }
    else if(node.list->inferredType->get_name() == "str") {
        if(node.index->inferredType->get_name() != "int") {
            typeError(&node, fmt::format("Error! Expected 'int', got '{}'", node.index->inferredType->get_name()));
        }
        node.inferredType = new ClassValueType("str");
    }
    else {
        typeError(&node, fmt::format("Error! Expected 'list', got '{}'", node.list->inferredType->get_name()));
        if(node.index->inferredType->get_name() != "int") {
            typeError(&node, fmt::format("Error! Expected 'int', got '{}'", node.index->inferredType->get_name()));
        }
        node.inferredType = new ClassValueType("object");
    }
}
void TypeChecker::visit(parser::IntegerLiteral &node) {
    node.inferredType = new ClassValueType("int");
}
void TypeChecker::visit(parser::ListExpr &node) {
    SymbolType* tmp = nullptr;
    if(node.has_expr) {
        for(auto& expr: *node.elements) {
            expr->accept(*this);
            // std::cerr<<"877\n";
            // if(expr->inferredType == nullptr){
            //     std::cerr<<">>asfjkalsjgfk\n";
            // }
            // std::cerr<<expr->inferredType->get_name()<<"\n";
            tmp = LCA(tmp, expr->inferredType);
            // std::cerr<<"END877\n";
        }
        if(tmp == nullptr) node.inferredType = new ClassValueType("<Empty>");
        else
            // node.inferredType = tmp;
            node.inferredType = new ListValueType((ValueType*)tmp);
        // if(tmp == nullptr) {
        //     std::cerr<<"87adsa7\n";
        // }
        // else{
        //     std::cerr<<tmp->get_name()<<"\n";
        // }
    }
    else{
        node.inferredType = new ClassValueType("<Empty>");
    }
}
void TypeChecker::visit(parser::MemberExpr &node) {
    node.object->accept(*this);
    auto obj_type = node.object->inferredType->get_name();
    auto tmp = globals->get<ClassDefType*>(obj_type);
    if(tmp == nullptr) {
        typeError(&node, fmt::format("Error! Expected 'class', got '{}'", obj_type));
        node.inferredType = new ClassValueType("object");
    }
    else {
        auto member_type = tmp->current_scope->get<ValueType*>(node.member->name);
        if(member_type == nullptr) {
            typeError(&node, fmt::format("Error! Member '{}' not found in class '{}'", node.member->name, obj_type));
            node.inferredType = new ClassValueType("object");
        }
        else {
            node.inferredType = member_type;
        }
    }
}
void TypeChecker::visit(parser::MethodCallExpr &node) {
    node.method->object->accept(*this);
    auto methodName = node.method->object->inferredType->get_name();
    auto methodType = globals->get<ClassDefType*>(methodName);
    if(methodType == nullptr) {
        typeError(&node, fmt::format("Error! '{}' is not a class.", methodName));
        node.inferredType = new ClassValueType("object");
    }
    else
    {
        if(node.has_args) {
            for(auto& arg: *node.args) {
                arg->accept(*this);
            }
        }
        auto tmp = methodType->current_scope->get<FunctionDefType*>(node.method->member->name);
        if(tmp == nullptr) {
            typeError(&node, fmt::format("Error! '{}' is not a method.", node.method->member->name));
            node.inferredType = new ClassValueType("object");
        }
        else {
            if(node.has_args) {
                if(node.args->size() != tmp->params->size()) {
                    typeError(&node, fmt::format("Error! Expected '{}' arguments, got '{}'", tmp->params->size(), node.args->size()));
                }
                else {
                    for(int i = 0; i < node.args->size(); ++i) {
                        if(tmp->params->at(i)->get_name() != node.args->at(i)->inferredType->get_name()) {
                            typeError(&node, fmt::format("Error! Expected '{}', got '{}'", tmp->params->at(i)->get_name(), node.args->at(i)->inferredType->get_name()));
                        }
                    }
                }
            }
            node.inferredType = tmp->return_type;
        }
        
    }
}
void TypeChecker::visit(parser::NoneLiteral &node) {
    node.inferredType = new ClassValueType("<None>");
}
void TypeChecker::visit(parser::ReturnStmt &node) {
    if(node.value == nullptr) {
        if(passing_type->get_name() != "<None>") {
            typeError(&node, fmt::format("Error! Expected '{}'", passing_type->get_name()));
        }
    }
    else {
        node.value->accept(*this);
        if(!CouldBeAssign(node.value->inferredType, passing_type)) {
            typeError(&node, fmt::format("Error! Expected '{}' <= '{}'", 
                    node.value->inferredType->get_name(), passing_type->get_name()));
        }
    }
}
void TypeChecker::visit(parser::StringLiteral &node) {
    node.inferredType = new ClassValueType("str");
}
void TypeChecker::visit(parser::UnaryExpr &node) {
    node.operand->accept(*this);
    if(node.operator_ == "-")
    {
        if(node.operand->inferredType->get_name() != "int") {
            typeError(&node, fmt::format("Error! Expected 'int', got '{}'", node.operand->inferredType->get_name()));
        }
        node.inferredType = new ClassValueType("int");
    }
    else if (node.operator_ == "not")
    {
        if(node.operand->inferredType->get_name() != "bool") {
            typeError(&node, fmt::format("Error! Expected 'bool', got '{}'", node.operand->inferredType->get_name()));
        }
        node.inferredType = new ClassValueType("bool");
    }
}
void TypeChecker::visit(parser::VarDef &node) {
    auto vartype = ValueType::annotate_to_val(node.var->type);
    node.var->inferredType = vartype;
    node.value->accept(*this);
    if (!CouldBeAssign(vartype, node.value->inferredType)) {
        typeError(&node, fmt::format("Error! Expected '{0}' <= '{1}'", 
                vartype->get_name(), node.value->inferredType->get_name()));
    }

}
void TypeChecker::visit(parser::WhileStmt &node) {
    node.condition->accept(*this);
    for (auto& stmt: *node.body){
        stmt->accept(*this);
    }
    if(node.condition->inferredType->get_name() != "bool") {
        typeError(&node, fmt::format("Expected type 'bool', got type '{}'", 
                node.condition->inferredType->get_name()));
    }
}
void TypeChecker::visit(parser::VarAssignStmt &node) {
    node.value->accept(*this);
    // std::cerr<<node.value->inferredType->get_name()<<"\n";
    if(!CouldBeAssign(sym->get<SymbolType*>(node.var->name), node.value->inferredType))
    {
        // debug(node.var->inferredType->get_name());
        typeError(&node, fmt::format("Expected type `{0}`; got type `{1}`", 
            sym->get<SymbolType*>(node.var->name)->get_name(), node.value->inferredType->get_name()));
    }
    // test("GGG");
}
void TypeChecker::visit(parser::VarAssignExpr &node) {
    node.value->accept(*this);
    if(!CouldBeAssign(sym->get<SymbolType*>(node.var->name), node.value->inferredType))
    {
        typeError(&node, fmt::format("Expected type `{0}`; got type `{1}`", 
            sym->get<SymbolType*>(node.var->name)->get_name(), node.value->inferredType->get_name()));
    }
    node.inferredType = node.value->inferredType;
}
void TypeChecker::visit(parser::MemberAssignStmt &node) {
    node.objectMember->object->accept(*this);
    auto objectMember = node.objectMember;
    auto obj_type = objectMember->object->inferredType->get_name();
    auto tmp = globals->get<ClassDefType*>(obj_type);
    if(tmp == nullptr) {
        typeError(&node, fmt::format("Error! Expected 'class', got '{}'", obj_type));
        objectMember->inferredType = new ClassValueType("object");
    }
    if(tmp != nullptr) {
        auto member_type = tmp->current_scope->get<ValueType*>(objectMember->member->name);
        if(member_type == nullptr) {
            typeError(&node, fmt::format("Error! Member '{}' not found in class '{}'", objectMember->member->name, obj_type));
            objectMember->inferredType = new ClassValueType("object");
        }
        else {
            objectMember->inferredType = member_type;
        }
    }
    node.value->accept(*this);
    if(!CouldBeAssign(node.objectMember->inferredType, node.value->inferredType))
    {
        typeError(&node, fmt::format("Expected type `{0}`; got type `{1}`", 
            node.objectMember->inferredType->get_name(), node.value->inferredType->get_name()));
    }
}
void TypeChecker::visit(parser::MemberAssignExpr &node) {
    node.objectMember->accept(*this);
    node.value->accept(*this);
    if(!CouldBeAssign(node.objectMember->inferredType, node.value->inferredType))
    {
        typeError(&node, fmt::format("Expected type `{0}`; got type `{1}`", 
            node.objectMember->inferredType->get_name(), node.value->inferredType->get_name()));
    }
    node.inferredType = node.value->inferredType;
}
void TypeChecker::visit(parser::IndexAssignStmt &node) {
    node.listElement->accept(*this);
    node.value->accept(*this);
    if(node.listElement->list->inferredType->get_name() == "str") {
        typeError(&node, "Error! Cannot assign to a string.");
    }
    else {
        // std::cerr<<((ListValueType*)node.listElement->inferredType)->element_type->get_name()<<"\n";
        // std::cerr<<node.value->inferredType->get_name()<<"\n";
        // std::cerr<<"BEGIN1\n";
        // if(node.listElement->lis)
        if(!CouldBeAssign(node.listElement->inferredType, node.value->inferredType)) {
            // std::cerr<<"??\n";
            typeError(&node, fmt::format("Expected type '{}', got type '{}'", 
                    node.listElement->list->inferredType->get_name(), node.value->inferredType->get_name()));
        }
        // std::cerr<<"END1\n";
    }
}
void TypeChecker::visit(parser::IndexAssignExpr &node) {
    node.listElement->accept(*this);
    node.value->accept(*this);
    if(node.listElement->list->inferredType->get_name() == "str")
    {
        typeError(&node, "Error! Cannot assign to a string");
    }
    else if(!CouldBeAssign(((ListValueType*)node.listElement->inferredType)->element_type, node.value->inferredType))
    {
        typeError(&node, fmt::format("Expected type `{0}`; got type `{1}`", 
            node.listElement->inferredType->get_name(), node.value->inferredType->get_name()));
    }
    node.inferredType = node.value->inferredType;
}
void TypeChecker::visit(parser::AssignStmt &node) {
    // typeError(&node, "TestError");
    // test("ASSIGN");
}
void TypeChecker::visit(parser::IfStmt &node) {
    node.condition->accept(*this);
    for(auto& stmt: *node.thenBody) {
        stmt->accept(*this);
    }
    if(node.el == parser::IfStmt::cond::THEN_ELIF) {
        node.elifBody->accept(*this);
    }
    if(node.el == parser::IfStmt::cond::THEN_ELSE) {
        for(auto& stmt: *node.elseBody) {
            stmt->accept(*this);
        }
    }
    if(node.condition->inferredType->get_name() != "bool") {
        typeError(&node, fmt::format("Expected type 'bool', got type '{}'", 
                node.condition->inferredType->get_name()));
    }
}

void TypeChecker::debug_sym() {
    for (const auto &x : *sym->tab) {
        if ((x.second)->is_list_type()) {
            LOG(INFO) << x.first << " : [" << ((ClassValueType *)((ListValueType *)x.second)->element_type)->get_name()
                      << "]\n";
        } else if ((x.second)->is_func_type()) {
            if (dynamic_cast<FunctionDefType *>(x.second)) {
                LOG(INFO) << "Function " << x.first << " : [ "
                          << dynamic_cast<FunctionDefType *>(x.second)->return_type->get_name() << " ]";
                debug_nested_func_sym(((FunctionDefType *)x.second)->current_scope, 1);
            }
            for (const auto y : *dynamic_cast<FunctionDefType *>(x.second)->params)
                if (!y->is_list_type())
                    LOG(INFO) << "      : " << ((ClassValueType *)y)->get_name() << "\n";
                else
                    LOG(INFO) << "      : " << ((ClassValueType *)((ListValueType *)y)->element_type)->get_name()
                              << "\n";
        } else if ((x.second)->is_value_type()) {
            LOG(INFO) << x.first << " : " << ((ClassValueType *)x.second)->get_name() << "\n";
        }
    }
}

void TypeChecker::debug_nested_func_sym(SymbolTable *func_sym, int tab) {
    for (auto x : *func_sym->tab) {
        if ((x.second)->is_list_type()) {
            LOG(INFO) << fmt::format("{:>{}} : [ {} ]", x.first, tab * 20,
                                     ((ClassValueType *)((ListValueType *)x.second)->element_type)->get_name());
        } else if ((x.second)->is_func_type()) {
            if (dynamic_cast<FunctionDefType *>(x.second)) {
                LOG(INFO) << fmt::format("{:>{}} : [ {} ]", "Function " + x.first, tab * 20,
                                         dynamic_cast<FunctionDefType *>(x.second)->return_type->get_name());
                debug_nested_func_sym(((FunctionDefType *)x.second)->current_scope, tab++);
            }
            for (const auto y : *dynamic_cast<FunctionDefType *>(x.second)->params)
                if (!y->is_list_type())
                    LOG(INFO) << fmt::format("{:>{}}       : [ {} ]", "", tab * 20, ((ClassValueType *)y)->get_name());
                else
                    LOG(INFO) << fmt::format("{:>{}}       : [ {} ]", "", tab * 20,
                                             ((ClassValueType *)((ListValueType *)y)->element_type)->get_name());
        } else if ((x.second)->is_value_type()) {
            LOG(INFO) << fmt::format("{:>{}} : [ {} ]", x.first, tab * 20, ((ClassValueType *)x.second)->get_name());
        }
    }
}
/** Get the right type */
string TypeChecker::get_common_type(SymbolType *first, SymbolType *second) {
    string tmp = first->get_name();
    if (tmp.starts_with("[")) {
        if (second->get_name() == "object")
            return "object";
        else
            return "";
    }
    list<string> first_dfs = {tmp};
    while (tmp != "object") {
        for (const auto &x : super_classes) {
            if (tmp == x.first) {
                first_dfs.push_back(x.second);
                tmp = x.second;
                break;
            }
        }
    }
    tmp = second->get_name();
    while (tmp != "object") {
        if (std::find(first_dfs.begin(), first_dfs.end(), tmp) != first_dfs.end()) {
            return tmp;
        }
        for (const auto &x : super_classes) {
            if (tmp == x.first) {
                tmp = x.second;
                break;
            }
            if (tmp == "None") {
                return "object";
            }
        }
    }
    return "object";
}
void TypeChecker::setup_num_to_class() {
    for (const auto &x : *sym->tab) {
        if (dynamic_cast<ClassDefType *>(x.second)) {
            auto tmp_dad = sym->get<ClassDefType *>(((ClassDefType *)x.second)->get_dad());
            super_classes[x.second->get_name()] = ((ClassDefType *)x.second)->get_dad();
            add_edge(((ClassDefType *)x.second)->get_dad(), x.second->get_name());
            while (tmp_dad != nullptr && tmp_dad->get_name() != "object" &&
                   !super_classes.contains(tmp_dad->get_name())) {
                add_edge(tmp_dad->get_dad(), tmp_dad->get_name());
                tmp_dad = sym->get<ClassDefType *>(tmp_dad->get_dad());
            }
        }
    }
    dfs("object");
    sym->class_tag_["list"] = -1;
    sym->class_tag_["object"] = 0;
    sym->class_tag_["int"] = 1;
    sym->class_tag_["bool"] = 2;
    sym->class_tag_["str"] = 3;
}
ValueType *ValueType::annotate_to_val(parser::TypeAnnotation *annotation) {
    if (dynamic_cast<parser::ClassType *>(annotation)) {
        return new ClassValueType((parser::ClassType *)annotation);
    } else {
        if (annotation != nullptr && annotation->kind == "<None>")
            return new ClassValueType("<None>");
        if (dynamic_cast<parser::ListType *>(annotation))
            return new ListValueType((parser::ListType *)annotation);
    }
    return nullptr;
}

ListValueType::ListValueType(parser::ListType *typeAnnotation)
    : element_type(ValueType::annotate_to_val(typeAnnotation->elementType)) {}

ClassValueType::ClassValueType(parser::ClassType *classTypeAnnotation) : class_name(classTypeAnnotation->className) {}

cJSON *SemanticError::toJSON() {
    cJSON *d = parser::Err::toJSON();
    cJSON_AddStringToObject(d, "message", this->message.c_str());
    cJSON_AddItemToObject(d, "loctaion", cJSON_CreateIntArray(this->get_location(), 4));
    return d;
}
string ValueType::get_name() { return ((ClassValueType *)this)->class_name; }
} // namespace semantic

#ifdef PA2
int main(int argc, char *argv[]) {
    parser::Program *tree = parse(argv[1]);

    auto error = new vector<parser::Err *>();

    auto *declarationAnalyzer = new semantic::DeclarationAnalyzer(error);

    if(DEBUG)cerr<<"----accept start----\n";
    tree->accept(*declarationAnalyzer);  
    if(DEBUG)cerr<<"----accept end----\n";
    semantic::SymbolTable *globalScope = declarationAnalyzer->getGlobals();
    error = declarationAnalyzer->errors;
    if (!error->empty()) {
        tree->add_error(error);
    } else {
        auto *typeChecker = new semantic::TypeChecker(globalScope, error);
        tree->accept(*typeChecker);
        if (!error->empty())/*semantic error in type checker*/
            tree->add_error(error);
    }

    cJSON *a = tree->toJSON();
    char *out = cJSON_Print(a);
    cout << out;
}
#endif
