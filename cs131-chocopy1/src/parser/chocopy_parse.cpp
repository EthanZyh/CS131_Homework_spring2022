//
// Created by yiwei yang on 2/15/21.
//

#include <chocopy_parse.hpp>
#include <cjson/cJSON.h>

namespace parser {
cJSON *add_inferred_type(semantic::SymbolType *class_) {
    auto inferred = cJSON_CreateObject();
    if (dynamic_cast<semantic::FunctionDefType *>(class_)) {
        return ((semantic::FunctionDefType *)class_)->toJSON();
    } else if (!class_->is_list_type()) {
        cJSON_AddItemToObject(inferred, "kind", cJSON_CreateString(class_->get_type().c_str()));
        cJSON_AddItemToObject(inferred, "className", cJSON_CreateString(class_->get_name().c_str()));
    } else {
        cJSON_AddItemToObject(inferred, "kind", cJSON_CreateString(class_->get_type().c_str()));
        cJSON_AddItemToObject(inferred, "elementType",
                              add_inferred_type(((semantic::ListValueType *)class_)->element_type));
    }
    return inferred;
}

Expr::Expr(int *location) : Node(location), inferredType(new semantic::ClassValueType()) {}
Expr::Expr(int *location, string kind)
    : Node(location, std::move(kind)), inferredType(new semantic::ClassValueType()) {}
Expr::Expr(int *location, string kind, string errMsg)
    : Node(location, std::move(kind), std::move(errMsg)), inferredType(new semantic::ClassValueType()) {}

StringLiteral::StringLiteral(int *location, const string &value) : Literal(location, "StringLiteral", value) {
    if (value == "\"\"") { // deal with null string
        this->value = "";
        ((Literal *)this)->value = "";
    } else
        this->value = value;
}

cJSON *Node::toJSON() {
    cJSON *d = cJSON_CreateObject();
    cJSON *loc;

    loc = cJSON_CreateIntArray(this->get_location(), 4);

    /* Create the output json */
#if PA1
    if (this->kind != "PassStmt" && !this->kind.ends_with("AssignStmt"))
        cJSON_AddStringToObject(d, "kind", this->kind.c_str());
    else if (this->kind.ends_with("AssignStmt"))
        cJSON_AddStringToObject(d, "kind", "AssignStmt");
#else
    if (this->kind != "PassStmt")
        cJSON_AddStringToObject(d, "kind", this->kind.c_str());
#endif
#if PA1
    cJSON_AddItemToObject(d, "location", loc);
#else
    if (dynamic_cast<Ident *>(this) || dynamic_cast<TypedVar *>(this) || dynamic_cast<TypeAnnotation *>(this))
        cJSON_AddItemToObject(d, "location", loc);
#endif
    if (((Err *)this)->top_level)
        if (this->has_err())
            cJSON_AddStringToObject(d, "error_msg", this->error_msg.c_str());

    if (this->has_type_err()) {
        auto s = this->typeError;
        std::string delimiter = "\t";

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            cJSON_AddStringToObject(d, "typeError", token.c_str());
            s.erase(0, pos + delimiter.length());
        }
        cJSON_AddStringToObject(d, "typeError", s.c_str());
    }
    return d;
}

cJSON *CompilerErr::toJSON() {
    cJSON *d = Node::toJSON();
    cJSON_AddStringToObject(d, "message", this->message.c_str());
    if (this->syntax)
        cJSON_AddStringToObject(d, "syntax", "true");
    else
        cJSON_AddStringToObject(d, "syntax", "false");
    return d;
}

cJSON *Err::toJSON() {
    cJSON *d = Node::toJSON();
    cJSON *msg_err = cJSON_CreateArray();
    if (this->top_level) {
        if (allow_multi_errors) {
            for (auto &error : *this->errors) {
                cJSON_AddItemToArray(msg_err, error->toJSON());
            }
        } else {
            cJSON_AddItemToArray(msg_err, this->errors->at(0)->toJSON());
        }
        cJSON_AddItemToObject(d, "errors", msg_err);
    }
    if (has_compiler_errors()) {
        if (!allow_multi_errors) {
            for (auto &error : *this->compiler_errors) {
                cJSON_AddItemToArray(msg_err, error->toJSON());
            }
            cJSON_AddItemToObject(d, "errors", msg_err);
        } else {
            if (!cJSON_HasObjectItem(d, "errors")) {
                cJSON_AddItemToArray(msg_err, this->errors->at(0)->toJSON());
                cJSON_AddItemToObject(d, "errors", msg_err);
            }
        }
    }
    return d;
}

cJSON *TypedVar::toJSON() {
    cJSON *d = Node::toJSON();

    /* d["identifier"] = self.identifier.toJSON() */
    cJSON_AddItemToObject(d, "identifier", this->identifier->toJSON());

    /* d["type"] = self.type.toJSON() */
    cJSON_AddItemToObject(d, "type", this->type->toJSON());

    return d;
}

cJSON *Expr::toJSON() {
    cJSON *d = Node::toJSON();
    if (this->emit_inferred()) {
        cJSON_AddItemToObject(d, "inferredType", add_inferred_type(this->inferredType));
    }
    /** The list type senario */
    /*if (!dynamic_cast<semantic::ClassValueType *>(this->inferredType)){
        return d;
    }

    if (!this->inferredType->className.empty()) {
        cJSON_AddStringToObject(d, "className", this->inferredType->className.c_str());
    }*/

    return d;
}
bool Expr::emit_inferred() {
    if (dynamic_cast<semantic::FunctionDefType *>(this->inferredType))
        return true;
    else
        return this->inferredType != nullptr && !this->inferredType->get_name().empty();
}

cJSON *Ident::toJSON() {
    cJSON *d = Expr::toJSON();
    cJSON_AddStringToObject(d, "name", this->name.c_str());
    return d;
}

cJSON *Literal::toJSON() {
    cJSON *d = Expr::toJSON();
    if (!dynamic_cast<NoneLiteral *>(this)) {
        if (dynamic_cast<IntegerLiteral *>(this))
            cJSON_AddItemToObject(d, "value", cJSON_CreateNumber(this->int_value));
        else if (!dynamic_cast<BoolLiteral *>(this))
            cJSON_AddStringToObject(d, "value", this->value.c_str());
    }
    return d;
}

cJSON *AssignStmt::toJSON() {
    cJSON *d = Stmt::toJSON();

    /* d["targets"] = [t.toJSON() for t in self.targets] */
#if PA1
    cJSON *target_stmt = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "targets", target_stmt);
    for (auto &target : *this->targets) {
        cJSON_AddItemToArray(target_stmt, target->toJSON());
    }
#elif PA2
    for (auto &target : *this->targets) {
        cJSON_AddItemToObject(d, "targets", target->toJSON());
    }
#endif

    /* d["value"] = self.value.toJSON() */
    cJSON_AddItemToObject(d, "value", this->value->toJSON());

    return d;
}

cJSON *BinaryExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    /* d["left"] = self.left.toJSON() */
    if (this->left != nullptr)
        cJSON_AddItemToObject(d, "left", this->left->toJSON());

    /* d["operator"] = self.operator */
    cJSON_AddStringToObject(d, "operator", this->operator_.c_str());

    /* d["right"] = self.right.toJSON() */
    if (this->right != nullptr)
        cJSON_AddItemToObject(d, "right", this->right->toJSON());
    return d;
}

cJSON *CallExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    /* d["left"] = self.function.toJSON() */
    cJSON_AddItemToObject(d, "function", this->function->toJSON());

    /* d["args"] = [a.toJSON() for a in self.args] */
    cJSON *call_args = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "args", call_args);
    if (this->has_args)
        for (auto &arg : *this->args) {
            if (arg->kind == "Identifier")
                cJSON_AddItemToArray(call_args, ((Ident *)arg)->toJSON());
            else
                cJSON_AddItemToArray(call_args, arg->toJSON());
        }

    return d;
}

cJSON *ClassDef::toJSON() {
    cJSON *d = Decl::toJSON();
    /* d["name"] = self.name.toJSON() */
    cJSON_AddItemToObject(d, "name", this->name->toJSON());

    /* d["superClass"] = self.superclass.toJSON() */
    cJSON_AddItemToObject(d, "superClass", this->superClass->toJSON());

    /* d["declarations"] = [decl.toJSON() for decl in self.declarations] */
    cJSON *decls = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "declarations", decls);
    for (auto &i : *this->declaration) {
        cJSON_AddItemToArray(decls, i->toJSON());
    }

    return d;
}

cJSON *ClassType::toJSON() {
    cJSON *d = TypeAnnotation::toJSON();

    /* d["className"] = self.className */
    cJSON_AddStringToObject(d, "className", this->className.c_str());

    return d;
}

cJSON *ExprStmt::toJSON() {
    cJSON *d = Stmt::toJSON();

    /** check whether there's a parsing error */
    if (!info.empty()) {
        return d;
    }

    /* d["expr"] = self.expr.toJSON() */
    if (!this->expr->kind.empty()) {
        if (this->expr->kind == "CallExpr") {
            cJSON_AddItemToObject(d, "expr", ((CallExpr *)(this->expr))->toJSON());
        } else if (this->expr->kind == "MethodCallExpr") {
            cJSON_AddItemToObject(d, "expr", ((MethodCallExpr *)(this->expr))->toJSON());
        } else if (this->expr->kind == "Identifier") {
            cJSON_AddItemToObject(d, "expr", ((Ident *)(this->expr))->toJSON());
        } else if (this->expr->kind == "BinaryExpr") {
            cJSON_AddItemToObject(d, "expr", ((BinaryExpr *)(this->expr))->toJSON());
        } else {
            cJSON_AddItemToObject(d, "expr", this->expr->toJSON());
        }
    }
    return d;
}

cJSON *ForStmt::toJSON() {
    cJSON *d = Stmt::toJSON();

    if (accOptions != nullptr)
        cJSON_AddItemToObject(d, "acc_options", this->accOptions->toJSON());

    /* d["identifier"] = self.identifier.toJSON() */
    cJSON_AddItemToObject(d, "identifier", this->identifier->toJSON());

    /* d["iterable"] = self.iterable.toJSON() */
    cJSON_AddItemToObject(d, "iterable", this->iterable->toJSON());

    /* d["body"] = [s.toJSON() for s in self.body_] */
    auto *body_ = cJSON_CreateArray();
    for (auto &i : *this->body)
        cJSON_AddItemToArray(body_, i->toJSON());

    cJSON_AddItemToObject(d, "body", body_);

    return d;
}

cJSON *FuncDef::toJSON() {
    cJSON *d = Decl::toJSON();

    if (this->decorator != nullptr)
        cJSON_AddItemToObject(d, "decorator", this->decorator->toJSON());

    /* d["name"] = self.name.toJSON() */
    cJSON_AddItemToObject(d, "name", this->name->toJSON());

    /* d["params"] = [t.toJSON() for t in self.params] */
    cJSON *param_ = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "params", param_);
    for (auto &param : *this->params) {
        cJSON_AddItemToArray(param_, param->toJSON());
    }

    /* d["returnType"] = self.returnType.toJSON() */
    if (this->returnType != nullptr)
        cJSON_AddItemToObject(d, "returnType", this->returnType->toJSON());
    else {
        auto none_return = cJSON_CreateObject();
        cJSON_AddItemToObject(none_return, "kind", cJSON_CreateString("ClassType"));
        int *i = new int[4]{0};
        i[0] = this->location[2];
        i[2] = this->location[2];
        i[1] = this->location[3];
        i[3] = this->location[3];
        cJSON_AddItemToObject(none_return, "location", cJSON_CreateIntArray(i, 4));
        cJSON_AddItemToObject(none_return, "className", cJSON_CreateString("<None>"));

        cJSON_AddItemToObject(d, "returnType", none_return);
    }
    /* d["declarations"] = [t.toJSON() for t in self.declarations] */
    cJSON *decl_ = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "declarations", decl_);
    for (auto &declaration : *this->declarations) {
        cJSON_AddItemToArray(decl_, declaration->toJSON());
    }

    /* d["statements"] = [t.toJSON() for t in self.statements] */
    cJSON *stmt_ = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "statements", stmt_);
    if (!this->statements->empty())
        for (auto &statement : *this->statements) {
            if (statement->kind == "ExprStmt")
                cJSON_AddItemToArray(stmt_, ((ExprStmt *)statement)->toJSON());
            else if (statement->kind == "IndexAssignStmt")
                cJSON_AddItemToArray(stmt_, ((IndexAssignStmt *)statement)->toJSON());
            else if (statement->kind == "MemberAssignStmt")
                cJSON_AddItemToArray(stmt_, ((MemberAssignStmt *)statement)->toJSON());
            else if (statement->kind == "VarAssignStmt")
                cJSON_AddItemToArray(stmt_, ((VarAssignStmt *)statement)->toJSON());
            else if (statement->kind == "WhileStmt")
                cJSON_AddItemToArray(stmt_, ((WhileStmt *)statement)->toJSON());
            else if (statement->kind == "ReturnStmt")
                cJSON_AddItemToArray(stmt_, ((ReturnStmt *)statement)->toJSON());
            else if (statement->kind == "IfStmt")
                cJSON_AddItemToArray(stmt_, ((IfStmt *)statement)->toJSON());
            else if (statement->kind == "ForStmt")
                cJSON_AddItemToArray(stmt_, ((ForStmt *)statement)->toJSON());
            else if (statement->kind == "AssignStmt")
                cJSON_AddItemToArray(stmt_, ((AssignStmt *)statement)->toJSON());
            else if (statement->kind == "PassStmt")
                continue;
            else
                cJSON_AddItemToArray(stmt_, statement->toJSON());
        }

    return d;
}

cJSON *GlobalDecl::toJSON() {
    cJSON *d = Decl::toJSON();
    cJSON_AddItemToObject(d, "variable", this->variable->toJSON());

    return d;
}

cJSON *IfStmt::toJSON() {
    cJSON *d = Stmt::toJSON();

    /* d["condition"] = self.condition.toJSON() */
    if (this->condition->kind == "Identifier")
        cJSON_AddItemToObject(d, "condition", ((Ident *)(this->condition))->toJSON());
    else
        cJSON_AddItemToObject(d, "condition", this->condition->toJSON());
    cJSON *then_body = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "thenBody", then_body);
     for (auto &i : *this->thenBody) {
        if (i->kind == "ExprStmt")
            cJSON_AddItemToArray(then_body, ((ExprStmt *)i)->toJSON());
        else if (i->kind == "IndexAssignStmt")
            cJSON_AddItemToArray(then_body, ((IndexAssignStmt *)i)->toJSON());
        else if (i->kind == "MemberAssignStmt")
            cJSON_AddItemToArray(then_body, ((MemberAssignStmt *)i)->toJSON());
        else if (i->kind == "VarAssignStmt")
            cJSON_AddItemToArray(then_body, ((VarAssignStmt *)i)->toJSON());
        else if (i->kind == "WhileStmt")
            cJSON_AddItemToArray(then_body, ((WhileStmt *)i)->toJSON());
        else if (i->kind == "ReturnStmt")
            cJSON_AddItemToArray(then_body, ((ReturnStmt *)i)->toJSON());
        else if (i->kind == "IfStmt")
            cJSON_AddItemToArray(then_body, ((IfStmt *)i)->toJSON());
        else if (i->kind == "ForStmt")
            cJSON_AddItemToArray(then_body, ((ForStmt *)i)->toJSON());
        else if (i->kind == "AssignStmt")
            cJSON_AddItemToArray(then_body, ((AssignStmt *)i)->toJSON());
        else
            cJSON_AddItemToArray(then_body, i->toJSON());
    }

    /* d["elseBody"] = [s.toJSON() for s in self.elseBody] */
    if (this->el == cond::THEN_ELSE) {
        cJSON *else_body = cJSON_CreateArray();
        cJSON_AddItemToObject(d, "elseBody", else_body);
        for (auto &i : *this->elseBody) {
            if (i->kind == "ExprStmt")
                cJSON_AddItemToArray(else_body, ((ExprStmt *)i)->toJSON());
            else if (i->kind == "IndexAssignStmt")
                cJSON_AddItemToArray(else_body, ((IndexAssignStmt *)i)->toJSON());
            else if (i->kind == "MemberAssignStmt")
                cJSON_AddItemToArray(else_body, ((MemberAssignStmt *)i)->toJSON());
            else if (i->kind == "VarAssignStmt")
                cJSON_AddItemToArray(else_body, ((VarAssignStmt *)i)->toJSON());
            else if (i->kind == "WhileStmt")
                cJSON_AddItemToArray(else_body, ((WhileStmt *)i)->toJSON());
            else if (i->kind == "ReturnStmt")
                cJSON_AddItemToArray(else_body, ((ReturnStmt *)i)->toJSON());
            else if (i->kind == "IfStmt")
                cJSON_AddItemToArray(else_body, ((IfStmt *)i)->toJSON());
            else if (i->kind == "ForStmt")
                cJSON_AddItemToArray(else_body, ((ForStmt *)i)->toJSON());
            else if (i->kind == "AssignStmt")
                cJSON_AddItemToArray(else_body, ((AssignStmt *)i)->toJSON());
            else
                cJSON_AddItemToArray(else_body, i->toJSON());
        }
    } else if (this->el == cond::THEN_ELIF) {
        cJSON *else_body = cJSON_CreateArray();
        cJSON_AddItemToObject(d, "elseBody", else_body);
        cJSON_AddItemToArray(else_body, this->elifBody->toJSON());
    }

    return d;
}

cJSON *IfExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    /* d["condition"] = self.condition.toJSON() */
    cJSON_AddItemToObject(d, "condition", this->condition->toJSON());

    /* d["thenExpr"] = self.thenExpr.toJSON() */
    cJSON_AddItemToObject(d, "thenExpr", this->thenExpr->toJSON());

    /* d["thenExpr"] = self.thenExpr.toJSON() */
    cJSON_AddItemToObject(d, "elseExpr", this->elseExpr->toJSON());

    return d;
}

cJSON *IndexExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    /* d["list"] = self.list.toJSON() */
    cJSON_AddItemToObject(d, "list", ((ListExpr *)(this->list))->toJSON());

    /* d["index"] = self.index.toJSON() */
    cJSON_AddItemToObject(d, "index", this->index->toJSON());

    return d;
}

cJSON *ListExpr::toJSON() {
    cJSON *d;
    d = Expr::toJSON();
    /* d["elements"] = [e.toJSON() for e in self.elements] */
    cJSON *elem_ = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "elements", elem_);
    if (this->has_expr)
        for (auto &element : *this->elements) {
            cJSON_AddItemToArray(elem_, element->toJSON());
        }
    return d;
}

cJSON *ListType::toJSON() {
    cJSON *d = TypeAnnotation::toJSON();

    /* d["elementType"] = self.elementType.toJSON() */
    cJSON_AddItemToObject(d, "elementType", this->elementType->toJSON());

    return d;
}

cJSON *MemberExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    /* d["object"] = self.object.toJSON()*/
    cJSON_AddItemToObject(d, "object", this->object->toJSON());
    /* d["member"] = self.member.toJSON()*/
    cJSON_AddItemToObject(d, "member", this->member->toJSON());

    return d;
}

cJSON *MethodCallExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    /* d["method"] = self.method.toJSON() */
    cJSON_AddItemToObject(d, "method", this->method->toJSON());

    /* d["args"] = [a.toJSON() for a in self.args] */
    cJSON *args_ = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "args", args_);
    if (has_args)
        for (auto &arg : *this->args)
            cJSON_AddItemToArray(args_, arg->toJSON());

    return d;
}

cJSON *NonlocalDecl::toJSON() {
    cJSON *d = Decl::toJSON();

    /* d["variable"] = self.variable.toJSON() */
    cJSON_AddItemToObject(d, "variable", this->variable->toJSON());

    return d;
}

cJSON *Program::toJSON() {
    cJSON *d;
    d = Node::toJSON();
    /* d['declarations'] = [d.toJSON() for d in self.declarations] */
    cJSON *decls = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "declarations", decls);
    if (!this->declarations->empty())
        for (auto &declaration : *this->declarations) {
            if (declaration->kind == "VarDef")
                cJSON_AddItemToArray(decls, ((VarDef *)declaration)->toJSON());
            else if (declaration->kind == "ClassDef")
                cJSON_AddItemToArray(decls, ((ClassDef *)declaration)->toJSON());
            else if (declaration->kind == "FuncDef")
                cJSON_AddItemToArray(decls, ((FuncDef *)declaration)->toJSON());
            else if (declaration->kind == "GlobalDecl")
                cJSON_AddItemToArray(decls, ((GlobalDecl *)declaration)->toJSON());
            else if (declaration->kind == "NonLocalDecl")
                cJSON_AddItemToArray(decls, ((NonlocalDecl *)declaration)->toJSON());
            else
                cJSON_AddItemToArray(decls, declaration->toJSON());
        }

    /* d['statements'] = [s.toJSON() for s in self.statements] */
    cJSON *stmt_ = cJSON_CreateArray();
    if (!this->statements->empty())
        for (auto &statement : *this->statements) {
            if (statement->kind == "ExprStmt")
                cJSON_AddItemToArray(stmt_, ((ExprStmt *)statement)->toJSON());
            else if (statement->kind == "ForStmt")
                cJSON_AddItemToArray(stmt_, ((ForStmt *)statement)->toJSON());
            else if (statement->kind == "IfStmt")
                cJSON_AddItemToArray(stmt_, ((IfStmt *)statement)->toJSON());
            else if (statement->kind == "IndexAssignStmt")
                cJSON_AddItemToArray(stmt_, ((IndexAssignStmt *)statement)->toJSON());
            else if (statement->kind == "MemberAssignStmt")
                cJSON_AddItemToArray(stmt_, ((MemberAssignStmt *)statement)->toJSON());
            else if (statement->kind == "VarAssignStmt")
                cJSON_AddItemToArray(stmt_, ((VarAssignStmt *)statement)->toJSON());
            else if (statement->kind == "WhileStmt")
                cJSON_AddItemToArray(stmt_, ((WhileStmt *)statement)->toJSON());
            else if (statement->kind == "ReturnStmt")
                cJSON_AddItemToArray(stmt_, ((ReturnStmt *)statement)->toJSON());
            else if (statement->kind == "AssignStmt")
                cJSON_AddItemToArray(stmt_, ((AssignStmt *)statement)->toJSON());
            else
                cJSON_AddItemToArray(stmt_, statement->toJSON());
        }
    cJSON_AddItemToObject(d, "statements", stmt_);

    if (this->has_compiler_errors) {
        for (auto tmp_compiler : *this->errors->compiler_errors) {
            cJSON *msg_err = tmp_compiler->toJSON();
            auto tmp = cJSON_CreateArray();
            cJSON_AddItemToArray(tmp, msg_err);
            cJSON_AddItemToObject(d, "errors", tmp);
        }
    } else if (this->has_semantic_errors) {
        cJSON *err = cJSON_CreateObject();
        cJSON_AddItemToObject(d, "errors", err);
        cJSON *errors1 = cJSON_CreateArray();
        cJSON_AddItemToObject(err, "errors", errors1);
        cJSON_AddItemToArray(errors1, this->errors->toJSON());
        cJSON_AddStringToObject(err, "kind", "Errors");
        int *i = new int[4]{0};
        cJSON_AddItemToObject(err, "locations", cJSON_CreateIntArray(i, 4));
    } else {
        cJSON *err = cJSON_CreateObject();
        cJSON_AddItemToObject(d, "errors", err);
        cJSON *errors1 = cJSON_CreateArray();
        cJSON_AddItemToObject(err, "errors", errors1);
        cJSON_AddStringToObject(err, "kind", "Errors");
        int *i = new int[4]{0};
        cJSON_AddItemToObject(err, "location", cJSON_CreateIntArray(i, 4));
    }

    return d;
}

cJSON *ReturnStmt::toJSON() {
    cJSON *d = Stmt::toJSON();

    /* d["value"] = self.value.toJSON() */
    if (this->value != nullptr) {
        cJSON_AddItemToObject(d, "value", this->value->toJSON());
    }

    return d;
}

cJSON *UnaryExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    /* d["operator"] = self.operator */
    cJSON_AddStringToObject(d, "operator", this->operator_.c_str());

    /* d["operand"] = self.operand.toJSON() */
    cJSON_AddItemToObject(d, "operand", this->operand->toJSON());

    return d;
}

cJSON *VarDef::toJSON() {
    cJSON *d = Decl::toJSON();

    /* d["var"] = self.var.toJSON() */
    cJSON_AddItemToObject(d, "var", this->var->toJSON());

    /* d["value"] = self.value.toJSON() */
    cJSON_AddItemToObject(d, "value", this->value->toJSON());

    return d;
}

cJSON *WhileStmt::toJSON() {
    cJSON *d = Stmt::toJSON();

    /* d["condition"] = self.condition.toJSON() */
    cJSON_AddItemToObject(d, "condition", this->condition->toJSON());

    /* d["body"] = [s.toJSON() for s in self.body] */
    auto while_stmt = cJSON_CreateArray();
    for (auto &&i : *this->body)
        if (i->kind != "PassStmt")
            cJSON_AddItemToArray(while_stmt, i->toJSON());

    cJSON_AddItemToObject(d, "body", while_stmt);
    return d;
}

cJSON *VarAssignStmt::toJSON() {
    cJSON *d = Stmt::toJSON();
#if PA1
    cJSON *target_stmt = cJSON_CreateArray();
    cJSON_AddItemToObject(d, "targets", target_stmt);

    cJSON_AddItemToObject(target_stmt, "var", this->var->toJSON());
#else
    cJSON_AddItemToObject(d, "var", this->var->toJSON());
#endif
    /** check whether there's a parsing error */
    if (!info.empty()) {
        return d;
    }
    /** If the object is chained value, we have to deal with it*/
    auto next_kind = this->value;

    while (next_kind->kind == "VarAssignExpr") {
#if PA1
        cJSON_AddItemToArray(target_stmt, ((VarAssignExpr *)next_kind)->var->toJSON());
#elif PA2
        cJSON_AddItemToArray(d, ((VarAssignExpr *)next_kind)->var->toJSON());
#endif
        next_kind = ((VarAssignExpr *)next_kind)->value;
        LOG(DEBUG) << next_kind->kind;
    }

    /* d["value"] = self.value.toJSON() */
    if (!this->value->kind.empty())
        cJSON_AddItemToObject(d, "value", this->value->toJSON());
    return d;
}

cJSON *MemberAssignStmt::toJSON() {
    cJSON *d = Stmt::toJSON();

    cJSON_AddItemToObject(d, "var", this->objectMember->toJSON());

    /* d["value"] = self.value.toJSON() */
    cJSON_AddItemToObject(d, "value", this->value->toJSON());
    return d;
}

cJSON *IndexAssignStmt::toJSON() {
    cJSON *d = Stmt::toJSON();

    cJSON_AddItemToObject(d, "var", this->listElement->toJSON());

    /* d["value"] = self.value.toJSON() */
    cJSON_AddItemToObject(d, "value", this->value->toJSON());
    return d;
}

cJSON *IndexAssignExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    cJSON_AddItemToObject(d, "var", this->listElement->toJSON());

    /* d["value"] = self.value.toJSON() */
    cJSON_AddItemToObject(d, "value", this->value->toJSON());
    return d;
}

cJSON *MemberAssignExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    cJSON_AddItemToObject(d, "var", this->objectMember->toJSON());

    /* d["value"] = self.value.toJSON() */
    cJSON_AddItemToObject(d, "value", this->value->toJSON());
    return d;
}

cJSON *VarAssignExpr::toJSON() {
    cJSON *d = Expr::toJSON();

    cJSON_AddItemToObject(d, "var", this->var->toJSON());

    /* d["value"] = self.value.toJSON() */
    cJSON_AddItemToObject(d, "value", this->value->toJSON());

    return d;
}

cJSON *IntegerLiteral::toJSON() {
    cJSON *d = Literal::toJSON();
    return d;
}

cJSON *BoolLiteral::toJSON() {
    cJSON *d = Literal::toJSON();
    cJSON_AddItemToObject(d, "value", cJSON_CreateBool(this->bin_value));
    return d;
}
cJSON *NoneLiteral::toJSON() {
    cJSON *d = Literal::toJSON();
    return d;
}

cJSON *AccOptions::toJSON() {
    cJSON *d = Node::toJSON();
    if (accType == AccType::VECTOR)
        cJSON_AddItemToObject(d, "Type", cJSON_CreateString("Vector"));
    else
        cJSON_AddItemToObject(d, "Type", cJSON_CreateString("Worker"));

    cJSON_AddItemToObject(d, "Number", cJSON_CreateNumber(this->num));
    return d;
}

string TypeAnnotation::get_name() {
    if (dynamic_cast<semantic::ClassValueType *>(semantic::ValueType::annotate_to_val(this)))
        return ((semantic::ClassValueType *)(semantic::ValueType::annotate_to_val(this)))->class_name;
    else if (dynamic_cast<semantic::ListValueType *>(semantic::ValueType::annotate_to_val(this)))
        return ((semantic::ListValueType *)semantic::ValueType::annotate_to_val(this))->get_name();
    return "";
}
} // namespace parser

#ifdef PA1
int main(int argc, char *argv[]) {
    // puts("------main start-------");
    parser::Program *tree = parse(argv[1]);

    cJSON *a = tree->toJSON();
    // puts("-------toJSON end--------");
    char *out = cJSON_Print(a);
    cout << fmt::format("{}\n", out);
    // puts("------main end-------");
}
#endif
