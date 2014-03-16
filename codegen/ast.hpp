#ifndef AST_HEADER
#define AST_HEADER

//Automatically Generated C++ Abstract Syntax Tree Interface

#include <list>
#include "attribute.hpp"
using namespace std;


/********** Forward Declarations **********/

class ProgramImpl;
class Program;
class ClassImpl;
class Class;
class DeclarationImpl;
class Declaration;
class MethodImpl;
class Method;
class MethodBodyImpl;
class MethodBody;
class ParameterImpl;
class Parameter;
class Assignment;
class Statement;
class If;
class Print;
class ReturnImpl;
class Return;
class TInteger;
class Type;
class TBoolean;
class TNothing;
class TObject;
class ClassIDImpl;
class ClassID;
class VariableIDImpl;
class VariableID;
class MethodIDImpl;
class MethodID;
class Plus;
class Expression;
class Minus;
class Times;
class Divide;
class And;
class LessThan;
class LessThanEqualTo;
class Not;
class UnaryMinus;
class MethodCall;
class SelfCall;
class Variable;
class IntegerLiteral;
class BooleanLiteral;
class Nothing;
class SymName;
class Primitive;
class ClassName;


/********** Pointer Typedefs **********/

typedef Program* Program_ptr;

typedef Class* Class_ptr;
typedef Declaration* Declaration_ptr;
typedef Method* Method_ptr;
typedef VariableID* VariableID_ptr;
typedef Parameter* Parameter_ptr;
typedef Statement* Statement_ptr;
typedef Expression* Expression_ptr;


/********** Union Type (from parse) **********/

#ifdef YYSTYPE_IS_TRIVIAL
#error Make sure to include this file _before_ parser.hpp
#endif
typedef union
{
list<Class_ptr>* u_class_list;
Program* u_program;
list<Declaration_ptr>* u_declaration_list;
list<Method_ptr>* u_method_list;
Class* u_class;
list<VariableID_ptr>* u_variableid_list;
Declaration* u_declaration;
list<Parameter_ptr>* u_parameter_list;
Method* u_method;
list<Statement_ptr>* u_statement_list;
MethodBody* u_methodbody;
Parameter* u_parameter;
Statement* u_statement;
Return* u_return;
Type* u_type;
ClassID* u_classid;
VariableID* u_variableid;
MethodID* u_methodid;
Expression* u_expression;
list<Expression_ptr>* u_expression_list;
SymName* u_symname;
Primitive* u_primitive;
ClassName* u_classname;

// a couple of hardcoded types
char* u_base_charptr;
int u_base_int;
} classunion_stype;
#define YYSTYPE classunion_stype

/********** Visitor Interfaces **********/

class Visitor{
 public:
  virtual ~Visitor() {}
  virtual void visitProgramImpl(ProgramImpl *p) = 0;
  virtual void visitClassImpl(ClassImpl *p) = 0;
  virtual void visitDeclarationImpl(DeclarationImpl *p) = 0;
  virtual void visitMethodImpl(MethodImpl *p) = 0;
  virtual void visitMethodBodyImpl(MethodBodyImpl *p) = 0;
  virtual void visitParameterImpl(ParameterImpl *p) = 0;
  virtual void visitAssignment(Assignment *p) = 0;
  virtual void visitIf(If *p) = 0;
  virtual void visitPrint(Print *p) = 0;
  virtual void visitReturnImpl(ReturnImpl *p) = 0;
  virtual void visitTInteger(TInteger *p) = 0;
  virtual void visitTBoolean(TBoolean *p) = 0;
  virtual void visitTNothing(TNothing *p) = 0;
  virtual void visitTObject(TObject *p) = 0;
  virtual void visitClassIDImpl(ClassIDImpl *p) = 0;
  virtual void visitVariableIDImpl(VariableIDImpl *p) = 0;
  virtual void visitMethodIDImpl(MethodIDImpl *p) = 0;
  virtual void visitPlus(Plus *p) = 0;
  virtual void visitMinus(Minus *p) = 0;
  virtual void visitTimes(Times *p) = 0;
  virtual void visitDivide(Divide *p) = 0;
  virtual void visitAnd(And *p) = 0;
  virtual void visitLessThan(LessThan *p) = 0;
  virtual void visitLessThanEqualTo(LessThanEqualTo *p) = 0;
  virtual void visitNot(Not *p) = 0;
  virtual void visitUnaryMinus(UnaryMinus *p) = 0;
  virtual void visitMethodCall(MethodCall *p) = 0;
  virtual void visitSelfCall(SelfCall *p) = 0;
  virtual void visitVariable(Variable *p) = 0;
  virtual void visitIntegerLiteral(IntegerLiteral *p) = 0;
  virtual void visitBooleanLiteral(BooleanLiteral *p) = 0;
  virtual void visitNothing(Nothing *p) = 0;
  virtual void visitSymName(SymName *p) = 0;
  virtual void visitPrimitive(Primitive *p) = 0;
  virtual void visitClassName(ClassName *p) = 0;

  virtual void visitNullPointer() {}
};

class Visitable
{
 public:
  virtual ~Visitable() {}
  virtual void visit_children(Visitor *v) = 0;
  virtual void accept(Visitor *v) = 0;
};


/********** Abstract Syntax Classes **********/

class Program : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual Program *clone() const = 0;
};

class Class : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual Class *clone() const = 0;
};

class Declaration : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual Declaration *clone() const = 0;
};

class Method : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual Method *clone() const = 0;
};

class MethodBody : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual MethodBody *clone() const = 0;
};

class Parameter : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual Parameter *clone() const = 0;
};

class Statement : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual Statement *clone() const = 0;
};

class Return : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual Return *clone() const = 0;
};

class Type : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual Type *clone() const = 0;
};

class ClassID : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual ClassID *clone() const = 0;
};

class VariableID : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual VariableID *clone() const = 0;
};

class MethodID : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual MethodID *clone() const = 0;
};

class Expression : public Visitable {
public:
   Attribute m_attribute;
   Attribute* m_parent_attribute;
   virtual Expression *clone() const = 0;
};


// Program ==> *Class
class ProgramImpl : public Program
{
  public:
  list<Class_ptr> *m_class_list;

  ProgramImpl(const ProgramImpl &);
  ProgramImpl &operator=(const ProgramImpl &);
  ProgramImpl(list<Class_ptr> *p1);
  ~ProgramImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  ProgramImpl  *clone() const;
  void swap(ProgramImpl &);
};

// Class ==> ClassID ClassID *Declaration *Method
class ClassImpl : public Class
{
  public:
  ClassID *m_classid_1;
  ClassID *m_classid_2;
  list<Declaration_ptr> *m_declaration_list;
  list<Method_ptr> *m_method_list;

  ClassImpl(const ClassImpl &);
  ClassImpl &operator=(const ClassImpl &);
  ClassImpl(ClassID *p1, ClassID *p2, list<Declaration_ptr> *p3, list<Method_ptr> *p4);
  ~ClassImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  ClassImpl  *clone() const;
  void swap(ClassImpl &);
};

// Declaration ==> *VariableID Type
class DeclarationImpl : public Declaration
{
  public:
  list<VariableID_ptr> *m_variableid_list;
  Type *m_type;

  DeclarationImpl(const DeclarationImpl &);
  DeclarationImpl &operator=(const DeclarationImpl &);
  DeclarationImpl(list<VariableID_ptr> *p1, Type *p2);
  ~DeclarationImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  DeclarationImpl  *clone() const;
  void swap(DeclarationImpl &);
};

// Method ==> MethodID *Parameter Type MethodBody
class MethodImpl : public Method
{
  public:
  MethodID *m_methodid;
  list<Parameter_ptr> *m_parameter_list;
  Type *m_type;
  MethodBody *m_methodbody;

  MethodImpl(const MethodImpl &);
  MethodImpl &operator=(const MethodImpl &);
  MethodImpl(MethodID *p1, list<Parameter_ptr> *p2, Type *p3, MethodBody *p4);
  ~MethodImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  MethodImpl  *clone() const;
  void swap(MethodImpl &);
};

// MethodBody ==> *Declaration *Statement Return
class MethodBodyImpl : public MethodBody
{
  public:
  list<Declaration_ptr> *m_declaration_list;
  list<Statement_ptr> *m_statement_list;
  Return *m_return;

  MethodBodyImpl(const MethodBodyImpl &);
  MethodBodyImpl &operator=(const MethodBodyImpl &);
  MethodBodyImpl(list<Declaration_ptr> *p1, list<Statement_ptr> *p2, Return *p3);
  ~MethodBodyImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  MethodBodyImpl  *clone() const;
  void swap(MethodBodyImpl &);
};

// Parameter ==> VariableID Type
class ParameterImpl : public Parameter
{
  public:
  VariableID *m_variableid;
  Type *m_type;

  ParameterImpl(const ParameterImpl &);
  ParameterImpl &operator=(const ParameterImpl &);
  ParameterImpl(VariableID *p1, Type *p2);
  ~ParameterImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  ParameterImpl  *clone() const;
  void swap(ParameterImpl &);
};

// Statement:Assignment ==> VariableID Expression
class Assignment : public Statement
{
  public:
  VariableID *m_variableid;
  Expression *m_expression;

  Assignment(const Assignment &);
  Assignment &operator=(const Assignment &);
  Assignment(VariableID *p1, Expression *p2);
  ~Assignment();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  Assignment  *clone() const;
  void swap(Assignment &);
};

// Statement:If ==> Expression Statement
class If : public Statement
{
  public:
  Expression *m_expression;
  Statement *m_statement;

  If(const If &);
  If &operator=(const If &);
  If(Expression *p1, Statement *p2);
  ~If();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  If  *clone() const;
  void swap(If &);
};

// Statement:Print ==> Expression
class Print : public Statement
{
  public:
  Expression *m_expression;

  Print(const Print &);
  Print &operator=(const Print &);
  Print(Expression *p1);
  ~Print();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  Print  *clone() const;
  void swap(Print &);
};

// Return ==> Expression
class ReturnImpl : public Return
{
  public:
  Expression *m_expression;

  ReturnImpl(const ReturnImpl &);
  ReturnImpl &operator=(const ReturnImpl &);
  ReturnImpl(Expression *p1);
  ~ReturnImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  ReturnImpl  *clone() const;
  void swap(ReturnImpl &);
};

// Type:TInteger ==>
class TInteger : public Type
{
  public:

  TInteger(const TInteger &);
  TInteger &operator=(const TInteger &);
  TInteger();
  ~TInteger();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  TInteger  *clone() const;
  void swap(TInteger &);
};

// Type:TBoolean ==>
class TBoolean : public Type
{
  public:

  TBoolean(const TBoolean &);
  TBoolean &operator=(const TBoolean &);
  TBoolean();
  ~TBoolean();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  TBoolean  *clone() const;
  void swap(TBoolean &);
};

// Type:TNothing ==>
class TNothing : public Type
{
  public:

  TNothing(const TNothing &);
  TNothing &operator=(const TNothing &);
  TNothing();
  ~TNothing();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  TNothing  *clone() const;
  void swap(TNothing &);
};

// Type:TObject ==> ClassID
class TObject : public Type
{
  public:
  ClassID *m_classid;

  TObject(const TObject &);
  TObject &operator=(const TObject &);
  TObject(ClassID *p1);
  ~TObject();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  TObject  *clone() const;
  void swap(TObject &);
};

// ClassID ==> ClassName
class ClassIDImpl : public ClassID
{
  public:
  ClassName *m_classname;

  ClassIDImpl(const ClassIDImpl &);
  ClassIDImpl &operator=(const ClassIDImpl &);
  ClassIDImpl(ClassName *p1);
  ~ClassIDImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  ClassIDImpl  *clone() const;
  void swap(ClassIDImpl &);
};

// VariableID ==> SymName
class VariableIDImpl : public VariableID
{
  public:
  SymName *m_symname;

  VariableIDImpl(const VariableIDImpl &);
  VariableIDImpl &operator=(const VariableIDImpl &);
  VariableIDImpl(SymName *p1);
  ~VariableIDImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  VariableIDImpl  *clone() const;
  void swap(VariableIDImpl &);
};

// MethodID ==> SymName
class MethodIDImpl : public MethodID
{
  public:
  SymName *m_symname;

  MethodIDImpl(const MethodIDImpl &);
  MethodIDImpl &operator=(const MethodIDImpl &);
  MethodIDImpl(SymName *p1);
  ~MethodIDImpl();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  MethodIDImpl  *clone() const;
  void swap(MethodIDImpl &);
};

// Expression:Plus ==> Expression Expression
class Plus : public Expression
{
  public:
  Expression *m_expression_1;
  Expression *m_expression_2;

  Plus(const Plus &);
  Plus &operator=(const Plus &);
  Plus(Expression *p1, Expression *p2);
  ~Plus();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  Plus  *clone() const;
  void swap(Plus &);
};

// Expression:Minus ==> Expression Expression
class Minus : public Expression
{
  public:
  Expression *m_expression_1;
  Expression *m_expression_2;

  Minus(const Minus &);
  Minus &operator=(const Minus &);
  Minus(Expression *p1, Expression *p2);
  ~Minus();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  Minus  *clone() const;
  void swap(Minus &);
};

// Expression:Times ==> Expression Expression
class Times : public Expression
{
  public:
  Expression *m_expression_1;
  Expression *m_expression_2;

  Times(const Times &);
  Times &operator=(const Times &);
  Times(Expression *p1, Expression *p2);
  ~Times();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  Times  *clone() const;
  void swap(Times &);
};

// Expression:Divide ==> Expression Expression
class Divide : public Expression
{
  public:
  Expression *m_expression_1;
  Expression *m_expression_2;

  Divide(const Divide &);
  Divide &operator=(const Divide &);
  Divide(Expression *p1, Expression *p2);
  ~Divide();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  Divide  *clone() const;
  void swap(Divide &);
};

// Expression:And ==> Expression Expression
class And : public Expression
{
  public:
  Expression *m_expression_1;
  Expression *m_expression_2;

  And(const And &);
  And &operator=(const And &);
  And(Expression *p1, Expression *p2);
  ~And();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  And  *clone() const;
  void swap(And &);
};

// Expression:LessThan ==> Expression Expression
class LessThan : public Expression
{
  public:
  Expression *m_expression_1;
  Expression *m_expression_2;

  LessThan(const LessThan &);
  LessThan &operator=(const LessThan &);
  LessThan(Expression *p1, Expression *p2);
  ~LessThan();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  LessThan  *clone() const;
  void swap(LessThan &);
};

// Expression:LessThanEqualTo ==> Expression Expression
class LessThanEqualTo : public Expression
{
  public:
  Expression *m_expression_1;
  Expression *m_expression_2;

  LessThanEqualTo(const LessThanEqualTo &);
  LessThanEqualTo &operator=(const LessThanEqualTo &);
  LessThanEqualTo(Expression *p1, Expression *p2);
  ~LessThanEqualTo();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  LessThanEqualTo  *clone() const;
  void swap(LessThanEqualTo &);
};

// Expression:Not ==> Expression
class Not : public Expression
{
  public:
  Expression *m_expression;

  Not(const Not &);
  Not &operator=(const Not &);
  Not(Expression *p1);
  ~Not();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  Not  *clone() const;
  void swap(Not &);
};

// Expression:UnaryMinus ==> Expression
class UnaryMinus : public Expression
{
  public:
  Expression *m_expression;

  UnaryMinus(const UnaryMinus &);
  UnaryMinus &operator=(const UnaryMinus &);
  UnaryMinus(Expression *p1);
  ~UnaryMinus();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  UnaryMinus  *clone() const;
  void swap(UnaryMinus &);
};

// Expression:MethodCall ==> VariableID MethodID *Expression
class MethodCall : public Expression
{
  public:
  VariableID *m_variableid;
  MethodID *m_methodid;
  list<Expression_ptr> *m_expression_list;

  MethodCall(const MethodCall &);
  MethodCall &operator=(const MethodCall &);
  MethodCall(VariableID *p1, MethodID *p2, list<Expression_ptr> *p3);
  ~MethodCall();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  MethodCall  *clone() const;
  void swap(MethodCall &);
};

// Expression:SelfCall ==> MethodID *Expression
class SelfCall : public Expression
{
  public:
  MethodID *m_methodid;
  list<Expression_ptr> *m_expression_list;

  SelfCall(const SelfCall &);
  SelfCall &operator=(const SelfCall &);
  SelfCall(MethodID *p1, list<Expression_ptr> *p2);
  ~SelfCall();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  SelfCall  *clone() const;
  void swap(SelfCall &);
};

// Expression:Variable ==> VariableID
class Variable : public Expression
{
  public:
  VariableID *m_variableid;

  Variable(const Variable &);
  Variable &operator=(const Variable &);
  Variable(VariableID *p1);
  ~Variable();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  Variable  *clone() const;
  void swap(Variable &);
};

// Expression:IntegerLiteral ==> Primitive
class IntegerLiteral : public Expression
{
  public:
  Primitive *m_primitive;

  IntegerLiteral(const IntegerLiteral &);
  IntegerLiteral &operator=(const IntegerLiteral &);
  IntegerLiteral(Primitive *p1);
  ~IntegerLiteral();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  IntegerLiteral  *clone() const;
  void swap(IntegerLiteral &);
};

// Expression:BooleanLiteral ==> Primitive
class BooleanLiteral : public Expression
{
  public:
  Primitive *m_primitive;

  BooleanLiteral(const BooleanLiteral &);
  BooleanLiteral &operator=(const BooleanLiteral &);
  BooleanLiteral(Primitive *p1);
  ~BooleanLiteral();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  BooleanLiteral  *clone() const;
  void swap(BooleanLiteral &);
};

// Expression:Nothing ==>
class Nothing : public Expression
{
  public:

  Nothing(const Nothing &);
  Nothing &operator=(const Nothing &);
  Nothing();
  ~Nothing();
  virtual void visit_children( Visitor* v );
  virtual void accept(Visitor *v);
  virtual  Nothing  *clone() const;
  void swap(Nothing &);
};




#endif //AST_HEADER

