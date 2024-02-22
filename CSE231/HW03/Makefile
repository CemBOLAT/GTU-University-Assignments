setJava := ./myContainerPackage/JavaContainer.java \
			./myContainerPackage/JavaSet.java \
			./JavaSetTest.java

vectorJava := ./myContainerPackage/JavaContainer.java \
			  ./myContainerPackage/JavaVector.java \
			  ./JavaVectorTest.java

all:
	@echo "Usage: make set|vector|clean"

set: $(setJava)
	@javac $(setJava)
	@java JavaSetTest

vector : $(vectorJava)
	@javac $(vectorJava)
	@java JavaVectorTest

clean:
	@rm -f *.class
	@rm -f ./myContainerPackage/*.class

.PHONY: clean set vector
