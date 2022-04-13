#! https://zhuanlan.zhihu.com/p/495372197
本文意在分享个人在刷LeetCode时遇到的题目思路

代码由C++实现，但其思路不影响其他语言使用者阅读与参考，并尽量使用易懂语法

若您之前没有做过该题目或做过但是忘记了思路，建议读完题后思考片刻，或者去Leetcode尝试解决

------------

# 题目
> **有一堆石头，每块石头的重量都是正整数。
> 每一回合，从中选出两块 最重的 石头，然后将它们一起粉碎。**
> 
> **假设石头的重量分别为 `x y`，且 `x <= y`。
> 那么粉碎的可能结果如下：
> 如果 `x == y`，那么两块石头都会被完全粉碎；
> 如果 `x != y`，那么重量为 x 的石头将会完全粉碎，而重量为 `y` 的石头新重量为 `y-x`。**
> 
> **最后，最多只会剩下一块石头。返回此石头的重量。如果没有石头剩下，就返回 `0`。**

> **You are given an array of integers stones where stones[i] is the weight of the ith stone.**
> 
> **We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:**
> 
> **If `x == y`, both stones are destroyed, and**
**If `x != y`, the stone of weight x is destroyed, and the stone of weight y has new weight `y - x`.
At the end of the game, there is at most one stone left.**
>
> **Return the smallest possible weight of the left stone. If there are no stones left, return `0`.**

 

## 示例：
```
输入：[2,7,4,1,8,1]
输出：1
解释：
先选出 7 和 8，得到 1，所以数组转换为 [2,4,1,1,1]，
再选出 2 和 4，得到 2，所以数组转换为 [2,1,1,1]，
接着是 2 和 1，得到 1，所以数组转换为 [1,1,1]，
最后选出 1 和 1，得到 0，最终数组转换为 [1]，这就是最后剩下那块石头的重量。
```

## 限制
```
1 <= stones.length <= 30
1 <= stones[i] <= 1000
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/last-stone-weight    

------------

# 提示

+ 为了实现全局最小，首先从实现**局部最小**开始吧
+ 本题关键字：**贪心算法，优先队列**


# 解析

## 思路
对于每一个`stone, s`，为了使相减结果最小，我们必然要寻找重量最接近`s`的另一个`stone`，且由于选大选小关系不方便判断，可以尝试从最大的`s`开始计算起（因为此时重量差距最小的即为第二大的`stone`），如此反复，当剩下最后一个（或者没有）石头的时候，结果必然最小。

**这种在局部力求最优的算法即为贪心算法**，~~说白了就是怎么贪怎么来XD~~

此时有如下伪代码
```
while(stones.size() > 1)
    max_val = stones.popMax()                   // 从列表中pop出最大值
    second_max_val = stones.popMax()            // 第二次pop即为第二大值
    if (max_val - second_max_val > 0)           // 相减并判断是否为零
        stones.append(max_val - second_max_val) // 不为0则再放回列表备用

if (stones.empty())
    return 0
return stones[0]
```


那么问题来了，怎么有效地在一个随时变化的容器中找到最大及第二大值呢？

## 优先队列 priority queue
STL为我们提供了优先队列。设置大顶堆，使`top()`能拿到当前列表中的最大值，结合`pop`使用两次即可得到最大的两个值

关于优先队列，可以参考我之后发的文章（咕咕咕中），或是[cppreference](https://en.cppreference.com/w/cpp/container/priority_queue)，该网站提供了很多优秀的C++文档

# 代码
```C++
#include<queue>
#include<vector>
using namespace std;
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        std::priority_queue<int> table(stones.begin(), stones.end());

        while(table.size() > 1){                    // Break when only 1 left; or no left in the queue
            int first_value = table.top();          // Get the largest 2 elements from the queue
            table.pop();
            int second_value = table.top();
            table.pop();

            if (first_value != second_value){       // Do subtraction and push the result back if necessary
                table.push(first_value - second_value);
            }
        }

        return table.empty() ? 0 : table.top();     // Return 0 or the last value in the queue
    }
};


```


# 补充：寻找容器中的最大值
除了使用堆`heap`或是优先队列`priority queue`以外，还有什么获得容器最大值的方法呢，~~貌似还真没啥好方法...~~

1. 挨个比吧...
   时间复杂度$O(n)$
    
    ```C++
    int greatest(std::vector<int> vec){
        if (vec.empty()){
            // throw exception...
        }

        // Compare one by one
        int result = vec[0];
        for (int i = 1; i < vec.size(); i++){
            if (vec[i] > result){
                result = vec[i];
            }
        }
        return result;
    }
    ```

2. `std::max_element`

    详见https://en.cppreference.com/w/cpp/algorithm/max_element，其底层实现与方法1类似


# 总结
本题难度不高，主要考验的是对STL容器的掌握


# 类似题目
703. 数据流中的第 K 大元素 https://leetcode-cn.com/problems/kth-largest-element-in-a-stream/