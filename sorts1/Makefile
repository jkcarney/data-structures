CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Wno-terminate -Wno-unused-parameter

.PHONY: handin clean grade submit

FILES := DivideAndConquer.hpp

autograder : $(FILES)

submit : $(FILES)
	autolab submit $<

grade : autograder
	./autograder

clean :
	-@rm -vf autograder *~
