#
# makefile for Project 1, part 1
#

YACC    = bison -d -v
LEX     = flex
CC      = gcc
CPP     = g++ -g

TARGET	= lang

OBJS += lexer.o parser.o main.o 
RMFILES = core.* lexer.cpp parser.cpp parser.hpp parser.output $(TARGET) $(OBJS)

# dependencies
$(TARGET): parser.cpp lexer.cpp parser.hpp $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS)

# rules
%.cpp: %.ypp
	$(YACC) -o $(@:%.o=%.d) $<

%.o: %.cpp
	$(CPP) -o $@ -c $<

%.cpp: %.l
	$(LEX) -o$(@:%.o=%.d) $<

# source
lexer.o: lexer.cpp parser.hpp 
lexer.cpp: lexer.l

parser.o: parser.cpp parser.hpp
parser.cpp: parser.ypp 

main.o: parser.hpp 

test:
	./$(TARGET) < test.good.lang

clean:
	rm -f $(RMFILES)
