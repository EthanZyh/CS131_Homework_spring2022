# ChocoPy PA2

student1: zhangyh5@shanghaitech.edu.cn
student2: yuanwd@shanghaitech.edu.cn

Compile the python 3.6 front-end code to type checked AST tree. [Start from using docker](./doc/common/build.md) and see the [doc](./doc/PA2/README.md).

## writeup

### 设计

**semantic部分：**

在visit遍历树的过程中，建立起scope的树状结构。绝大多数问题都可以在顺序dfs语法树的同时维护。但有两点例外：

- 变量定义、参数定义、函数返回值定义中，type可以是程序后面定义的class。解决方法：我们在DeclarationAnalyzer里加入一个类型为`set<string>`的成员变量，用来记录这个程序定义过的class名字。在program的visit里，可以预处理：直接枚举declarations来设定这个变量（因为classDef都在最顶层）。获得这个变量后，我们在check某个type的时候，不仅仅去查符号表，也查这个变量；以此来避免这个时候的符号表还不“认识”此class的问题。

- 函数内，nonlocal和global声明的变量，其定义可以在当前函数的后面。解决方法：在program, FuncDef以及ClassDef中枚举declarations时，先visit其中的VarDef，再visit其他。

semantic部分对statement所做的要求较少，主要是检查AssignStmt中被赋值的变量是否在当前scope里定义过，以及部分函数的return的存在性。为了完成后者的检查，我们在DeclarationAnalyzer中加入一个类型为`bool`的变量，用来记录当前visit到的节点里，是否所有的path都有return。对于条件语句，这个变量需要特殊维护：只有then, elif, else代码块（如果存在）都有return，才算这个条件语句的所有path都有return。



**type部分:**

整棵树的根是Program节点，所以在进入Program节点时先建一棵class继承关系树，记录每个class的father和他的son，通过在树上遍历来求LCA和path来求继承关系，整体的思想是从上往下不断visit, 但问题在于不同位置的相同种类节点可能需要返回的东西不一致，比如说function的identifier()和variable的identifier。所以在某些特殊的节点我们截断了某些节点的向下访问，在父级手动的去visit他的节点以实现个性化的visit.

type部分主要解决了

- 如何判断赋值语句的可行性(TypeError: Expected #1, get #2)
- 判断function的参数是否合法(type错误或者数量错误)
- 对于不同的节点如何个性化的向下visit，并尽最大可能的去优化了流程



### 成员分工

张英皓负责semant部分，袁维铎负责type部分



### 小组交流

与王鹏程(wangpch@shanghaitech.edu.cn)进行过交流，无代码共享，由于文档不够全面，交流了部分typeError的原因及判别方式。