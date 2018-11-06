#include "AST_node.h"
#include "C_syntax.hpp"

#define INDENTION_LENGHT 2

extern int yyparse();
extern BlockExprNode *root;

// bool error = false;

string modify_funcname(string name) {
    if (name == "strlen") {
        return "length";
    } else if (name == "isdigit") {
        return "isDigit";
    }
    return name;
}

GenBlockP::GenBlockP() {
    isFunction = false;
}

GenContextP::GenContextP() {
    funcDeclaring = false;
    indent_num = 0;
    blocks.push(new GenBlockP());
}

GenContextP::~GenContextP() {

}

void GenContextP::CodeGen(BlockExprNode &root) {
    code << "# -*- coding:utf-8" << endl;
    code << "Nil on: '=' do: {:o ^o isNil.}, on: '!=:' do: {:o ^o isNil not.}.\n";
    code << "var printf is {:format:*args\n    format is format join: ''.\n    args count > 0 ifTrue: {\n        var new_args is Array new.\n        args each: {:i:arg\n            new_args push: (arg isA: Array, either: {^arg join: ''.} or: {^arg toString.}).\n        }.\n    Pen write: format % new_args.}, ifFalse: {\n    Pen write: format.\n    }.\n}.\n";
    code << "var atoi is {:s var str is ''. s each: {:i:c (c = 0) break. str +=: c.}. ^str toNumber.}.\n";
    code << "Array learn: 'length' means: 'count'.\n";
    code << "var length is {:arr ^arr length.}.\n";
    code << "var isDigit is {:str ^{str at: 0, toNumber. ^True.} catch: {^False.}, run.}.\n";
    root.CodeGenP(*this);
    code << "main[].";
}

void GenContextP::OutputCode(ostream& out) {
    string c = code.str();
    out << c;
}

void GenContextP::clearBuf() {
    code_buf.str("");
}

void GenContextP::applyBuf() {
    string s = code_buf.str();
    code << s;
    clearBuf();
}

set<string>& GenContextP::locals() {
    return blocks.top()->locals;
}

set<string>& GenContextP::declared_globals() {
    return blocks.top()->declared_globals;
}

set<string>& GenContextP::globals() {
    return globalVariables;
}

GenBlockP* GenContextP::currentBlock() {
    return blocks.top();
}

void GenContextP::PushBlock(bool copy_locals, bool isFunction) {
    GenBlockP *block = new GenBlockP();
    if (copy_locals) {
        block->locals = blocks.top()->locals;
    }
    if (!isFunction) {
        block->declared_globals = blocks.top()->declared_globals;
    }
    block->isFunction = isFunction;
    blocks.push(block);
    indent_num = indent_num + INDENTION_LENGHT;
}

void GenContextP::popBlock() {
    GenBlockP *top = blocks.top();
    blocks.pop();
    indent_num = indent_num - INDENTION_LENGHT;
    delete top;
}

void GenContextP::indent(bool use_buf) {
    for (int i = 0; i < indent_num; ++i) {
        if (use_buf) {
            code_buf << ' ';
        } else {
            code << ' ';
        }
    }
}

void GenContextP::declare_global(string name) {
    code << name;
}

void GenContextP::nextLine(bool use_buf, bool end) {
    if (use_buf) {
        if (end) code_buf << ".";
        code_buf << "\n";
    } else {
        if (end) code << ".";
        code << "\n";
    }
}

void SpawnExprNode::CodeGenP(GenContextP& context) {
    target->CodeGenP(context);
    context.code_buf << " is ";
    auto* exp = new FuncExprNode(functor, args);
    exp->CodeGenP(context);
    delete exp;
}

void SyncStatementNode::CodeGenP(GenContextP& context) {
    // no-op
    context.code_buf << "Nil";
}

void VariableExprNode::CodeGenP(GenContextP &context) {
    if (context.funcDeclaring) {
        if (context.globals().count(name) == 1) {
            fprintf(stderr, "duplicate symbol %s\n", name.c_str());
        } else {
            context.locals().insert(name);
            context.code << name;
        }
    } else {
        if (context.locals().count(name) == 1) {
            context.code_buf << name;
        } else if (context.globals().count(name) == 1) {
            if (context.declared_globals().count(name) == 1) {
                context.code_buf << name;
            } else {
                context.declared_globals().insert(name);
                context.code_buf << name;
            }
        } else {
            fprintf(stderr, "undeclared symbol %s\n", name.c_str());
        }
    }
}

void CharExprNode::CodeGenP(GenContextP &context) {
    if (val == '\'' || val == '\\') {
        context.code_buf << "\'\\" << val << "\'";
    } else {
        context.code_buf << "\'" << val << "\'";
    }
}

void IntExprNode::CodeGenP(GenContextP &context) {
    context.code_buf << val;
}

void DoubleExprNode::CodeGenP(GenContextP &context) {
    context.code_buf << val;
}

void BlockExprNode::CodeGenP(GenContextP &context) {
    for(auto it = statements->begin(); it != statements->end(); it++) {
        context.indent();
        (*it)->CodeGenP(context);
        context.nextLine(true, true);
    }
    if (context.currentBlock()->isFunction) {
        for (set<string>::iterator it = context.declared_globals().begin(); it != context.declared_globals().end(); it++) {
            context.indent(false);
            context.declare_global(*it);
            context.nextLine(false, true);
        }
        context.applyBuf();
    }
}

void OperatorExprNode::CodeGenP(GenContextP &context) {
    string opStr = "";
    switch (op) {
    case EQ:
        opStr = "=";
        break;
    case NE:
        opStr = "!=:";
        break;
    case GR:
        opStr = ">";
        break;
    case LW:
        opStr = "<";
        break;
    case GE:
        opStr = ">=:";
        break;
    case LE:
        opStr = "<=:";
        break;
    case AND:
        opStr = "&";
        break;
    case OR:
        opStr = "|";
        break;
    case ADD:
    case SADD:
        opStr = "+";
        break;
    case SUB:
    case SSUB:
        opStr = "-";
        break;
    case MUL:
    case SMUL:
        opStr = "*";
        break;
    case DIV:
    case SDIV:
        opStr = "/";
        break;
    }
    context.code_buf << "(";
    left->CodeGenP(context);
    context.code_buf << " " << opStr << " ";
    right->CodeGenP(context);
    context.code_buf << ")";
}

void AssignExprNode::CodeGenP(GenContextP &context) {
    left->CodeGenP(context);
    context.code_buf << " is ";
    right->CodeGenP(context);
}

void FuncExprNode::CodeGenP(GenContextP &context) {
    context.code_buf << modify_funcname(functor->name);
    context.code_buf << "[";
    vector<ExprNode*>::iterator it = args->begin();
    if (it != args->end()) {
        (*it)->CodeGenP(context);
        for (it++; it != args->end(); it++) {
            context.code_buf << ", ";
            (*it)->CodeGenP(context);
        }
    }
    context.code_buf << "]";
}

void CastExprNode::CodeGenP(GenContextP &context) {
    // do no extra moves
    expr->CodeGenP(context);
}

void IndexExprNode::CodeGenP(GenContextP &context) {
    context.code_buf << "(";
    name->CodeGenP(context);
    if (assign != NULL) {
        context.code_buf << " put: (";
        assign->CodeGenP(context);
        context.code_buf << ")";
    }
    context.code_buf << " at: ";
    expr->CodeGenP(context);
    context.code_buf << ")";
}

void ExprStatementNode::CodeGenP(GenContextP &context) {
    expr->CodeGenP(context);
}

void VarDecStatementNode::CodeGenP(GenContextP &context) {
    printf ("Declaration of %s\n", name->name.c_str());
    if (context.locals().count(name->name) == 1) {
        fprintf(stderr, "redefinition %s\n", name->name.c_str());
    } else {
        context.locals().insert(name->name);
    }
    if (!context.funcDeclaring)
        context.code_buf << "var ";
    name->CodeGenP(context);
    if (!context.funcDeclaring) {
        context.code_buf << " is ";
        if (expr != NULL) {
            expr->CodeGenP(context);
        } else {
            context.code_buf << "Nil";
        }
    }
}

void ArrayDecStatementNode::CodeGenP(GenContextP &context) {
    printf("Declaration of array %s\n", name->name.c_str());
    if (context.locals().count(name->name) == 1) {
        fprintf(stderr, "redefinition %s\n", name->name.c_str());
    } else {
        context.locals().insert(name->name);
    }
    context.code_buf << "var ";
    name->CodeGenP(context);
    if (init->size() == 0) {
        context.code_buf << " is [Nil] * " << size;
    } else {
        context.code_buf << " is [";
        vector<ExprNode*>::iterator it = init->begin();
        if (it != init->end()) {
            (*it)->CodeGenP(context);
            for (it = it + 1; it != init->end(); it++) {
                if (isString && (it+1) == init->end()) {
                    break;
                }
                context.code_buf << ", ";
                (*it)->CodeGenP(context);
            }
        }
        context.code_buf << "]";
    }
}

void ReturnStatementNode::CodeGenP(GenContextP &context) {
    context.code_buf << "^ ";
    expr->CodeGenP(context);
}

void FuncDecStatementNode::CodeGenP(GenContextP &context) {
    context.funcDeclaring = true;
    context.PushBlock(false, true);
    context.clearBuf();
    context.code << "var ";
    name->CodeGenP(context);
    context.code << " is {";
    vector<VarDecStatementNode*>::iterator it = args->begin();
    if (it != args->end()) {
        for (; it != args->end(); it++) {
            context.code << ':';
            (*it)->CodeGenP(context);
        }
    }
    context.funcDeclaring = false;
    context.nextLine(false, false);
    block->CodeGenP(context);
    context.indent(false);
    context.code << "}.\n";
    context.popBlock();
}

void ExternFuncDecStatementNode::CodeGenP(GenContextP &context) {
    // don't generate code
}

void IfStatementNode::CodeGenP(GenContextP &context) {
    context.code_buf << "(";
    condExpr->CodeGenP(context);
    context.code_buf << ") ifTrue: {";
    context.nextLine();
    context.PushBlock(true, false);
    trueBlock->CodeGenP(context);
    context.popBlock();
    context.indent();
    context.code_buf << "}";
    if (falseBlock->statements->size() == 0) {
        return;
    }
    context.code_buf << ", ifFalse: {";
    context.nextLine();
    context.PushBlock(true, false);
    falseBlock->CodeGenP(context);
    context.popBlock();
    context.indent();
    context.code_buf << "}";
}

void ForStatementNode::CodeGenP(GenContextP &context) {
    initExpr->CodeGenP(context);
    context.nextLine(true, true);
    context.indent();
    context.code_buf << "{^";
    condExpr->CodeGenP(context);
    context.code_buf << ".} whileTrue: {";
    context.nextLine();
    context.PushBlock(true, false);
    block->statements->push_back(new ExprStatementNode(loopExpr));
    block->CodeGenP(context);
    context.popBlock();
    context.indent();
    context.code_buf << "}";
}

void WhileStatementNode::CodeGenP(GenContextP &context) {
    context.code_buf << "{^";
    whileExpr->CodeGenP(context);
    context.code_buf << ".} whileTrue: {";
    context.nextLine();
    context.PushBlock(true, false);
    block->CodeGenP(context);
    context.popBlock();
    context.indent();
    context.code_buf << "}";
}
