# Default target
all: run

debug:
	@mkdir -p output
	python3 GTUC312.py ./sep_thread/1.txt -D 3 > output/1.txt 2>&1
	python3 GTUC312.py ./sep_thread/2.txt -D 0 > output/2.txt 2>&1
	python3 GTUC312.py ./sep_thread/3.txt -D 0 > output/3.txt 2>&1
	python3 GTUC312.py ./sep_thread/4.txt -D 0 > output/4.txt 2>&1
	python3 GTUC312.py ./sep_thread/5.txt -D 0 > output/5.txt 2>&1
	python3 GTUC312.py ./sep_thread/6.txt -D 0 > output/6.txt 2>&1
	python3 GTUC312.py ./sep_thread/7.txt -D 0 > output/7.txt 2>&1
	python3 GTUC312.py ./sep_thread/8.txt -D 0 > output/8.txt 2>&1

run: help
	@echo "\033[1;33m"
	@echo "make debug to run each thread seperately and dump output to output/ directory"
	@echo "\033[1;32m"
	@echo "Dumping all output to <output file>..."
	@echo "Usage: python3 GTUC312.py <filename> -D <debug mode> > <output file> 2>&1"
	@echo "\033[0m"
	@echo "\033[1;34m"
	@echo "Dumping only print syscall to <output file>..."
	@echo "Usage: python3 GTUC312.py <filename> -D <debug mode> > <output file>"
	@echo "\033[0m"


help:
	@echo "\033[1;33m"
	@echo "==== GTU-C312 CPU Simulator Usage ===="
	@echo "Available commands:"
	@echo "  LEVEL=0 - Run with debug level 0 (memory dump only at end)"
	@echo "  LEVEL=1 - Run with debug level 1 (memory dump after each instruction)"
	@echo "  LEVEL=2 - Run with debug level 2 (memory dump after each instruction with user prompt)"
	@echo "  LEVEL=3 - Run with debug level 3 (thread table dumb only during context switches and system calls)"
	@echo "\033[0m"

.PHONY: all run help