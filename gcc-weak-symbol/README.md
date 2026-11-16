# GCC Weak Symbol 实验

**作者：AnQing**

本项目通过独立的 C 语言实验，研究 GCC 弱符号（Weak Symbol）机制，以及 ELF 链接阶段的符号解析规则。

通过实际编译、链接和反汇编，理解弱函数定义、强函数覆盖、符号属性以及重定位机制。

## 1. 实验内容

1. GCC `__attribute__((weak))` 弱函数定义
2. 强符号覆盖弱符号
3. 多个弱符号的链接行为
4. 多个强符号重复定义
5. LOCAL、GLOBAL、WEAK 符号属性分析
6. 使用 nm、readelf、objdump 分析目标文件
7. ELF 符号解析与重定位机制

## 2. 实验环境

| 项目 | 版本或说明 |
|---|---|
| 操作系统 | Ubuntu 22.04 |
| GCC | 11.4.0 |
| Binutils | GNU Binutils |
| 目标格式 | ELF 64-bit |
| 编程语言 | C |

## 3. 文件说明

| 文件 | 作用 |
|---|---|
| main.c | 主程序，调用 test_hook() |
| weak_hook.c | 定义默认弱函数 |
| weak_hook2.c | 定义第二个弱函数 |
| strong_hook.c | 定义强函数 |
| strong_hook2.c | 定义第二个强函数 |
| local_hook.c | 验证 LOCAL 和 GLOBAL 符号属性 |

## 4. 实验一：默认弱函数调用

编译命令：

```bash
gcc main.c weak_hook.c -o test_weak
```

运行：

```bash
./test_weak
```

预期输出：

```text
Program start
Weak function called
```

验证只有弱函数定义时，程序可以调用默认弱函数。

## 5. 实验二：强函数覆盖弱函数

编译命令：

```bash
gcc main.c weak_hook.c strong_hook.c -o test_strong
```

运行：

```bash
./test_strong
```

预期输出：

```text
Program start
Strong function called
```

验证存在同名强符号和弱符号时，强符号优先。

## 6. 实验三：多个弱函数的链接行为

编译命令：

```bash
gcc main.c weak_hook2.c weak_hook.c -o test_weak_duplicate2
```

运行：

```bash
./test_weak_duplicate2
```

预期输出：

```text
Program start
Second weak function called
```

交换两个弱函数目标文件的链接顺序：

```bash
gcc main.c weak_hook.c weak_hook2.c -o test_weak_duplicate
```

通过两次实验观察多个同名弱符号参与链接时的选择行为。

注意：这里的结果与本次 Ubuntu GCC/ld 实验环境及链接输入顺序有关，不应将其简单推广为所有工具链的统一保证。

## 7. 实验四：多个强函数重复定义

编译命令：

```bash
gcc main.c strong_hook.c strong_hook2.c -o test_duplicate
```

预期结果：

链接失败，出现 `multiple definition of test_hook` 错误。

验证同一个程序中存在多个同名强定义时，链接器会报告重复定义错误。

## 8. 实验五：符号属性分析

编译：

```bash
gcc -c local_hook.c -o local_hook.o
```

查看符号表：

```bash
readelf -s local_hook.o
```

观察以下符号：

- `local_hook`：LOCAL，局部符号。
- `public_hook`：GLOBAL，全局符号。

查看弱符号和强符号：

```bash
nm weak_hook.o
nm strong_hook.o
```

观察：

- `W`：弱定义符号。
- `T`：位于代码段的全局强定义符号。
- `U`：未定义符号引用。

## 9. 常用分析工具

| 工具 | 用途 |
|---|---|
| nm | 查看目标文件符号表 |
| readelf | 分析 ELF 文件及符号属性 |
| objdump | 反汇编、查看重定位记录 |
| gcc | 编译与链接实验程序 |

常用命令：

```bash
nm main.o
readelf -s weak_hook.o
objdump -dr main.o
objdump -d test_strong
```

## 10. 实验总结

通过本次实验，验证了 GCC 弱函数的基本覆盖机制，并结合 nm、readelf、objdump 等工具观察了编译和链接过程中的符号信息。

实验表明，弱函数机制不仅涉及 C 语言层面的函数定义，还与目标文件符号属性、链接器符号解析以及重定位处理密切相关。

通过从代码编写到编译、链接、反汇编的完整实验过程，加深对 GCC、ELF 和链接器工作机制的理解。

---

**AnQing | Embedded Software Engineering & Technology Research**
