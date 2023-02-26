# CustomDataStructures
Custom built data structures for some of the most popular STL data structures  
All functionality may not be available for a particular data structure as STL  
The purpose of this repo is to demonstrate how containers and data structures within STL are manifested, not to say that the implementation here matches the STL one but the concept more or less remains the same.  

## Build instructions
This project aims at building a shared library for data structure implementations containing source files  
Some data structures use templates thus eliminating the need of a source file. For instance `Vector` and `List` can be used as headers only  
You might find implementation of such templates in source file but that is to keep the sources separate from the class structure in the header  
If the project is loaded in VSCode click **Clean Reconfigure All** followed by **Clean Rebuild All**  
If you're working on the command line, create a `build` dir in the project root and run the following commands within it  
```
cmake ..
make
```
The shared lib should be generated in the lib directory if there are appropriate sources for the data structures as explained above  
If there are no errors and no shared library is generated, use the include path `path/to/CustomDataStructures/include` in your project and simply include the respective headers to import the custom data structure functionality  

Shopping cart app (https://github.com/amoldhamale1105/ShoppingCart) serves as a usage reference of this library and API. In case of any questions or clarifications, you can reach out to me at amoldhamale1105@gmail.com  

## Contribution
As usual, the code here is not perfect so feel free to raise PRs by creating a branch against master, report issues and make suggestions  
The changes will be reviewed and merged if approved  

