#include <iostream>
#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
#include "classhierarchy.hpp"
#include "assert.h"
#include <typeinfo>
#include <stdio.h>

/***********

    Typechecking has some code already provided, you need to fill in the blanks. You should only add code where WRITEME labels
    are inserted. You can just search for WRITEME to find all the instances.
    
    You can find descriptions of every type condition that you must check for in the project webpage. Each condition has its own
    error condition that should be thrown when it fails. Every error condition listed there and also in the "errortype" enum in
    this file must be used somewhere in your code.
    
    Be careful when throwing errors - always throw an error of the right type, using the m_attribute of the node you're visiting
    when performing the check. Sometimes you'll see errors being thrown at strange line numbers; that is okay, don't let that
    bother you as long as you follow the above principle.

*****/

class Typecheck : public Visitor {
    private:
    FILE* m_errorfile;
    SymTab* m_symboltable;
    ClassTable* m_classtable;
    
    const char * bt_to_string(Basetype bt) {
        switch (bt) {
            case bt_undef:    return "bt_undef";
            case bt_integer:  return "bt_integer";
            case bt_boolean:  return "bt_boolean";
            case bt_function: return "bt_function";
            case bt_object:   return "bt_object";
            default:
                              return "unknown";
        }
    }
    
    // the set of recognized errors
    enum errortype 
    {
        no_program,
        no_start,
        start_args_err,
        
        dup_ident_name,
        sym_name_undef,
        sym_type_mismatch,
        call_narg_mismatch,
        call_args_mismatch,
        ret_type_mismatch,
        
        incompat_assign,
        if_pred_err,
        
        expr_type_err,
        
        no_class_method,
    };
    
    // Throw errors using this method
    void t_error( errortype e, Attribute a ) 
    {
        fprintf(m_errorfile,"on line number %d, ", a.lineno );
        
        switch( e ) {
            case no_program: fprintf(m_errorfile,"error: no Program class\n"); break;
            case no_start: fprintf(m_errorfile,"error: no start function in Program class\n"); break;
            case start_args_err: fprintf(m_errorfile,"error: start function has arguments\n"); break;
            
            case dup_ident_name: fprintf(m_errorfile,"error: duplicate identifier name in same scope\n"); break;
            case sym_name_undef: fprintf(m_errorfile,"error: symbol by name undefined\n"); break;
            case sym_type_mismatch: fprintf(m_errorfile,"error: symbol by name defined, but of unexpected type\n"); break;
            case call_narg_mismatch: fprintf(m_errorfile,"error: function call has different number of args than the declaration\n"); break;
            case call_args_mismatch: fprintf(m_errorfile,"error: type mismatch in function call args\n"); break;
            case ret_type_mismatch: fprintf(m_errorfile, "error: type mismatch in return statement\n"); break;
            
            case incompat_assign: fprintf(m_errorfile,"error: types of right and left hand side do not match in assignment\n"); break;
            case if_pred_err: fprintf(m_errorfile,"error: predicate of if statement is not boolean\n"); break;
            
            case expr_type_err: fprintf(m_errorfile,"error: incompatible types used in expression\n"); break;
            
            case no_class_method: fprintf(m_errorfile,"error: function doesn't exist in object\n"); break;
            
            
            default: fprintf(m_errorfile,"error: no good reason\n"); break;
        }
        exit(1);
    }
    
    public:
    
    Typecheck(FILE* errorfile, SymTab* symboltable) {
        m_errorfile = errorfile;
        m_symboltable = symboltable;
        m_classtable = new ClassTable();
    }
    ~Typecheck() {
        delete m_classtable;
    }
    void visitProgramImpl(ProgramImpl *p) {
      p->visit_children(this);
     //WRITE ME
    }
    
    void visitClassImpl(ClassImpl *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitDeclarationImpl(DeclarationImpl *p) {
      
 
       // cout<< "this is my first variable : "<< VarIdP->m_symname->spelling()<<endl;
        p->visit_children(this);
        Symbol * symp = new Symbol;

        typename std::list<VariableID_ptr>::iterator it = p->m_variableid_list->begin();
        for( ; it != p->m_variableid_list->end(); ++it) {

          VariableIDImpl * VarIdP = dynamic_cast<VariableIDImpl*>(*it);
          p->m_attribute.m_type.baseType = p->m_type->m_attribute.m_type.baseType; // i think this is setting the type of the assignment node
          char * key = strdup(VarIdP->m_symname->spelling());
          if(m_symboltable->exist(key))
            t_error(dup_ident_name, p->m_attribute);
          else{
            m_symboltable->insert(key, symp);
            symp->baseType = p->m_type->m_attribute.m_type.baseType;
          }
      }//forloop      //cout<<"declaration TYPE: "<<p->m_type->m_attribute.m_type.baseType<<endl;
      //WRITE ME
    }
    
    void visitMethodImpl(MethodImpl *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitMethodBodyImpl(MethodBodyImpl *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitParameterImpl(ParameterImpl *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitAssignment(Assignment *p) {
     p->visit_children(this);

     Symbol * symp;
      VariableIDImpl * VarIdP = dynamic_cast<VariableIDImpl*>(p->m_variableid);
      char * key = strdup(VarIdP->m_symname->spelling());

       symp = m_symboltable->lookup(key);
      
      if(m_symboltable->exist(key)){
        if(p->m_expression->m_attribute.m_type.baseType != symp->baseType)
          t_error(incompat_assign, p->m_attribute);

      }
        
      else
         t_error(sym_name_undef, p->m_attribute);

      //WRITE ME
    }
    
    void visitIf(If *p) {
      p->visit_children(this);
      p->m_attribute.m_type.mbaseType = bt_boolean;

      if(p->m_expression->m_attribute.m_type.baseType != 2 || p->m_statement->m_attribute.m_type.baseType !=2)
          t_error(if_pred_err, p->m_attribute);

      //WRITE ME
    }
    
    void visitPrint(Print *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitReturnImpl(ReturnImpl *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitTInteger(TInteger *p) {
      p->m_attribute.m_type.baseType = bt_integer;

      p->visit_children(this);
      //WRITE ME
    }
    
    void visitTBoolean(TBoolean *p) {
      p->m_attribute.m_type.baseType = bt_boolean;

      p->visit_children(this);
      //WRITE ME
    }
    
    void visitTNothing(TNothing *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitTObject(TObject *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitClassIDImpl(ClassIDImpl *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitVariableIDImpl(VariableIDImpl *p) {

      p->visit_children(this);
      //WRITE ME
    }
    
    void visitMethodIDImpl(MethodIDImpl *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitPlus(Plus *p) {
      p->m_attribute.m_type.baseType = bt_integer;
      p->visit_children(this);
      if(p->m_expression_1->m_attribute.m_type.baseType != 1)
        t_error(expr_type_err, p->m_expression_1->m_attribute);
      if(p->m_expression_2->m_attribute.m_type.baseType != 1)
        t_error(expr_type_err, p->m_expression_2->m_attribute);

      //WRITE ME
    }
    
    void visitMinus(Minus *p) {
      p->m_attribute.m_type.baseType = bt_integer;
      p->visit_children(this);
      if(p->m_expression_1->m_attribute.m_type.baseType != 1)
        t_error(expr_type_err, p->m_expression_1->m_attribute);
      if(p->m_expression_2->m_attribute.m_type.baseType != 1)
        t_error(expr_type_err, p->m_expression_2->m_attribute);      

        //WRITE ME
    }
    
    void visitTimes(Times *p) {
      p->m_attribute.m_type.baseType = bt_integer;
      p->visit_children(this);
      if(p->m_expression_1->m_attribute.m_type.baseType != 1)
        t_error(expr_type_err, p->m_expression_1->m_attribute);
      if(p->m_expression_2->m_attribute.m_type.baseType != 1)
        t_error(expr_type_err, p->m_expression_2->m_attribute); 
              //WRITE ME
    }
    
    void visitDivide(Divide *p) {
      p->m_attribute.m_type.baseType = bt_integer;
      p->visit_children(this);
      if(p->m_expression_1->m_attribute.m_type.baseType != 1)
        t_error(expr_type_err, p->m_expression_1->m_attribute);
      if(p->m_expression_2->m_attribute.m_type.baseType != 1)
        t_error(expr_type_err, p->m_expression_2->m_attribute); 
              //WRITE ME
    }
    
    void visitAnd(And *p) {
      p->m_attribute.m_type.baseType = bt_boolean;
      p->visit_children(this);
      if(p->m_expression_1->m_attribute.m_type.baseType != 2)
        t_error(expr_type_err, p->m_expression_1->m_attribute);
       if(p->m_expression_2->m_attribute.m_type.baseType != 2)
        t_error(expr_type_err, p->m_expression_2->m_attribute); 
              //WRITE ME      //WRITE ME
    }
    
    void visitLessThan(LessThan *p) {
      p->m_attribute.m_type.baseType = bt_boolean;
      p->visit_children(this);
      if(p->m_expression_1->m_attribute.m_type.baseType != 1)
         t_error(expr_type_err, p->m_expression_1->m_attribute);
      if(p->m_expression_2->m_attribute.m_type.baseType != 1)
         t_error(expr_type_err, p->m_expression_2->m_attribute); 
              //WRITE ME
    }
    
    void visitLessThanEqualTo(LessThanEqualTo *p) {
      p->m_attribute.m_type.baseType = bt_boolean;
      p->visit_children(this);
      if(p->m_expression_1->m_attribute.m_type.baseType != 1)
          t_error(expr_type_err, p->m_expression_1->m_attribute);
      if(p->m_expression_2->m_attribute.m_type.baseType != 1)
          t_error(expr_type_err, p->m_expression_2->m_attribute); 
              //WRITE ME
    }
    
    void visitNot(Not *p) {
      p->m_attribute.m_type.baseType = bt_boolean;
      p->visit_children(this);
      if(p->m_expression->m_attribute.m_type.baseType != 2)
        t_error(expr_type_err, p->m_expression->m_attribute);
    }
    
    void visitUnaryMinus(UnaryMinus *p) {
      p->m_attribute.m_type.baseType = bt_integer;
      p->visit_children(this);
      if(p->m_expression->m_attribute.m_type.baseType != 1)
        t_error(expr_type_err, p->m_expression->m_attribute);
    }
    
    void visitMethodCall(MethodCall *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitSelfCall(SelfCall *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitVariable(Variable *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitIntegerLiteral(IntegerLiteral *p) {
      p->m_attribute.m_type.baseType = bt_integer;
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitBooleanLiteral(BooleanLiteral *p) {
      p->m_attribute.m_type.baseType = bt_boolean;
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitNothing(Nothing *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitSymName(SymName *p) {
    //  cout<<"declaration bottom TYPE: "<<p->m_parent_attribute->m_type.baseType<<endl;

      // if(m_symboltable->exist(p->spelling())){
      //     cout<<"figure out how to access teh attribute for this duplicate name error: "<<p->spelling()<<endl;
      //   }
      // else{
      //   m_symboltable->insert(p->spelling(),symp);
      // }
      //WRITE ME
    }
    
    void visitPrimitive(Primitive *p) {
      // p->m_parent_attribute->m_type.baseType = bt_integer;

      //WRITE ME
    }
    
    void visitClassName(ClassName *p) {

      //WRITE ME
    }
    
    
    void visitNullPointer() {}
};
