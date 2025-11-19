# Priority Queue with O(1) operation

用一個Adjacent list管理一群物件，並採用double circular linked list和FIFO(先進先出)管理同一權限的物件，並用O(1)實現delete、insert函式。

## Project Structure

```
graph/
│
├── include/
│     └── graph.h
│
├── src/
│     ├── graph.c
│     └── main.c
│
└── README.md
```

## Data Structures

本實作的核心結構如下。

### `struct grp`

```c
struct grp{
    struct gnode mats[MAX_PRIORITY];//裡面存放各自Priority linked list的head(哨兵)
    int size;
    int current_max;//紀錄現在權限值最大的物件
};
```
其中 MAX_PRIORITY 表示的是2的K次方(最大值)

### `struct gnode`

```c
//這個結構表示了相同權限值的雙向環狀串列，其哨兵節點由grp.mats[i]擔任
struct gnode{
    int prior;
    struct gnode *next;
    struct gnode *prev;
};
```

### `G[MAX_PRIORITY]`

此陣列紀錄每個priority是否已存在。若存在，priority存在陣列會等於1；反之，則為 0。

### `prev_nonempty[MAX_PRIORITY]`

此陣列用來記錄當每個priority刪空之後，下一個非空的priority是哪個。

## operation

### `initQ()`

1. 將哨兵初始化成環狀
2. 將 G[] 初始化為0 (全空)
3. 將 prev_nonempty[] 設為-1 (全空)
4. 將 current_max 設為-1 (全空)

### `insertQ(gptr, pri, alloc)`

因為不能使用GNU C 提供的所有內建函數，我把malloc交給使用者決定。

insert 分為兩種情況。

1. priority 已存在（G[pri] == 1）
- 直接插進串列頭部

2. priority 第一次出現（G[pri] == 0）
- 建立新的小型環狀串列
- 重新計算 current_max (找最小的非空priority)
- 重新計算 prev_nonempty[]（使 deleteQ 不需要任何迴圈）

因為insert沒有禁止loop。所以因為 MAX_PRIORITY 是常數，這些迴圈仍為O(1)。

### `deleteQ(gptr, delloc)`

因為不能使用GNU C 提供的所有內建函數，我把free交給使用者決定。

1. 若 queue (雙向鏈結串列)為空，則回傳prior = -1(錯誤)
2. 找出目前最高 priority
3. 刪除 priority 串列的尾端節點，此舉動達成了FIFO的要求
4.  free 該節點
5. 若該 priority 被刪成空，則把 current_max 換成 prev_nonempty 裡記錄的下一個 index

```c
gptr->current_max = prev_nonempty[index];
```

delete 函式做到了O(1) (且沒有使用loop)。

## Example

插入順序 :
```c
    insertQ(&g,2,user_alloc);
    insertQ(&g,3,user_alloc);
    insertQ(&g,1,user_alloc);
    insertQ(&g,3,user_alloc);
```
非空 priority : 1,2,3
current_max = 1

刪除順序 :
```c
    delete → pri 1
    delete → pri 2
    delete → pri 3
    delete → pri 3
    delete → pri -1 // 代表已經空了
```
最後 queue 清空,current_max = -1。

## Homework requirement

- [x] 設計一個類似 adjacent list 的資料結構來管理這一群物件
- [x] 將相同權限值的物件串在同一個Linked list中
- [x] 採用先進先出的方式來管理相同權限值的物件
- [x] insertQ 必須在 常數時間完成 O(1)
- [x] deleteQ 必須在 常數時間完成 O(1)(無loop)
- [x] 不能使用 GNU C 提供的所有內建函數


