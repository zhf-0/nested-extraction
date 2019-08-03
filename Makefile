CC = g++
CXXFALG = -g

ne:nested-extract.cpp
	$(CC) $^ $(CXXFALG) -o  $@

test:test.cpp
	$(CC) $^ -o  $@

PHONY:all try1 try2 try3 try4 try5 try6

all: try1 try2 try3 try4 try5 try6
 
try1:
	./ne -p "2-1"  -a '''\MS{10:30--10:55}{\Hyperlink{hollbachersusanne}{H\"{o}llbacher, Susanne} }{}{AMCS, KAUST}{\nGradient-consistent finite}'''

try2:
	cat a.txt | ./ne -p "2-1"

try3:
	./ne -p "2-1" -f a.txt

try4:
	./ne -r "2-1;zhf"  -a '''\MS{10:30--10:55}{\Hyperlink{hollbachersusanne}{H\"{o}llbacher, Susanne} }{}{AMCS, KAUST}{\nGradient-consistent finite}'''

try5:
	./ne -R "2-1;zhf"  -a '''\MS{10:30--10:55}{\Hyperlink{hollbachersusanne}{H\"{o}llbacher, Susanne} }{}{AMCS, KAUST}{\nGradient-consistent finite}'''

try6:
	./ne -r "2-1;zhf;4;hello"  -a '''\MS{10:30--10:55}{\Hyperlink{hollbachersusanne}{H\"{o}llbacher, Susanne} }{}{AMCS, KAUST}{\nGradient-consistent finite}'''
