#include "ast.hpp"
#include "symtab.hpp"
#include "classhierarchy.hpp"
#include "primitive.hpp"
#include "assert.h"
#include <typeinfo>
#include <stdio.h>

class Codegen : public Visitor
{
  private:
  
  FILE * m_outputfile;
  SymTab *m_symboltable;
  ClassTable *m_classtable;
  
  const char * heapStart="_heap_start";
  const char * heapTop="_heap_top";
  const char * printFormat=".LC0";
  const char * printFun="Print";
  
  OffsetTable*currClassOffset;
  OffsetTable*currMethodOffset;
  
  // basic size of a word (integers and booleans) in bytes
  static const int wordsize = 4;
  
  int label_count; //access with new_label
  
  // ********** Helper functions ********************************
  
  // this is used to get new unique labels (cleverly named label1, label2, ...)
  int new_label() { return label_count++; }

  // PART 1:
  // 1) get arithmetic expressions on integers working:
  //	  you wont really be able to run your code,
  //	  but you can visually inspect it to see that the correct
  //    chains of opcodes are being generated.
  // 2) get function calls working:
  //    if you want to see at least a very simple program compile
  //    and link successfully against gcc-produced code, you
  //    need to get at least this far
  // 3) get boolean operation working
  //    before we can implement any of the conditional control flow 
  //    stuff, we need to have booleans worked out.  
  // 4) control flow:
  //    we need a way to have if-elses and for loops in our language. 
  //
  // Hint: Symbols have an associated member variable called m_offset
  //    That offset can be used to figure out where in the activation 
  //    record you should look for a particuar variable
  
  ///////////////////////////////////////////////////////////////////////////////
  //
  //  function_prologue
  //  function_epilogue
  //
  //  Together these two functions implement the callee-side of the calling
  //  convention.  A stack frame has the following layout:
  //
  //                          <- SP (before pre-call / after epilogue)
  //  high -----------------
  //	   | actual arg 1  |
  //	   | ...           |
  //	   | actual arg n  |
  //	   -----------------
  //	   |  Return Addr  | 
  //	   =================
  //	   | temporary 1   |    <- SP (when starting prologue)
  //	   | ...           |
  //	   | temporary n   | 
  //  low -----------------   <- SP (when done prologue)
  //
  //
  //			  ||		
  //			  ||
  //			 \  /
  //			  \/
  //
  //
  //  The caller is responsible for placing the actual arguments
  //  and the return address on the stack. Actually, the return address
  //  is put automatically on the stack as part of the x86 call instruction.
  //
  //  On function entry, the callee
  //
  //  (1) allocates space for the callee's temporaries on the stack
  //  
  //  (2) saves callee-saved registers (see below) - including the previous activation record pointer (%ebp)
  //
  //  (3) makes the activation record pointer (frame pointer - %ebp) point to the start of the temporary region
  //
  //  (4) possibly copies the actual arguments into the temporary variables to allow easier access
  //
  //  On function exit, the callee:
  //
  //  (1) pops the callee's activation record (temporay area) off the stack
  //  
  //  (2) restores the callee-saved registers, including the activation record of the caller (%ebp)	 
  //
  //  (3) jumps to the return address (using the x86 "ret" instruction, this automatically pops the 
  //	  return address off the stack
  //
  //////////////////////////////////////////////////////////////////////////////
  //
  // Since we are interfacing with code produced by GCC, we have to respect the 
  // calling convention that GCC demands:
  //
  // Contract between caller and callee on x86: 
  //	 * after call instruction: 
  //		   o %eip points at first instruction of function 
  //		   o %esp+4 points at first argument 
  //		   o %esp points at return address 
  //	 * after ret instruction: 
  //		   o %eip contains return address 
  //		   o %esp points at arguments pushed by caller 
  //		   o called function may have trashed arguments 
  //		   o %eax contains return value (or trash if function is void) 
  //		   o %ecx, %edx may be trashed 
  //		   o %ebp, %ebx, %esi, %edi must contain contents from time of call 
  //	 * Terminology: 
  //		   o %eax, %ecx, %edx are "caller save" registers 
  //		   o %ebp, %ebx, %esi, %edi are "callee save" registers 
  ////////////////////////////////////////////////////////////////////////////////
  
  void init()
  {
    fprintf( m_outputfile, ".text\n\n");
    fprintf( m_outputfile, ".comm %s,4,4\n", heapStart);
    fprintf( m_outputfile, ".comm %s,4,4\n\n", heapTop);
    
    fprintf( m_outputfile, "%s:\n", printFormat);
    fprintf( m_outputfile, "       .string \"%%d\\n\"\n");
    fprintf( m_outputfile, "       .text\n");
    fprintf( m_outputfile, "       .globl  %s\n",printFun);
    fprintf( m_outputfile, "       .type   %s, @function\n\n",printFun);
    fprintf( m_outputfile, ".global %s\n",printFun);
    fprintf( m_outputfile, "%s:\n",printFun);
    fprintf( m_outputfile, "       pushl   %%ebp\n");
    fprintf( m_outputfile, "       movl    %%esp, %%ebp\n");
    fprintf( m_outputfile, "       movl    8(%%ebp), %%eax\n");
    fprintf( m_outputfile, "       pushl   %%eax\n");
    fprintf( m_outputfile, "       pushl   $.LC0\n");
    fprintf( m_outputfile, "       call    printf\n");
    fprintf( m_outputfile, "       addl    $8, %%esp\n");
    fprintf( m_outputfile, "       leave\n");
    fprintf( m_outputfile, "       ret\n\n");
  }

  void start(int programSize)
  {
    fprintf( m_outputfile, "# Start Function\n");
    fprintf( m_outputfile, ".global Start\n");
    fprintf( m_outputfile, "Start:\n");
    fprintf( m_outputfile, "        pushl   %%ebp\n");
    fprintf( m_outputfile, "        movl    %%esp, %%ebp\n");
    fprintf( m_outputfile, "        movl    8(%%ebp), %%ecx\n");
    fprintf( m_outputfile, "        movl    %%ecx, %s\n",heapStart);
    fprintf( m_outputfile, "        movl    %%ecx, %s\n",heapTop);
    fprintf( m_outputfile, "        addl    $%d, %s\n",programSize,heapTop);
    fprintf( m_outputfile, "        pushl   %s \n",heapStart);
    fprintf( m_outputfile, "        call    Program_start \n");
    fprintf( m_outputfile, "        leave\n");
    fprintf( m_outputfile, "        ret\n");
  }

  void allocSpace(int size)
  {
	// Optional WRITE ME
  }

////////////////////////////////////////////////////////////////////////////////
public:
  
  Codegen(FILE * outputfile, SymTab * st, ClassTable* ct)
  {
    m_outputfile = outputfile;
    m_symboltable = st;
    m_classtable = ct;
    label_count = 0;
    currMethodOffset=currClassOffset=NULL;
  }
    void printSymTab(){
      FILE * pFile;
      pFile = fopen ("myfile.txt" , "w");
      m_symboltable->dump(pFile);
      fclose (pFile);
      }

  void visitProgramImpl(ProgramImpl *p) {

	    init();      
      p->visit_children(this);
         // WRITEME

  }
  void visitClassImpl(ClassImpl *p) {
      ClassIDImpl * ClassIdP = dynamic_cast<ClassIDImpl*>(p->m_classid_1);
      char * key1 = strdup(ClassIdP->m_classname->spelling());
      Symbol * symPtr = new Symbol;
      symPtr->classType.classID = ClassIdP->m_classname->spelling();
      m_symboltable->insert((char *)"xxx", symPtr);

      p->visit_children(this);
         // WRITEME

  }
  void visitDeclarationImpl(DeclarationImpl *p) {
    // cout<<"can i subtract here?"<<endl;
      p->visit_children(this);
      // cout<<"whaddabout here?"<<endl;
         // WRITEME

  }
  void visitMethodImpl(MethodImpl *p) {
    fprintf( m_outputfile, "#### METHOD IMPLEMENTATION\n");
    int localSpace, args, mem;
    int j=0;
    int methMem = 0;
    CompoundType info;
    currMethodOffset = new OffsetTable();
// cout<<"before my childen"<<endl;

//this is to make the label name
    Symbol * symbP;
    SymScope * sync;
    MethodIDImpl * MethIdP = dynamic_cast<MethodIDImpl*>(p->m_methodid);
    char * funcName = strdup(MethIdP->m_symname->spelling());
    sync = m_symboltable->get_current_scope();
    symbP = sync->lookup((const char *)"xxx");
    char * classMethName = strdup(symbP->classType.classID);
    strcat(classMethName,"_");
    strcat(classMethName,funcName);
    fprintf( m_outputfile, "_%s:\n",classMethName);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    fprintf( m_outputfile, " pushl %%ebp\n");
    fprintf( m_outputfile, " movl %%esp , %%ebp\n");
    MethodBodyImpl * MethBodP = dynamic_cast<MethodBodyImpl*>(p->m_methodbody);
    localSpace = (p->m_parameter_list->size() + MethBodP->m_declaration_list->size());

    localSpace = localSpace * wordsize;
    // currMethodOffset->insert(classMethName, localSpace, 4,symbP->classType);
    currMethodOffset->setTotalSize(localSpace);
    currMethodOffset->setParamSize(p->m_parameter_list->size() * wordsize);

//### inserting paramaters into the offset table ###########
    for (std::list<Parameter_ptr>::iterator it = p->m_parameter_list->begin() ; it != p->m_parameter_list->end(); ++it){
    ParameterImpl * param = dynamic_cast<ParameterImpl*>(*it);
      VariableIDImpl * VarId = dynamic_cast<VariableIDImpl*>(param->m_variableid);

      info.baseType = param->m_type->m_attribute.m_type.baseType; 
      if(info.baseType == 8){ 
        info.classID = param->m_type->m_attribute.m_type.classType.classID;
        }
      else{
        info.classID = "NO CLASS";
        }
        methMem -= 4;
// cout<<"Offset-> symname: "<<VarId->m_symname->spelling()<<" offset: "<<methMem<<" class type: " <<info.baseType<<endl;
      currMethodOffset->insert(VarId->m_symname->spelling(), methMem, 4,info);
      
    }
//################################  

      

//<><>Diving into Declaration <><><><>><><><><><><><><><><><>><><><><><><
       typename std::list<Declaration_ptr>::iterator it = MethBodP->m_declaration_list->begin();
       for( ; it != MethBodP->m_declaration_list->end(); ++it) {
          DeclarationImpl * DeclaP = dynamic_cast<DeclarationImpl *> (*it);
          typename std::list<VariableID_ptr>::iterator it = DeclaP->m_variableid_list->begin();
          for( ; it != DeclaP->m_variableid_list->end(); ++it) {
            methMem -= 4; // need to move to the next offset
            VariableIDImpl * VarIdP = dynamic_cast<VariableIDImpl*>(*it);
            char * var = strdup(VarIdP->m_symname->spelling());
 // cout<<"Offset-> symname: "<<var<<" Offset: "<<methMem<<" Class type: " <<endl;
            info.baseType = DeclaP->m_type->m_attribute.m_type.baseType; 
            if(info.baseType == 8){ 
              info.classID = DeclaP->m_type->m_attribute.m_type.classType.classID;
              }
            else{
              info.classID = "NO CLASS";
              }
            currMethodOffset->insert(var, methMem, 4,info);

           }

        }
//<><><><><><><><><><><><><><><><><>><><><><><><
//~~~~ allocating space on the stack and  moves parameters into local ~~~~~~   

// cout<<"param size: "<<currMethodOffset->getParamSize()<<endl;
// cout<<" LocalSpace: "<< -(methMem)<<endl;

  fprintf( m_outputfile, " subl $%d, %%esp\n",-(methMem));
   mem = -4;
   for(int i = currMethodOffset->getParamSize() + 4; i>= 8; i = i-4){
     
      fprintf( m_outputfile, " movl %d(%%ebp) , %%eax\n",i);
      fprintf( m_outputfile, " movl %%eax , %d(%%ebp)\n",mem);
      mem -= 4;
      // symbP->methodType.argsType[j].baseType;
     }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


     p->visit_children(this);
// cout<<"after the children"<<endl;
    fprintf( m_outputfile, " leave\n");
    fprintf( m_outputfile, " ret\n");  
         // WRITEME
  }
  void visitMethodBodyImpl(MethodBodyImpl *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitParameterImpl(ParameterImpl *p) {
		      p->visit_children(this);
         // WRITEME

  }
  void visitAssignment(Assignment *p) {
      fprintf( m_outputfile, "#### ASSIGNMENT\n");

// cout<<"Before assignment@@@@@@@@@@@@@@@@@@@@@@ "<<endl;
      p->visit_children(this);
// cout<<"AFTER assignment$$$$$$$$$$$$$$$$$$$$$$$$ "<<endl;
      VariableIDImpl * VarId = dynamic_cast<VariableIDImpl*>(p->m_variableid);
      char * varName = strdup(VarId->m_symname->spelling());
      // fprintf( m_outputfile, " popl %%eax\n");

      fprintf( m_outputfile, " movl %%eax , %d(%%ebp)\n",currMethodOffset->get_offset(varName));
      


         // WRITEME

  }
  void visitIf(If *p) {
     fprintf( m_outputfile, "#### IF Statemet\n");

// cout<<"before IF Express"<<endl;
  if (p->m_expression != NULL) {
    p->m_expression->accept( this );
  } else {
    this->visitNullPointer();
  }
      fprintf( m_outputfile, " popl %%eax\n");
      fprintf( m_outputfile, " movl $0 , %%ebx\n");
      fprintf( m_outputfile, " cmp %%eax, %%ebx\n");
      fprintf( m_outputfile, " je skip_%d\n", new_label());
// cout<<"the label count is: "<<label_count<<endl;
// cout<<"Before IF state after express"<<endl;
  if (p->m_statement != NULL) {
    p->m_statement->accept( this );
  } else {
    this->visitNullPointer();
  }
// cout<<"After IF Statemetn"<<endl;
      fprintf( m_outputfile, " skip_%d: \n",label_count-1);

         // WRITEME

  }
  void visitPrint(Print *p) {
        fprintf( m_outputfile, "#### PRINT\n");

	      p->visit_children(this);

         // WRITEME

  }
  void visitReturnImpl(ReturnImpl *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitTInteger(TInteger *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitTBoolean(TBoolean *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitTNothing(TNothing *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitTObject(TObject *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitClassIDImpl(ClassIDImpl *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitVariableIDImpl(VariableIDImpl *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitMethodIDImpl(MethodIDImpl *p) {

    p->visit_children(this);
         // WRITEME

  }
  void visitPlus(Plus *p) {
    fprintf( m_outputfile, "#### ADD\n");
    p -> visit_children(this);

    fprintf( m_outputfile, " popl %%ebx\n");
    fprintf( m_outputfile, " popl %%eax\n");
    fprintf( m_outputfile, " addl %%ebx, %%eax\n");
    fprintf( m_outputfile, " pushl %%eax\n");

         // WRITEME

  }
  void visitMinus(Minus *p) {
    fprintf( m_outputfile, "#### MINUS\n");
    p -> visit_children(this);
    fprintf( m_outputfile, " popl %%ebx\n");
    fprintf( m_outputfile, " popl %%eax\n");
    fprintf( m_outputfile, " subl %%ebx, %%eax\n");
    fprintf( m_outputfile, " pushl %%eax\n");
         // WRITEME

  }
  void visitTimes(Times *p) {
    fprintf( m_outputfile, "#### TIMES\n");
    p -> visit_children(this);
    fprintf( m_outputfile, " popl %%ebx\n");
    fprintf( m_outputfile, " popl %%eax\n");
    fprintf( m_outputfile, " imull %%ebx, %%eax\n");
    fprintf( m_outputfile, " pushl %%eax\n");
         // WRITEME

  }
  void visitDivide(Divide *p) {
    fprintf( m_outputfile, "#### DIVIDE\n");
    p -> visit_children(this);
    fprintf( m_outputfile, " popl %%ebx\n");
    fprintf( m_outputfile, " popl %%eax\n");
    fprintf( m_outputfile, " cdq\n");


    fprintf( m_outputfile, " idivl %%ebx\n");
    fprintf( m_outputfile, " pushl %%eax\n");
         // WRITEME

  }
  void visitAnd(And *p) {
    fprintf( m_outputfile, "#### AND\n");
    p -> visit_children(this);
    fprintf( m_outputfile, " popl %%ebx\n");
    fprintf( m_outputfile, " popl %%eax\n");
    fprintf( m_outputfile, " andl %%ebx, %%eax\n");
    fprintf( m_outputfile, " pushl %%eax\n");
         // WRITEME

  }
  void visitLessThan(LessThan *p) {
    fprintf( m_outputfile, "#### LESSTHAN\n");
    p -> visit_children(this);
    new_label();
    fprintf( m_outputfile, " popl %%ebx\n");
    fprintf( m_outputfile, " popl %%eax\n");
    fprintf( m_outputfile, " cmp %%ebx, %%eax\n");
    fprintf( m_outputfile, " jl True_%d\n", label_count);
    fprintf( m_outputfile, " jmp False_%d\n", label_count);
    fprintf( m_outputfile, "True_%d: \n",label_count);
    fprintf( m_outputfile, " movl $1 , %%eax\n");
    fprintf( m_outputfile, " pushl %%eax\n");
    fprintf( m_outputfile, " jmp EndLT_%d\n", label_count);

    fprintf( m_outputfile, "False_%d: \n",label_count);
    fprintf( m_outputfile, " pushl %%eax\n");    
    fprintf( m_outputfile, " movl $0 , %%eax\n");

    fprintf( m_outputfile, "EndLT_%d: \n",label_count);

         // WRITEME

  }
  void visitLessThanEqualTo(LessThanEqualTo *p) {
    fprintf( m_outputfile, "#### LESS THAN EQUAL TOO\n");
    p -> visit_children(this);
    new_label();
    fprintf( m_outputfile, " popl %%ebx\n");
    fprintf( m_outputfile, " popl %%eax\n");
    fprintf( m_outputfile, " cmp %%ebx, %%eax\n");
    fprintf( m_outputfile, " jle True_%d\n", label_count);
    fprintf( m_outputfile, " jmp False_%d\n", label_count);
    fprintf( m_outputfile, "True_%d: \n",label_count);
    fprintf( m_outputfile, " movl $1 , %%eax\n");
    fprintf( m_outputfile, " jmp EndLE_%d\n", label_count);

    fprintf( m_outputfile, " pushl %%eax\n");
    fprintf( m_outputfile, "False_%d: \n",label_count);
    fprintf( m_outputfile, " pushl %%eax\n");    
    fprintf( m_outputfile, " movl $0 , %%eax\n");

    fprintf( m_outputfile, "EndLE_%d: \n",label_count);
   
         // WRITEME

  }
  void visitNot(Not *p) {
    fprintf( m_outputfile, "#### NOT\n");
    p -> visit_children(this);
    fprintf( m_outputfile, " popl %%eax\n");
    fprintf( m_outputfile, " notl %%eax\n");
    fprintf( m_outputfile, " pushl %%eax\n");    

         // WRITEME

  }
  void visitUnaryMinus(UnaryMinus *p) {
    fprintf( m_outputfile, "#### UNARY MINUS\n");
    p -> visit_children(this);
    fprintf( m_outputfile, " popl %%eax\n");
    fprintf( m_outputfile, " neg %%eax\n");
    fprintf( m_outputfile, " pushl %%eax\n");
         // WRITEME

  }
  void visitMethodCall(MethodCall *p) {
    fprintf( m_outputfile, "#### METHOD CALL\n");

      p->visit_children(this);
         // WRITEME

  }
  void visitSelfCall(SelfCall *p) {
    fprintf( m_outputfile, "#### SELF CALL\n");
    int args;
    Symbol * symbP;
    SymScope * sync;
    MethodIDImpl * MethIdP = dynamic_cast<MethodIDImpl*>(p->m_methodid);
    char * funcName = strdup(MethIdP->m_symname->spelling());
    sync = m_symboltable->get_current_scope();
    symbP = sync->lookup((const char *)"xxx");


    p->visit_children(this);
    args = p->m_expression_list->size();
    args = args * wordsize;
// cout<<"the number of params: "<<args<<endl;
    char * className = strdup(symbP->classType.classID);
    strcat(className,"_");
    strcat(className,funcName);

    fprintf( m_outputfile, "call %s\n",className);
    fprintf( m_outputfile, "addl $%d , %%esp\n",args);

         // WRITEME

  }
  void visitVariable(Variable *p) {
    //get value put in eax and push
      VariableIDImpl * VarId = dynamic_cast<VariableIDImpl*>(p->m_variableid);
      char * varName = strdup(VarId->m_symname->spelling());
      fprintf( m_outputfile, " movl %d(%%ebp) , %%eax\n",currMethodOffset->get_offset(varName));
      fprintf( m_outputfile, " pushl %%eax\n");

      p->visit_children(this);
         // WRITEME

  }
  void visitIntegerLiteral(IntegerLiteral *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitBooleanLiteral(BooleanLiteral *p) {
      p->visit_children(this);

         // WRITEME

  }
  void visitNothing(Nothing *p) {
      p->visit_children(this);
         // WRITEME

  }
  void visitSymName(SymName *p) {

         // WRITEME

  }
  void visitPrimitive(Primitive *p) {

    fprintf( m_outputfile, "#### PRIMITIVE \n");
    fprintf( m_outputfile, " movl $%d, %%eax\n", p->m_data);
    fprintf( m_outputfile, " pushl %%eax\n");



         // WRITEME

  }
  void visitClassName(ClassName *p) {

         // WRITEME

  }

  void visitNullPointer() {}
 
};




