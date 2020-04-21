1:
	  g++ -Wall -g -o bad1 bad1.cpp
	  g++ -Wall -g -o prog1 prog1.cpp
	  time ./bad1 100000 > input1
	  time ./prog1 < input1

2:
	  g++ -Wall -g -o bad2 bad2.cpp
	  g++ -Wall -g -o prog2 prog2.cpp
	  time ./bad2 100000 > input2
	  time ./prog2 < input2

3:
	  g++ -Wall -g -o bad3 bad3.cpp
	  g++ -Wall -g -o prog3 prog3.cpp
	  time ./bad3 100000 > input3
	  time ./prog3 < input3 > output3

yes:
	  make 1
	  make 2
	  make 3

clean:
	  rm -f bad1 prog1 input1
	  rm -f bad2 prog2 input2
	  rm -f bad3 prog3 input3 output3
