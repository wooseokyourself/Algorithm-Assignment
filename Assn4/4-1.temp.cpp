#include <cstdio>
#include <cstdlib>
#include <stdbool.h>
#include <iostream>
#include <vector>
#include <algorithm>


using std::vector;
using namespace std;


struct Code
{
    //int start =0;
    int finish ,profit;

    bool operator<(const Code &other) const { // member function
    return profit < other.profit;
  }
};

bool Code_less(const Code &lhs, const Code &rhs) // free function
{
    return lhs.profit < rhs.profit;
}

int make_schedule(Code arr[], int n);
bool compare(Code s1, Code s2);
int binarySearch(Code jobs[], int index, int count);


int main(){

  // put test case num
  int c;//test c #

  scanf("%d",&c);
  std::vector<int> results(c);
  int n;

  int f ,d ;
  for(int i = 0 ; i < c ; i ++){
    scanf("%d",&n);
    Code codes[n];

    for(int j = 0 ; j < n ; j ++){

      scanf("%d", &f );
      scanf("%d", &d );
      codes[j].profit = f;
      //codes[j].start = d-1;
      codes[j].finish = d;

    }

    results[i] = make_schedule(codes , n);
  }

  for(int i = 0 ; i < c ; i ++){
    printf("%d\n", results[i]);
  }

  return 0;
}


bool compare(Code s1, Code s2){
    if(s1.finish == s2.finish) return (s1.profit > s2.profit);
    else return (s1.finish < s2.finish);
}

int make_schedule(Code arr[], int n){

  sort(arr, arr+n, compare); // sort by finsish day desc and profit asec
  std::vector<int> table(n);

  table[0] = arr[0].profit; // 데드라인이 가장 짧고 가장 값이 큰거 첫번째 성분으로 적합
  arr[0].finish = 1; // 첫날에 배정받았으니 첫날에 끝.
  int count  = 1; // 몇번째날까지 배정됐는지 알려주는 함수.
  printf("1 th table: %d count: %d\n",  table[0], count);

  for (int i=1; i<n; i++){ // 모든 제안들을 탐색
      int current_profit = arr[i].profit; // i 번째 노드를 본다.

      for(int k = 0 ; k < n ; k ++){
        printf( "start: %d , finish: %d, profit: %d\n", count , arr[k].finish , arr[k].profit);
      }

      if(count < arr[i].finish){ // count보다 앞서서 배정받을수 있는 노드인지
        int l = binarySearch(arr, i , count); // i 번째 노드와 이어질 수 있는 이전 table을 본다.
        if (l != -1) current_profit += table[l]; // 찾았으면 이전 최선과 누적

        table[i] = max(current_profit, table[i-1]); //최대인노드를 선택해서 다음 선택지에
        if(table[i] == current_profit){
          //arr[i].start = count;
          arr[i].finish = count+1;
          count ++;
        }
      }
      else{ // 이전의 값들을 수정해서 최대를 생성할 수 있는지 봐야된다.
        //int max, max_idx;
        Code *ptr = std::min_element(arr, arr + count, Code_less);

//        int temp =table[i-1]+current_profit-ptr->profit;
        printf("find ptr->profit : %d\n", ptr->profit);
        if(ptr->profit >= current_profit){
          table[i] = table[i-1];
          arr[i].profit = 100000;
        }
        else {
          table[i] = table[i-1]+current_profit-ptr->profit;\
          ptr->profit = current_profit;
        }
        printf("change ptr->profit : %d\n", ptr->profit);
        //table[i] = max(table[i-1] ,temp );
        //ptr->profit = current_profit;
      }
      printf("%d th table: %d count: %d\n", i+1 , table[i], count);
    }


    int return_val = table[n-1];
    table.clear();

    return return_val;
}

int binarySearch(Code jobs[], int index, int count){
  // using binary search log n tome
    int bottom = 0, top = index - 1;

    while (bottom <= top){
        int mid = (bottom + top) / 2;
        if (jobs[mid].finish <= count){
            if (jobs[mid + 1].finish <= count)
                bottom = mid + 1;
            else
                return mid;
        }
        else top = mid - 1;
    }
    return -1;
}