<center><font color=#ffa500>Author</font>:<font color=#39c5bb> Vito(DevVitoP,朮朮):tada:</font></center>

## :sparkles:词库处理内容说明:sparkles:
* <font color=#ffa500>使用:</font>    
> <font color=#39c5bb>&nbsp;&nbsp;`词库处理后`文件夹内有`测试理论码长`,`用户短语`,`针对词库练习`功能相关的文本,可根据目录名称找到。</font>    

* <font color=#ffa500>个人调整:</font>    
> <font color=#39c5bb>&nbsp;&nbsp;`编码排序`,`码长分类排序`,`有无候选分类排序`相关的几个文件夹,用来方便用文本工具来快速处理词库,你可以用vim,nvim,gvim,notepad,emacs等高效的文本工具来处理</font>    

* <font color=#ffa500>Fork SDK:</font>    
> <font color=#39c5bb>&nbsp;&nbsp;此工作的内容完全开放,repo为unlicense,因为要灵活,不做GUI,
你可以在本repe的src内看到源码文件。如果你想添加简繁处理,可以加入opencc,
本repo意在unlicense,opencc等有apache等要求,故不加入;
为了方便阅读和使用,我已经简化了代码,你可以当作一个SDK使用;
为了能够合适大部分人使用,src全部使用的是C语言,
假如你有语法基础就可以考虑使用;
(注:本人18,目前词库已经维护差不多了,
可能不会有更多的精力在词库上面了,后续可能不会再维护此repo)。</font>

## :sparkles:`快速用户短语`说明: :sparkles: 
* <font color=#ffa500>此内容主要解决搜狗五笔的用户自定义短语卡顿问题:</font>    

> <font color=#39c5bb>:star:1.根据内置的极少量短语的规律生成表(即对每个长度的编码分区排序),但如果读入此树,此树相对不那么平衡,会存在旋转操作;</font>    
> <font color=#39c5bb>:star:2.考虑搜狗读入内存为了搜索会建立AVL树,则可以先外部生成AVL,再层序输出录入到表中,以使搜狗读入时旋转操作的执行为零(编码量大时实际效果相当不错)。</font>    
 
## :sparkles:`词库练习`说明:sparkles:
 
> <font color=#39c5bb>`针对词库练习`目录内的`practice.txt`,是词库的`1简1`,`1简2`,`2简1`的并集</font>    
> <font color=#39c5bb>可以快速阅览目录下的`practice_codec.txt`熟悉打法</font>    


<center><font color=#ffa500>Author</font>:<font color=#39c5bb> Vito(DevVitoP,朮朮):tada:</font></center>

<center><font color=#39c5bb>https://github.com/DevVitoP/sougou-wubi-custom-phrases.git</font></center>
