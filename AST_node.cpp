#include "AST_node.h"
#include "C_syntax.hpp"

extern int yyparse();
extern BlockExprNode* root;
bool error = false;

static Value* cast(Value* value, Type* type, GenContext& context);

Function* printfFunction(GenContext& context) {
    vector<Type*> printfArgs;
    printfArgs.push_back(Type::getInt8PtrTy(_ctx));
    FunctionType* printfType = FunctionType::get(Type::getInt32Ty(_ctx), printfArgs, true);
    Function *printfFunc = Function::Create(printfType, Function::ExternalLinkage, Twine("printf"), context.module);
    printfFunc->setCallingConv(CallingConv::C);
    return printfFunc;
}

Function* strlenFunction(GenContext& context) {
    vector<Type*> strlenArgs;
    strlenArgs.push_back(Type::getInt8PtrTy(_ctx));
    FunctionType* strlenType = FunctionType::get(Type::getInt64Ty(_ctx), strlenArgs, false);
    Function *strlenFunc = Function::Create(strlenType, Function::ExternalLinkage, Twine("strlen"), context.module);
    strlenFunc->setCallingConv(CallingConv::C);
    return strlenFunc;
}

Function* isdigitFunction(GenContext& context) {
    vector<Type*> isdigitArgs;
    isdigitArgs.push_back(Type::getInt8Ty(_ctx));
    FunctionType* isdigitType = FunctionType::get(Type::getInt1Ty(_ctx), isdigitArgs, false);
    Function *isdigitFunc = Function::Create(isdigitType, Function::ExternalLinkage, Twine("isdigit"), context.module);
    isdigitFunc->setCallingConv(CallingConv::C);
    return isdigitFunc;
}

Function* atoiFunction(GenContext& context) {
    vector<Type*> atoiArgs;
    atoiArgs.push_back(Type::getInt8PtrTy(_ctx));
    FunctionType* atoiType =FunctionType::get(Type::getInt64Ty(_ctx), atoiArgs, false);
    Function *atoiFunc = Function::Create(atoiType, Function::ExternalLinkage, Twine("atoi"), context.module);
    atoiFunc->setCallingConv(CallingConv::C);
    return atoiFunc;
}

Function* spawnRTSFunction(GenContext& context) {
    vector<Type*> srtsArgs {
        Type::getInt64PtrTy(_ctx),
        Type::getInt8PtrTy(_ctx),
        Type::getInt8PtrTy(_ctx),
        Type::getInt8PtrTy(_ctx)
    };
    FunctionType* pthread_create_ty = FunctionType::get(Type::getInt32Ty(_ctx), srtsArgs, false);
    Function *pthread_create_func = Function::Create(pthread_create_ty, Function::ExternalLinkage, Twine(RTS_SPAWN), context.module);
    pthread_create_func->setCallingConv(CallingConv::C);
    return pthread_create_func;
}

void genericRTSFunctions(GenContext& context) {
#if WITH_LWT
    vector<Type*> srtsArgs {
        Type::getInt64PtrTy(_ctx),
        Type::getInt64Ty(_ctx),
        Type::getInt64Ty(_ctx),
        Type::getInt64Ty(_ctx),
        Type::getInt64Ty(_ctx)
    };
    FunctionType* begin_ty = FunctionType::get(Type::getVoidTy(_ctx), srtsArgs, false);
    Function *begin = Function::Create(begin_ty, Function::ExternalLinkage, Twine("cilk_begin_thread_system"), context.module);
    begin->setCallingConv(CallingConv::C);
#endif
}

Function* mallocFunction(GenContext& context) {
    vector<Type*> srtsArgs {
        Type::getInt64Ty(_ctx)
    };
    FunctionType* malloc_ty = FunctionType::get(Type::getInt64PtrTy(_ctx), srtsArgs, false);
    Function *malloc_func = Function::Create(malloc_ty, Function::ExternalLinkage, Twine("malloc"), context.module);
    malloc_func->setCallingConv(CallingConv::C);
    return malloc_func;
}

Function* joinRTSFunction(GenContext& context) {
    vector<Type*> joinArgs {
        Type::getInt64Ty(_ctx),
        Type::getInt64PtrTy(_ctx)
    };
    FunctionType* pthread_join_ty = FunctionType::get(Type::getInt32Ty(_ctx), joinArgs, false);
    Function *pthread_join_func = Function::Create(pthread_join_ty, Function::ExternalLinkage, Twine(RTS_JOIN), context.module);
    pthread_join_func->setCallingConv(CallingConv::C);
    return pthread_join_func;
}

void linkExternalFunctions(GenContext& context) {
    printfFunction(context);
    strlenFunction(context);
    isdigitFunction(context);
    atoiFunction(context);
    spawnRTSFunction(context);
    mallocFunction(context);
    joinRTSFunction(context);
    genericRTSFunctions(context);
}

static BasicBlock* entrybb = nullptr;
void GenContext::CodeGen(BlockExprNode& root) {
    vector<Type*> arg_types;
    FunctionType *ftype = FunctionType::get(Type::getVoidTy(_ctx), makeArrayRef(arg_types), false);
    // SmallVector<AttributeSet, 4> attrs;
    // AttrBuilder builder;
    // builder.addAttribute(Attribute::NoUnwind);
    // attrs.push_back(AttributeSet::get(_ctx, ~0U, builder));
    // AttributeSet funcFunc = AttributeSet::get(_ctx, attrs);
    Function* entry = Function::Create(ftype, GlobalValue::ExternalLinkage, "__entry", module);
    currentFunction(entry);
    entrybb = BasicBlock::Create(_ctx, "begin", entry, 0);
    push(entrybb, false, true);
    root.CodeGen(*this);
    CallInst::Create(
#if WITH_LWT
      module->getFunction("cilk_begin_thread_system"),
      makeArrayRef(vector<Value*>{
        ConstantExpr::getBitCast(module->getFunction("main"), PointerType::get(Type::getVoidTy(_ctx), 0)),
        ConstantInt::get(_ctx, APInt(32, StringRef("65536"),   10)),
        ConstantInt::get(_ctx, APInt(32, StringRef("4"),       10)),
        ConstantInt::get(_ctx, APInt(32, StringRef("16"),      10)),
        ConstantInt::get(_ctx, APInt(32, StringRef("128"),     10))
      }),
#else
      module->getFunction("main"),
      makeArrayRef(vector<Value*>{}),
#endif
      "", entrybb);
    ReturnInst::Create(_ctx, entrybb);
    pop();
    ModuleAnalysisManager am{};
    PassManager<Module> pm;
    raw_string_ostream *out = new raw_string_ostream(code);
    pm.addPass(PrintModulePass(*out));
    pm.run(*module, am);
}

void GenContext::OutputCode(ostream &out) {
    out << code;
}

GenericValue GenContext::run(string fnname) {
    ExecutionEngine *ee = EngineBuilder(unique_ptr<Module>(module)).create();
    vector<GenericValue> noargs;
    GenericValue v;
    ee->finalizeObject();
    mainFunction = module->getFunction("__entry");
    v = ee->runFunction(mainFunction, noargs);
    return v;
}

static Type *typeOf(VariableExprNode *var) {
    Type *type = nullptr;
    if (var->name == "int")
        type = Type::getInt64Ty(_ctx);
    else if (var->name == "char")
        type = Type::getInt8Ty(_ctx);
    else if (var->name == "double")
        type = Type::getDoubleTy(_ctx);
    else if (var->name == "void")
        type = Type::getVoidTy(_ctx);
    else if (var->name == "auto")
        switch(var->_type.plain) {
            case R_INT:
                type = Type::getInt64Ty(_ctx);
            break;
            case R_CHAR:
                type = Type::getInt8Ty(_ctx);
            break;
            case R_DOUBLE:
                type = Type::getDoubleTy(_ctx);
            break;
            case R_VOID:
                type = Type::getVoidTy(_ctx);
            break;
            case R_PTR:
                type = Type::getInt32PtrTy(_ctx);
            break;
            case R_FUNC:
                type = Type::getInt32PtrTy(_ctx);
            break;
        }
    return type;
}

Value* VariableExprNode::CodeGen(GenContext& context) {
    Value* val;
    bool glob = false;
    if ((val = context.generated_locals()[name]) != nullptr)
        return val;
    if (!context.funcDeclaring || context.locals().find(name) == context.locals().end()) {
        if (context.globals().find(name) == context.globals().end()) {
            cerr << "Undeclared Variable " << name << endl;
            return NULL;
        } else {
            val = context.globals()[name];
            glob = true;
        }
    } else
        val = context.locals()[name];
    if (glob) {
        if (((GlobalVariable*)val)->getValueType()->isArrayTy()) goto isarray;
        goto loadthis;
    }
    if (((AllocaInst*)val)->getAllocatedType()->isArrayTy()) {
        isarray:;
        ConstantInt* constInt = ConstantInt::get(_ctx, APInt(32, StringRef("0"), 10));
        vector<Value*> args;
        args.push_back(constInt);
        args.push_back(constInt);
        Type* type;
        type = glob ? ((GlobalVariable*)val)->getValueType() : ((AllocaInst*)val)->getAllocatedType();
        val = GetElementPtrInst::Create(type, val, args, "", context.context());
    } else loadthis:
        val = new LoadInst(val, "", false, context.context());
    context.generated_locals()[name] = val;
    return val;
}

Value* CharExprNode::CodeGen(GenContext& context) {
    return ConstantInt::get(Type::getInt8Ty(_ctx), val, true);
}

Value* IntExprNode::CodeGen(GenContext& context) {
    return ConstantInt::get(Type::getInt64Ty(_ctx), val, true);
}

Value* DoubleExprNode::CodeGen(GenContext& context) {
    return ConstantFP::get(Type::getDoubleTy(_ctx), val);
}

Value* BlockExprNode::CodeGen(GenContext& context) {
    Value *returnValue = NULL;
    for (auto it = statements->begin(); it != statements->end(); it++)
        returnValue = (*it)->CodeGen(context);
    return returnValue;
}

Value* OperatorExprNode::CodeGen(GenContext& context) {
    Instruction::BinaryOps instr;
    ICmpInst::Predicate pred;
    bool floatOp = false;
    bool mathOP = false;
    Value* leftVal = left->CodeGen(context);
    Value* rightVal = right->CodeGen(context);
    if (leftVal->getType()->isDoubleTy() || rightVal->getType()->isDoubleTy()) {
        leftVal = cast(leftVal, Type::getDoubleTy(_ctx), context);
        rightVal = cast(rightVal, Type::getDoubleTy(_ctx), context);
        floatOp = true;
    } else if (leftVal->getType() == rightVal->getType()) {
    } else {
        leftVal = cast(leftVal, Type::getInt64Ty(_ctx), context);
        rightVal = cast(rightVal, Type::getInt64Ty(_ctx), context);
    }
    if (!floatOp) {
        switch (op) {
            case EQ:
                pred = ICmpInst::ICMP_EQ;
                break;
            case NE:
                pred = ICmpInst::ICMP_NE;
                break;
            case GR:
                pred = ICmpInst::ICMP_SGT;
                break;
            case LW:
                pred = ICmpInst::ICMP_SLT;
                break;
            case GE:
                pred = ICmpInst::ICMP_SGE;
                break;
            case LE:
                pred = ICmpInst::ICMP_SLE;
                break;
            case ADD:
            case SADD:
                instr = Instruction::Add;
                mathOP=true;
                break;
            case SUB:
            case SSUB:
                instr = Instruction::Sub;
                mathOP=true;
                break;
            case MUL:
            case SMUL:
                instr = Instruction::Mul;
                mathOP=true;
                break;
            case DIV:
            case SDIV:
                instr = Instruction::SDiv;
                mathOP=true;
                break;
            case OR:
                instr = Instruction::Or;
                mathOP=true;
                break;
            case AND:
                instr = Instruction::And;
                mathOP=true;
                break;
        }
    } else {
        switch (op) {
            case EQ:
                pred = ICmpInst::FCMP_OEQ;
                break;
            case NE:
                pred = ICmpInst::FCMP_ONE;
                break;
            case GR:
                pred = ICmpInst::FCMP_OGT;
                break;
            case LW:
                pred = ICmpInst::FCMP_OLT;
                break;
            case GE:
                pred = ICmpInst::FCMP_OGE;
                break;
            case LE:
                pred = ICmpInst::FCMP_OLE;
                break;
            case ADD:
            case SADD:
                instr = Instruction::FAdd;
                mathOP=true;
                break;
            case SUB:
            case SSUB:
                instr = Instruction::FSub;
                mathOP=true;
                break;
            case MUL:
            case SMUL:
                instr = Instruction::FMul;
                mathOP=true;
                break;
            case DIV:
            case SDIV:
                instr = Instruction::FDiv;
                mathOP=true;
                break;
        }
    }
    if (mathOP)
        return BinaryOperator::Create(instr, leftVal, rightVal, "", context.context());
    else
        return new ICmpInst(*context.context(), pred, leftVal, rightVal, "");
}

Value* AssignExprNode::CodeGen(GenContext& context) {
    Value* rightVal;
    Value* leftVal;
    if (!context.funcDeclaring || context.locals().find(left->name) == context.locals().end()) {
        if (context.globals().find(left->name) == context.globals().end())
            return NULL;
        else
            leftVal = context.globals()[left->name];
    }
    else
        leftVal = context.locals()[left->name];
    rightVal = right->CodeGen(context);
    if (leftVal->getType() == Type::getInt64PtrTy(_ctx))
        rightVal = cast(rightVal, Type::getInt64Ty(_ctx), context);
    else if (leftVal->getType() == Type::getDoublePtrTy(_ctx))
        rightVal = cast(rightVal, Type::getDoubleTy(_ctx), context);
    else if (leftVal->getType() == Type::getInt8PtrTy(_ctx))
        rightVal = cast(rightVal, Type::getInt8Ty(_ctx), context);
    Value* res = new StoreInst(rightVal, leftVal, false, context.context());
    context.generated_locals()[left->name] = nullptr;
    return res;
}

Value* FuncExprNode::CodeGen(GenContext& context) {
    // Get functor
    Function *function = context.module->getFunction(functor->name.c_str());
    if (function == NULL) {
        cerr << "No such function " << functor->name << endl;
        return nullptr;
    }
    vector<Value*> argsRef;
    for (auto it = args->begin(); it != args->end(); it++)
        argsRef.push_back((*it)->CodeGen(context));
    CallInst *call = CallInst::Create(function, makeArrayRef(argsRef), "", context.context());
    return call;
}

Value* SpawnExprNode::CodeGen(GenContext& context) {
    auto& argsStrTystuff = spawnStructTypes[functor->name];
    auto& argType = get<0>(argsStrTystuff);
    Type* realArgType;
    Function *func = context.module->getFunction(functor->name.c_str());
    bool has_data = spawnStructTypes.count(functor->name) > 0 ? get<1>(argsStrTystuff) : true, single = get<2>(argsStrTystuff);
    if (func == NULL) {
        cerr << "No such function " << functor->name << endl;
        return nullptr;
    }
    int data_length = func->arg_size();
    if (args->size() != data_length) {
        cerr << "Function " << functor->name << " called with wrong number of arguments: must be " << data_length << " but is " << args->size() << endl;
    }
    if (argType == nullptr) {
        if (func->arg_size() < 2) {
            argType = Type::getInt64PtrTy(_ctx);
            has_data = false;
            single = func->arg_size() == 1;
            if (single)
                realArgType = func->getFunctionType()->params()[0];
        }
        else {
            auto *ft = func->getFunctionType();
            // generate a struct to hold the arguments
            argType = StructType::create(ft->params());
        }
        get<1>(argsStrTystuff) = has_data;
        get<2>(argsStrTystuff) = single;
    }

    Value* thread = new AllocaInst(Type::getInt64Ty(_ctx), 0, "thread", context.context());
    Function*& function = spawnWrappers[functor->name];
    if (has_data) {
        Function* _malloc = context.module->getFunction("malloc");
        if (!_malloc) {
            cerr << "malloc not available; cannot create working threads" << endl;
            return nullptr;
        }
        PointerType* structptr = PointerType::get(argType, 0);
        Value* Size_ = GetElementPtrInst::Create(argType, ConstantPointerNull::get(structptr), ConstantInt::get(Type::getInt32Ty(_ctx), 1), "", context.context());
        Value* size  = new PtrToIntInst(Size_, Type::getInt64PtrTy(_ctx), "size", context.context());
        vector<Value*> mallocArgs { size };
        auto memNode = CallInst::Create(_malloc, makeArrayRef(mallocArgs), "malloc", context.context());
        auto const elementTypes = ((StructType *&)argType)->elements();
        for (int i = 0; i < data_length; i++) {
            Value* addr = GetElementPtrInst::CreateInBounds(
                structptr,
                memNode,
                ConstantInt::get(Type::getInt32Ty(_ctx), i),
                "",
                context.context()
            );
            llvmDebugPrint(addr);
            Value* store= new StoreInst(args->at(i)->CodeGen(context), addr, false, context.context());
        }
        // now generate a fancy function for pthread to call
        auto ptrty = PointerType::get(Type::getInt8Ty(_ctx), 0);
        if (!function) {
            vector<Type*> argTypeRef { ptrty };
            FunctionType *funcType = FunctionType::get(func->getReturnType(), makeArrayRef(argTypeRef), false);
            function = Function::Create(funcType, GlobalValue::ExternalLinkage, ("cilk_spawn_" + functor->name).c_str(), context.module);
            func->setCallingConv(CallingConv::C);
            Function* prevF = context.currentFunction();

            context.currentFunction(function);
            context.funcDeclaring = true;

            BasicBlock *funcBlock = BasicBlock::Create(_ctx, "", function, 0);
            context.push(funcBlock, false);
            Argument* arg = function->arg_begin();
            vector<Value*> structMembers {};
            auto* castarg = new BitCastInst(arg, structptr, "unpack", context.context());
            for (int i = 0; i < data_length; i++) {
                Value* addr = GetElementPtrInst::CreateInBounds(
                    structptr,
                    castarg,
                    makeArrayRef(vector<Value*> {ConstantInt::get(Type::getInt32Ty(_ctx), 0), ConstantInt::get(Type::getInt32Ty(_ctx), i)}),
                    "",
                    context.context()
                );
                structMembers.push_back(
                    new LoadInst(addr, "", false, context.context())
                );
            }
            Value* callinst = CallInst::Create(func, makeArrayRef(structMembers), "retv", context.context());
            Value* retInst = ReturnInst::Create(_ctx, callinst, context.context());
            context.pop();
            // now generate a call to pthread_create
            context.currentFunction(prevF);
        }
        Function* pthreadc_ = context.module->getFunction(RTS_SPAWN);
        if (!pthreadc_) {
            cerr << "runtime system not available; cannot spawn threads" << endl;
            return nullptr;
        }
        Value* ok = CallInst::Create(pthreadc_, makeArrayRef(vector<Value*>{thread, ConstantPointerNull::get(ptrty), ConstantExpr::getBitCast(function, ptrty), memNode}), "tid", context.context());
        context.local_threads()[id] = {thread, target->CodeGen(context), target->name};
        return ok;
    } else {
        // no data to unpack
        // now generate a fancy function for pthread to call
        auto ptrty = PointerType::get(Type::getInt8Ty(_ctx), 0);
        vector<Type*> argTypeRef { ptrty };
        if (!function) {
            FunctionType *funcType = FunctionType::get(func->getReturnType(), makeArrayRef(argTypeRef), false);
            function = Function::Create(funcType, GlobalValue::ExternalLinkage, ("cilk_spawn_" + functor->name).c_str(), context.module);
            function->setCallingConv(CallingConv::C);
            Function* prevF = context.currentFunction();

            context.currentFunction(function);
            context.funcDeclaring = true;

            BasicBlock *funcBlock = BasicBlock::Create(_ctx, "", function, 0);
            context.push(funcBlock, false);
            vector<Value*> sargs;
            if (single)
                sargs.push_back(new BitCastInst(function->arg_begin(), realArgType, "", context.context()));
            Value* callinst = CallInst::Create(func, sargs, "retv", context.context());
            Value* retInst = ReturnInst::Create(_ctx, callinst, context.context());
            context.pop();
            // now generate a call to pthread_create
            context.currentFunction(prevF);
        }
        Function* pthreadc_ = context.module->getFunction(RTS_SPAWN);
        if (!pthreadc_) {
            cerr << "runtime system not available; cannot spawn threads" << endl;
            return nullptr;
        }
        Value* ok = CallInst::Create(
            pthreadc_,
            makeArrayRef(vector<Value*>{
                thread,
                ConstantPointerNull::get(ptrty),
                ConstantExpr::getBitCast(function, ptrty),
                single ? (Value*)new BitCastInst(args->at(0)->CodeGen(context), ptrty, "", context.context()) : ConstantPointerNull::get(ptrty)
            }),
            "tid",
            context.context()
        );
        // todo: check if ok
        context.local_threads()[id] = {thread, target->CodeGen(context), target->name};
        return ok;
    }
}

int SpawnExprNode::_id = 0;

Value* SyncStatementNode::CodeGen(GenContext& context) {
    Function* pthreadc_ = context.module->getFunction(RTS_JOIN);
    auto ptrty = PointerType::get(Type::getInt8Ty(_ctx), 0);
    if (!pthreadc_) {
        cerr << "runtime system not available; cannot sync threads" << endl;
        return nullptr;
    }
    for (auto thread : context.local_threads()) {
        auto& locs = context.generated_locals();
        Value* res = new AllocaInst(get<1>(thread.second)->getType(), 0, "res", context.context());
        Value* ok = CallInst::Create(
            pthreadc_,
            makeArrayRef(vector<Value*>{
                new LoadInst(get<0>(thread.second), "", false, context.context()),
                new BitCastInst(res, ptrty, "", context.context()),
            }), "tid", context.context()
        );
        auto& var = locs[get<2>(thread.second)];
        var = new LoadInst(res, "", false, context.context());
        // Value *save = new StoreInst(get<1>(thread.second), res, false, context.context());
    }
    return nullptr;
}

Value* CastExprNode::CodeGen(GenContext& context) {
    Value* value = expr->CodeGen(context);
    Type* castType = typeOf(type);
    value = cast(value, castType, context);
    return value;
}

Value* IndexExprNode::CodeGen(GenContext& context) {
    Value* array = name->CodeGen(context);
    Value* num = cast(expr->CodeGen(context), Type::getInt64Ty(_ctx), context);
    num = new TruncInst(num, Type::getInt32Ty(_ctx), "", context.context());
    Type* arrayType = cast<PointerType>(array->getType()->getScalarType())->getElementType();
    Instruction* instr;
    Value* retInst;
    instr = GetElementPtrInst::Create(arrayType, array, num, "", context.context());
    // whether read or write
    if (assign == NULL)
        retInst = new LoadInst(instr, "", false, context.context());
    else
        retInst = new StoreInst(assign->CodeGen(context), instr, false, context.context());
    return retInst;
}

Value* ExprStatementNode::CodeGen(GenContext& context) {
    return expr->CodeGen(context);
}

Value* VarDecStatementNode::CodeGen(GenContext& context) {
    Value* newVar;
    if (context.isGlobal())
        newVar = context.global(name->name, typeOf(type));
    else {
        newVar = new AllocaInst(typeOf(type), 0, name->name.c_str(), context.context());
        context.locals()[name->name] = newVar;
    }
    if (expr != NULL) {
        AssignExprNode assign(name, expr);
        assign.CodeGen(context);
    }
    return newVar;
}

Value* ArrayDecStatementNode::CodeGen(GenContext& context) {
    ArrayType* arrayType = ArrayType::get(typeOf(type), size);
    Value *val;
    if (context.isGlobal())
        val = context.global(name->name, arrayType);
    else {
        AllocaInst *alloc = new AllocaInst(arrayType, 0, name->name.c_str(), context.context());
        context.locals()[name->name] = alloc;
        val = alloc;
    }
    if (init->size() != 0) {
        for (auto it = init->begin(); it != init->end(); ++it) {
            ExprNode* num = new IntExprNode(it - init->begin());
            IndexExprNode a(name, num, (*it));
            a.CodeGen(context);
            delete num;
        }
    }
    return val;
}

Value* ReturnStatementNode::CodeGen(GenContext& context) {
    return expr->CodeGen(context);
}

Value* FuncDecStatementNode::CodeGen(GenContext& context) {
    // Function type
    vector<Type*> argTypeRef;
    for (auto it = args->begin(); it != args->end(); it++)
        argTypeRef.push_back(typeOf((*it)->type));
    FunctionType *funcType = FunctionType::get(typeOf(type), ArrayRef<Type*>(argTypeRef), false);
    Function *function = Function::Create(funcType, GlobalValue::ExternalLinkage, name->name.c_str(), context.module);
    function->setCallingConv(CallingConv::C);
    // SmallVector<AttributeSet, 4> Attrs;
    // AttrBuilder Builder;
    // Builder.addAttribute(Attribute::NoUnwind);
    // Attrs.push_back(AttributeSet::get(_ctx, ~0U, Builder));
    // AttributeSet funcFuncAttrSet = AttributeSet::get(_ctx, Attrs);
    // function->setAttributes(funcFuncAttrSet);
    context.currentFunction(function);
    context.funcDeclaring = true;
    // Start function
    BasicBlock *funcBlock = BasicBlock::Create(_ctx, "", function, 0);
    context.push(funcBlock, false);
    Function::arg_iterator argsValues = function->arg_begin();
    for (auto it = args->begin(); it != args->end(); it++, argsValues++) {
        (*it)->CodeGen(context);
        Value *argumentValue = &(*argsValues);
        argumentValue->setName((*it)->name->name.c_str());
        StoreInst *inst = new StoreInst(argumentValue, context.locals()[(*it)->name->name], false, funcBlock);
    }
    // Get return value
    Value* returnValue = block->CodeGen(context);
    context.funcDeclaring = false;
    // Return
    BasicBlock *returnBlock = BasicBlock::Create(_ctx, "", function, 0);
    BranchInst::Create(returnBlock, context.context());
    ReturnInst::Create(_ctx, returnValue, returnBlock);
    context.pop();
    return function;
}

Value* ExternFuncDecStatementNode::CodeGen(GenContext& context) {
    vector<Type*> argTypes;
    FunctionType *ftype;
    Function *function;
    for (auto it = args->begin(); it != args->end(); it++)
        argTypes.push_back(typeOf((*it)->type));
    ftype = FunctionType::get(Type::getVoidTy(_ctx), makeArrayRef(argTypes), false);
    function = Function::Create(ftype, GlobalValue::ExternalLinkage, name->name.c_str(), context.module);
    return function;
}

Value* IfStatementNode::CodeGen(GenContext& context) {
    BasicBlock* ifTrue = BasicBlock::Create(_ctx, "", context.currentFunction(), 0);
    BasicBlock* ifEnd = BasicBlock::Create(_ctx, "", context.currentFunction(), 0);
    BasicBlock* ifFalse = falseBlock ? BasicBlock::Create(_ctx, "", context.currentFunction(), 0) : ifEnd;
    BranchInst::Create(ifTrue, ifFalse, condExpr->CodeGen(context), context.context());
    // Entering IF
    context.push(ifTrue);
    trueBlock->CodeGen(context);
    // JMP to END
    BranchInst::Create(ifEnd, context.context());
    context.pop();
    if (falseBlock != nullptr) {
        // Entering ELSE
        context.push(ifFalse);
        falseBlock->CodeGen(context);
        // JMP to END
        BranchInst::Create(ifEnd, context.context());
        context.pop();
    }
    // Return END
    context.ret(ifEnd);
    return ifEnd;
}

Value* ForStatementNode::CodeGen(GenContext& context) {
    // Initialize
    initExpr->CodeGen(context);
    BasicBlock* forIter = BasicBlock::Create(_ctx, "", context.currentFunction(), 0);
    BasicBlock* forEnd = BasicBlock::Create(_ctx, "", context.currentFunction(), 0);
    BasicBlock* forCheck = BasicBlock::Create(_ctx, "", context.currentFunction(), 0);
    // Check condition satisfaction
    BranchInst::Create(forCheck, context.context());
    context.push(forCheck);
    // Whether break the loop
    BranchInst::Create(forIter, forEnd, condExpr->CodeGen(context), forCheck);
    context.pop();
    // Entering loop block
    context.push(forIter);
    block->CodeGen(context);
    // Iteration
    loopExpr->CodeGen(context);
    // Jump back to condition checking
    BranchInst::Create(forCheck, context.context());
    context.pop();
    // Return END
    context.ret(forEnd);
    return forEnd;
}

Value* WhileStatementNode::CodeGen(GenContext& context) {
    BasicBlock* whileIter = BasicBlock::Create(_ctx, "", context.currentFunction(), 0);
    BasicBlock* whileEnd = BasicBlock::Create(_ctx, "", context.currentFunction(), 0);
    BasicBlock* whileCheck = BasicBlock::Create(_ctx, "", context.currentFunction(), 0);
    // Check condition satisfaction
    BranchInst::Create(whileCheck, context.context());
    context.push(whileCheck);
    // Whether break the loop
    BranchInst::Create(whileIter, whileEnd, whileExpr->CodeGen(context), context.context());
    context.pop();
    // Entering loop block
    context.push(whileIter);
    block->CodeGen(context);
    // Jump back to condition checking
    BranchInst::Create(whileCheck, context.context());
    context.pop();
    // Return END
    context.ret(whileEnd);
    return whileEnd;
}

static Value* cast(Value* value, Type* type, GenContext& context) {
    if (type == value->getType())
        return value;
    if (type == Type::getDoubleTy(_ctx)) {
        if (value->getType() == Type::getInt64Ty(_ctx) || value->getType() == Type::getInt8Ty(_ctx))
            value = new SIToFPInst(value, type, "", context.context());
        else
            cout << "Cannot cast this value.\n";
    }
    else if (type == Type::getInt64Ty(_ctx)) {
        if (value->getType() == Type::getDoubleTy(_ctx))
            value = new FPToSIInst(value, type, "", context.context());
        else if (value->getType() == Type::getInt8Ty(_ctx))
            value = new SExtInst(value, type, "", context.context());
        else if (value->getType() == Type::getInt32Ty(_ctx))
            value = new ZExtInst(value, type, "", context.context());
        else if (value->getType() == Type::getInt8PtrTy(_ctx))
            value = new PtrToIntInst(value, type, "", context.context());
        else if (value->getType() == Type::getInt64PtrTy(_ctx))
            value = new PtrToIntInst(value, type, "", context.context());
        else
            cout << "Cannot cast this value.\n";
    } else if (type == Type::getInt8Ty(_ctx)) {
        if (value->getType() == Type::getDoubleTy(_ctx))
            value = new FPToSIInst(value, type, "", context.context());
        else if (value->getType() == Type::getInt64Ty(_ctx))
            value = new TruncInst(value, type, "", context.context());
        else
            cout << "Cannot cast this value.\n";
    } else
        cout << "Cannot cast this value.\n";
    return value;
}
