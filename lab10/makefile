CC= g++
FLAGS1= -Wall -std=c++11 -g
FLAGS2= -o
TARGET1= encode
TARGET2= decode
TRANSFER= a.txt
INFILE= test.txt
OUT= out.txt

run:
	  $(CC) $(FLAGS1) encode.cpp $(FLAGS2) $(TARGET1)
	  $(CC) $(FLAGS1) decode.cpp $(FLAGS2) $(TARGET2)
	  ./$(TARGET1) < $(INFILE) > $(TRANSFER)
	  ./$(TARGET2) < $(TRANSFER) > $(OUT) 

gnome:
	  $(CC) $(FLAGS1) encode.cpp $(FLAGS2) $(TARGET1)
	  $(CC) $(FLAGS1) decode.cpp $(FLAGS2) $(TARGET2)
	  ./$(TARGET1) < gnome.txt > $(TRANSFER)
	  ./$(TARGET2) < $(TRANSFER) > $(OUT)

clean:
	  rm -f $(TARGET1) $(TARGET2)
	  rm -f $(TRANSFER) $(OUT)
