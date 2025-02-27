<center><font color=#ffa500>Author</font>:<font color=#39c5bb> Vito(DevVitoP,朮朮):tada:</font></center>

## :sparkles:编码表说明:sparkles:
> <font color=#ffa500>:star:目录内`BBST_Phrases.txt`</font>:<font color=#39c5bb>为`PC搜狗五笔`自定义短语的定制的码表;</font>     
> <font color=#ffa500>:star:目录内`scheme(for_android)/86scheme.txt`</font>:<font color=#39c5bb>为`手机搜狗`方案的定制的码表;</font>     

## :sparkles:入手词库:sparkles:
* <font color=#39c5bb>&nbsp;&nbsp;本词库向下完全兼容原版86(编码有2简词区别)</font>
> <font color=#39c5bb>$\begin{cases} 编码重点熟悉[2简2词] \\ 编码顺序熟悉[1简1,1简2,2简1] \end{cases} $</font>    


> <font color=#ffa500>`针对词库练习文本`目录内的`practice.txt`</font>:
<font color=#39c5bb>是本词库的`1简1`,`1简2`,`2简1`的并集,
    具体编码可以快速阅览目录下的`practice_codec.txt`</font>    

## :sparkles:编码表优化:sparkles: 
* <font color=#ff0044>大体问题描述：</font>    

> <font color=#39c5bb>:one:.键名字太长,单键4连打慢;</font>    

> <font color=#39c5bb>:two:.简码交集影响大;</font>    

> <font color=#39c5bb>:three:.词库词编码不对,打不出,还乱占地方;</font>    

> <font color=#39c5bb>:four:.依靠词频表定词序很粗糙;</font>    

> <font color=#39c5bb>:five:.编码少,首选占比$ \frac{75000(原编码量)}{\frac{25(1-25^4)}{1-25}(理论编码量)}$,太小不到$\frac{1}{4}$,理码过长;</font>    

> <font color=#39c5bb>:six:.无规则编码量过大,PC搜狗短语读入时间复杂度高;</font>    

> <font color=#39c5bb>:seven:.(新增1)词库缺少金山打字通练习文本的五笔编码;</font>    

> <font color=#39c5bb>:eight:.(新增2)简码编码空挂,集中在1简3,2简2,2简3,3简1.</font>    


---


* <font color=#ff0044>解决方案：</font>    

> <font color=#39c5bb>:one:.增加`1简2`规律:令`键名字`在2号位置。</font>    
> <font color=#ff0044>&nbsp;&nbsp;下面被括号括起来的位置,键名字已经存在对应(1简1,2简1),故改为高频字</font>    

<font color=#ffa500>

|输入：|单键|+|2|||
|-|-|-|-|-|-|
|撇区|金|(您)|月|白|禾|
|捺区|言|(着)|水|火|之|
|横区|(藏)|木|大|土|王|
|竖区|目|日|口|田|山|
|折区|已|子|女|又|纟|

|输入:|剩余键名字|
|-|-|
|w|人|
|a|工|
|uu|立|

</font>


> <font color=#39c5bb>:two:.`2简1`修改：</font>    
> <font color=#39c5bb>:star:1.保留直观的2简;</font>    
> <font color=#39c5bb>:star:2.尽可能去除与简码交集;</font>    
> <font color=#39c5bb>:star:3.尽可能调入高频难打字;</font>    

> <font color=#39c5bb>:three:.所有词录入之前要么反编码,要么反编码检测,确保正确性(不含2简2,2简3的检测);</font>

> <font color=#39c5bb>:four:.序号优化</font>    
> <font color=#39c5bb>:star:1.基于常用单字1500进行更改,使常单1500尽可能占1号位。当字频率不如词的时候,它将被置后,尽可能地在2号位置(为生文杂文提速);</font>    
> <font color=#39c5bb>:star:2.代码逻辑分出有重码的编码,将重码完全浏览根据认知逐一更改顺序。</font>    
> <font color=#39c5bb>:star:3.受`1简1`,`1简2`,`2简1`的影响,如果说两词实际实用中差不多,简码能打出来的将被后置;</font>    
> <font color=#39c5bb>:star:4.当两词使用情况差不多,而打单时单字更难打更不直观的会被前置;</font>    
> <font color=#39c5bb>:star:5.简体在繁体前面;</font>    
> <font color=#39c5bb>&nbsp;&nbsp;注:此86词库有几万多行编码含重(人工4天内改了两遍);</font>    

> <font color=#39c5bb>:five:.扩充编码量;</font>    
> <font color=#39c5bb>:star:1.根据词频表反编码;</font>    
> <font color=#39c5bb>:star:2.收集网络方案(减少词频表过时性)</font>    

> <font color=#39c5bb>:six:.考虑搜狗读入时间的解决方法：</font>    
> <font color=#39c5bb>:star:1.根据内置的极少量短语的规律生成表(即对每个长度的编码分区排序),但如果读入此树,此树相对不那么平衡,会存在旋转操作;</font>    
> <font color=#39c5bb>:star:2.考虑搜狗读入内存为了搜索会建立AVL树,则可以先外部生成AVL,再层序输出录入到表中,以使搜狗读入时旋转操作的执行为零(编码量大时实际效果相当不错)。</font>    

> <font color=#39c5bb>:seven:.将金山打字通的的词纳入,向下兼容原词库;</font>    

> <font color=#39c5bb>:eight:.增加2简词,位置在2,3号位置;增加3简词(魔改,2025年1月20日23:35:52)</font>    

> <font color=#39c5bb>校正:one:.进行不少于100次打文测试并评估调整。</font>    

> <font color=#39c5bb>校正:two:.过量的实际使用与打文评估调整(进行中……)</font>    


## :sparkles:工作说明:sparkles:
* <font color=#ff0044>工作继承</font>
> <font color=#39c5bb>:star:1.本项目的内容完全开放开源,repo为unlicense,请随意使用;</font>    
> <font color=#39c5bb>:star:2.本项目源码可以当作一个SDK,为了使用操作灵活,方便阅读,不制作GUI;</font>    
> <font color=#39c5bb>:star:3.如果你想添加简繁处理,可以加入opencc,本repo意在unlicense,opencc等有apache等要求,故不加入。</font>    

* <font color=#ff0044>性能评估</font>

|文本来源|理码|
|-|-|
|(跟打器,作者:消逝)18w内部测试文本|1.94|
|...|...|

<center><font color=#ffa500>Author</font>:<font color=#39c5bb> Vito(DevVitoP,朮朮):tada:</font></center>

<center><font color=#39c5bb>https://github.com/DevVitoP/sougou-wubi-custom-phrases.git</font></center>
