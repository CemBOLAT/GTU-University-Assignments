EXECUTABLE := Test.class
SRC := *.java

all :
	@echo 'make	compile|run|clean|rerun'

run : $(EXECUTABLE)
	@java Test

compile : $(EXECUTABLE)

$(EXECUTABLE) : $(SRC)
	@javac $(SRC)

clean:
	@rm -f $(EXECUTABLE)
	@rm -f *.class

rerun : re run

.PHONY: all clean re rerun
