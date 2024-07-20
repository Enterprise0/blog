## 开放封闭原则
[https://www.cnblogs.com/gaochundong/p/open_closed_principle.html](https://www.cnblogs.com/gaochundong/p/open_closed_principle.html)

## 可变参数模板
[https://blog.csdn.net/brahmsjiang/article/details/138377789](https://blog.csdn.net/brahmsjiang/article/details/138377789)

## noexcept关键字
保证不抛出异常的函数声明为noexcept，可以编译优化

[https://www.cnblogs.com/RioTian/p/15115387.html](https://www.cnblogs.com/RioTian/p/15115387.html)

## 原子类型
从效率上来说，原子操作要比互斥量的方式效率要高。互斥量的加锁一般是针对一个代码段，而原子操作针对的一般都是一个变量

[https://juejin.cn/post/7086226046931959838](https://juejin.cn/post/7086226046931959838)

## 多线程内存序std::memory_order_relaxed
[https://blog.csdn.net/qls315/article/details/119930248](https://blog.csdn.net/qls315/article/details/119930248)

## 深拷贝和浅拷贝
深拷贝和浅拷贝是针对`引用或指针`类型，对于基本数据类型，都是简单的复制值

[https://juejin.cn/post/6844904197595332622](https://juejin.cn/post/6844904197595332622)

## 万能引用
右值引用只有发生类型推断时才是万能引用，也就是在使用模板时
```
template<typename T>
void func(T&& value)
{
    ...
}
```

## std::move
移动const对象，实际调用的是拷贝构造函数。如果拷贝构造函数被delete,编译会报错

## constexpr
C++11中的constexpr指定的函数返回值和参数必须要保证是字面值，而且必须有且只有一行return代码。所以编译器在编译期间会尝试优化。

## string_view
[https://segmentfault.com/a/1190000018387368](https://segmentfault.com/a/1190000018387368)
