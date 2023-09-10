# Custom Data Structures
Custom built data structures for some of the most widely used data structures in C++  
The purpose of this repo is to demonstrate how containers and data structures work under the hood. Most of the APIs match the standard API found within STL and Boost libraries. In fact, there are few valuable enhancements and additions to what the standard libraries offer.  

The following data structures are implemented at the time of writing this readme:
- Graph
- Hashmap
- Priority Queue
- List
- Pair
- Queue
- Stack
- String
- Trie
- Vector  

Except `String` and `Trie` which are type specific, all other data structures are generically implemented as templates making them usable across different datatypes.  
> **__Note:__** Specializations may have to be defined for non-primitive types using special methods within an applicable data structure type

## Build instructions
For ready to use library, check out [Releases](https://github.com/amoldhamale1105/CustomDataStructures/releases)  

Most of the data structures use templates thus eliminating the need of a separate source file. For instance, `Vector` can be used as header only. The generated library will only be required for types with non-generic implementation and a separate source file. As of the writing of this readme, you need your application to link with `libCustomDataStructures.so` only if you're using the `String` and `Trie` data structures.  

To the build the project, use the build script in the source tree with `-a` option as follows:   
```
./build.sh -a
```
Clean generated output and build artifacts with the `-c` option
```
./build.sh -c
```
To know usage details for other options like build type and generator configuration, use the `-h` option with the script
```
./build.sh -h
```
[Shopping cart](https://github.com/amoldhamale1105/ShoppingCart) app serves as a usage reference of the custom data structures implemented here.  

## Contribution
If writing code for data structures and algorithms in C++ and dogfooding makes you tick like me, I'm sure you'll enjoy contributing to this project. If you know anyone who might be interested in such work, do let them know. I'm looking for looking for some exciting enhancements and additions and a critical review of existing implementation.    

As a potential contributor you are welcome to
- Review pull requests and open issues and check if you can resolve any of them
- Create new issues for bugs or feature requests so that either I or others in the community can get to it
- Raise PRs to address existing issues, to fix potential bugs or make any improvements to existing source code

I am reachable at amoldhamale1105@gmail.com for anything  
  

