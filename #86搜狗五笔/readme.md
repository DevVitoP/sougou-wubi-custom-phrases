<center><font color=#39c5bb>Author:<font color=#00ff88> Vito(DevVitoP,朮朮,小斌,小斌鹏)</font></font></center>

# <font color=#ff8800>:zap:编码表说明:zap:</font>
> <font color=#00ffff>:star:目录内`86短语BBST.ini`为搜狗五笔自定义短语的定制的码表;</font>     
> <font color=#00ffff>编码同搜狗默认UTF-16LE,因为有fffe开头,UTF-8也能打开;</font>    
> <font color=#00ffff>可以在自定义短语功能中粘贴内容或替换文件。</font>    


## <font color=#ffff88>:boom:本词库的上手:boom:</font>
> <font color=#00ffff>&nbsp;&nbsp;本词库就是86词库，打法并没有变，重点熟悉`1简1`,`1简2`,`2简1`现在的顺序就可以上手</font>    
> <font color=#00ffff>`针对词库练习文本`目录内的`practice.txt`,是本词库的`1简1`,`1简2`,`2简1`的并集</font>    
> <font color=#00ffff>具体打法可以快速阅览目录下的`practice_codec.txt`(只含里面有的单字的编码)</font>    

## <font color=#ffff88>:fire:关于编码表的优化:fire:</font> 
* <font color=#ff0088>大体问题描述：</font>    

> <font color=#00ffff>:one:.键名字太长，单键4连打慢;</font>    

> <font color=#00ffff>:two:.简码交集大;</font>    

> <font color=#00ffff>:three:.词库词编码不对,打不出,还乱占地方;</font>    

> <font color=#00ffff>:four:.依靠词频表定词序很粗糙。</font>    

> <font color=#00ffff>:five:.首选词编码少，首选占比$ \frac{74649}{\frac{25(1-25^4)}{1-25}}$甚至不到$\frac{1}{4}$,理码过长。</font>    

> <font color=#00ffff>:six:.编码量过大，且无序，搜狗短语读入时间复杂度高。</font>    

> <font color=#00ffff>:seven:.(新增)词库不兼容金山打字通的五笔。</font>    

* <font color=#ff0088>解决方案：</font>    

> <font color=#00ffff>:one:.`1简2`规律,令`键名字`在2号位置。</font>    
> <font color= #ffff88>&nbsp;&nbsp;下面被括号括起来的表示不是键名字，而是实际输入，由实际经验而来。</font>    
> |输入：|单键|+|2|||
> |-|-|-|-|-|-|
> |撇区|金|(您)|月|白|禾|
> |捺区|言|(着)|水|火|之|
> |横区|(藏)|木|大|土|王|
> |竖区|目|日|口|田|山|
> |折区|已|子|女|又|纟|

> |输入:|剩余键名字|
> |-|-|
> |w|人|
> |a|工|
> |uu|立|

> <font color=#00ffff>:two:.`2简1`修改：</font>    
> <font color=#00ff88>:star:1.保留直观的2简;</font>    
> <font color=#00ff88>:star:2.尽可能去除与`1简1`,`1简2`交集;</font>    
> <font color=#00ff88>:star:3.尽可能调入调频难打字;</font>    

> <font color=#00ffff>:three:.所有词录入之前要么反编码，要么反编码检测；</font>

> <font color=#00ffff>:four:.基于常用单字1500进行更改，使常单1500尽可能盲打出来。当字的使用不如词的时候，它将被置后，尽可能地在2号位置(为生文杂文提速)。</font>    

> <font color=#00ffff>:five:.逻辑代码分出有重码的编码,将重码完全浏览根据认知逐一更改顺序。</font>    

* <font color=#00ff88>词频调整:</font>    
> <font color=#00ff88>:star:1.受`1简1`,`1简2`,`2简1`的影响，如果说两词实际实用中差不多，简码能打出来的将被后置;</font>    
> <font color=#00ff88>:star:2.当两词使用情况差不多，而打单时单字更难打更不直观的会被前置;</font>    
> <font color=#00ff88>:star:3.简体在繁体前面;</font>    

> <font color=#00ff88>注:此86词库有几万多行字词有重码;</font>    
> <font color=#00ff88>大约两天改了一遍,共改了两遍。</font>    

> <font color=#00ffff>:six:.考虑搜狗读入时间的解决方法：</font>    
> <font color=#00ff88>:star:1.根据内置的极少量短语的规律生成表(对每个长度的编码分区排序)，但如果读入树，此树相对不那么平衡;</font>    
> <font color=#00ff88>:star:2.考虑搜狗读入内存为了搜索会建立AVL树，则可以先外部生成AVL，再层序输出录入到表中，以使搜狗读入时旋转操作的执行为零(实际效果相当不错)。</font>    

> <font color=#00ffff>:seven:.将金山打字通的的词纳入，向下兼容原词库；</font>    

> <font color=#00ffff>:eight:.进行不少于100次打文测试并评估调整。</font>    

> <font color=#00ffff>:nine:.实际使用与打文,评估调整(进行中……)</font>    



## <font color=#ffff88>:boom:词库的说明:boom:</font>
* <font color=#ff0088>工作继承</font>
> <font color=#00ff88>:star:1.本项目的内容完全开放开源，repo为unlicense，你可以随意使用;</font>    
> <font color=#00ff88>:star:2.本项目源码可以当作一个SDK，为了使用操作灵活，方便阅读，不制作GUI;</font>    
> <font color=#00ff88>:star:3.如果你想添加简繁处理，可以加入opencc，本repo意在unlicense，opencc等有apche等要求，故不加入。</font>    

* <font color=#ff0088>性能展示</font>

|文本来源|理码|
|-|-|
|(跟打器)18w测试文本|1.91|
|...|...|

<center><font color=#39c5bb>Author:<font color=#00ff88> Vito(DevVitoP,朮朮,小斌,小斌鹏)</font></font></center>
<center><font color=#39c5bb>https://github.com/DevVitoP/sougou-wubi-custom-phrases.git</font></font></center>
