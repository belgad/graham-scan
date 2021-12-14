// Copiryght 2021 Gleb "belgad" Danshin
#ifndef GRAHAM_SCAN_SRC_HEAPSORT_HH_
#define GRAHAM_SCAN_SRC_HEAPSORT_HH_

#include <cstddef>

#include "point.hh"

void heapify(Point* data, int length, int i = 0);
void heapsort(Point* data, int length);

#endif  // GRAHAM_SCAN_SRC_HEAPSORT_HH_
