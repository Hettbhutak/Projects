#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//global variable delaration
#define SIZE 1000
#define NUM_SORTS 11

//Function Prototypes
double bubbleSort(int arr[], int n);
double selectionSort(int arr[], int n);
double insertionSort(int arr[], int n);
double mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
double heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
double radixsort(int arr[], int n);
int getMax(int arr[], int n);
void countSort(int arr[], int n, int exp);
double shellSort(int arr[], int n);
double countingSort(int arr[], int n);

int main() 
{
   int arr[SIZE];

   double ss[NUM_SORTS];

   //gererates ramdom numbers
   srand(time(0));
   for(int i = 0; i < SIZE; i++) {
      arr[i] = rand() % SIZE;
   }

   //perform sorting
   ss[1] = bubbleSort(arr, SIZE);
   printf("1. Bubble Sort took %f seconds to execute \n", ss[1]);

   ss[2] = selectionSort(arr, SIZE);
   printf("2. Selection Sort took %f seconds to execute \n", ss[2]);

   ss[3] = insertionSort(arr, SIZE);
   printf("3. Insertion Sort took %f seconds to execute \n", ss[3]);

   ss[4] = heapSort(arr, SIZE);
   printf("5. Heap Sort took %f seconds to execute \n", ss[4]); 

   ss[5] = radixsort(arr, SIZE);
   printf("6. Radix Sort took %f seconds to execute \n", ss[5]);

   ss[6] = shellSort(arr, SIZE);
   printf("7. Shell Sort took %f seconds to execute \n", ss[6]);
 
   ss[7] = countingSort(arr, SIZE);
   printf("8. Counting Sort took %f seconds to execute \n", ss[7]);


   clock_t start, end;

   start = clock();
   mergeSort(arr, 0, SIZE - 1);
   end = clock();
   ss[8] = ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("9. Merge Sort took %f seconds to execute \n", ss[8]);

   start = clock();
   quickSort(arr, 0, SIZE - 1);
   end = clock();
   ss[9]= ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("10. Quick Sort took %f seconds to execute \n", ss[9]);
   
   //sort the times
   for(int i = 1; i < NUM_SORTS; i++) {
      for(int j = i + 1; j < NUM_SORTS; j++) {
         if(ss[i] > ss[j]) {
            double temp = ss[i];
            ss[i] = ss[j];
            ss[j] = temp;
         }
      }
   }
   //print the sorted times
   printf("\nSorted Times\n");
   for(int i = 1; i < NUM_SORTS; i++) {
      printf("%f\n",ss[i]);
   }
   
   return 0;
}

// Bubble Sort
double bubbleSort(int arr[], int n) {

   clock_t start, end;
   double cpu_time_used;
    
   start = clock();

   for(int i = 0; i < n-1; i++) {     
       for (int j = 0; j < n-i-1; j++) { 
           if (arr[j] > arr[j+1]) {
              int temp = arr[j];
              arr[j] = arr[j+1];
              arr[j+1] = temp;
           }
       }
   }

   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   return cpu_time_used;
}

// Selection Sort
double selectionSort(int arr[], int n) {

   clock_t start, end;
   double cpu_time_used;

   start = clock();

   for(int i = 0; i < n; i++) {
      int min = i;
      for(int j = i+1; j < n; j++)
         if(arr[j] < arr[min])
            min = j;
      int temp = arr[i];
      arr[i] = arr[min];
      arr[min] = temp;
   }

   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   return cpu_time_used;
}

// Insertion Sort
double insertionSort(int arr[], int n) {
   int key, j;

   clock_t start, end;
   double cpu_time_used;

   start = clock();

   for(int i = 1; i < n; i++) {
      key = arr[i];
      j = i - 1;
      while(j >= 0 && arr[j] > key) {
         arr[j+1] = arr[j];
         j--;
      }
      arr[j+1] = key;
   }

   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   return cpu_time_used;
}

// Merge Sort
void merge(int arr[], int l, int m, int r) {
   int i, j, k;
   int n1 = m - l + 1;
   int n2 = r - m;
   int L[n1], R[n2];
   for (i = 0; i < n1; i++)
      L[i] = arr[l + i];
   for (j = 0; j < n2; j++)
      R[j] = arr[m + 1 + j];
   i = 0;
   j = 0;
   k = l;
   while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
         arr[k] = L[i];
         i++;
      } else {
         arr[k] = R[j];
         j++;
      }
      k++;
   }
   while (i < n1) {
      arr[k] = L[i];
      i++;
      k++;
   }
   while (j < n2) {
      arr[k] = R[j];
      j++;
      k++;
   }
}

double mergeSort(int arr[], int l, int r) {
   if (l < r) {
      int m = l + (r - l) / 2;
      mergeSort(arr, l, m);
      mergeSort(arr, m + 1, r);
      merge(arr, l, m, r);
   }
}

// Quick Sort
int partition(int arr[], int low, int high) {
   int pivot = arr[high];
   int i = (low - 1);
   for (int j = low; j <= high - 1; j++) {
      if (arr[j] < pivot) {
         i++;
         int temp = arr[i];
         arr[i] = arr[j];
         arr[j] = temp;
      }
   }
   int temp = arr[i + 1];
   arr[i + 1] = arr[high];
   arr[high] = temp;
   return (i + 1);
}

void quickSort(int arr[], int low, int high) {
   if (low < high) {
      int pi = partition(arr, low, high);
      quickSort(arr, low, pi - 1);
      quickSort(arr, pi + 1, high);
   }
}

// Heap Sort
void heapify(int arr[], int n, int i) {
   int largest = i;
   int left = 2 * i + 1;
   int right = 2 * i + 2;
   if (left < n && arr[left] > arr[largest])
      largest = left;
   if (right < n && arr[right] > arr[largest])
      largest = right;
   if (largest != i) {
      int swap = arr[i];
      arr[i] = arr[largest];
      arr[largest] = swap;
      heapify(arr, n, largest);
   }
}

double heapSort(int arr[], int n) {

      clock_t start, end;
   double cpu_time_used;

   start = clock();

   for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);
   for (int i = n - 1; i >= 0; i--) {
      int temp = arr[0];
      arr[0] = arr[i];
      arr[i] = temp;
      heapify(arr, i, 0);
   }

   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   return cpu_time_used;
}

// Radix Sort
int getMax(int arr[], int n) {
   int mx = arr[0];
   for (int i = 1; i < n; i++)
      if (arr[i] > mx)
         mx = arr[i];
   return mx;
}

void countSort(int arr[], int n, int exp) {
   int output[n];
   int i, count[10] = {0};
   for (i = 0; i < n; i++)
      count[(arr[i] / exp) % 10]++;
   for (i = 1; i < 10; i++)
      count[i] += count[i - 1];
   for (i = n - 1; i >= 0; i--) {
      output[count[(arr[i] / exp) % 10] - 1] = arr[i];
      count[(arr[i] / exp) % 10]--;
   }
   for (i = 0; i < n; i++)
      arr[i] = output[i];
}

double radixsort(int arr[], int n) {

       clock_t start, end;
   double cpu_time_used;

   start = clock();

   int m = getMax(arr, n);
   for (int exp = 1; m / exp > 0; exp *= 10)
      countSort(arr, n, exp);

      end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   return cpu_time_used;
}

// Shell Sort
double shellSort(int arr[], int n) {

   clock_t start, end;
   double cpu_time_used;

   start = clock();

   for (int gap = n / 2; gap > 0; gap /= 2) {
      for (int i = gap; i < n; i += 1) {
         int temp = arr[i];
         int j;
         for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            arr[j] = arr[j - gap];
         arr[j] = temp;
      }
   }

     end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   return cpu_time_used;
}

// Counting Sort
double countingSort(int arr[], int n) 
{
   clock_t start, end;
   double cpu_time_used;

   start = clock();

   int max = arr[0];
   for (int i = 1; i < n; i++)
      if (arr[i] > max)
         max = arr[i];
   int count[max + 1];
   for (int i = 0; i <= max; ++i)
      count[i] = 0;
   for (int i = 0; i < n; i++)
      count[arr[i]]++;
   for (int i = 1; i <= max; i++)
      count[i] += count[i - 1];
   int output[n];
   for (int i = n - 1; i >= 0; i--) {
      output[count[arr[i]] - 1] = arr[i];
      count[arr[i]]--;
   }
   for (int i = 0; i < n; i++)
      arr[i] = output[i];

        end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   return cpu_time_used;
}
