#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void swap(size_t first, size_t second, vector<int>& list){
  //line 7-9: if indexes are the same no need to swap
  if(first == second){
    return;
  }
  //line 11-13: swaps index values
  int temp = list[first];
  list[first] = list[second];
  list[second] = temp;
}

int partition(vector<int>& list, int first, int last) {
  //Will hold pivot value
  int pivot;
  //will be used to access the elements and enables the use of quicksort
  int index, smallIndex;
  //holds the middle index of the vector
  int middle;
  //holds index of the median value
  int medianIndex;
  //finding of middle index
  middle = (first + last)/2;
  //Line 28-36: finds the median value and assigns medianIndex
  if((list[middle] <= list[last] &&  list[middle] >= list[first]) || (list[middle] >= list[last] && list[middle] <= list[first])){
    medianIndex = middle;
  }
  else if((list[first] >= list[middle] && list[first] <= list[last])||(list[first] <= list[middle] && list[first] >= list[first])){
    medianIndex = first;
  }
  else{
    medianIndex = last;
  }
  //puts median value at the beginning of the list
  swap(first, medianIndex, list);
  //assigns pivot value
  pivot = list[first];
  //assigns small index
  smallIndex = first;
  //line 44-48: begins swapping values in accordance to quicksort
  for(index = first + 1; index <= last; index++){
    if(list[index] < pivot){
      smallIndex++;
      swap(smallIndex, index, list);
    }
  }
  //swaps the values at first index and smallIndex
  swap(first, smallIndex, list);
  //return that will be used for the partion
  return smallIndex;
}


void quicksort(vector<int>& list, int first, int last) {
  //will hold the partition index
  int partitionIndex;
  //line 61-65: quick sort implementation
  if(first < last){
    partitionIndex = partition(list, first, last);
    quicksort(list, first, partitionIndex - 1);
    quicksort(list, partitionIndex + 1, last);
  }
}
//struct used to store the list id and value of the sublist elements
struct mergelist{
  int value;
  int list_ID;
};
//overloaded less than operator so a min heap of the mergelist type can be created
bool operator <(mergelist val1, mergelist val2) 
{ 
    return val2.value < val1.value; 
} 
//erases the top element of the sublist
void erase_element(vector<int>& list){
  list.erase(list.begin());
}
void multiway_merge(vector<vector<int> >& input_lists, vector<int>& output_list) 
{
  //checks to see if there is anything in the input list
  if(!input_lists.empty()){
    //finds how many columns in the 2D vector
    size_t col_size = input_lists.size();
    //will be used to assign specific values within the output_list
    int i = 0;
    //priority queue of type mergelist will be used as a min heap implementation
    priority_queue<mergelist> output_queue;
    //line 93-98: loads the top element of each sublist into the priority queue
    for(size_t i = 0; i < col_size; i++){
      mergelist element;
      element.list_ID = i;
      element.value = input_lists[i].front();
      output_queue.push(element);
    }
    //continues executing until the stack is empty
    while(!output_queue.empty()){
      //contains the list_ID of the top element of the priority queue
      int ID = output_queue.top().list_ID;
      //moves the top value of the priority queue into the output_list
      output_list[i] = output_queue.top().value;
      //increases the index for the next element value to be loaded in
      i++;
      //deletes top element of a certain sublist
      erase_element(input_lists[ID]);
      //pops off the top element of the priority queue
      output_queue.pop();
      //checks to see if there is a successor of the newly deleted item and loads the successor into the priority queue
      if(!input_lists[ID].empty()){
        mergelist elements;
        elements.list_ID = ID;
        elements.value = input_lists[ID].front();
        output_queue.push(elements);
      }
    }
  }
} 
int main(int argc, char** argv) {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > input_lists(n, vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> input_lists[i][j];
    }
  }

  // Quicksort k sublists
  for (int i = 0; i < input_lists.size(); ++i)
    quicksort(input_lists[i], 0, m-1);

  // Merge n input sublists into one sorted list
  vector<int> output_list(n * m);
  multiway_merge(input_lists, output_list);

  for (int i = 0; i < output_list.size(); ++i)
    cout << output_list[i] << " ";
  cout << endl;
}
