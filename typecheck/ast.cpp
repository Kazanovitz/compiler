//Automatically Generated C++ Abstract Syntax Tree Class Hierarchy

#include <algorithm>
#include "ast.hpp"
extern int yylineno;
#include "symtab.hpp"
#include "primitive.hpp"
#include "classhierarchy.hpp"



/********* ProgramImpl ************/
 ProgramImpl::ProgramImpl(list<Class_ptr> *p1)  {
	m_class_list = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_class_list != NULL) {
	  list<Class_ptr>::iterator m_class_list_iter;
	  for(m_class_list_iter = m_class_list->begin();
	    m_class_list_iter != m_class_list->end();
	    ++m_class_list_iter){
		  if(*m_class_list_iter != NULL) {
		    (*m_class_list_iter)->m_parent_attribute = &m_attribute;
		  }
	  }
	}
 }
 ProgramImpl::ProgramImpl(const ProgramImpl & other) {
	if (m_class_list != NULL) {
	  m_class_list = new list<Class_ptr>;
	  list<Class_ptr>::iterator m_class_list_iter;
	  for(m_class_list_iter = other.m_class_list->begin();
	    m_class_list_iter != other.m_class_list->end();
	    ++m_class_list_iter){
		  m_class_list->push_back( (*m_class_list_iter)->clone() );
	  }
	}
 }
 ProgramImpl &ProgramImpl::operator=(const ProgramImpl & other) { ProgramImpl tmp(other); swap(tmp); return *this; }
 void ProgramImpl::swap(ProgramImpl & other) {
	std::swap(m_class_list, other.m_class_list);
 }
 ProgramImpl::~ProgramImpl() {
 	if (m_class_list != NULL) {
	  list<Class_ptr>::iterator m_class_list_iter;
	  for(m_class_list_iter = m_class_list->begin();
	    m_class_list_iter != m_class_list->end();
	    ++m_class_list_iter){
		  delete( *m_class_list_iter );
	  }
	}
 }
 void ProgramImpl::visit_children( Visitor* v ) {
 	if (m_class_list != NULL) {
	  list<Class_ptr>::iterator m_class_list_iter;
	  for(m_class_list_iter = m_class_list->begin();
	    m_class_list_iter != m_class_list->end();
	    ++m_class_list_iter){
		  if(*m_class_list_iter != NULL) {
		    (*m_class_list_iter)->accept( v );
		  } else {
		    v->visitNullPointer();
		  }
	  }
	} else {
		v->visitNullPointer();
	}
 }
 void ProgramImpl::accept(Visitor *v) { v->visitProgramImpl(this); }
 ProgramImpl *ProgramImpl::clone() const { return new ProgramImpl(*this); }
 
 
/********* ClassImpl ************/
 ClassImpl::ClassImpl(ClassID *p1, ClassID *p2, list<Declaration_ptr> *p3, list<Method_ptr> *p4)  {
	m_classid_1 = p1;
	m_classid_2 = p2;
	m_declaration_list = p3;
	m_method_list = p4;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_classid_1 != NULL) {
	  m_classid_1->m_parent_attribute = &m_attribute;
 	}
	if (m_classid_2 != NULL) {
	  m_classid_2->m_parent_attribute = &m_attribute;
 	}
	if (m_declaration_list != NULL) {
	  list<Declaration_ptr>::iterator m_declaration_list_iter;
	  for(m_declaration_list_iter = m_declaration_list->begin();
	    m_declaration_list_iter != m_declaration_list->end();
	    ++m_declaration_list_iter){
		  if(*m_declaration_list_iter != NULL) {
		    (*m_declaration_list_iter)->m_parent_attribute = &m_attribute;
		  }
	  }
	}
	if (m_method_list != NULL) {
	  list<Method_ptr>::iterator m_method_list_iter;
	  for(m_method_list_iter = m_method_list->begin();
	    m_method_list_iter != m_method_list->end();
	    ++m_method_list_iter){
		  if(*m_method_list_iter != NULL) {
		    (*m_method_list_iter)->m_parent_attribute = &m_attribute;
		  }
	  }
	}
 }
 ClassImpl::ClassImpl(const ClassImpl & other) {
	if (m_classid_1 != NULL) {
	  m_classid_1 = other.m_classid_1->clone();
	}
	if (m_classid_2 != NULL) {
	  m_classid_2 = other.m_classid_2->clone();
	}
	if (m_declaration_list != NULL) {
	  m_declaration_list = new list<Declaration_ptr>;
	  list<Declaration_ptr>::iterator m_declaration_list_iter;
	  for(m_declaration_list_iter = other.m_declaration_list->begin();
	    m_declaration_list_iter != other.m_declaration_list->end();
	    ++m_declaration_list_iter){
		  m_declaration_list->push_back( (*m_declaration_list_iter)->clone() );
	  }
	}
	if (m_method_list != NULL) {
	  m_method_list = new list<Method_ptr>;
	  list<Method_ptr>::iterator m_method_list_iter;
	  for(m_method_list_iter = other.m_method_list->begin();
	    m_method_list_iter != other.m_method_list->end();
	    ++m_method_list_iter){
		  m_method_list->push_back( (*m_method_list_iter)->clone() );
	  }
	}
 }
 ClassImpl &ClassImpl::operator=(const ClassImpl & other) { ClassImpl tmp(other); swap(tmp); return *this; }
 void ClassImpl::swap(ClassImpl & other) {
	std::swap(m_classid_1, other.m_classid_1);
	std::swap(m_classid_2, other.m_classid_2);
	std::swap(m_declaration_list, other.m_declaration_list);
	std::swap(m_method_list, other.m_method_list);
 }
 ClassImpl::~ClassImpl() {
 	if (m_classid_1 != NULL) {
	  delete(m_classid_1);
 	}
	if (m_classid_2 != NULL) {
	  delete(m_classid_2);
 	}
	if (m_declaration_list != NULL) {
	  list<Declaration_ptr>::iterator m_declaration_list_iter;
	  for(m_declaration_list_iter = m_declaration_list->begin();
	    m_declaration_list_iter != m_declaration_list->end();
	    ++m_declaration_list_iter){
		  delete( *m_declaration_list_iter );
	  }
	}
	if (m_method_list != NULL) {
	  list<Method_ptr>::iterator m_method_list_iter;
	  for(m_method_list_iter = m_method_list->begin();
	    m_method_list_iter != m_method_list->end();
	    ++m_method_list_iter){
		  delete( *m_method_list_iter );
	  }
	}
 }
 void ClassImpl::visit_children( Visitor* v ) {
 	if (m_classid_1 != NULL) {
	  m_classid_1->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_classid_2 != NULL) {
	  m_classid_2->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_declaration_list != NULL) {
	  list<Declaration_ptr>::iterator m_declaration_list_iter;
	  for(m_declaration_list_iter = m_declaration_list->begin();
	    m_declaration_list_iter != m_declaration_list->end();
	    ++m_declaration_list_iter){
		  if(*m_declaration_list_iter != NULL) {
		    (*m_declaration_list_iter)->accept( v );
		  } else {
		    v->visitNullPointer();
		  }
	  }
	} else {
		v->visitNullPointer();
	}
	if (m_method_list != NULL) {
	  list<Method_ptr>::iterator m_method_list_iter;
	  for(m_method_list_iter = m_method_list->begin();
	    m_method_list_iter != m_method_list->end();
	    ++m_method_list_iter){
		  if(*m_method_list_iter != NULL) {
		    (*m_method_list_iter)->accept( v );
		  } else {
		    v->visitNullPointer();
		  }
	  }
	} else {
		v->visitNullPointer();
	}
 }
 void ClassImpl::accept(Visitor *v) { v->visitClassImpl(this); }
 ClassImpl *ClassImpl::clone() const { return new ClassImpl(*this); }
 
 
/********* DeclarationImpl ************/
 DeclarationImpl::DeclarationImpl(list<VariableID_ptr> *p1, Type *p2)  {
	m_variableid_list = p1;
	m_type = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_variableid_list != NULL) {
	  list<VariableID_ptr>::iterator m_variableid_list_iter;
	  for(m_variableid_list_iter = m_variableid_list->begin();
	    m_variableid_list_iter != m_variableid_list->end();
	    ++m_variableid_list_iter){
		  if(*m_variableid_list_iter != NULL) {
		    (*m_variableid_list_iter)->m_parent_attribute = &m_attribute;
		  }
	  }
	}
	if (m_type != NULL) {
	  m_type->m_parent_attribute = &m_attribute;
 	}
 }
 DeclarationImpl::DeclarationImpl(const DeclarationImpl & other) {
	if (m_variableid_list != NULL) {
	  m_variableid_list = new list<VariableID_ptr>;
	  list<VariableID_ptr>::iterator m_variableid_list_iter;
	  for(m_variableid_list_iter = other.m_variableid_list->begin();
	    m_variableid_list_iter != other.m_variableid_list->end();
	    ++m_variableid_list_iter){
		  m_variableid_list->push_back( (*m_variableid_list_iter)->clone() );
	  }
	}
	if (m_type != NULL) {
	  m_type = other.m_type->clone();
	}
 }
 DeclarationImpl &DeclarationImpl::operator=(const DeclarationImpl & other) { DeclarationImpl tmp(other); swap(tmp); return *this; }
 void DeclarationImpl::swap(DeclarationImpl & other) {
	std::swap(m_variableid_list, other.m_variableid_list);
	std::swap(m_type, other.m_type);
 }
 DeclarationImpl::~DeclarationImpl() {
 	if (m_variableid_list != NULL) {
	  list<VariableID_ptr>::iterator m_variableid_list_iter;
	  for(m_variableid_list_iter = m_variableid_list->begin();
	    m_variableid_list_iter != m_variableid_list->end();
	    ++m_variableid_list_iter){
		  delete( *m_variableid_list_iter );
	  }
	}
	if (m_type != NULL) {
	  delete(m_type);
 	}
 }
 void DeclarationImpl::visit_children( Visitor* v ) {
 	if (m_variableid_list != NULL) {
	  list<VariableID_ptr>::iterator m_variableid_list_iter;
	  for(m_variableid_list_iter = m_variableid_list->begin();
	    m_variableid_list_iter != m_variableid_list->end();
	    ++m_variableid_list_iter){
		  if(*m_variableid_list_iter != NULL) {
		    (*m_variableid_list_iter)->accept( v );
		  } else {
		    v->visitNullPointer();
		  }
	  }
	} else {
		v->visitNullPointer();
	}
	if (m_type != NULL) {
	  m_type->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void DeclarationImpl::accept(Visitor *v) { v->visitDeclarationImpl(this); }
 DeclarationImpl *DeclarationImpl::clone() const { return new DeclarationImpl(*this); }
 
 
/********* MethodImpl ************/
 MethodImpl::MethodImpl(MethodID *p1, list<Parameter_ptr> *p2, Type *p3, MethodBody *p4)  {
	m_methodid = p1;
	m_parameter_list = p2;
	m_type = p3;
	m_methodbody = p4;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_methodid != NULL) {
	  m_methodid->m_parent_attribute = &m_attribute;
 	}
	if (m_parameter_list != NULL) {
	  list<Parameter_ptr>::iterator m_parameter_list_iter;
	  for(m_parameter_list_iter = m_parameter_list->begin();
	    m_parameter_list_iter != m_parameter_list->end();
	    ++m_parameter_list_iter){
		  if(*m_parameter_list_iter != NULL) {
		    (*m_parameter_list_iter)->m_parent_attribute = &m_attribute;
		  }
	  }
	}
	if (m_type != NULL) {
	  m_type->m_parent_attribute = &m_attribute;
 	}
	if (m_methodbody != NULL) {
	  m_methodbody->m_parent_attribute = &m_attribute;
 	}
 }
 MethodImpl::MethodImpl(const MethodImpl & other) {
	if (m_methodid != NULL) {
	  m_methodid = other.m_methodid->clone();
	}
	if (m_parameter_list != NULL) {
	  m_parameter_list = new list<Parameter_ptr>;
	  list<Parameter_ptr>::iterator m_parameter_list_iter;
	  for(m_parameter_list_iter = other.m_parameter_list->begin();
	    m_parameter_list_iter != other.m_parameter_list->end();
	    ++m_parameter_list_iter){
		  m_parameter_list->push_back( (*m_parameter_list_iter)->clone() );
	  }
	}
	if (m_type != NULL) {
	  m_type = other.m_type->clone();
	}
	if (m_methodbody != NULL) {
	  m_methodbody = other.m_methodbody->clone();
	}
 }
 MethodImpl &MethodImpl::operator=(const MethodImpl & other) { MethodImpl tmp(other); swap(tmp); return *this; }
 void MethodImpl::swap(MethodImpl & other) {
	std::swap(m_methodid, other.m_methodid);
	std::swap(m_parameter_list, other.m_parameter_list);
	std::swap(m_type, other.m_type);
	std::swap(m_methodbody, other.m_methodbody);
 }
 MethodImpl::~MethodImpl() {
 	if (m_methodid != NULL) {
	  delete(m_methodid);
 	}
	if (m_parameter_list != NULL) {
	  list<Parameter_ptr>::iterator m_parameter_list_iter;
	  for(m_parameter_list_iter = m_parameter_list->begin();
	    m_parameter_list_iter != m_parameter_list->end();
	    ++m_parameter_list_iter){
		  delete( *m_parameter_list_iter );
	  }
	}
	if (m_type != NULL) {
	  delete(m_type);
 	}
	if (m_methodbody != NULL) {
	  delete(m_methodbody);
 	}
 }
 void MethodImpl::visit_children( Visitor* v ) {
 	if (m_methodid != NULL) {
	  m_methodid->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_parameter_list != NULL) {
	  list<Parameter_ptr>::iterator m_parameter_list_iter;
	  for(m_parameter_list_iter = m_parameter_list->begin();
	    m_parameter_list_iter != m_parameter_list->end();
	    ++m_parameter_list_iter){
		  if(*m_parameter_list_iter != NULL) {
		    (*m_parameter_list_iter)->accept( v );
		  } else {
		    v->visitNullPointer();
		  }
	  }
	} else {
		v->visitNullPointer();
	}
	if (m_type != NULL) {
	  m_type->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_methodbody != NULL) {
	  m_methodbody->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void MethodImpl::accept(Visitor *v) { v->visitMethodImpl(this); }
 MethodImpl *MethodImpl::clone() const { return new MethodImpl(*this); }
 
 
/********* MethodBodyImpl ************/
 MethodBodyImpl::MethodBodyImpl(list<Declaration_ptr> *p1, list<Statement_ptr> *p2, Return *p3)  {
	m_declaration_list = p1;
	m_statement_list = p2;
	m_return = p3;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_declaration_list != NULL) {
	  list<Declaration_ptr>::iterator m_declaration_list_iter;
	  for(m_declaration_list_iter = m_declaration_list->begin();
	    m_declaration_list_iter != m_declaration_list->end();
	    ++m_declaration_list_iter){
		  if(*m_declaration_list_iter != NULL) {
		    (*m_declaration_list_iter)->m_parent_attribute = &m_attribute;
		  }
	  }
	}
	if (m_statement_list != NULL) {
	  list<Statement_ptr>::iterator m_statement_list_iter;
	  for(m_statement_list_iter = m_statement_list->begin();
	    m_statement_list_iter != m_statement_list->end();
	    ++m_statement_list_iter){
		  if(*m_statement_list_iter != NULL) {
		    (*m_statement_list_iter)->m_parent_attribute = &m_attribute;
		  }
	  }
	}
	if (m_return != NULL) {
	  m_return->m_parent_attribute = &m_attribute;
 	}
 }
 MethodBodyImpl::MethodBodyImpl(const MethodBodyImpl & other) {
	if (m_declaration_list != NULL) {
	  m_declaration_list = new list<Declaration_ptr>;
	  list<Declaration_ptr>::iterator m_declaration_list_iter;
	  for(m_declaration_list_iter = other.m_declaration_list->begin();
	    m_declaration_list_iter != other.m_declaration_list->end();
	    ++m_declaration_list_iter){
		  m_declaration_list->push_back( (*m_declaration_list_iter)->clone() );
	  }
	}
	if (m_statement_list != NULL) {
	  m_statement_list = new list<Statement_ptr>;
	  list<Statement_ptr>::iterator m_statement_list_iter;
	  for(m_statement_list_iter = other.m_statement_list->begin();
	    m_statement_list_iter != other.m_statement_list->end();
	    ++m_statement_list_iter){
		  m_statement_list->push_back( (*m_statement_list_iter)->clone() );
	  }
	}
	if (m_return != NULL) {
	  m_return = other.m_return->clone();
	}
 }
 MethodBodyImpl &MethodBodyImpl::operator=(const MethodBodyImpl & other) { MethodBodyImpl tmp(other); swap(tmp); return *this; }
 void MethodBodyImpl::swap(MethodBodyImpl & other) {
	std::swap(m_declaration_list, other.m_declaration_list);
	std::swap(m_statement_list, other.m_statement_list);
	std::swap(m_return, other.m_return);
 }
 MethodBodyImpl::~MethodBodyImpl() {
 	if (m_declaration_list != NULL) {
	  list<Declaration_ptr>::iterator m_declaration_list_iter;
	  for(m_declaration_list_iter = m_declaration_list->begin();
	    m_declaration_list_iter != m_declaration_list->end();
	    ++m_declaration_list_iter){
		  delete( *m_declaration_list_iter );
	  }
	}
	if (m_statement_list != NULL) {
	  list<Statement_ptr>::iterator m_statement_list_iter;
	  for(m_statement_list_iter = m_statement_list->begin();
	    m_statement_list_iter != m_statement_list->end();
	    ++m_statement_list_iter){
		  delete( *m_statement_list_iter );
	  }
	}
	if (m_return != NULL) {
	  delete(m_return);
 	}
 }
 void MethodBodyImpl::visit_children( Visitor* v ) {
 	if (m_declaration_list != NULL) {
	  list<Declaration_ptr>::iterator m_declaration_list_iter;
	  for(m_declaration_list_iter = m_declaration_list->begin();
	    m_declaration_list_iter != m_declaration_list->end();
	    ++m_declaration_list_iter){
		  if(*m_declaration_list_iter != NULL) {
		    (*m_declaration_list_iter)->accept( v );
		  } else {
		    v->visitNullPointer();
		  }
	  }
	} else {
		v->visitNullPointer();
	}
	if (m_statement_list != NULL) {
	  list<Statement_ptr>::iterator m_statement_list_iter;
	  for(m_statement_list_iter = m_statement_list->begin();
	    m_statement_list_iter != m_statement_list->end();
	    ++m_statement_list_iter){
		  if(*m_statement_list_iter != NULL) {
		    (*m_statement_list_iter)->accept( v );
		  } else {
		    v->visitNullPointer();
		  }
	  }
	} else {
		v->visitNullPointer();
	}
	if (m_return != NULL) {
	  m_return->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void MethodBodyImpl::accept(Visitor *v) { v->visitMethodBodyImpl(this); }
 MethodBodyImpl *MethodBodyImpl::clone() const { return new MethodBodyImpl(*this); }
 
 
/********* ParameterImpl ************/
 ParameterImpl::ParameterImpl(VariableID *p1, Type *p2)  {
	m_variableid = p1;
	m_type = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_variableid != NULL) {
	  m_variableid->m_parent_attribute = &m_attribute;
 	}
	if (m_type != NULL) {
	  m_type->m_parent_attribute = &m_attribute;
 	}
 }
 ParameterImpl::ParameterImpl(const ParameterImpl & other) {
	if (m_variableid != NULL) {
	  m_variableid = other.m_variableid->clone();
	}
	if (m_type != NULL) {
	  m_type = other.m_type->clone();
	}
 }
 ParameterImpl &ParameterImpl::operator=(const ParameterImpl & other) { ParameterImpl tmp(other); swap(tmp); return *this; }
 void ParameterImpl::swap(ParameterImpl & other) {
	std::swap(m_variableid, other.m_variableid);
	std::swap(m_type, other.m_type);
 }
 ParameterImpl::~ParameterImpl() {
 	if (m_variableid != NULL) {
	  delete(m_variableid);
 	}
	if (m_type != NULL) {
	  delete(m_type);
 	}
 }
 void ParameterImpl::visit_children( Visitor* v ) {
 	if (m_variableid != NULL) {
	  m_variableid->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_type != NULL) {
	  m_type->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void ParameterImpl::accept(Visitor *v) { v->visitParameterImpl(this); }
 ParameterImpl *ParameterImpl::clone() const { return new ParameterImpl(*this); }
 
 
/********* Assignment ************/
 Assignment::Assignment(VariableID *p1, Expression *p2)  {
	m_variableid = p1;
	m_expression = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_variableid != NULL) {
	  m_variableid->m_parent_attribute = &m_attribute;
 	}
	if (m_expression != NULL) {
	  m_expression->m_parent_attribute = &m_attribute;
 	}
 }
 Assignment::Assignment(const Assignment & other) {
	if (m_variableid != NULL) {
	  m_variableid = other.m_variableid->clone();
	}
	if (m_expression != NULL) {
	  m_expression = other.m_expression->clone();
	}
 }
 Assignment &Assignment::operator=(const Assignment & other) { Assignment tmp(other); swap(tmp); return *this; }
 void Assignment::swap(Assignment & other) {
	std::swap(m_variableid, other.m_variableid);
	std::swap(m_expression, other.m_expression);
 }
 Assignment::~Assignment() {
 	if (m_variableid != NULL) {
	  delete(m_variableid);
 	}
	if (m_expression != NULL) {
	  delete(m_expression);
 	}
 }
 void Assignment::visit_children( Visitor* v ) {
 	if (m_variableid != NULL) {
	  m_variableid->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression != NULL) {
	  m_expression->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void Assignment::accept(Visitor *v) { v->visitAssignment(this); }
 Assignment *Assignment::clone() const { return new Assignment(*this); }
 
 
/********* If ************/
 If::If(Expression *p1, Statement *p2)  {
	m_expression = p1;
	m_statement = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression != NULL) {
	  m_expression->m_parent_attribute = &m_attribute;
 	}
	if (m_statement != NULL) {
	  m_statement->m_parent_attribute = &m_attribute;
 	}
 }
 If::If(const If & other) {
	if (m_expression != NULL) {
	  m_expression = other.m_expression->clone();
	}
	if (m_statement != NULL) {
	  m_statement = other.m_statement->clone();
	}
 }
 If &If::operator=(const If & other) { If tmp(other); swap(tmp); return *this; }
 void If::swap(If & other) {
	std::swap(m_expression, other.m_expression);
	std::swap(m_statement, other.m_statement);
 }
 If::~If() {
 	if (m_expression != NULL) {
	  delete(m_expression);
 	}
	if (m_statement != NULL) {
	  delete(m_statement);
 	}
 }
 void If::visit_children( Visitor* v ) {
 	if (m_expression != NULL) {
	  m_expression->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_statement != NULL) {
	  m_statement->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void If::accept(Visitor *v) { v->visitIf(this); }
 If *If::clone() const { return new If(*this); }
 
 
/********* Print ************/
 Print::Print(Expression *p1)  {
	m_expression = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression != NULL) {
	  m_expression->m_parent_attribute = &m_attribute;
 	}
 }
 Print::Print(const Print & other) {
	if (m_expression != NULL) {
	  m_expression = other.m_expression->clone();
	}
 }
 Print &Print::operator=(const Print & other) { Print tmp(other); swap(tmp); return *this; }
 void Print::swap(Print & other) {
	std::swap(m_expression, other.m_expression);
 }
 Print::~Print() {
 	if (m_expression != NULL) {
	  delete(m_expression);
 	}
 }
 void Print::visit_children( Visitor* v ) {
 	if (m_expression != NULL) {
	  m_expression->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void Print::accept(Visitor *v) { v->visitPrint(this); }
 Print *Print::clone() const { return new Print(*this); }
 
 
/********* ReturnImpl ************/
 ReturnImpl::ReturnImpl(Expression *p1)  {
	m_expression = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression != NULL) {
	  m_expression->m_parent_attribute = &m_attribute;
 	}
 }
 ReturnImpl::ReturnImpl(const ReturnImpl & other) {
	if (m_expression != NULL) {
	  m_expression = other.m_expression->clone();
	}
 }
 ReturnImpl &ReturnImpl::operator=(const ReturnImpl & other) { ReturnImpl tmp(other); swap(tmp); return *this; }
 void ReturnImpl::swap(ReturnImpl & other) {
	std::swap(m_expression, other.m_expression);
 }
 ReturnImpl::~ReturnImpl() {
 	if (m_expression != NULL) {
	  delete(m_expression);
 	}
 }
 void ReturnImpl::visit_children( Visitor* v ) {
 	if (m_expression != NULL) {
	  m_expression->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void ReturnImpl::accept(Visitor *v) { v->visitReturnImpl(this); }
 ReturnImpl *ReturnImpl::clone() const { return new ReturnImpl(*this); }
 
 
/********* TInteger ************/
 TInteger::TInteger()  {
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
 }
 TInteger::TInteger(const TInteger & other) {
 }
 TInteger &TInteger::operator=(const TInteger & other) { TInteger tmp(other); swap(tmp); return *this; }
 void TInteger::swap(TInteger & other) {
 }
 TInteger::~TInteger() {
  }
 void TInteger::visit_children( Visitor* v ) {
  }
 void TInteger::accept(Visitor *v) { v->visitTInteger(this); }
 TInteger *TInteger::clone() const { return new TInteger(*this); }
 
 
/********* TBoolean ************/
 TBoolean::TBoolean()  {
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
 }
 TBoolean::TBoolean(const TBoolean & other) {
 }
 TBoolean &TBoolean::operator=(const TBoolean & other) { TBoolean tmp(other); swap(tmp); return *this; }
 void TBoolean::swap(TBoolean & other) {
 }
 TBoolean::~TBoolean() {
  }
 void TBoolean::visit_children( Visitor* v ) {
  }
 void TBoolean::accept(Visitor *v) { v->visitTBoolean(this); }
 TBoolean *TBoolean::clone() const { return new TBoolean(*this); }
 
 
/********* TNothing ************/
 TNothing::TNothing()  {
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
 }
 TNothing::TNothing(const TNothing & other) {
 }
 TNothing &TNothing::operator=(const TNothing & other) { TNothing tmp(other); swap(tmp); return *this; }
 void TNothing::swap(TNothing & other) {
 }
 TNothing::~TNothing() {
  }
 void TNothing::visit_children( Visitor* v ) {
  }
 void TNothing::accept(Visitor *v) { v->visitTNothing(this); }
 TNothing *TNothing::clone() const { return new TNothing(*this); }
 
 
/********* TObject ************/
 TObject::TObject(ClassID *p1)  {
	m_classid = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_classid != NULL) {
	  m_classid->m_parent_attribute = &m_attribute;
 	}
 }
 TObject::TObject(const TObject & other) {
	if (m_classid != NULL) {
	  m_classid = other.m_classid->clone();
	}
 }
 TObject &TObject::operator=(const TObject & other) { TObject tmp(other); swap(tmp); return *this; }
 void TObject::swap(TObject & other) {
	std::swap(m_classid, other.m_classid);
 }
 TObject::~TObject() {
 	if (m_classid != NULL) {
	  delete(m_classid);
 	}
 }
 void TObject::visit_children( Visitor* v ) {
 	if (m_classid != NULL) {
	  m_classid->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void TObject::accept(Visitor *v) { v->visitTObject(this); }
 TObject *TObject::clone() const { return new TObject(*this); }
 
 
/********* ClassIDImpl ************/
 ClassIDImpl::ClassIDImpl(ClassName *p1)  {
	m_classname = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_classname != NULL) {
	  m_classname->m_parent_attribute = &m_attribute;
 	}
 }
 ClassIDImpl::ClassIDImpl(const ClassIDImpl & other) {
	if (m_classname != NULL) {
	  m_classname = other.m_classname->clone();
	}
 }
 ClassIDImpl &ClassIDImpl::operator=(const ClassIDImpl & other) { ClassIDImpl tmp(other); swap(tmp); return *this; }
 void ClassIDImpl::swap(ClassIDImpl & other) {
	std::swap(m_classname, other.m_classname);
 }
 ClassIDImpl::~ClassIDImpl() {
 	if (m_classname != NULL) {
	  delete(m_classname);
 	}
 }
 void ClassIDImpl::visit_children( Visitor* v ) {
 	if (m_classname != NULL) {
	  m_classname->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void ClassIDImpl::accept(Visitor *v) { v->visitClassIDImpl(this); }
 ClassIDImpl *ClassIDImpl::clone() const { return new ClassIDImpl(*this); }
 
 
/********* VariableIDImpl ************/
 VariableIDImpl::VariableIDImpl(SymName *p1)  {
	m_symname = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_symname != NULL) {
	  m_symname->m_parent_attribute = &m_attribute;
 	}
 }
 VariableIDImpl::VariableIDImpl(const VariableIDImpl & other) {
	if (m_symname != NULL) {
	  m_symname = other.m_symname->clone();
	}
 }
 VariableIDImpl &VariableIDImpl::operator=(const VariableIDImpl & other) { VariableIDImpl tmp(other); swap(tmp); return *this; }
 void VariableIDImpl::swap(VariableIDImpl & other) {
	std::swap(m_symname, other.m_symname);
 }
 VariableIDImpl::~VariableIDImpl() {
 	if (m_symname != NULL) {
	  delete(m_symname);
 	}
 }
 void VariableIDImpl::visit_children( Visitor* v ) {
 	if (m_symname != NULL) {
	  m_symname->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void VariableIDImpl::accept(Visitor *v) { v->visitVariableIDImpl(this); }
 VariableIDImpl *VariableIDImpl::clone() const { return new VariableIDImpl(*this); }
 
 
/********* MethodIDImpl ************/
 MethodIDImpl::MethodIDImpl(SymName *p1)  {
	m_symname = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_symname != NULL) {
	  m_symname->m_parent_attribute = &m_attribute;
 	}
 }
 MethodIDImpl::MethodIDImpl(const MethodIDImpl & other) {
	if (m_symname != NULL) {
	  m_symname = other.m_symname->clone();
	}
 }
 MethodIDImpl &MethodIDImpl::operator=(const MethodIDImpl & other) { MethodIDImpl tmp(other); swap(tmp); return *this; }
 void MethodIDImpl::swap(MethodIDImpl & other) {
	std::swap(m_symname, other.m_symname);
 }
 MethodIDImpl::~MethodIDImpl() {
 	if (m_symname != NULL) {
	  delete(m_symname);
 	}
 }
 void MethodIDImpl::visit_children( Visitor* v ) {
 	if (m_symname != NULL) {
	  m_symname->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void MethodIDImpl::accept(Visitor *v) { v->visitMethodIDImpl(this); }
 MethodIDImpl *MethodIDImpl::clone() const { return new MethodIDImpl(*this); }
 
 
/********* Plus ************/
 Plus::Plus(Expression *p1, Expression *p2)  {
	m_expression_1 = p1;
	m_expression_2 = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression_1 != NULL) {
	  m_expression_1->m_parent_attribute = &m_attribute;
 	}
	if (m_expression_2 != NULL) {
	  m_expression_2->m_parent_attribute = &m_attribute;
 	}
 }
 Plus::Plus(const Plus & other) {
	if (m_expression_1 != NULL) {
	  m_expression_1 = other.m_expression_1->clone();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2 = other.m_expression_2->clone();
	}
 }
 Plus &Plus::operator=(const Plus & other) { Plus tmp(other); swap(tmp); return *this; }
 void Plus::swap(Plus & other) {
	std::swap(m_expression_1, other.m_expression_1);
	std::swap(m_expression_2, other.m_expression_2);
 }
 Plus::~Plus() {
 	if (m_expression_1 != NULL) {
	  delete(m_expression_1);
 	}
	if (m_expression_2 != NULL) {
	  delete(m_expression_2);
 	}
 }
 void Plus::visit_children( Visitor* v ) {
 	if (m_expression_1 != NULL) {
	  m_expression_1->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void Plus::accept(Visitor *v) { v->visitPlus(this); }
 Plus *Plus::clone() const { return new Plus(*this); }
 
 
/********* Minus ************/
 Minus::Minus(Expression *p1, Expression *p2)  {
	m_expression_1 = p1;
	m_expression_2 = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression_1 != NULL) {
	  m_expression_1->m_parent_attribute = &m_attribute;
 	}
	if (m_expression_2 != NULL) {
	  m_expression_2->m_parent_attribute = &m_attribute;
 	}
 }
 Minus::Minus(const Minus & other) {
	if (m_expression_1 != NULL) {
	  m_expression_1 = other.m_expression_1->clone();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2 = other.m_expression_2->clone();
	}
 }
 Minus &Minus::operator=(const Minus & other) { Minus tmp(other); swap(tmp); return *this; }
 void Minus::swap(Minus & other) {
	std::swap(m_expression_1, other.m_expression_1);
	std::swap(m_expression_2, other.m_expression_2);
 }
 Minus::~Minus() {
 	if (m_expression_1 != NULL) {
	  delete(m_expression_1);
 	}
	if (m_expression_2 != NULL) {
	  delete(m_expression_2);
 	}
 }
 void Minus::visit_children( Visitor* v ) {
 	if (m_expression_1 != NULL) {
	  m_expression_1->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void Minus::accept(Visitor *v) { v->visitMinus(this); }
 Minus *Minus::clone() const { return new Minus(*this); }
 
 
/********* Times ************/
 Times::Times(Expression *p1, Expression *p2)  {
	m_expression_1 = p1;
	m_expression_2 = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression_1 != NULL) {
	  m_expression_1->m_parent_attribute = &m_attribute;
 	}
	if (m_expression_2 != NULL) {
	  m_expression_2->m_parent_attribute = &m_attribute;
 	}
 }
 Times::Times(const Times & other) {
	if (m_expression_1 != NULL) {
	  m_expression_1 = other.m_expression_1->clone();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2 = other.m_expression_2->clone();
	}
 }
 Times &Times::operator=(const Times & other) { Times tmp(other); swap(tmp); return *this; }
 void Times::swap(Times & other) {
	std::swap(m_expression_1, other.m_expression_1);
	std::swap(m_expression_2, other.m_expression_2);
 }
 Times::~Times() {
 	if (m_expression_1 != NULL) {
	  delete(m_expression_1);
 	}
	if (m_expression_2 != NULL) {
	  delete(m_expression_2);
 	}
 }
 void Times::visit_children( Visitor* v ) {
 	if (m_expression_1 != NULL) {
	  m_expression_1->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void Times::accept(Visitor *v) { v->visitTimes(this); }
 Times *Times::clone() const { return new Times(*this); }
 
 
/********* Divide ************/
 Divide::Divide(Expression *p1, Expression *p2)  {
	m_expression_1 = p1;
	m_expression_2 = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression_1 != NULL) {
	  m_expression_1->m_parent_attribute = &m_attribute;
 	}
	if (m_expression_2 != NULL) {
	  m_expression_2->m_parent_attribute = &m_attribute;
 	}
 }
 Divide::Divide(const Divide & other) {
	if (m_expression_1 != NULL) {
	  m_expression_1 = other.m_expression_1->clone();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2 = other.m_expression_2->clone();
	}
 }
 Divide &Divide::operator=(const Divide & other) { Divide tmp(other); swap(tmp); return *this; }
 void Divide::swap(Divide & other) {
	std::swap(m_expression_1, other.m_expression_1);
	std::swap(m_expression_2, other.m_expression_2);
 }
 Divide::~Divide() {
 	if (m_expression_1 != NULL) {
	  delete(m_expression_1);
 	}
	if (m_expression_2 != NULL) {
	  delete(m_expression_2);
 	}
 }
 void Divide::visit_children( Visitor* v ) {
 	if (m_expression_1 != NULL) {
	  m_expression_1->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void Divide::accept(Visitor *v) { v->visitDivide(this); }
 Divide *Divide::clone() const { return new Divide(*this); }
 
 
/********* And ************/
 And::And(Expression *p1, Expression *p2)  {
	m_expression_1 = p1;
	m_expression_2 = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression_1 != NULL) {
	  m_expression_1->m_parent_attribute = &m_attribute;
 	}
	if (m_expression_2 != NULL) {
	  m_expression_2->m_parent_attribute = &m_attribute;
 	}
 }
 And::And(const And & other) {
	if (m_expression_1 != NULL) {
	  m_expression_1 = other.m_expression_1->clone();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2 = other.m_expression_2->clone();
	}
 }
 And &And::operator=(const And & other) { And tmp(other); swap(tmp); return *this; }
 void And::swap(And & other) {
	std::swap(m_expression_1, other.m_expression_1);
	std::swap(m_expression_2, other.m_expression_2);
 }
 And::~And() {
 	if (m_expression_1 != NULL) {
	  delete(m_expression_1);
 	}
	if (m_expression_2 != NULL) {
	  delete(m_expression_2);
 	}
 }
 void And::visit_children( Visitor* v ) {
 	if (m_expression_1 != NULL) {
	  m_expression_1->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void And::accept(Visitor *v) { v->visitAnd(this); }
 And *And::clone() const { return new And(*this); }
 
 
/********* LessThan ************/
 LessThan::LessThan(Expression *p1, Expression *p2)  {
	m_expression_1 = p1;
	m_expression_2 = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression_1 != NULL) {
	  m_expression_1->m_parent_attribute = &m_attribute;
 	}
	if (m_expression_2 != NULL) {
	  m_expression_2->m_parent_attribute = &m_attribute;
 	}
 }
 LessThan::LessThan(const LessThan & other) {
	if (m_expression_1 != NULL) {
	  m_expression_1 = other.m_expression_1->clone();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2 = other.m_expression_2->clone();
	}
 }
 LessThan &LessThan::operator=(const LessThan & other) { LessThan tmp(other); swap(tmp); return *this; }
 void LessThan::swap(LessThan & other) {
	std::swap(m_expression_1, other.m_expression_1);
	std::swap(m_expression_2, other.m_expression_2);
 }
 LessThan::~LessThan() {
 	if (m_expression_1 != NULL) {
	  delete(m_expression_1);
 	}
	if (m_expression_2 != NULL) {
	  delete(m_expression_2);
 	}
 }
 void LessThan::visit_children( Visitor* v ) {
 	if (m_expression_1 != NULL) {
	  m_expression_1->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void LessThan::accept(Visitor *v) { v->visitLessThan(this); }
 LessThan *LessThan::clone() const { return new LessThan(*this); }
 
 
/********* LessThanEqualTo ************/
 LessThanEqualTo::LessThanEqualTo(Expression *p1, Expression *p2)  {
	m_expression_1 = p1;
	m_expression_2 = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression_1 != NULL) {
	  m_expression_1->m_parent_attribute = &m_attribute;
 	}
	if (m_expression_2 != NULL) {
	  m_expression_2->m_parent_attribute = &m_attribute;
 	}
 }
 LessThanEqualTo::LessThanEqualTo(const LessThanEqualTo & other) {
	if (m_expression_1 != NULL) {
	  m_expression_1 = other.m_expression_1->clone();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2 = other.m_expression_2->clone();
	}
 }
 LessThanEqualTo &LessThanEqualTo::operator=(const LessThanEqualTo & other) { LessThanEqualTo tmp(other); swap(tmp); return *this; }
 void LessThanEqualTo::swap(LessThanEqualTo & other) {
	std::swap(m_expression_1, other.m_expression_1);
	std::swap(m_expression_2, other.m_expression_2);
 }
 LessThanEqualTo::~LessThanEqualTo() {
 	if (m_expression_1 != NULL) {
	  delete(m_expression_1);
 	}
	if (m_expression_2 != NULL) {
	  delete(m_expression_2);
 	}
 }
 void LessThanEqualTo::visit_children( Visitor* v ) {
 	if (m_expression_1 != NULL) {
	  m_expression_1->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression_2 != NULL) {
	  m_expression_2->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void LessThanEqualTo::accept(Visitor *v) { v->visitLessThanEqualTo(this); }
 LessThanEqualTo *LessThanEqualTo::clone() const { return new LessThanEqualTo(*this); }
 
 
/********* Not ************/
 Not::Not(Expression *p1)  {
	m_expression = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression != NULL) {
	  m_expression->m_parent_attribute = &m_attribute;
 	}
 }
 Not::Not(const Not & other) {
	if (m_expression != NULL) {
	  m_expression = other.m_expression->clone();
	}
 }
 Not &Not::operator=(const Not & other) { Not tmp(other); swap(tmp); return *this; }
 void Not::swap(Not & other) {
	std::swap(m_expression, other.m_expression);
 }
 Not::~Not() {
 	if (m_expression != NULL) {
	  delete(m_expression);
 	}
 }
 void Not::visit_children( Visitor* v ) {
 	if (m_expression != NULL) {
	  m_expression->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void Not::accept(Visitor *v) { v->visitNot(this); }
 Not *Not::clone() const { return new Not(*this); }
 
 
/********* UnaryMinus ************/
 UnaryMinus::UnaryMinus(Expression *p1)  {
	m_expression = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_expression != NULL) {
	  m_expression->m_parent_attribute = &m_attribute;
 	}
 }
 UnaryMinus::UnaryMinus(const UnaryMinus & other) {
	if (m_expression != NULL) {
	  m_expression = other.m_expression->clone();
	}
 }
 UnaryMinus &UnaryMinus::operator=(const UnaryMinus & other) { UnaryMinus tmp(other); swap(tmp); return *this; }
 void UnaryMinus::swap(UnaryMinus & other) {
	std::swap(m_expression, other.m_expression);
 }
 UnaryMinus::~UnaryMinus() {
 	if (m_expression != NULL) {
	  delete(m_expression);
 	}
 }
 void UnaryMinus::visit_children( Visitor* v ) {
 	if (m_expression != NULL) {
	  m_expression->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void UnaryMinus::accept(Visitor *v) { v->visitUnaryMinus(this); }
 UnaryMinus *UnaryMinus::clone() const { return new UnaryMinus(*this); }
 
 
/********* MethodCall ************/
 MethodCall::MethodCall(VariableID *p1, MethodID *p2, list<Expression_ptr> *p3)  {
	m_variableid = p1;
	m_methodid = p2;
	m_expression_list = p3;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_variableid != NULL) {
	  m_variableid->m_parent_attribute = &m_attribute;
 	}
	if (m_methodid != NULL) {
	  m_methodid->m_parent_attribute = &m_attribute;
 	}
	if (m_expression_list != NULL) {
	  list<Expression_ptr>::iterator m_expression_list_iter;
	  for(m_expression_list_iter = m_expression_list->begin();
	    m_expression_list_iter != m_expression_list->end();
	    ++m_expression_list_iter){
		  if(*m_expression_list_iter != NULL) {
		    (*m_expression_list_iter)->m_parent_attribute = &m_attribute;
		  }
	  }
	}
 }
 MethodCall::MethodCall(const MethodCall & other) {
	if (m_variableid != NULL) {
	  m_variableid = other.m_variableid->clone();
	}
	if (m_methodid != NULL) {
	  m_methodid = other.m_methodid->clone();
	}
	if (m_expression_list != NULL) {
	  m_expression_list = new list<Expression_ptr>;
	  list<Expression_ptr>::iterator m_expression_list_iter;
	  for(m_expression_list_iter = other.m_expression_list->begin();
	    m_expression_list_iter != other.m_expression_list->end();
	    ++m_expression_list_iter){
		  m_expression_list->push_back( (*m_expression_list_iter)->clone() );
	  }
	}
 }
 MethodCall &MethodCall::operator=(const MethodCall & other) { MethodCall tmp(other); swap(tmp); return *this; }
 void MethodCall::swap(MethodCall & other) {
	std::swap(m_variableid, other.m_variableid);
	std::swap(m_methodid, other.m_methodid);
	std::swap(m_expression_list, other.m_expression_list);
 }
 MethodCall::~MethodCall() {
 	if (m_variableid != NULL) {
	  delete(m_variableid);
 	}
	if (m_methodid != NULL) {
	  delete(m_methodid);
 	}
	if (m_expression_list != NULL) {
	  list<Expression_ptr>::iterator m_expression_list_iter;
	  for(m_expression_list_iter = m_expression_list->begin();
	    m_expression_list_iter != m_expression_list->end();
	    ++m_expression_list_iter){
		  delete( *m_expression_list_iter );
	  }
	}
 }
 void MethodCall::visit_children( Visitor* v ) {
 	if (m_variableid != NULL) {
	  m_variableid->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_methodid != NULL) {
	  m_methodid->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression_list != NULL) {
	  list<Expression_ptr>::iterator m_expression_list_iter;
	  for(m_expression_list_iter = m_expression_list->begin();
	    m_expression_list_iter != m_expression_list->end();
	    ++m_expression_list_iter){
		  if(*m_expression_list_iter != NULL) {
		    (*m_expression_list_iter)->accept( v );
		  } else {
		    v->visitNullPointer();
		  }
	  }
	} else {
		v->visitNullPointer();
	}
 }
 void MethodCall::accept(Visitor *v) { v->visitMethodCall(this); }
 MethodCall *MethodCall::clone() const { return new MethodCall(*this); }
 
 
/********* SelfCall ************/
 SelfCall::SelfCall(MethodID *p1, list<Expression_ptr> *p2)  {
	m_methodid = p1;
	m_expression_list = p2;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_methodid != NULL) {
	  m_methodid->m_parent_attribute = &m_attribute;
 	}
	if (m_expression_list != NULL) {
	  list<Expression_ptr>::iterator m_expression_list_iter;
	  for(m_expression_list_iter = m_expression_list->begin();
	    m_expression_list_iter != m_expression_list->end();
	    ++m_expression_list_iter){
		  if(*m_expression_list_iter != NULL) {
		    (*m_expression_list_iter)->m_parent_attribute = &m_attribute;
		  }
	  }
	}
 }
 SelfCall::SelfCall(const SelfCall & other) {
	if (m_methodid != NULL) {
	  m_methodid = other.m_methodid->clone();
	}
	if (m_expression_list != NULL) {
	  m_expression_list = new list<Expression_ptr>;
	  list<Expression_ptr>::iterator m_expression_list_iter;
	  for(m_expression_list_iter = other.m_expression_list->begin();
	    m_expression_list_iter != other.m_expression_list->end();
	    ++m_expression_list_iter){
		  m_expression_list->push_back( (*m_expression_list_iter)->clone() );
	  }
	}
 }
 SelfCall &SelfCall::operator=(const SelfCall & other) { SelfCall tmp(other); swap(tmp); return *this; }
 void SelfCall::swap(SelfCall & other) {
	std::swap(m_methodid, other.m_methodid);
	std::swap(m_expression_list, other.m_expression_list);
 }
 SelfCall::~SelfCall() {
 	if (m_methodid != NULL) {
	  delete(m_methodid);
 	}
	if (m_expression_list != NULL) {
	  list<Expression_ptr>::iterator m_expression_list_iter;
	  for(m_expression_list_iter = m_expression_list->begin();
	    m_expression_list_iter != m_expression_list->end();
	    ++m_expression_list_iter){
		  delete( *m_expression_list_iter );
	  }
	}
 }
 void SelfCall::visit_children( Visitor* v ) {
 	if (m_methodid != NULL) {
	  m_methodid->accept( v );
 	} else {
		v->visitNullPointer();
	}
	if (m_expression_list != NULL) {
	  list<Expression_ptr>::iterator m_expression_list_iter;
	  for(m_expression_list_iter = m_expression_list->begin();
	    m_expression_list_iter != m_expression_list->end();
	    ++m_expression_list_iter){
		  if(*m_expression_list_iter != NULL) {
		    (*m_expression_list_iter)->accept( v );
		  } else {
		    v->visitNullPointer();
		  }
	  }
	} else {
		v->visitNullPointer();
	}
 }
 void SelfCall::accept(Visitor *v) { v->visitSelfCall(this); }
 SelfCall *SelfCall::clone() const { return new SelfCall(*this); }
 
 
/********* Variable ************/
 Variable::Variable(VariableID *p1)  {
	m_variableid = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_variableid != NULL) {
	  m_variableid->m_parent_attribute = &m_attribute;
 	}
 }
 Variable::Variable(const Variable & other) {
	if (m_variableid != NULL) {
	  m_variableid = other.m_variableid->clone();
	}
 }
 Variable &Variable::operator=(const Variable & other) { Variable tmp(other); swap(tmp); return *this; }
 void Variable::swap(Variable & other) {
	std::swap(m_variableid, other.m_variableid);
 }
 Variable::~Variable() {
 	if (m_variableid != NULL) {
	  delete(m_variableid);
 	}
 }
 void Variable::visit_children( Visitor* v ) {
 	if (m_variableid != NULL) {
	  m_variableid->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void Variable::accept(Visitor *v) { v->visitVariable(this); }
 Variable *Variable::clone() const { return new Variable(*this); }
 
 
/********* IntegerLiteral ************/
 IntegerLiteral::IntegerLiteral(Primitive *p1)  {
	m_primitive = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_primitive != NULL) {
	  m_primitive->m_parent_attribute = &m_attribute;
 	}
 }
 IntegerLiteral::IntegerLiteral(const IntegerLiteral & other) {
	if (m_primitive != NULL) {
	  m_primitive = other.m_primitive->clone();
	}
 }
 IntegerLiteral &IntegerLiteral::operator=(const IntegerLiteral & other) { IntegerLiteral tmp(other); swap(tmp); return *this; }
 void IntegerLiteral::swap(IntegerLiteral & other) {
	std::swap(m_primitive, other.m_primitive);
 }
 IntegerLiteral::~IntegerLiteral() {
 	if (m_primitive != NULL) {
	  delete(m_primitive);
 	}
 }
 void IntegerLiteral::visit_children( Visitor* v ) {
 	if (m_primitive != NULL) {
	  m_primitive->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void IntegerLiteral::accept(Visitor *v) { v->visitIntegerLiteral(this); }
 IntegerLiteral *IntegerLiteral::clone() const { return new IntegerLiteral(*this); }
 
 
/********* BooleanLiteral ************/
 BooleanLiteral::BooleanLiteral(Primitive *p1)  {
	m_primitive = p1;
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
	if (m_primitive != NULL) {
	  m_primitive->m_parent_attribute = &m_attribute;
 	}
 }
 BooleanLiteral::BooleanLiteral(const BooleanLiteral & other) {
	if (m_primitive != NULL) {
	  m_primitive = other.m_primitive->clone();
	}
 }
 BooleanLiteral &BooleanLiteral::operator=(const BooleanLiteral & other) { BooleanLiteral tmp(other); swap(tmp); return *this; }
 void BooleanLiteral::swap(BooleanLiteral & other) {
	std::swap(m_primitive, other.m_primitive);
 }
 BooleanLiteral::~BooleanLiteral() {
 	if (m_primitive != NULL) {
	  delete(m_primitive);
 	}
 }
 void BooleanLiteral::visit_children( Visitor* v ) {
 	if (m_primitive != NULL) {
	  m_primitive->accept( v );
 	} else {
		v->visitNullPointer();
	}
 }
 void BooleanLiteral::accept(Visitor *v) { v->visitBooleanLiteral(this); }
 BooleanLiteral *BooleanLiteral::clone() const { return new BooleanLiteral(*this); }
 
 
/********* Nothing ************/
 Nothing::Nothing()  {
	m_attribute.lineno = yylineno;
	m_parent_attribute = NULL;
 }
 Nothing::Nothing(const Nothing & other) {
 }
 Nothing &Nothing::operator=(const Nothing & other) { Nothing tmp(other); swap(tmp); return *this; }
 void Nothing::swap(Nothing & other) {
 }
 Nothing::~Nothing() {
  }
 void Nothing::visit_children( Visitor* v ) {
  }
 void Nothing::accept(Visitor *v) { v->visitNothing(this); }
 Nothing *Nothing::clone() const { return new Nothing(*this); }
 
 

