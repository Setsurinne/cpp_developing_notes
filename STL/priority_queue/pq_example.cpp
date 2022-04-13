#include<queue>
#include<iostream>
#include <functional>

// Max top queue
#if 0
// Print all element in the queue in order
void printQueue(std::priority_queue<int>& q){
    while(!q.empty()){
        std::cout << q.top() << ' ';
        q.pop();
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{

    // Initialize the queue
    std::vector<int> val = {1, 5, 3, -10, 0};
    std::priority_queue<int> max_top_queue(val.begin(), val.end());
#if 0
    // Equivalent to:
    std::priority_queue<int, std::vector<int>, std::less<int>> 
        max_top_queue(val.begin(), val.end());
#endif

    // Try push() and top()
    std::cout << max_top_queue.top() << std::endl;      // 5
    max_top_queue.push(100);    
    std::cout << max_top_queue.top() << std::endl;      // 100

    // Try pop()
    printQueue(max_top_queue);                          // 100 5 3 1 0 -10
    return 0;
}
#endif


// min top queue
#if 0
int main(int argc, char const *argv[]){
    std::vector<int> val = {1, 5, 100, 3, -10, 0};

    // Use greater as compare function
    std::priority_queue<int, std::vector<int>, std::greater<int>>
        min_top_queue(val.begin(), val.end());

    // Print all
    while(!min_top_queue.empty()){
        std::cout << min_top_queue.top() << ' ';
        min_top_queue.pop();
    }
    std::cout << std::endl;     // -10 0 1 3 5 100
}
#endif

// self design
#if 1
int main(int argc, char const *argv[]){
    std::vector<int> val = {1, 5, 100, 3, -10, 0};
    std::vector<int> ind = {0, 1, 2, 3, 4, 5};

    // Self-design compare function
    // Use a priority queue to get the order of val, in index
    std::function<bool (int, int)> cmp = 
        [&val](int v_1, int v_2){return val[v_1] < val[v_2]; };
    
    std::priority_queue<int, std::vector<int>, decltype(cmp)> 
        max_ind_queue(ind.begin(), ind.end(), cmp);
    
    // Print all
    while(!max_ind_queue.empty()){
        std::cout << max_ind_queue.top() << ' ';
        max_ind_queue.pop();
    }
    std::cout << std::endl;     // 2 1 3 0 5 4
}
#endif

