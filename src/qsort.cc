// Copiryght 2021 Gleb "belgad" Danshin
#include "qsort.hh"

void qsort(Point* data, int length) {
  if (length < 2) return;

  // reference points
  int left = -1, right = length;
  Point ref = data[(length - 1) / 2];

  // swapper
  while (left < right) {
    while (data[++left] < ref) {}
    while (data[--right] >= ref) {}
    if (left < right) {
      swap(data[left], data[right]);
    }
  }
  if (left <= (length - 1) / 2) {
    swap(data[(length - 1)/ 2], data[length - 1]);
  }
  qsort(data, left);
  qsort(data + left, length - left);
}
