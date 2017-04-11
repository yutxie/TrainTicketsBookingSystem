# 开发手册

## 相关规范

1. 文件名与类名相同与规范相同
2. 规范代码风格: 
	1. 除常量全大写外其余均按大小驼峰命名法(小写开头)
	2. 二元运算符两侧加空格
	3. 大括号与函数头同行
3. 使用sjtu名字空间
4. 使用头文件保护符号

*myClass.hpp*
```cpp
#ifndef SJTU_MYCLASS_HPP
#define SJTU_MYCLASS_HPP
namespace sjtu {

class myClass {
private:
public:
};

}
#endif
```

## 思路图解
尚待更新!

## 文件汇总
| file name | description |
|:---:|:----:|
| system.hpp | 订票系统 |
| train.hpp | 车次 |
| plan.hpp | 运行计划 |
| station.hpp | 车站 |
| ticket.hpp | 车票 |
| user.hpp | 管理员或用户 |
| vector.hpp | vector容器 |
| map.hpp | map容器 |
| list.hpp | list容器 |
| timer.hpp | 时间 |
| log.hpp | 系统日志 |

## 类接口

### 第8周

注意: 
1. 带*号表示暂缓实现
2. 所需要调用的已经实现好的工具类(如timer)请于dev-tools查找

#### station
车站类, train的一个"内嵌类", 某个具体车次运行路线中的某个车站
如A次列车和与其不同B次列车均会经过的上海站, 在这里认为是不同的

| return type | method | description |
|:----------:|:---------------:|:----------:|
| / | station(const string &_name, int _id, const string &_train, const timer &_stopTime, const timer &_departTIme, int _length, int _price[]) |  构造函数 |
| string | getName() | 返回该车站的名字 |
| int | getId() | 返回该车站的编号 |
| string | getTrain() | 返回所属的车次 |
| timer | getStopTime() | 返回在该车次从出发到停靠在该站的时间差 |
| timer | getDepartTime() | 返回该车次从出发到离开该站的时间差 |
| int | getLength() | 返回该车次从出发到停靠在该站的行驶里程数 |
| int | getPrice(int type) | 返回该车次的type类型座位从出发到该站的票价 其中type=1,2,3分别表示一等座,二等座,三等座 |

#### plan
运行计划类, train的一个"内嵌类", 由所属车次与始发时间唯一确定

| return type | method | description |
|:-----:|:------:|
| / | plan(const string &_train, const timer &_startTime, bool _status = false) | 构造函数 |
| string | getTrain() | 返回所属的车次 |
| timer | getStartTime() | 返回始发时间 |
| bool | getStatus() | 返回发售状态 |
| int | getLeftTickets(int type, int u, int v) | 返回从该车次uth站点到vth站点type类型座位剩余票数 特殊地若传入不合法则返回0 |
| void | modifyStartTime() | 修改始发时间 |
| void | modifyStatus(bool newStatus) | 修改售票状态 |
| void | query(int type, int u, int v) | 输出始发时间, 发售状态, 剩余票数 |
| ticket | **orderTicket**(int type, int u, int v) | 返回订得的票 |
| void | **disorderTicket**(const ticket &tk) | 退订该票 |

注意:
1. 所有修改均需要check发售状态为false
2. 订票后记得修改余票信息
3. 余票信息的修改与查询要求用树状数组实现

#### ticket
车票类, 记录一张车票的相关信息

| return type | method | description |
|:-----:|:------:|
| / | ticket(const string &_train, const timer &_sartTime, int type, int u, int v | 构造函数 其中u/v为起/终点站在该车次中的位置 |
| string | getTrain() | 返回所属车次 |
| timer | getStartTime() | 返回所属运行计划的始发时间 |
| int | getType() | 返回座位类型 |
| int | getPrice() | 返回票价 |
| friend std::ostream &  | operator<< (const std::ostream &os, const &obj) | 输出所属车次, 始发时间, 作为类型, 票价, 起点站与终点站(, 所属用户信息) |
| user | **getUser**() | 返回所属用户 |


### 第7周

#### timer

时间类, 用于处理时间相关的问题

| return type | method | description |
|:-----:|:------:|
| / | timer(int _yy = 0, int _mm = 0, int _dd = 0, int _hh = 0, int _ss = 0) | 构造函数 其中ss表示分 |
| friend std::ostream & | operator<< (std::ostream &os, const timer &obj) | 按 yy/mm/dd hh:ss 的格式输出时间信息 |
| friend timer | operator- (const timer &obj1, const timer &obj2) | 输出obj1与obj2的时间差 要求obj2>obj1否则抛出exception()异常 要求输入尽量合法最多只能相差天数级别 |
| friend bool | operator == (const timer &obj1, const timer &obj2) | 比较函数 |
| friend bool | operator < (const timer &obj1, const timer &obj2) | 比较函数 |
| friend bool | operator > (const timer &obj1, const timer &obj2) | 比较函数 |
| friend bool | operator <= (const timer &obj1, const timer &obj2)  | 比较函数 |
| friend bool | operator >= (const timer &obj1, const timer &obj2) | 比较函数 |

