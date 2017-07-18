all: cmm

CC       = g++

OBJS = abstract_syntax_tree.o               \
       and_operation.o                      \
       assignment.o                         \
       basic_block.o                        \
       boolean.o                            \
       break_stmt.o                         \
       codegen_context.o                    \
       equal_operation.o                    \
       expression.o                         \
       error_manager.o                      \
       for_stmt.o                           \
       if_stmt.o                            \
       greater_operation.o                  \
       greater_or_equal_operation.o         \
       less_operation.o                     \
       less_or_equal_operation.o            \
       minus_operation.o                    \
       module_operation.o                   \
       not_equal_operation.o                \
       number.o                             \
       or_operation.o                       \
       over_operation.o                     \
       plus_operation.o                     \
       read_stmt.o                          \
       return_stmt.o                        \
       scanner.o                            \
       string_literal.o                     \
       subprogram_call.o                    \
       subprogram_declaration.o             \
       symbol.o                             \
       symbol_declaration.o                 \
       symbol_table.o                       \
       ternary_if_operation.o               \
       times_operation.o                    \
       unary_minus_operation.o              \
       unary_not_operation.o                \
       parser.o                             \
       write_stmt.o                         \
       while_stmt.o                         \

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++11 ${DEFINE}
LLVMFLAGS = `$(LLVMCONFIG) --ldflags --libs --system-libs`

clean:
	@$(RM) -rf parser.cpp parser.hpp cmm scanner.cpp parser.output $(OBJS)

parser.cpp: simple_c_compiler.y
	@bison -d -o $@ $^

parser.hpp: parser.cpp

scanner.cpp: simple_c_compiler.l parser.hpp
	@flex -o $@ $^

%.o: %.cpp
	@$(CC) -c $(CPPFLAGS) -o $@ $< -g

%.o: %.hpp

cmm: $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LLVMFLAGS)


