// Copyright 2021 Gleb "belgad" Danshin
#include <iostream>
#include <random>
#include <cstring>
#include <vector>
#include <chrono>

#include "point.hh"
#include "heapsort.hh"
#include "qsort.hh"

static int N = 10;
static bool do_qsort = false;

std::vector<Point> convex_hull(Point data[], int length = N) {
  // find minimum point
  int min = 0;
  for (int i = 1; i < length; ++i) {
    if (data[i].X < data[min].X ||
    (data[i].X == data[min].X && data[i].Y < data[min].Y)) {
      min = i;
    }
  }
  swap(data[0], data[min]);

  // move origin to min point
  Point diff = data[0];
  for (int i = 0; i < length; ++i) {
    data[i] -= diff;
  }

  // sort points
  if (do_qsort) {
    qsort(data + 1, length - 1);
  } else {
    heapsort(data + 1, length - 1);
  }

  for (int i = 0; i < length; ++i) {
    data[i] += diff;
  }

  // print sorted
  // std::cout << "data after sorting:" << std::endl;
  // for (int i = 0; i < length; ++i) {
  //   std::cout << data[i] << std::endl;
  // }

  // find convex hull
  std::vector<Point> answer;
  answer.push_back(data[0]);
  answer.push_back(data[1]);
  int last = 1;
  for (int i = 2; i < length; ++i) {
    if (Point::det(answer[last] - answer[last - 1],
    data[i] - answer[last]) > 0) {
      answer.push_back(data[i]);
      ++last;
    } else {
      while (last > 1 && Point::det(answer[last] - answer[last - 1],
      data[i] - answer[last]) <= 0) {
        answer.pop_back();
        --last;
      }
      answer.push_back(data[i]);
      ++last;
    }
  }

  // print convex hull
  // std::cout << "convex hull" << std::endl;
  // for (int i = 0; i <= last; ++i) {
  //   std::cout << answer[i] << std::endl;
  // }

  return answer;
}

int main(int argc, char** argv) {
  double q = 100.0, w = 100.0;
  int mode = 0;

  // command line parameters
  for (int i = 1; i < argc; ++i) {
    // sorting algorithm to use
    // `-qsort` - use qsort, otherwise heapsort
    if (strcmp(argv[i], "-qsort") == 0) {
      do_qsort = true;
    }
    // `-n` - N parameter
    if (argc >= i + 2 && strcmp(argv[i], "-n") == 0) {
      N = atoi(argv[++i]);
    }
    // `-q` - q parameter
    if (argc >= i + 2 && strcmp(argv[i], "-q") == 0) {
      q = atof(argv[++i]);
    }
    // `-w` - w parameter
    if (argc >= i + 2 && strcmp(argv[i], "-w") == 0) {
      w = atof(argv[++i]);
    }
    // `-m` - mode parameter
    if (argc >= i + 2 && strcmp(argv[i], "-m") == 0) {
      mode = atoi(argv[++i]);
    }
  }

  // create random generator
  std::random_device random_device;
  std::mt19937 random_generator(random_device());
  Point* data = new Point[N];

  if (mode == 1) {
    std::uniform_real_distribution<double> q_random(0.0, q);
    std::uniform_real_distribution<double> w_random(0.0, w);
    for (int i = 0; i < N; ++i) {
      data[i].X = q_random(random_generator);
      data[i].Y = w_random(random_generator);
    }
  } else if (mode == 2) {
    std::uniform_real_distribution<double> qw_random(0.0, 2 * (q + w));
    for (int i = 0; i < N; ++i) {
      double tmp = qw_random(random_generator);
      if (tmp < q) {
        data[i].X = tmp;
        data[i].Y = 0.0;
      } else if ((tmp -= q) < w) {
        data[i].X = 0.0;
        data[i].Y = tmp;
      } else if ((tmp -= w) < q) {
        data[i].X = tmp;
        data[i].Y = w;
      } else {
        data[i].X = q;
        data[i].Y = tmp;
      }
    }
  }

  // generate random points (or not)
  // Point data[N] = {
  //   {0, 0}, {4, 19}, {8, 18}, {16, 3}, {12, 11},
  //   {18, 7}, {14, 14}, {2, 20}, {6, 17}, {10, 17}
  // };
  // std::uniform_real_distribution<double> random_real(0.0, 100.0);
  // std::cout << "data before sorting:" << std::endl;
  // for (int i = 0; i < N; ++i) {
  //  data[i].X = random_real(random_generator);
  //  data[i].Y = random_real(random_generator);
    // std::cout << data[i] << std::endl;
  // }

  auto time_1 = std::chrono::high_resolution_clock::now();
  auto answer = convex_hull(data);
  auto time_2 = std::chrono::high_resolution_clock::now();

  auto dt = std::chrono::duration_cast<std::chrono::microseconds>(time_2 - time_1).count();

  std::cout << (do_qsort ? "quick" : "heaps") << "; mode: " << mode << " ; q: " << q << "; w: " << w << "; n: " << N << "; t: " << dt << std::endl;

  delete[] data;

  return 0;
}
