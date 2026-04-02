# CS106l 

以前说实话大部分用的是 cin+cout+C+算法，补充一些学到的特性吧。

### using 创建类型别名

```cpp
std::pair<bool,std::pair<double,double>> solveQuadratic(double a,double b,double c);
// 简化
using Zeros=std::pair<double,double>;
using Solution=std::pair<bool,Zeros>;
Solution solveQuadratic(double a,double b,double c);
```

### Uniform initialization(C++11)

大括号赋初值可以自动检查类型, map,vector 等其他容器也可用大括号

```cpp
int number{1.0}; // compile erroe
int number{1};
```

### Structured Binding(C++17)

```cpp
#include <iostream>
#include <tuple>
#include <string>
std::tuple<std::string, std::string, std::string> getClassInfo() {
	std::string className = "CS106L";
	std::string buildingName = ”Thornton 110";
	std::string language = "C++";
	return {className, buildingName, language};
}
int main() {
	auto [className, buildingName, language] = getClassInfo();
	std::cout << "Come to " << buildingName << " and join us for " 		<< className << " to learn " << language << "!" << std::endl;
	return 0;
}
```

### 引用的细节问题

```cpp
void shift(std::vector<std::pair<int,int>> &nums){
    // 不会改变nums里面的值
    for(auto [num1,num2]:nums){
        num1++;
        num2++;
    }
    // 改变nums里面的值
    for(auto &[num1,num2]:nums){
        num1++;
        num2++;
    }
    for(size_t i=0;i<nums.size();i++){
        nums[i].first++;
        nums[i].second++;
    }
}
```

### 左值和右值

```cpp
void squareN(int &n){
    n=std::pow(n,2);
}

int main(){
    // 右值不能传引用
    squareN(5);
    return 0;
}
```

```cpp
void squareN(const int &n){
    n=std::pow(n,2);
}

int main(){
    // 但是如果是const引用可以传入右值
    squareN(5);
    return 0;
}
```

```cpp
// &c[2] 是取地址操作，结果是纯右值（prvalue），因为取地址操作返回的是一个地址值（临时值）
int *e=&c[2];

// c.size()和static_cast<int>(f)都是右值
size_t f=c.size();
int g=static_cast<int>(f);
```

```cpp
// 左值引用
void update(Photo& pic);

int main(){
    Photo selfie=takePhoto();
    upload(selfie);
}

// 右值引用
void update(Photo&& pic);

int main(){
    upload(takePhoto());
}
```

### 关于 cin 和 getline

最好不要一起用，对于 \n 的处理不同，cin 会把 \n 留在缓冲区，但 getline 会把 \n 也处理掉，直接到下一行，先 cin 再直接 getline 可能会让 getline 只读到一个 \n 

### 关于 auto

遍历的时候一般使用 

```cpp
for(const auto &x:v)
```

好一点，能够避免拷贝，也能防止引用产生的可能会改变数据。

### 关于 unordered_map

提供了可以查询 load factor 的函数，即每个”桶“平均挂了几个数据，也可以设置最大 load factor ，超过这个阈值会自动进行 reharsh

```cpp
std::unordered_map<std::string,int>map;

double lf=map.load_factor();
map.max_load_factor(2.0);
```

### 关于迭代器

让迭代器 $+1$ 的时候用 ++it 比 it++ 好一些，前缀 ++ 避免进行不必要的拷贝，迭代器是一个完整的对象，拷贝它更消耗更大

```cpp
// Prefix form - ++it
// Increments it and returns a reference to same object
Iterator& operator++();

// Postfix form - it++
// Increments it and returns a copy of the old value
Iterator operator++(int);
```

### 迭代器类型

**Input Iterator**:只读，单向，无法多趟遍历，例： std::istream_iterator

**Output Iterator**:只写，单向，无法多趟遍历，例： std::ostream_iterator

**Forward Iterator**:读写，单向，可以多趟遍历，例： std::forward_list 的迭代器

**Bidirectional Iterator**:读写，双向，可以多趟遍历，例： std::list,std::set 的迭代器

**Random Access Iterator**:读写，双向，可以多趟遍历，例： std::vector,std::deque 的迭代器

### 菱形继承

A -> B , A -> C , B -> D , C -> D ，从 D 直接访问 A 中元素会产生歧义，使用虚继承解决，让 B 和 C 在 D 中共享一个 A 对象

```cpp
class C:virtual public A{
    public:
    	C();
}
class B:virtual public A{
    public:
    	B();
}
```

### 虚函数

| **其他语言默认虚** | Java、C# 等为了便利性，默认使用动态绑定      |
| ------------------ | -------------------------------------------- |
| **C++ 默认非虚**   | 遵循零开销原则，不为不需要的功能付费         |
| **虚函数成本**     | 对象增大（vptr）、调用变慢（间接）、无法内联 |
| **适用场景**       | 需要运行时多态时使用虚函数                   |
| **性能敏感领域**   | 量化金融、游戏引擎、嵌入式避免使用虚函数     |
| **替代方案**       | 模板、CRTP、策略模式等编译时多态             |

### 非类型模板

```cpp
template <size_t N>
class SizeTemplate {};
SizeTemplate<5> s;
```

### 模板实现

1.  .cpp 文件实现时必须有 template 那行

```cpp
// Vector.h
template <typename T>
class Vector {
	public:
	T& at(size_t i);
};

// Vector.cpp
template <typename T>
T& Vector<T>::at(size_t i) {
	// Implementation...
};
```

2.  .h 文件末尾必须 include 对应的 .cpp 文件

3. typename 和 class 是一样的

```cpp
template <typename K, typename V>
struct pair;
// same as
template <class K, class V>
struct pair;
```

### const 重载

```cpp
template <class T>
const T& Vector<T>::at(size_t index) const {
	return elems[index];
}
template <class T>
T& Vector<T>::at(size_t index) {
	return elems[index];
}
```

```cpp
template <typename T>
T& Vector<T>::findElement(const T& value) {
	for (size_t i = 0; i < logical_size; i++) {
		if (elems[i] == elem) return elems[i];
	}
	throw std::out_of_range("Element not found");
}
template <typename T>
const T& Vector<T>::findElement(const T& value) const {
    // const_cast<Vector<T>&> 移除 const 属性
    // 几乎永远不要用 const_cast ！！！！！
    // 应该在设计时就考虑是否 mutable
	return const_cast<Vector<T>&>(*this).findElement(value);
}
```

```cpp
struct MutableStruct {
	int dontTouchThis;
    // 谨慎使用
	mutable double iCanChange;
};
const MutableStruct cm;
// cm.dontTouchThis = 42; // Not allowed, cm is const
cm.iCanChange = 3.14; // Ok, iCanChange is mutable
```

### 模板函数

```cpp
// auto 解决类型问题
template <typename T, typename U>
auto min(const T& a, const U& b) {
	return a < b ? a : b;
}
min(106, 3.14);
```

### C++ concepts

```cpp
template <typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};
template <typename T> requires Comparable<T>
T min(const T& a, const T& b);
// Super slick shorthand for the above
template <Comparable T>
T min(const T& a, const T& b);
```

C++20 引入了很多自带的 concepts

### 可变参数模板

递归实现

```cpp
// 可变参数类型相同
template <Comparable T>
T min(const T& v) { return v; }

template <Comparable T, Comparable... Args>
T min(const T& v, const Args&... args) {
	auto m = min(args...);
	return v < m ? v : m;
}
```

```cpp
// 可变参数类型不同
void format(const std::string& fmt) {
	std::cout << fmt << std::endl;
}

template <typename T, typename... Args>
void format(const std::string& fmt, T value, Args... args) {
	auto pos = fmt.find("{}");
	if (pos == std::string::npos) throw std::runtime_error("Extra arg");
	std::cout << fmt.substr(0, pos);
	std::cout << value;
	format(fmt.substr(pos + 2), args...);
}
```

### Compile-time execution

```cpp
// 这么写较为复杂
template <>
struct Factorial<0> {
	enum { value = 1 };
};

template <size_t N>
struct Factorial {
	enum { value = N * Factorial<N - 1>::value };
};

std::cout << Factorial<7>::value << std::endl;
```

```cpp
// try to run at compile time
constexpr size_t factorial(size_t n) {
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

// must run at compile time
consteval size_t factorial(size_t n) {
	if (n == 0) return 1;
	return n * factorial(n - 1);
}
```

### 传函数作为参数

```cpp
template <typename It, typename Pred>
It find_if(It first, It last, Pred pred) {
	for (auto it = first; it != last; ++it) {
		if (pred(*it)) return it;
	}
	return last;
}
// Pred 可以是一个函数指针
find_if(corlys.begin(), corlys.end(), isVowel);
// Pred = bool(*)(char)
find_if(ints.begin(), ints.end(), isPrime);
// Pred = bool(*)(int)
```

### lambda 表达式

```cpp
int n;
std::cin >> n;
auto lessThanN = [n](int x) { return x < n; };
find_if(begin, end, lessThanN);

auto lambda = [capture-values](arguments) {
	return expression;
}
// lambda 的"捕获所有变量"只捕获局部变量（包括当前函数的参数），不包括全局变量、静态变量、类成员变量。
[x](arguments) // captures x by value (makes a copy)
[&x](arguments) // captures x by reference
[x, y](arguments) // captures x, y by value
[&](arguments) // captures everything by reference
[&, x](arguments) // captures everything except x by reference
[=](arguments) // captures everything by value
```

### 函数对象 (functor)

可以像函数一样调用的对象，通常通过重载 operator() 实现， lambda 表达式本质上就是编译器自动生成的 functor ，函数对象可以保存自己的状态，可以有不同的实例

```cpp
class __lambda_6_18
{
public:
	bool operator()(int x) const { return x < n; }
	__lambda_6_18(int& _n) : n{_n} {}
private:
	int n;
};

int n = 10;
auto lessThanN = __lambda_6_18{ n };
find_if(begin, end, lessThanN);
```

### std::function

std::function is an overarching type for functions/lambdas 

• Any functor/lambda/function pointer can be cast to it 

• It is a bit slower 

• usually use auto/templates and don’t worry about the types!

**只有在真正需要类型擦除时才使用 std::function**，比如存储不同类型的可调用对象到容器中，或者作为多态接口。

### Ranges & Views (C++20)

1. Ranges: 可以遍历的元素序列
2. Views: 延迟求值的范围适配器(a way to compose algorithms)

```cpp
int main(){
    std::vector<char> v={'a','b','c','d','e'};
    auto it=std::ranges::find(v,'c');
    std::cout<<*it;
    return 0;
}

int main() {
	std::vector<char> v = {'a', 'b', 'c', 'd', 'e'};
	// Search from 'b' to 'd’
	auto first = v.begin() + 1;
	auto last = v.end() - 1;
	auto it = std::ranges::find(first, last, 'c');
}
```

```cpp
std::vector<char> v = {'a', 'b', 'c', 'd', 'e'};

// Filter -- Get only the vowels
std::vector<char> f;
std::copy_if(v.begin(), v.end(), std::back_inserter(f), isVowel);

// Transform -- Convert to uppercase
std::vector<char> t;
std::transform(f.begin(), f.end(), std::back_inserter(t), toupper);

// { 'A', 'E' }


// using view
// Views 最重要的特性：不立即计算，只在遍历时才计算
std::vector<char> letters = {'a', 'b', 'c', 'd', 'e’};
    
auto f = std::ranges::views::filter(letters, isVowel);
// f is a view! It takes an underlying range letters
// and yields a new range with only vowels!
                             
auto t = std::ranges::views::transform(f, toupper);
// t is a view! It takes an underlying range f
// and yields a new range with uppercase chars!
                             
auto vowelUpper = std::ranges::to<std::vector<char>>(t);
// Here we materialize the view into a vector!
// Nothing actually happens until this line!
                             
                             
// We can chain views together use operator |
std::vector<char> letters = {'a','b','c','d','e'};
std::vector<char> upperVowel = letters
	| std::ranges::views::filter(isVowel)
	| std::ranges::views::transform(toupper)
	| std::ranges::to<std::vector<char>>();
                             
// upperVowel = { 'A', 'E' }
```

• Why you might like ranges/views?

​	• Worry less about iterators 

​	• Constrained algorithms mean better error messages 

​	• Super readable, functional syntax 

• Why you might dislike ranges/views? 

​	• They are extremely new, not fully feature complete yet 

​	• Lack of compiler support 

​	• Loss of performance compared to hand-coded version

### 运算符重载

分为两种：1. member overloading 2. non-member overloading

STL 更偏好于 non-member 的，因为：

1. 允许左侧操作数是非类类型
2. 能为无法修改的类重载运算符

```cpp
// Non-member Operator Overloading
bool operator< (const StanfordID& lhs, const StanfordID& rhs);
// Member Operator Overloading
bool StanfordID::operator< (const StanfordID& rhs) const {...}
```

### rule of contrariety

```cpp
bool StanfordID::operator==(const StanfordID& other) const {
	return (name == other.name) && (sunet == other.sunet) &&
	(idNumber == other.idNumber);
}
bool StanfordID::operator!=(const StanfordID& other) const {
	return !(*this == other);
}
```

### 特殊成员函数(SMF->Special Member Function)

1. 默认构造函数(Default Constructor)
2. 析构函数(Destructor)
3. 拷贝构造函数(Copy Constructor)：从同类型对象拷贝构造新对象
4. 拷贝赋值运算符(Copy Assignment Operator)：将一个对象赋值给另一个已存在的对象
5. 移动构造函数(Move Constructor)：从临时对象转移资源
6. 移动赋值运算符(Move Assignment Operator)：将临时对象资源转移给已存在的对象

### Rule of Zero

如果自带的特殊成员函数可以运行，不要自己新定义

如果不需要使用构造或析构之类的函数，那就不要使用即可

如果你的类依赖已经有同样特殊成员函数的东西，不需要重新实现这些函数

### Rule of Three

如果类需要自定义析构函数、拷贝构造函数或拷贝赋值运算符中的任何一个，那么通常这三个函数都需要自定义

原因：当你在析构函数中手动释放资源时，意味着类在管理某种资源（通常是动态内存、文件句柄、网络连接等）。这时候编译器自动生成的拷贝操作会执行**浅拷贝**，导致严重问题。

### Rule of Five

析构函数、拷贝构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符，如果自定义其中任何一个，通常需要自定义全部五个

不是必须的，但如果不这样代码可能会因为一些不必要的拷贝变得更慢

### 移动构造与赋值

```
Photo(Photo&& other) : wid(other.wid), length(other.length), data(other.data) {
    other.wid = 0;
    other.length = 0;
    other.data = nullptr;
}

Photo& operator=(Photo&& other)  {
    if (this != &other) {
        delete[] data;
        wid = other.wid;
        length = other.length;
        data = other.data;
        other.wid = 0;
        other.length = 0;
        other.data = nullptr;
    }
    return *this;
}
```

### std::move

强制对左值进行移动，被移动的对象执行完之后会变成一个未知的状态

### std::optional

```cpp
void removeOddsFromEnd(vector<int>& vec){
	while(vec.back() % 2 == 1){
		vec.pop_back();
	}
}
// 假设一个这样的函数，如果 vec 本身就是空的，那访问 vec.back() 会导致错误或不可预期结果
// std::optional 是一个模版类，表示一个可能包含值，也可能不包含值的对象
// 主要有 3 个成员方法
// .value() 获取值，如果是 std::nullopt 即不包含值，会抛出 std::bad_optional_access
// .value_or(default_val) 获取值，如果是 std::nullopt 会返回 default_val
// .has_value() 检查是否有值

// 但 std::optional 也不能解决所有未定义行为
std::optional<valueType&>
vector<valueType>::operator[](size_t index){
	return *(begin() + index);
}
// 如果访问的 vector 是空的，按理要返回一个值为引用的 optional ，但是引用 std::nullopt 是未定义行为

std::optional<int> opt = std::nullopt;
int val = *opt;  // 未定义行为！没有错误检查

// 其他成员方法
- .and_then(function f)
returns the result of calling f(value) if contained value exists,
otherwise null_opt (f must return optional)
- .transform(function f)
returns the result of calling f(value) if contained value exists,
otherwise null_opt (f must return optional<valueType>)
-
.or_else(function f)
returns value if it exists, otherwise returns result of calling f
```

### RAII(Resource Acquisition Is Initialization)

资源的获取在对象构造时完成，资源的释放在对象析构时进行

优势：

1. 即使发生异常，栈上对象也会自动析构，避免资源泄露
2. 无需手动编写资源释放代码
3. 编译器保证析构函数的调用

RAII for locks -> lock_guard

RAII for memory->smart pointers

1. std::unique_ptr：拥有唯一资源，不可拷贝，只能移动
2. std::shared_ptr：多个指针共享所有权，引用计数管理生命周期
3. std::weak_ptr：避免循环引用，防止内存泄漏

smart pointers 初始化

```cpp
// Always use std::make_unique<T> and std::make_shared<T>
std::unique_ptr<T> uniquePtr=std::make_unique<T>();
std::shared_ptr<T> sharedPtr=std::make_shared<T>();
std::weak_ptr<T> wp=sharedPtr;

// 不安全：可能存在内存泄漏
void risky_function(std::shared_ptr<Widget> sp, int priority);

// 调用方式
risky_function(std::shared_ptr<Widget>(new Widget), compute_priority());

// 可能的执行顺序：
// 1. new Widget（分配内存）
// 2. compute_priority()（可能抛出异常）
// 3. shared_ptr 构造函数
// 
// 如果 compute_priority() 抛出异常，new Widget 的内存就泄漏了！

// 使用 new：两次内存分配
std::shared_ptr<Widget> sp1(new Widget);
// 分配1: new Widget 的控制块
// 分配2: Widget 对象本身
// 总共 2 次内存分配
```

```cpp
// 循环引用导致的内存泄漏
class Parent {
public:
    std::shared_ptr<Child> child;
    ~Parent() { std::cout << "Parent destroyed" << std::endl; }
};

class Child {
public:
    std::shared_ptr<Parent> parent;  // 强引用
    ~Child() { std::cout << "Child destroyed" << std::endl; }
};

void createFamily() {
    auto p = std::make_shared<Parent>();
    auto c = std::make_shared<Child>();
    
    p->child = c;   // Parent 持有 Child
    c->parent = p;  // Child 持有 Parent
    
    // 离开作用域时：
    // p 引用计数: 1 (被 c->parent 持有)
    // c 引用计数: 1 (被 p->child 持有)
    // 内存泄漏！两个对象永远不会被销毁
}

// 使用 weak_ptr 打破循环
class Parent {
public:
    std::shared_ptr<Child> child;
    ~Parent() { std::cout << "Parent destroyed" << std::endl; }
};

class Child {
public:
    std::weak_ptr<Parent> parent;  // 弱引用，不增加引用计数
    ~Child() { std::cout << "Child destroyed" << std::endl; }
};

void createFamily() {
    auto p = std::make_shared<Parent>();
    auto c = std::make_shared<Child>();
    
    p->child = c;           // Parent 强引用 Child
    c->parent = p;          // Child 弱引用 Parent（不增加计数）
    
    // 离开作用域：
    // p 引用计数: 1 (仅自身) → 降为 0，Parent 销毁
    // Parent 销毁时，p->child 析构，Child 引用计数降为 0
    // Child 也被销毁
}

// 输出：
// Parent destroyed
// Child destroyed
```

### CMake

1. You need to have a CMakeLists.txt ﬁle in your project’s root directory
2. Make a build folder (mkdir build) within your project!
3. Go into the build folder (cd build)
4. Run cmake ..
a. This command runs cmake using the CMakeLists.txt in your project’s root
folder!
b. This generates a Makefile
5. Run make
6. Execute your program using ./main as usual
