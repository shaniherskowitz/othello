# Shani Herskowitz
# 321658387
# Liora Zaidner
# 323742775
INC=-I/src/server/commands
a.out: compileAll
	g++ -pthread *.o
	rm -f *.o
	rm -f commands/*.o

compileAll: *.h *.cpp commands/*.h commands/*.cpp
	g++ -pthread -c *.cpp
	g++ -c commands/*.cpp