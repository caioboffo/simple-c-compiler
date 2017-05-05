all: simple_c_compiler


CC       = g++
OBJS     = parser.o  \
           scanner.o \

LDFLAGS  = -lm
CPPFLAGS = -std=c++11

clean:
	@$(RM) -rf parser.cpp parser.hpp simple_c_compiler scanner.cpp parser.output $(OBJS)

parser.cpp: simple_c_compiler.y
	@bison -d -o $@ $^

parser.hpp: parser.cpp

scanner.cpp: simple_c_compiler.l parser.hpp
	@flex -o $@ $^

%.o: %.cpp
	@$(CC) -c $(CPPFLAGS) -o $@ $<

simple_c_compiler : $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)


