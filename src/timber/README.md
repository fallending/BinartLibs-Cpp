<!--
 * @Author: your name
 * @Date: 2021-03-24 11:21:18
 * @LastEditTime: 2021-03-25 18:39:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/timber/README.md
-->

# 日志中间层

> 一般我们将中间层作为策略层，不同的策略实现，称之为中间件


https://gitbook.cn/gitchat/column/5b2c5b29072e851cae4299f3/topic/5b2c633e072e851cae42a1aa
https://zhuanlan.zhihu.com/p/100082717


## TODO
https://www.google.com.hk/search?q=c%2B%2B+%E6%97%A5%E5%BF%97+%E7%BA%BF%E7%A8%8B%E5%AE%89%E5%85%A8&oq=c%2B%2B+%E6%97%A5%E5%BF%97+%E7%BA%BF%E7%A8%8B%E5%AE%89%E5%85%A8&aqs=chrome..69i57j0l3.474928j0j7&sourceid=chrome&ie=UTF-8
http://armsword.com/2016/09/10/a-high-performace-and-thread-safe-cpp-log-lib/
https://zhuanlan.zhihu.com/p/21477468


- [ ] 支持 logger << val << val2 << endl
- [ ] 支持 tag
- [ ] 支持 包含四种日志级别，分别为WARN、DEBUG、INFO、ERROR，日志级别大小依次递增
- [ ] 支持 可配置输出日志路径
- [ ] 支持 可配置输出日志前缀
- [ ] 支持 可定义输出的日志级别，默认DEBUG
- [ ] 支持 可定义日志文件切分大小
- [ ] 支持 支持多线程程序
- [ ] 支持 可定义日志往磁盘刷新的方式
- [ ] 支持 每天切换新的日志文件
- [ ] 支持 log文件被删除时，从新建立日志文件