all: cmm

CC       = g++

OBJS = parser.o                             \
       scanner.o                            \
       abstract_syntax_tree.o               \
       symbol_table.o                       \
       expression.o                         \
       identifier.o                         \
       variable_declaration.o               \
       number.o                             \
       string_literal.o                     \
       boolean.o                            \
       assignment.o                         \
       plus_operation.o                     \
       minus_operation.o                    \
       times_operation.o                    \
       over_operation.o                     \
       module_operation.o                   \
       less_operation.o                     \
       greater_operation.o                  \
       less_or_equal_operation.o            \
       greater_or_equal_operation.o         \
       and_operation.o                      \
       or_operation.o                       \
       equal_operation.o                    \
       not_equal_operation.o                \
       unary_not_operation.o                \
       unary_minus_operation.o              \
       ternary_if_operation.o               \


LDFLAGS  = -lm
CPPFLAGS = -g -std=c++11 ${DEFINE}

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


