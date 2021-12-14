// Copiryght 2021 Gleb "belgad" Danshin
#include "heapsort.hh"

void heapify(Point* data, int length, int i) {
  int largest = i,
  left = 3 * i + 1, center = 3 * i + 2, right = 3 * i + 3;
  if (left < length && data[largest] < data[left]) {
    largest = left;
  }
  if (center < length && data[largest] < data[center]) {
    largest = center;
  }
  if (right < length && data[largest] < data[right]) {
    largest = right;
  }
  if (largest != i) {
    swap(data[i], data[largest]);
    heapify(data, length, largest);
  }
}

void heapsort(Point* data, int length) {
  for (int i = (length - 1) / 3; i >= 0; --i) {
    heapify(data, length, i);
  }
  for (int i = length - 1; i >= 0; --i) {
    swap(data[0], data[i]);
    heapify(data, i, 0);
  }
}
 