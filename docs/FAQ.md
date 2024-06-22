# FAQ

## CMake / CMake-GUI 爆红字

如果是 warning 的话，有可能不必担心，看到 build 完成了可以 generate 即可。

如果是 error ，下面的几行里就包含报错信息。可以自己检索一下找找原因或者 Piazza 发帖。


## MacOS 上常见问题

- Could Not find X11: X11是一个图形窗口库。试一下 `brew install xquartz --cask` 命令安装 xquartz ，或者搜索一下相关信息，安装一个 X11 。
- CMake build 不出来：有往年同学反映过是 toolchain 需要用 gcc 而不能用 clang 。先 `brew install gcc` 安装一个gcc，再在根目录的 `CMakeLists.txt` 的第3行之前添加：
  ```
  set(CMAKE_C_COMPILER "/opt/homebrew/bin/gcc-14")
  set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-14")
  ```
- 因为历年 MacOS 问题五花八门而经验也较少，建议开始之前去看一下CMake教学视频。


## 我的游戏运行起来有 bug 但看不出在哪怎么办？

你之前的所有 debug 经验，在这个项目里都可以使用。你可以通过 `std::cout` 向控制台打印一些输出，可以将一些没有贴图的物体换上贴图以便显示，当然也可以使用 debugger ，在指定代码处打上断点或逐行运行。

## GameWorld.hpp 中的 `std::enable_shared_from_this` 是什么？

省流：这是对 `this` 指针的“智能指针”版替代。当你需要在 `GameWorld` 里获得一个指向自己的 `std::shared_ptr` 的时候，可以换成调用 [`shared_from_this()`](https://en.cppreference.com/w/cpp/memory/enable_shared_from_this/shared_from_this) 获得一个智能指针，类型为 `pGameWorld` ，也就是 `std::shared_ptr<GameWorld>` 的别名。

一般地，通过让一个类 `X` 继承自 [`std::enable_shared_from_this<X>`](https://en.cppreference.com/w/cpp/memory/enable_shared_from_this) ，我们将能够在 `X` 的内部调用 `shared_from_this()` 来安全地获得一个管理 `*this` 的 `std::shared_ptr<X>` 。注意，调用 `shared_from_this()` 意味着**现在存在某个 `std::shared_ptr` 正在管理 `*this` ，且我们想要获得一个与它共享 `*this` 的 `std::shared_ptr`** 。什么时候会出现这种情况？考虑下面的代码。

```cpp
struct X;

void do_something(std::shared_ptr<X> ptr);

std::vector<std::shared_ptr<X>> gObjects;

struct X {
  void some_action() {
    do_something(std::shared_ptr<X>(this)); // 这将导致灾难！
    // shared_ptr<X>(this) 创建了一个新的管理 *this 的 shared_ptr ，
    // 但其实现在 *this 正在被某个 shared_ptr （也就是 gObjects[0] ）管理着，
    // 而且这两个 shared_ptr 还都不知道对方的存在！它们自己都以为自己独占了这个对象。
  }
};

int main() {
  gObjects.push_back(std::make_shared<X>()); // 创建了一个 shared_ptr<X>
  gObjects.front()->some_action();
}
```

要解决这个问题，需要这样做：

```cpp
struct X;

void do_something(std::shared_ptr<X> ptr);

std::vector<std::shared_ptr<X>> gObjects;

struct X : public std::enable_shared_from_this<X> {
  void some_action() {
    do_something(shared_from_this()); // 没问题。这将正确地创建一个与 gObjects[0] 共享 *this 的 shared_ptr 。
  }
};

int main() {
  gObjects.push_back(std::make_shared<X>()); // 没问题。 std::make_shared<X> 会认识到： X 是一个继承自 std::enable_shared_from_this 的类型！它将会做一些特殊处理。
  gObjects.front()->some_action();
}
```

注意：

1. **并非**需要将所有的 `this` 都替换为 `shared_from_this()` 。不要胡乱使用 `shared_from_this()` 。
2. 调用 `shared_from_this()` 的前提是**现在 `*this` 正被某个 `shared_ptr` 管理着**。如果不是这样，则 `shared_from_this()` 会抛出 `std::bad_weak_ptr` 异常。

## [ERROR] Error loading asset ***.png

这是程序没有找到对应路径的图片素材产生的报错。报错信息中的路径为程序尝试去寻找图片的路径，是 `utils.hpp` 中的 `ASSET_DIR` 。你可以将 `ASSET_DIR` 修改成正确的路径。

如果你使用相对路径， `ASSET_DIR` 应当是从你的项目工程文件（Windows 下的 `.sln` 文件）开始，指向 Assets 目录的路径。

MacOS 上，如果你使用 XCode 等开发工具，相对路径也可能是从你的工程文件目录或 /build 目录开始。如果命令行运行时，由于相对路径会跟运行程序的终端打开的目录有关，建议自己调试时使用绝对路径，或使用确定的相对路径并且如果打包给别人玩的话说明清楚。

## 我删除 `std::list` 内元素的时候，为什么程序会崩溃？

省流：对于 `std::list` ，一边遍历一边删除一些指定元素的正确方法是使用迭代器作为循环变量，调用 [`erase()`](https://en.cppreference.com/w/cpp/container/list/erase) ，而不是使用 range-for 遍历每个元素。**请你耐心地点开这个链接读一下 `erase` 的用法，特别是注意它的返回值。你会需要的。**

Range-for 本质上也是在使用迭代器遍历你的 `list` 。当你删除 `list` 中元素时，会[**无效化** (invalidate)](https://en.cppreference.com/w/cpp/container#Iterator_invalidation) 指向被删除元素的迭代器，也就是 range-for 在背后使用的那个，于是引发错误。这其实很好理解：所谓“链表”就是在每个元素的身上记录它前一个和后一个元素的地址。如果你把 `iter` 指向的元素删除了， `++iter` 还怎么执行呢？它怎么知道自己指向谁、下一个又是谁呢？

当然，你也可以考虑使用 [`std::list<T>::remove` 或 `std::list<T>::remove_if`](https://en.cppreference.com/w/cpp/container/list/remove) 。

## 【最常见的问题】 使用了未定义类型 `GameWorld` / `GameWorld` is an incomplete type / undeclared identifiers / not overriding virtual functions / 为什么要把函数的声明和定义分开在 `.hpp` 和 `.cpp` 文件里？都写在 `.hpp` 里为什么报错？/ 循环依赖与 forward declaration

省流： `#include` 就是简单的文本复制粘贴。两个头文件互相包含就会产生错误。一些情况下，将声明和定义分开在 `.hpp` 和 `.cpp` 文件里可以消除一些循环依赖问题。如果你忘记了什么是声明、什么是定义，请去复习 Lecture 16 。

`#include` 就是简单的文本复制粘贴。假如 `A.hpp` 和 `B.hpp` 中分别定义了类 `A` 和类 `B` 。当 `A.hpp` 与 `B.hpp` 互相 `#include` 时，若 `A` 类与 `B` 类彼此互相依赖，都需要对方提前给出自己类的完整定义，一定会有一个类因为“出现在前面”而不满足依赖。

实际上，这种情况一般不太会出现：如果 `A` 类有一个 `B` 类型的成员， `B` 类肯定不能有一个 `A` 类型的成员，否则它们所占的空间将是无穷大。常见的情况是其中一方需要另一方的指针 `*` 或引用 `&` （也包括智能指针和容器等）。只创建类 `A` 的指针或引用是不需要 `A` 的完整定义的，仅需要在事先有一个对 `A` 的声明，也就是只需要 `class A;` 这样一条语句，**而不需要 `#include "A.hpp"` 来拿到 `A` 的定义**。这样就解决了两个文件互相依赖的问题：其中一方只用到指针或引用时，可以将 `#include` 改为声明。

然而，像 `class A;` 这样的声明只告诉了编译器 `A` 是一个类，编译器并不知道关于 `A` 类的任何信息。在类 `A` 的定义（即，包括它所有成员的**声明**）出现之前，任何依赖于其定义的行为都无法编译，比方说调用 `A` 的某个成员函数、创建 `A` 类型的对象等等。要想找到定义，就必须 `#include "A.hpp"` ，而这又回到了循环依赖的问题。

所以，头文件之间是不能随便互相 `#include` 的。但是，通常你可以在一个 `.cpp` 文件里随意 `#include` 你需要的东西，因为 `.cpp` 文件一般不会被别人 `#include` ，不会有循环依赖问题。所以，前文提到的依赖于某个类的定义的行为，一般都应该放在 `.cpp` 文件里。

## Linking error: 无法解析的外部符号

这个错误指的是文件之间互相 `#include` 或者项目之间互相依赖的时候找不到依赖的文件。

第一准则：你的代码写在了哪里，需要的地方就要 `#include` 哪里。

 - 如果你创建的新文件仍在 `GameObject` 文件夹，你需要修改这个文件夹下的 `CMakeLists.txt` ，让新的文件参与编译成整个 `GameObject` 项目。
 - 如果你为他们创建了新的文件夹，这是最好的做法，他们将会成为一个单独的 CMake 目标（target），但你需要做的东西会更多：
    - 你需要在这个文件夹下也创建一个 `CMakeLists.txt` ，然后“照葫芦画瓢”地去参考 `GameObject` 目录下的 `CMakeLists.txt` ，将这个新文件夹下的代码 build 成一个新的 target ，比如叫 Background 或 UI 。
    - 【重要】第二，如果有任何其他 target 依赖你的这个 target ，或需要 `#include` 它的头文件（例如 `GameWorld` 中需要你的新代码），你需要分别修改他们目录下的 `CMakeLists.txt` ，在 `target_link_libraries` 和 `target_include_directories` 里加入你的新 target 。
      - 如果是项目级的依赖关系，则需要 `target_link_libraries` 。
      - 不管项目是否依赖， `target_include_directories` 都可以让项目之间通过简洁的方式找到文件所在的目录从而 `#include` 它。
    - 【重要】最后，你需要修改根目录（最外面）的 `CMakeLists.txt` ，在↓和↑箭头之间的区域，把新的文件夹添加为子目录，从而让你新写的 `CMakeLists.txt` 参与项目的生成。

## 另一些 `#include` 错误：我没有循环引用， CMakeLists 也改了，还是 Linking error？

省流：最快的解决方案是使用以 `/src/` 为起始路径的，带文件夹名的路径。例如，将 `#include "Sunflower.hpp"` 改为 `#include "Sunflower/Sunflower.hpp"` 。问题的根本出在 `#include` 与 `target_include_directories` 。

万恶之源仍然是 `#include` ： `#include` 就是简单的文本复制粘贴。

`#include` 通过相对路径来寻找目标头文件。你的每个 `CMakeLists.txt` 中的 `target_include_directories` 列出了这个 target 能够“看得到”的 `#include` 路径。在上一条 FAQ 中的第二步中，你可能已经为会用到你的文件的项目添加了 `target_include_directories` ，然而，有时会忽视一些特殊的情况：

例如，你的 `GameObject.cpp` 中不出意外应该会有 `#include "GameWorld.hpp"` ，然而如果你的 `GameWorld.hpp` 中还有 `#include "Sunflower.hpp"` ，这行代码将会在被 `#include` 时一并被复制粘贴到 `GameObject.cpp` 中。此时， `GameObject.cpp` 虽然并没有依赖 `Sunflower` 项目，但仍然尝试 `#include "Sunflower.hpp"` ，他在“看得到”的 `#include` 路径中找不到，便产生了错误。

解决方法有以下几种：
  - 使用以 `/src/` 为起始路径的，带文件夹名的路径。例如， `#include "Sunflower/Sunflower.hpp"` 。因为每个项目的 `target_include_directories` 中都包含 `/src/` ，他们一定能“看得到”这个文件。
  - 为这种情况下的 `GameObject` 项目，将 `Sunflower.hpp` 的位置添加到 `target_include_directories` ，即使他们不以 `target_link_libraries` 互相依赖。
  - `GameWorld.hpp` 中真的需要 `#include "Sunflower.hpp"` 吗？有些情况下确有需求，但如果没有需求，只让 `GameWorld.cpp` 去 `#include` 它，就不会有这些麻烦。


## VS（中文版）的默认字体好难看，影响我编程了

确实难看并且不适合作为代码字体。工具-选项-环境-字体和颜色，将“文本编辑器”的字体设置为适合编程的等宽字体，例如系统内置的<font face="Consolas">Consolas</font>或<font face="Cascadia Mono">Cascadia Mono</font>等。

~~也可以现在卸载 Windows ，使用 Linux 。~~

## 我想把我的游戏打包出来给别人玩，可以吗？

当然可以，你需要做的是像示例程序一样，将程序的可执行文件，必要的库（Windows dll）和图片素材文件夹整理出来。

你可以在 build/Debug 或 build/Release 中找到你的可执行文件，在 Windows 下，你也可能会找到一些 dll 库。这些文件都是必要的。

要注意的是，你定义的 `ASSET_DIR` 如果是相对路径的话，在你双击 `.exe` 运行游戏时，它应该从到 `.exe` 可执行文件所在位置到 Assets 目录的相对路径。（注意与上一条的区别，在 project 里运行时会被解析为从项目工程文件开始的路径）

## Debug 和 Release 是什么？有什么区别？

你的项目能以 Debug/Release 两种方式生成 (build) 。Debug 模式下可以接入调试器 (debugger) ，利用断点或堆栈检查来调试代码，而 Release 模式则会进行一些编译器优化等，获得更快的运行速度。**并且， Release 模式下编译时会定义 `NDEBUG` 宏，这会使得你程序里的所有 `assert` 都被去除。**

你的项目的默认生成模式一般是 Debug 。你可以在你的开发环境（IDE）的顶端状态栏看到并调整生成模式。其实 CMake 提供了 `CMAKE_BUILD_TYPE` 这个变量，在最初 build 项目时设定生成模式，但是这个设定一般会被 IDE 接管覆盖。

## 如何添加文字？

在 `Framework` 目录下有 `TextBase.hpp` 文件。其构造函数中，必须提供的参数是 `x` 和 `y` 。其初始文字内容默认为空字符串、颜色默认为 `0, 0, 0`（黑色），居中模式默认为 `true` 。

你可以通过 `TextBase.hpp` 中提供的方法来修改它的位置、内容、颜色。

当你想要创建一个文字时，我们建议你以对待 `GameObject` 类似的方式创建它，即使用指针去动态地分配。与 `GameObject` 不同的是，你不必将所有文字都存放在 `GameWorld` 里的某个容器中，因为游戏对象每帧都需要 `Update()` 做出不同的行为，而文字不需要。通过将文字与一些 `GameObject` 绑定，你还可以做到比如显示每棵植物的 HP 或冷却时间等功能。

## 我想做一份自己的“杂交植物”的图片资源显示进游戏，应该怎么做？

我们欢迎你在有余力的情况下这样做，因为视觉效果的不同是游戏对玩家的很重要的反馈。

想要获得新的图片资源，对游戏中现有的图片素材进行 PS /调色是最简单的方法。将新的资源放进 assets 文件夹后，你还需要：
 - 在 `utils.hpp` 里新建一个属于你的 `IMGID` ，如果你加入了新的动画，也可以创建新的 `ANIMID` 。
 - 在 `Framework/SpriteManager.cpp` 里，加载你的新素材。 15-50 行中的代码用来完成这些，并且 hard-code 录入了素材的大小和帧数信息。你可以复制一行，参考它对应的图片素材与它的写法，填入你的信息。每个参数的意义是：
  ```
  { EncodeAnim(/* 你的 IMGID */, /* 你的 ANIMID */), SpriteInfo{/* 文件名 */,
   /* 图片总宽 */, /* 图片总高 */, /* 每帧宽 */, /* 每帧高 */,
   /* 每行帧数，默认 1 */, /* 动画长度，默认 1 */} }
  ```
  - 【注意】你加入的上面这行中，至少有两处需要更改，分别是 `EncodeAnim` 的 `IMGID` 和 `SpriteInfo` 的文件名。
  