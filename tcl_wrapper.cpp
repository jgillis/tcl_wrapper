/*
 *   Copyright (C) 2017  Paul Springer (springer@aices.rwth-aachen.de)
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdlib.h>
#include <iostream>

#include <tcl.h>

#define casadi_int long long int

#define MAX_DIM 10

extern "C" {
  int einstein_eval(
      casadi_int n_dim_a, // size of dim_a
      const casadi_int* dim_a,
      const casadi_int* a_contr,
      casadi_int n_dim_b, // size of dim_b
      const casadi_int* dim_b,
      const casadi_int* b_contr,
      casadi_int n_dim_c, // size of dim_c
      const casadi_int* dim_c,
      const casadi_int* c_contr,
      const double* A,
      const double* B,
      double* C) {

    /**

    double *dataA, *dataB, *dataC;
    int pA = 1;
    for (int i=0;i<n_dim_a;++i) pA*= dim_a[i];
    int pB = 1;
    for (int i=0;i<n_dim_b;++i) pB*= dim_b[i];
    int pC = 1;
    for (int i=0;i<n_dim_c;++i) pC*= dim_c[i];
    posix_memalign((void**) &dataA, 64, sizeof(double) * pA);
    posix_memalign((void**) &dataB, 64, sizeof(double) * pB);
    posix_memalign((void**) &dataC, 64, sizeof(double) * pC);
    std::copy(A, A+pA, dataA);
    std::copy(B, B+pB, dataB);
    std::copy(C, C+pC, dataC);
    */

    char alphabet[] = "mnpqrst";
    long sizeA[MAX_DIM];
    std::copy(dim_a, dim_a + n_dim_a, sizeA);
    long sizeB[MAX_DIM];
    std::copy(dim_b, dim_b + n_dim_b, sizeB);
    long sizeC[MAX_DIM];
    std::copy(dim_c, dim_c + n_dim_c, sizeC);

    char indA[2*MAX_DIM];
    char indB[2*MAX_DIM];
    char indC[2*MAX_DIM];

    char* indA_ptr = indA;
    char* indB_ptr = indB;
    char* indC_ptr = indC;

    bool ind_active[2*MAX_DIM];
    std::fill(ind_active, ind_active+2*MAX_DIM, false);

    int i;
    for (i=0;i<n_dim_a;++i) {
      (*indA_ptr++) = alphabet[-a_contr[i]-1];
      ind_active[-a_contr[i]-1] = true;
      if (i<n_dim_a-1) (*indA_ptr++) = ',';
    }
    (*indA_ptr++) = '\0';

    bool has_contr = false;
    for (i=0;i<n_dim_b;++i) {
      (*indB_ptr++) = alphabet[-b_contr[i]-1];
      if (ind_active[-b_contr[i]-1]) has_contr = true;
      if (i<n_dim_b-1) (*indB_ptr++) = ',';
    }
    (*indB_ptr++) = '\0';

    if (!has_contr) return 1;

    for (i=0;i<n_dim_c;++i) {
      (*indC_ptr++) = alphabet[-c_contr[i]-1];
      if (i<n_dim_c-1) (*indC_ptr++) = ',';
    }
    (*indC_ptr++) = '\0';

    /**
    std::cout << "A" << indA << std::endl;
    std::cout << "B" << indB << std::endl;
    std::cout << "C" << indC << std::endl;

    for (auto e : std::vector<long>(sizeA,sizeA+n_dim_a))
    std::cout << "A: " << e << std::endl;
    for (auto e : std::vector<long>(sizeB,sizeB+n_dim_b))
    std::cout << "B: " << e << std::endl;
    for (auto e : std::vector<long>(sizeC,sizeC+n_dim_c))
    std::cout << "C: " << e << std::endl;
    */
    

    dTensorMult(1, A, sizeA, nullptr, indA,
                   B, sizeB, nullptr, indB,
                1, C, sizeC, nullptr, indC);
    //std::copy(dataC, dataC+pC, C);

    return 0;
  }
}


