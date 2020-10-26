#pragma once

#include <cmath>
#include <cstdlib>
#include <time.h>
#include <vector>


void normalize_vector(std::vector<double>& v);

void fill_random_vector(std::vector<double>& v);

double scalar_composition(const std::vector<double>& a,
                          const std::vector<double>& b);

void transpose(std::vector<std::vector<double> >& m);