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


    void printSymTab(){
      FILE * pFile;
      pFile = fopen ("myfile.txt" , "w");
      m_symboltable->dump(pFile);
      fclose (pFile);
      }

    void visitProgramImpl(ProgramImpl *p) {
      p->visit_children(this);
      printSymTab();

     //WRITE ME
    }
    
    void visitClassImpl(ClassImpl *p) {
      m_symboltable->open_scope();
      p->visit_children(this);
      ClassNode * clasp = new ClassNode;
      Symbol * symp = new Symbol;
      ClassIDImpl * ClassIdP = dynamic_cast<ClassIDImpl*>(p->m_classid_1);
      char * key = strdup(ClassIdP->m_classname->spelling());
      if(m_classtable->exist(key)){
        t_error(dup_ident_name, p->m_attribute);
      }
      else{
        cout<< "instered this in class table: "<< key<<endl;
        m_classtable->insert(key,NULL, p,  m_symboltable->get_scope());

      }
     // DeclarationImpl * Dimp = dynamic_cast<DeclarationImpl *> (*it);
      //  typename std::list<Declaration_ptr>::iterator it = p->m_declaration_list->begin();
      //  for( ; it != p->m_declaration_list->end(); ++it) {
      //     DeclarationImpl * Dimp = dynamic_cast<DeclarationImpl*>(*it);
      //     typename std::list<VariableID_ptr>::iterator it2 = Dimp->m_variableid_list->begin();
      //     for( ; it2 != Dimp->m_variableid_list->end(); ++it2) {

      //     VariableIDImpl * VarIdP = dynamic_cast<VariableIDImpl*>(*it2);
      //     char * key = strdup(VarIdP->m_symname->spelling());
      //     if(m_symboltable->exist(key)){
      //       cout<<"key ; "<<key<<endl;
      //       t_error(dup_ident_name, Dimp->m_attribute);
      //     }
      //     else{
      //       symp->baseType = Dimp->m_attribute.m_type.baseType;
      //       cout<< "class; key: "<< key <<" type : "<< symp->baseType<<endl;

      //       m_symboltable->insert(key, symp);
      //     }
      // }
      // }

      m_symboltable->close_scope();
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
            symp->baseType = p->m_type->m_attribute.m_type.baseType;
            if(symp->baseType == 8){
            // ClassIDImpl * ClassIdP = dynamic_cast<ClassIDImpl*>(*it);

            //   char * key2 = strdup(ClassIdP->m_classname->spelling());
            //   symp->classType.classID = key2;
              symp->classType.classID = p->m_type->m_attribute.m_type.classType.classID;

              //cout<< "this is what i'm SEETTTING: " << symp->classType.classID<<endl;

            }
          //  cout<< "Decla; key: "<< key <<" type : "<< symp->baseType<<endl;

            m_symboltable->insert(key, symp);
          }
      }//forloop      //cout<<"declaration TYPE: "<<p->m_type->m_attribute.m_type.baseType<<endl;
      //WRITE ME
    }
    
    void visitMethodImpl(MethodImpl *p) {
     m_symboltable->open_scope();
      p->visit_children(this);
      Symbol *symp = new Symbol;
      Symbol *Msymp = new Symbol;
      MethodIDImpl * MethIdP = dynamic_cast<MethodIDImpl*>(p->m_methodid);

      p->m_attribute.m_type.baseType = p->m_type->m_attribute.m_type.baseType;
//this is dealing with duplicate method names
      char * key = strdup(MethIdP->m_symname->spelling());
          if(m_symboltable->exist(key))
            t_error(dup_ident_name, p->m_attribute);
          else{
            Msymp->methodType.returnType.baseType = p->m_type->m_attribute.m_type.baseType;
            Msymp->baseType = p->m_type->m_attribute.m_type.baseType;
            //cout<< "meth; key: "<< key <<" type : "<< Msymp->methodType.returnType.baseType<<endl;
            m_symboltable->insert_in_parent_scope(key, Msymp);
          }

      CompoundType arg;
      MethodBodyImpl * MethBodP = dynamic_cast<MethodBodyImpl*>(p->m_methodbody);
      ReturnImpl * RetP = dynamic_cast<ReturnImpl*>(MethBodP->m_return);

//Adding parameters to sym table and each argument to method vector
       typename std::list<Parameter_ptr>::iterator it = p->m_parameter_list->begin();
       for( ; it != p->m_parameter_list->end(); ++it) {
          ParameterImpl * Pimp = dynamic_cast<ParameterImpl *> (*it);
          VariableIDImpl * VarIdP = dynamic_cast<VariableIDImpl*>(Pimp->m_variableid);
          char * key = strdup(VarIdP->m_symname->spelling());

            arg.baseType = Pimp->m_type->m_attribute.m_type.baseType;
            Msymp->methodType.argsType.push_back(arg);
      

}
//This Check the return type mismatch  
      if(p->m_type->m_attribute.m_type.baseType != RetP->m_expression->m_attribute.m_type.baseType){
          t_error(ret_type_mismatch, p->m_attribute);

      }
      m_symboltable->close_scope();


      //WRITE ME
    }
    
    void visitMethodBodyImpl(MethodBodyImpl *p) {
      p->visit_children(this);






      //WRITE ME
    }
    
    void visitParameterImpl(ParameterImpl *p) {
      p->visit_children(this);
      Symbol *symp = new Symbol;




      VariableIDImpl * VarIdP = dynamic_cast<VariableIDImpl*>(p->m_variableid);

      char * key = strdup(VarIdP->m_symname->spelling());
        if(m_symboltable->exist(key))
            t_error(dup_ident_name, p->m_attribute);
        else{
            symp->baseType = p->m_type->m_attribute.m_type.baseType;
        //    cout<< "param; key: "<< key <<" type : "<< symp->baseType<<endl;
            if(symp->baseType == 8){
              symp->classType.classID = p->m_type->m_attribute.m_type.classType.classID;
        //      cout<< "this is what i'm SEETTTING key: " << symp->classType.classID<<endl;

            }
            m_symboltable->insert(key, symp);
          }      

      //WRITE ME
    }
    
    void visitAssignment(Assignment *p) {
     p->visit_children(this);
     string str1, str2;
     Symbol * symp;
      VariableIDImpl * VarIdP = dynamic_cast<VariableIDImpl*>(p->m_variableid);
      char * key = strdup(VarIdP->m_symname->spelling());

       symp = m_symboltable->lookup(key);
      if(m_symboltable->exist(key)){
        if(p->m_expression->m_attribute.m_type.baseType == 8){
          if(p->m_expression->m_attribute.m_type.baseType == 8 && symp->baseType == 8){

          std::string temp1(p->m_expression->m_attribute.m_type.classType.classID);
          std::string temp2(symp->classType.classID);
cout<<"temp1 "<<temp1<<endl;
cout<<"temp2 "<<temp2<<endl;
          if(temp1!= temp2){
            t_error(incompat_assign, p->m_attribute);
          }
          if(p->m_expression->m_attribute.m_type.methodType.returnType.baseType != symp->baseType){
            t_error(incompat_assign, p->m_attribute);

          }
       } 
        }
        if(p->m_expression->m_attribute.m_type.baseType != 8 && p->m_expression->m_attribute.m_type.baseType != symp->baseType){
          cout<<"here ou"<<endl;
          // cout<<p->m_expression->m_attribute.m_type.methodType.returnType.classID<<endl;
          // cout<<symp->baseType<<endl;
          t_error(incompat_assign, p->m_attribute);
      }
        }     
      else
         t_error(sym_name_undef, p->m_attribute);

      //WRITE ME
    }
    
    void visitIf(If *p) {
      p->visit_children(this);
      p->m_attribute.m_type.baseType = p->m_statement->m_attribute.m_type.baseType;

      if(p->m_expression->m_attribute.m_type.baseType != 2){
          t_error(if_pred_err, p->m_attribute);
}
      //WRITE ME
    }
    
    void visitPrint(Print *p) {
      p->visit_children(this);
      //WRITE ME
    }
    
    void visitReturnImpl(ReturnImpl *p) {
      p->visit_children(this);
     //p->m_attribute.m_type.methodType.returnType.baseType = p->m_expression->m_attribute.m_type.baseType;
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
      p->m_attribute.m_type.baseType = bt_object;
      p->visit_children(this);
      ClassIDImpl * ClassIdP = dynamic_cast<ClassIDImpl*>(p->m_classid);
      char *name = strdup(ClassIdP->m_classname->spelling());
      p->m_attribute.m_type.classType.classID = name;
      ClassNode * classptr;
      if(!m_classtable->exist(name))
        t_error(sym_name_undef, p->m_attribute);


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
      Symbol* symp;
      ClassNode * clasp;
      Basetype bargs;
      int i =0;
     // SymScope * sync;
      VariableIDImpl * VarIdP = dynamic_cast<VariableIDImpl*>(p->m_variableid);
      MethodIDImpl * MethIdP = dynamic_cast<MethodIDImpl*>(p->m_methodid);
      char * meth = strdup(MethIdP->m_symname->spelling());
     // Basetype bargs;
      char * var = strdup(VarIdP->m_symname->spelling());
      cout<<"the var : "<<var<<endl;
      if( !m_symboltable->exist(var)){//if symbol not defined within class
              t_error(sym_name_undef, p->m_attribute);
}
        symp = m_symboltable->lookup(var);
        char *name = strdup(symp->classType.classID);
          clasp = m_classtable->lookup(name);
          cout<<name<<endl;
          if(!m_classtable->exist(name)){
            t_error(sym_name_undef,p->m_attribute);
          }
          SymScope *sync = clasp->scope;
          //cout<<"1"<<endl;
         //sync = m_symboltable->get_current_scope();
          symp = sync->lookup(meth);
          if(sync->lookup(meth) == NULL){
            cout<<"obviously doesn't exist"<<endl;
            t_error(no_class_method, p->m_attribute);
          }
        if(p->m_expression_list->size()!= symp->methodType.argsType.size() )
          t_error(call_args_mismatch,p->m_attribute);
     
      typename std::list<Expression_ptr>::iterator it = p->m_expression_list->begin();
       for( ; it != p->m_expression_list->end(); ++it) {
        Expression * Expoin = dynamic_cast<Expression *> (*it);
           bargs = symp->methodType.argsType[i].baseType;
         if(bargs != Expoin->m_attribute.m_type.baseType)
            t_error(call_args_mismatch, p->m_attribute);
        i++;
        }     

      cout<<"SYMPP    type "<<symp->methodType.returnType.baseType<<endl;


      p->m_attribute.m_type.baseType = symp->methodType.returnType.baseType;
      p->m_attribute.m_type.methodType.returnType.baseType = symp->methodType.returnType.baseType;


      //WRITE ME
    }
    
    void visitSelfCall(SelfCall *p) {
      p->visit_children(this);
      Symbol * symp;
      MethodIDImpl * MethIdP = dynamic_cast<MethodIDImpl*>(p->m_methodid);
      Basetype bargs;
      char * key = strdup(MethIdP->m_symname->spelling());
      symp = m_symboltable->lookup(key);
      std::vector<CompoundType> args;
      args = symp->methodType.argsType;
      int i = 0;
      if(args.size() != p->m_expression_list->size()){
          t_error(call_narg_mismatch, p->m_attribute);
}

      typename std::list<Expression_ptr>::iterator it = p->m_expression_list->begin();
       for( ; it != p->m_expression_list->end(); ++it) {
        Expression * Expoin = dynamic_cast<Expression *> (*it);
        //ParameterImpl * Pimp = p->m_expression_list->front();
       // Expression * lop = p->m_expression_list->front();
         bargs = symp->methodType.argsType[i].baseType;
         if(bargs != Expoin->m_attribute.m_type.baseType)
            t_error(call_args_mismatch, p->m_attribute);
        i++;
        }


      p->m_attribute.m_type.baseType = symp->baseType;

      //WRITE ME
    }
    
    void visitVariable(Variable *p) {
      p->visit_children(this);
     Symbol * symp;
    VariableIDImpl * VarIdP = dynamic_cast<VariableIDImpl*>(p->m_variableid);
    char * key = strdup(VarIdP->m_symname->spelling());

    symp = m_symboltable->lookup(key);


    p->m_attribute.m_type.baseType = symp -> baseType;
    if(symp->baseType == 8)
      p->m_attribute.m_type.classType.classID = symp->classType.classID;

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
