<!--
 * @Author: your name
 * @Date: 2021-03-06 19:22:25
 * @LastEditTime: 2021-03-06 20:02:43
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/README.temp.md
-->


https://azmddy.github.io/article/%E7%BC%96%E8%AF%91%E6%9E%84%E5%BB%BA/cmake-day-4.html
https://www.jianshu.com/p/7e4aa4be239a


1. cmake 包含源文件好的写法
2. cmake 配置本地相对库的头文件引用路径
3. 这些库，如何发布到vcpkg？？？？？


## 一个现代化工程需要哪些东西？

1. 编译脚本
2. 打包脚本、打包工作流（makefile）
3. 版本管理
4. 单元测试
5. 例子工程
6. lint工具
7. 提交卡点（过lint，过ut）
8. 模块化机制，包管理
9. ci集成
10. 出包（sdk/app）、分发自动化


## 一个现代化软件需要哪些东西？

11. 各种类别的基础库
12. 模块化（代码和资源）

资源模块化：
依赖关系单一化。所有CSS和图片等资源的依赖关系统一走JS路线，无需额外处理CSS预处理器的依赖关系，也不需处理代码迁移时的图片合并、字体图片等路径问题；
资源处理集成化。现在可以用loader对各种资源做各种事情，比如复杂的vue-loader等等。
项目结构清晰化。使用Webpack后，你的项目结构总可以表示成这样的函数：
dest = webpack(src, config)


 - 如果是前端，还有css模块化

BEM风格；
Bootstrap风格；
Semantic UI风格；
我们公司的NEC风格


1.  工程化
2.  组件化
3.  规范化（各种规范）

目录结构的制定
编码规范
前后端接口规范
文档规范
组件管理
Git分支管理
Commit描述规范
定期CodeReview
视觉图标规范

4. 自动化（各种能用工具的全用工具）
5. 持续集成
6. 构建部署测试自动化


## 参考：

https://www.zhihu.com/question/24558375