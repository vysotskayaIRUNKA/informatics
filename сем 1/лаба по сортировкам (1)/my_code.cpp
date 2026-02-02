#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
using namespace std;

int rand_uns(int min, int max) {
  unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
  static std::default_random_engine e(seed);
  std::uniform_int_distribution<int> d(min, max);
  return d(e);
}

void sw(int *a, int j, int i) {
  auto h = a[j];
  a[j] = a[i];
  a[i] = h;
}

void BubbleSort(int *a, int n) {
  for (auto i = 0; i < n - 1; i++) {
    bool swapped = false;
    for (auto j = 0; j < n - i - 1; j++) {
      if (a[j] > a[j + 1]) {
        sw(a, j, j + 1);
        swapped = true;
      }
    }
    if (not swapped)
      return;
  }
}

void SelectionSort(int *a, int n) {
  for (auto i = 0; i < n; i++) {
    int min_el = i;
    for (auto j = i; j < n; j++) {
      if (a[min_el] > a[j])
        min_el = j;
    }
    sw(a, min_el, i);
  }
}

void InsertionSort(int *a, int n) {
  for (int i = 1; i < n; i++) {
    int prev = i - 1;
    int j = i;
    int nash = a[i];
    while (prev >= 0 && a[prev] > nash) {
      sw(a, prev, j);
      prev--;
      j--;
    }
  }
}

void QuickSort(int *a, int left, int right) {
  if (left >= right)
    return;
  int opora = a[(left + right) / 2];
  int i_l = left;
  int i_r = right;
  while (i_l <= i_r) {
    while (a[i_l] < opora)
      i_l++;
    while (a[i_r] > opora)
      i_r--;
    if (i_l <= i_r) {
      sw(a, i_l, i_r);
      i_l++;
      i_r--;
    }
  }
  QuickSort(a, left, i_r);
  QuickSort(a, i_l, right);
}

void CombSort(int *a, int n) {
  int step = n;
  bool swapped = true;
  while (step > 1 || swapped == true) {
    step = max(1, int(step / 1.2));
    swapped = false;
    for (int i = 0; i + step < n; i++)
      if (a[i] > a[i + step]) {
        sw(a, i, i + step);
        swapped = true;
      }
  }
}

void Merge(int *a, int left, int mid, int right) {
  int n_l = mid - left + 1;
  int n_r = right - mid;
  int left_sorted[50000];
  int right_sorted[50000];
  for (int i = 0; i < n_l; i++)
    left_sorted[i] = a[left + i];
  for (int i = 0; i < n_r; i++)
    right_sorted[i] = a[mid + 1 + i];
  int l = 0, r = 0, index = left;
  while (l < n_l && r < n_r) {
    if (left_sorted[l] < right_sorted[r]) {
      a[index] = left_sorted[l];
      l++;
    } else {
      a[index] = right_sorted[r];
      r++;
    }
    index++;
  }
  while (l < n_l) {
    a[index] = left_sorted[l];
    l++;
    index++;
  }
  while (r < n_r) {
    a[index] = right_sorted[r];
    r++;
    index++;
  }
}

void MergeSort(int *a, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    Merge(a, left, mid, right);
  }
}

void ObrSort(int *a, int n) {
  for (auto i = 0; i < n - 1; i++) {
    bool swapped = false;
    for (auto j = 0; j < n - i - 1; j++) {
      if (a[j] < a[j + 1]) {
        sw(a, j, j + 1);
        swapped = true;
      }
    }
    if (not swapped)
      return;
  }
}

const unsigned int l[5] = {1000, 5000, 10000, 50000, 100000};

int main() {
  ofstream file;
  // file.open("вставка.csv");
  // file.open("пузырек.csv");
  // file.open("выбор.csv");
  // file.open("слияние худший вариант.csv");
  for (int i = 0; i < sizeof(l) / sizeof(l[0]); i++) {
    cout << "Размер массива - " << l[i] << endl;
    for (int j = 0; j < 10; j++) {
      int a[100000];
      for (int k = 0; k < l[i]; k++) {
        a[k] = rand_uns(0, 10000);
      }
      // BubbleSort(a, l[i]);
      // ObrSort(a, l[i]);
      auto start = std::chrono::high_resolution_clock::now();
      BubbleSort(a, l[i]);
      auto end = std::chrono::high_resolution_clock::now();
      auto nsec = end - start;
      cout << nsec.count() << " нсек." << endl;
    }
  }
  file.close();
}
