# nested extract

## need to do 
- add debug module
- option `-f`, deal with file. seperate path and file name in C++
- the same option with multiple parameters, how to tell them apart
- input string without symbol`\`

`vector`越界检查，对于
```cpp
./ne -R "2-1;zhf;4"  -a '''\MS{10:30--10:55}{\Hyperlink{hollbachersusanne}{H\"{o}llbacher, Susanne} }{}{AMCS, KAUST}{\nGradient-consistent finite}'''
```
程序会正常运行，得到和
```cpp
./ne -R "2-1;zhf;4;"  -a '''\MS{10:30--10:55}{\Hyperlink{hollbachersusanne}{H\"{o}llbacher, Susanne} }{}{AMCS, KAUST}{\nGradient-consistent finite}'''
```
相同的结果，但是上一个程序在运行过程中超过了`vector`的界限，如果使用`vec.at(n)`会使程序变慢。应该严格按照格式要求输入。