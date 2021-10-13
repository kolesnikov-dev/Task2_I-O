.PHONY: run build rebuild clean

#The FILE_NAME variable contains the filename
FILE_NAME = Print_File

run: build
	./$(FILE_NAME)

build: $(FILE_NAME)

$(FILE_NAME): $(FILE_NAME).o
	g++ -o $(FILE_NAME) $(FILE_NAME).o

$(FILE_NAME).o: $(FILE_NAME).cpp
	g++ -o $(FILE_NAME).o -c $(FILE_NAME).cpp

rebuild: clean build

clean: 
	rm -vf $(FILE_NAME).o $(FILE_NAME)