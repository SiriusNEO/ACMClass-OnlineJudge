# ACM Programming Contest 0



## P1004 Pio's Sequence

**Statement: ** Suppose you have an array  $a_i$  , the array  $b_i$  is defined as :  $b_i = \min_{1 \leq j < i} |a_i - a_j|$ 

​                        find  $\sum_{i=1}^{n} b_i$ . Particularly, $0 \leq a_i \leq 65536$ , $1 \leq n \leq 10^5$

Simple idea:  O(n^2) , can't pass

A little more excellent: for every a_i , our task is to find the nearest a_j ( the difference of value ) ,  $j < i$

​	                                     Notice that the range of array a is 65,536, we can use the idea of bucket sort

​                                         use a bool array **vis** , vis[num] represents whether num has already existed.

​                                         for every a_i , use a for-loop in vis to find the nearest existed num

At the first look, we may consider this solution may be O(65536n) which can't pass neither

but actually this is O(n log 65536) : think the worst circumstance, which is 0, 65536, 32768, ...

Every time you add a number, the range is divided by 2 

In the contest, I use sort and monotonous stack which is actually wrong

2 9 7 4 6 2 6 ->(sort) 2(1) 2(6) 4(4) 6(5) 6(7) 7(3) 9(2), stack[1 6], when it comes to 4(4), 2(6) pops from the stack, but it may be useful in the following process

（单调栈不行，直接桶排暴力复杂度正确）

**Lesson:** Always complete the violent program first! (Probably AC)



## P1005 Linked List

**Statement:** Maintain a linked list which satisfies some needs.

A trivial task, AC in the contest



## P1006 Magic Cards

**Statement:** You have n cards, every card has numbers 1 - m on its two faces (some on the up face while others on the down face)

​                      Given q queries ([l, r]) , if number x is on a face of these cards, you can add $x^2$ to the total score.

​                      For each query, print the max possible score

In the contest I even didn't start to read the problem ...

Think if the length of query is long enough, numbers 1-m can all have chances to be put on the up face

think the worst situation, numbers are distributed averagely on two faces, so for the first card you can add half of the numbers

and continue to do the same thing, each time the numbers is divided by 2, so if the length is larger than log_2 m, we can directly print $\sum_{i=1}^m i^2$ as our answer

if the length is smaller than log2 m, notice that: if the number x ( [1,m] ) isn't on any up face, the scheme is determined (because numbe x must be on a face, which must be put as the down face)

so we can enumerate m, the scheme's score is substracted by $x^2$    

（分类讨论：如果区间足够大，直接输出；区间小的，for m，每个 m 不出现确定一种方案，可以把这个方案的值减去）     

​              





