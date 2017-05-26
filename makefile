all: cmm

CC       = g++

OBJS = parser.o                             \
       scanner.o                            \
       program.o                            \
       expression.o                         \
       identifier.o                         \
       variable_declaration.o               \
       number.o                             \
       string_literal.o                     \
       boolean.o                            \
       assigment.o                          \
       plus_operation.o                     \

LDFLAGS  = -lm
CPPFLAGS = -std=c++11

clean:
	@$(RM) -rf parser.cpp parser.hpp cmm scanner.cpp parser.output $(OBJS)

parser.cpp: simple_c_compiler.y
	@bison -d -o $@ $^

parser.hpp: parser.cpp

scanner.cpp: simple_c_compiler.l parser.hpp
	@flex -o $@ $^

%.o: %.cpp
	@$(CC) -c $(CPPFLAGS) -o $@ $<

cmm: $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)


