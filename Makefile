CC = g++
CXXFALG = -g

ne:nested-extract.cpp
	$(CC) $^ $(CXXFALG) -o  $@

test:test.cpp
	$(CC) $^ -o  $@

