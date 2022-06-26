/*
 * (C) Copyright 2005- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
 * virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "grib_api.h"

static void usage(const char* prog)
{
    printf("Usage: %s grib_file\n", prog);
    exit(1);
}

int main(int argc, char** argv)
{
    FILE* in = NULL;
    int err  = 0;
    double lat, lon, value;
    int n                        = 0;
    const int numberOfDataPoints = 13280;
    const char* sample_filename  = "gg_sfc_grib2";
    grib_handle* h               = NULL;
    grib_iterator* iter          = NULL;

    h = grib_handle_new_from_samples(0, sample_filename);
    assert(h);

    iter = grib_iterator_new(h, 0, &err);
    assert(!err);
    assert(iter);

    assert(grib_iterator_has_next(iter));
    n = 0;

    while (grib_iterator_next(iter, &lat, &lon, &value)) {
        if (n < numberOfDataPoints - 1)
            assert(grib_iterator_has_next(iter));
        n++;
    }
    assert(n == numberOfDataPoints);

    assert(grib_iterator_has_next(iter) == 0);

    grib_iterator_delete(iter);

    grib_handle_delete(h);

    return 0;
}
