JFLAGS := -classpath .
JD := javadoc
JDOCFLAGS := -protected -splitindex -use -author -version -d ./javadoc

SRC := $(wildcard *.java)
CLASSES := $(SRC:.java=.class)


NODE := 1000
ADD := 1000
REMOVE := 300
UPDATE := 300
SEARCH := 200

FILE := input.txt

all: $(CLASSES)
	@echo "\033[0;32mThe Stock Management System has been created by Cemal BOLAT.\nStudent No: 210104004010\033[0m"
	@echo "\033[0;34mDefault run option is with using 'input.txt' file.\033[0m"
	@echo "\033[0;34mIf you want to fill 'input.txt' file with random values, you can use 'make random' command.\033[0m"
	@echo "\033[0;34mDefault node count is $(NODE), add count is $(ADD), remove count is $(REMOVE), update count is $(UPDATE), search count is $(SEARCH).\033[0m"
	@echo "\033[0;34mIf you want to change these values, you can change the values from makefile.\033[0m"
	@echo "\033[0;33mmake | doc | clean | cleandoc | re | redoc | fclean | run | random\033[0m"

random: $(CLASSES)
	@java -Djava.compiler=NONE $(JFLAGS) RandomInputGenerator $(FILE) $(NODE) $(ADD) $(REMOVE) $(UPDATE) $(SEARCH)

run: $(CLASSES)
	@java -Djava.compiler=NONE $(JFLAGS) Main $(FILE)

%.class : %.java
	@javac $(JFLAGS) $<

doc : $(SRC)
	@javadoc $(JDOCFLAGS) $(SRC)
	@echo "\033[0;32mThe documentation has been created successfully.\033[0m"

clean:
	@rm -f $(CLASSES)
	@echo "\033[0;31mAll class files have been removed.\033[0m"

cleandoc:
	@rm -rf ./javadoc
	@echo "\033[0;31mThe documentation has been removed.\033[0m"

fclean: clean cleandoc

re: clean all

redoc: cleandoc doc

.PHONY: all run doc clean cleandoc re redoc fclean
