#include "Instrument.hpp"

bool Instrument::doInitialization(Module &M __attribute__((unused))) {
  return false;
}


bool Instrument::runOnModule(Module &M) {
  for(Module::iterator f = M.begin(), fe = M.end(); f != fe; f++) {
    if (!f->isDeclaration()) {
      runOnFunction(M, *f);
    }
  }
  return true;
}


bool Instrument::runOnFunction(Module &M, Function &F) {


  for (Function::iterator b = F.begin(), be = F.end(); b != be; b++) {
    for (BasicBlock::iterator i = b->begin(), ie = b->end(); i != ie; i++) {      
      Instruction *inst = (Instruction*)i;

      /***
       ** STEP-1: 
       ** Reimplement the following if-condition statement to check
       ** for the instructions of interest (array accesses).
       ***/
      // errs() << "  Instruction: " << *inst << "\n";
      for (unsigned num = 0; num < inst->getNumOperands(); num++) 
      	if (isa<GEPOperator>(inst)) {

	/* Use the following to print the instruction to instrument for debugging purposes. */
	// errs() << "  Instruction: " << *inst << "\n";

	/***
	 ** STEP-2: Retrieve the size of the array
	 **/

	Type *T = cast<PointerType>(cast<GetElementPtrInst>(inst)->getPointerOperandType())->getElementType();
	int no_of_elements = cast<ArrayType>(T)->getNumElements();
	// Type *Ty = cast<ArrayType>(T)->getElementType();
	Value *size = dyn_cast<GetElementPtrInst>(inst)->getOperand(1);
	// errs() << no_of_elements << "\n" << size << "\n\n";

	// Value *array_size = dyn_cast<Value*>(no_of_elements);
	// Value *array_size = llvm::getInt32(no_of_elements);
	// ConstantInt* CI = dyn_cast<ConstantInt>(no_of_elements);

  
	/***
	 ** STEP-3: Retrieve the index of the array element being accessed
	 **/

	// int index_accessed =  cast<GetElementPtrInst>(inst)->getOperand(3);
	Value *index = dyn_cast<GetElementPtrInst>(inst)->getOperand(inst->getNumOperands()-2);

	// ConstantInt* CI = dyn_cast<ConstantInt>(index);
	// int intIndex = CI->getZExtValue();

	printf("%i\n", no_of_elements);
	// errs() << no_of_elements << "\n";


	/***
	 ** STEP-4: Retrieve the source information of the instruction
	 **/

	StringRef fileName = F.getParent()->getName();
	// Value *fn = cast<PointerType>(cast<Value>(fileName));
	LLVMContext& context = F.getContext();
	// LLVMContext& context;
	IRBuilder<> builder(inst);

	// Value *fn = builder.CreateGlobalString(fileName, "", 0, F.getParent());
	Value *fn = builder.CreateGlobalStringPtr(fileName);
	// Value *fn = builder.CreateGEP(cast<PointerType>(fileName));

	// errs() << fileName << " || " << *fn << "\n\n";

	const llvm::DebugLoc &debugInfo = inst->getDebugLoc();
	int line = debugInfo->getLine();
	// Type *int_type = Type::getInt8Ty(F.getContext());
	llvm::Type *int_ = llvm::IntegerType::getInt64Ty(context);
	Constant *ln = ConstantInt::get(int_, line);

	// errs() << "line: " << ln << "\n\n";


  
	/***
	 ** STEP-5: Create and store the arguments of function check_bounds
	 ** in the vector args.
	 **/

	std::vector<Value*> args = {size, index, ln, fn};

	/***
	 ** The code below creates and inserts the call before inst. Modify as needed.
	 **/

	Function *callee = M.getFunction("check_bounds");
	if (callee) {
	  CallInst::Create(callee, args, "", inst);
	}
      } 
    }
  }

  return false;
}


bool Instrument::doFinalization(Module &M __attribute__((unused))) {
  return false;
}

void Instrument::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char Instrument::ID = 0;

static const RegisterPass<Instrument> registration("instrument", "Instrument array accesses");
