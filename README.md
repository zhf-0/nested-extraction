# nested extraction

The command line tool `nested extraction`, abbreviated as `ne` is orignally designed to extract information from `latex`. But it can also be used to extract any content between any pair of symbols from strings. For now, its functionality will only be demonstrated within `latex`.

Some other command line tools, like`awk`, can also extract content from a pair of symbols, but it is not easy to extract content from nested pari of symbols, which is quite common in `latex`. With the help of`ne`,the solution will be much easy and intuitive.

## Usage
The input of `ne` can be a single string, or a file, or through pipeline. The options are:
- `-h`: display help information
- `-a`: the string that needed to be dealt with
- `-s`: using which pair of symbols to split the string, default symbols are '{}'
- `-f`: the name of file that needed to be dealt with
- `-p`: print which part of string, default behavior is printing the whole string
- `-d`: using which delimiter to seperate the output, default symbol is ':'
- `-r`: replace the selected content with new content, exclude the pair of symbols
- `-R`: replace the selected content with new content, include the pair of symbols

## Example
if the single string is
```bash
\MS{1991}{\Hyperlink{abc}{H\"{o}bby} }{male}{AMerica}{e^{2x}}
```
and the content of input file`a.txt` is:
```bash
\MS{1991}{\Hyperlink{abc}{H\"{o}bby} }{male}{AMerica}{e^{2x}}
\MS{1993}{\Hyperlink{de}{Helen }{female}{AMerica}{\sum^{n}_{i=1}a_i}
```

Firstly, you have to decide to use which kind of input:
- if the input is a single string,
```bash
ne -a '''\MS{1991}{\Hyperlink{abc}{H\"{o}bby} }{male}{AMerica}{e^{2x}}'''
```
- if the input is the file`a.txt`,
```bash
ne -f a.txt
```
- if the input is through pipeline,
```bash
cat a.txt | ne
```

Once set up the input, you shoud decide to use which pair of symbols to sepreate one string. By default, the pair of symbols are `{`and`}`, but you can also use other symbols, for example `()`. The way to set  a new pair of symbols is
```bash
ne -s "()"
```

Next is the part of output.`ne` can parse the input and store positions of the nested pair of symbols in a tree. The index begins with 0, but it means printing the whole string, which won't be used in normal cases. Taking the following string as an example
```bash
\MS{1991} {\Hyperlink{abc}{H\"{o}bby}} {male} {AMerica} {e^{2x}}
```
There are five parts within each pair of`{}`. Especially, the second  and fiveth part include nested content. Without the `-p` option, the program will just print the whole string. The syntax of `-p` is
- if you want to print the first part, `1991`
```bash
ne -a '''\MS{1991} {\Hyperlink{abc}{H\"{o}bby}} {male} {AMerica} {e^{2x}}'''  -p 1
```
- if you want to print the first, second and third part,
```bash
ne -a '''\MS{1991} {\Hyperlink{abc}{H\"{o}bby}} {male} {AMerica} {e^{2x}}''' -p "1;2;3"
```
- if you want to print the nested part`abc`and`H\"{o}bby`,
```bash
ne -a '''\MS{1991} {\Hyperlink{abc}{H\"{o}bby}} {male} {AMerica} {e^{2x}}''' -p "2-1;2-2"
```

When there are multiple outputs, the default delimiter is `:`, you can change the delimiter to`;` by
```bash
ne -a '''\MS{1991} {\Hyperlink{abc}{H\"{o}bby}} {male} {AMerica} {e^{2x}}''' -p "1;2;3" -d ";"
```

Other than printing the selected parts, you can substitue the selected part with new content by `-r`and`-R`, then print out the new string. The difference between`-r`and`-R`is:`-r`will only subsitute the content within the pair of symbols, but`-R` will subsitute the selected content and the pair of symbols.
- if you want to substitue`1991`with`1994`
```bash
ne -a '''\MS{1991} {\Hyperlink{abc}{H\"{o}bby}} {male} {AMerica} {e^{2x}}''' -r "1;1994"
```
- if you want to substitue`{1991}`with`(1994)`
```bash
ne -a '''\MS{1991} {\Hyperlink{abc}{H\"{o}bby}} {male} {AMerica} {e^{2x}}''' -R "1;(1994)"
```
- if you want to substitue`1991`with`1994`and substitue the third part`male`with`female`
```bash
ne -a '''\MS{1991} {\Hyperlink{abc}{H\"{o}bby}} {male} {AMerica} {e^{2x}}''' -r "1;1994;3;female"
```
- if you want to substitue`1991`with`1994`and delete the third part`male`
```bash
ne -a '''\MS{1991} {\Hyperlink{abc}{H\"{o}bby}} {male} {AMerica} {e^{2x}}''' -r "1;1994;3;"
```
Warning: if you want to use`-r`to delete the content, don't miss the final`;`! Because in the program, the command argument`1;1994;3;` will be splited into 4 parts, and the forth part is empty. Using empty to substute content acts like delete. Without the final`;`, the program doesn't how to do, Althought sometimes it may works, but it's not safe! 

## need to do in the future
- add debug module
- add modern `try...except`


`vector`越界检查，对于
```cpp
./ne -R "2-1;zhf;4"  -a '''\MS{10:30--10:55}{\Hyperlink{hollbachersusanne}{H\"{o}llbacher, Susanne} }{}{AMCS, KAUST}{\nGradient-consistent finite}'''
```
程序会正常运行，得到和
```cpp
./ne -R "2-1;zhf;4;"  -a '''\MS{10:30--10:55}{\Hyperlink{hollbachersusanne}{H\"{o}llbacher, Susanne} }{}{AMCS, KAUST}{\nGradient-consistent finite}'''
```
相同的结果，但是上一个程序在运行过程中超过了`vector`的界限，如果使用`vec.at(n)`会使程序变慢。应该严格按照格式要求输入。