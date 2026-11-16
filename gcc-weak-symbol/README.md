# GCC Weak Symbol 实验

本目录用于记录和验证 GCC 弱符号（Weak Symbol）机制，以及 ELF 链接阶段的符号解析规则。

## 实验内容

1. GCC `__attribute__((weak))` 弱函数定义
2. 强符号覆盖弱符号
3. 多个弱符号的链接行为
4. 多个强符号重复定义
5. LOCAL、GLOBAL、WEAK 符号属性分析
6. 使用 nm、readelf、objdump 分析目标文件

## 实验环境

- 操作系统：Ubuntu 22.04
- GCC：11.4.0
- Binutils：GNU Binutils
- 目标格式：ELF 64-bit

## 说明

本实验为独立编写的通用 C 语言示例，用于学习 GCC 编译、ELF 符号表及链接器行为。
