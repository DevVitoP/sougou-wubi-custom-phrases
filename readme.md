
<center><font color=#39c5bb>Author:<font color=#00ff88> Vito(DevVitoP,朮朮)</font></font></center>

# <font color=#ff8800>:zap:词库处理内容说明:zap:</font>
* <font color=#ff0088>实际使用：</font>    
> <font color=#00ffff>&nbsp;&nbsp;方案内`词库处理后`文件夹内有`测试理论码长`,`快速用户短语`,`词库针对练习`相关的文本,可根据目录名称找到。</font>    

* <font color=#ff0088>词库调整：</font>    
> <font color=#00ffff>&nbsp;&nbsp;`编码排序`,`码长分类排序`,`有无候选分类排序`相关的几个文件夹,用来方便用文本来快速处理词库，你可以用vim,nvim,gvim,notepad,emacs等高效的文本工具来处理后,简单的复制粘贴到同一个文件内,在拖给程序处理得到与之对应的`快速用户短语`用于实际使用。</font>    

* <font color=#ff0088>Fork SDK去工作：</font>    
> <font color=#00ffff>&nbsp;&nbsp;此工作的内容完全开放，rope为unlicense,因为要灵活,不做GUI,你可以在本rope的src内看到源码文件。如果你想添加简繁处理，可以加入opencc，本repo意在unlicense，opencc等有apache等要求，故不加入。为了方便阅读和使用，我已经简化了代码，你可以当作一个SDK使用，为了能够合适大部分人使用，src全部使用的是C语言，假如你有语法基础就可以考虑使用。(注:本人18，05后，目的词库已经维护差不多了,可能不会有更多的精力在词库上面了,后续可能不会再维护此rope)。</font>

## <font color=#ffff88>:fire:关于`快速用户短语`的说明: :fire:</font> 
* <font color=#ff0088>此内容主要解决搜狗五笔的用户自定义短语慢的问题：</font>    

* <font color=#ff0088>方案一：</font>    
> <font color=#00ffff>&nbsp;&nbsp;(Phrases.ini)是根据其内置的极少量系统短语的编排方式可能的规律来工作(长度分区再排序);</font>    

* <font color=#ff0088>方案二：</font>    
> <font color=#00ffff>&nbsp;&nbsp;方案二(BBST\_Phrases.ini)是根据实际使用经验,当自定义了几十万的时候,搜狗五笔会在每次输入的时候会卡顿，考虑其是在内部读为平衡搜索树，尝试以将输入词库读入到一棵AVL树中，以层序输出，这样要是软件内部同样是内存中读入树，则读入的时候，不会在旋转调整平衡的时候浪费时间，以减少其在读入的时候的时间。</font>    
 
* <font color=#ff0088>建议使用方案二：</font>    
> <font color=#00ff88>&nbsp;&nbsp;&nbsp;&nbsp;在实际的使用中，方案一和方案二不能感知出区别，但方案一是不平衡的树，读入时有旋转操作，所以用方案二。</font>    

## :boom:关于`词库上手练习`:boom:
 
> <font color=#88ff00>&nbsp;&nbsp;&nbsp;&nbsp;可以载入`词库针对练习`相关文本夹内的文本，</font>    
> <font color=#88ff00>`针对词库练习文本`目录内的`practice.txt`,是本词库的`1简1`,`1简2`,`2简1`的并集</font>    
> <font color=#88ff00>词库对应具体打法可以快速阅览目录下的`practice_codec.txt`(只含里面有practice.txt的单字的编码)</font>    


<center><font color=#39c5bb>Author:<font color=#00ff88> Vito(DevVitoP,朮朮)</font></font></center>
<center><font color=#39c5bb>https://github.com/DevVitoP/sougou-wubi-custom-phrases.git</font></font></center>

