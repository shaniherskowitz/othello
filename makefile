# Shani Herskowitz
# 321658387
# Liora Zaidner
# 323742775

a.out: compileAll
	g++ *.o 
	rm -f *.o

compileAll: *.h *.cpp
	g++ -c *.cpp