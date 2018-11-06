all: rts compiler

OBJS =  C_syntax.o  		\
	AST_node.o 				\
	main.o    				\
	C_lexical.o  			\
	AST_node_citron.o \
	rts.o

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++11 -g
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lz -lncurses -rdynamic sewing/build/libsewing.a
LIBS = `$(LLVMCONFIG) --libs`
SYSTEMLIBS = `$(LLVMCONFIG) --system-libs`

C_syntax.cpp: C_syntax.yacc
	bison -d -t --no-lines -o $@ $^
	sed -i -e 's/\.string\b/.stringvalue/g' C_syntax.cpp

C_syntax.hpp: C_syntax.cpp

C_lexical.cpp: C_lexical.lex C_syntax.hpp
	flex -L -o $@ $^

%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $<

compiler: $(OBJS)
	g++ -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

rts: sewing
	gcc -g -o rts.o -c rts.c $(LDFLAGS)

sewing:
	cd sewing && mkdir -p build && cd build && cmake ../ -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=RelWithDebInfo && make

rtstest: sewing
	gcc -g -DTEST -o rts.o rts.c $(LDFLAGS)

clean:
	$(RM) -rf C_syntax.cpp C_syntax.hpp compiler y.output c_code/*.ctr c_code/*.ll C_lexical.cpp $(OBJS)
