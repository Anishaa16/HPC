#include <iostream>
#include <omp.h>
#include <ctime>

using namespace std;

void min(int *arr, int n)
{
   double min_val = 10000;
   int i;
   double start_time = omp_get_wtime();
#pragma omp parallel for reduction(min : min_val)
   for (i = 0; i < n; i++)
   {
      if (arr[i] < min_val)
      {
         min_val = arr[i];
      }
   }
   double end_time = omp_get_wtime();
   cout << "\nMin function execution time: " << (end_time - start_time) << " seconds" << endl;
   cout << "\nmin_val = " << min_val << endl;
}

void max(int *arr, int n)
{
   double max_val = 0.0;
   int i;
   double start_time = omp_get_wtime();
#pragma omp parallel for reduction(max : max_val)
   for (i = 0; i < n; i++)
   {
      if (arr[i] > max_val)
      {
         max_val = arr[i];
      }
   }
   double end_time = omp_get_wtime();
   cout << "\nMax function execution time: " << (end_time - start_time) << " seconds" << endl;
   cout << "\nmax_val = " << max_val << endl;
}

void avg(int *arr, int n)
{
   int i;
   float avg = 0, sum = 0;
   double start_time = omp_get_wtime();
#pragma omp parallel reduction(+:sum)
   {
#pragma omp for
      for (i = 0; i < n; i++)
      {
         sum = sum + arr[i];
      }
   }
   double end_time = omp_get_wtime();
   cout << "\nAvg function execution time: " << (end_time - start_time) << " seconds" << endl;
   cout << "\nSum = " << sum << endl;
   avg = sum / n;
   cout << "\nAverage = " << avg << endl;
}

int main()
{
   omp_set_num_threads(4);
   int n, i;

   cout << "Enter the number of elements in the array: ";
   cin >> n;
   int arr[n];

   cout << "Enter " << n << " elements for the array: ";
   for (i = 0; i < n; ++i)
   {
      cin >> arr[i];
   }

   cout << "\nArray elements are: ";
   for (i = 0; i < n; i++)
   {
      cout << arr[i] << ",";
   }

   min(arr, n);
   max(arr, n);
   avg(arr, n);
   return 0;
}
