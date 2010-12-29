/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "nmod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result, r1;

    printf("to/from_string....");
    fflush(stdout);

    /* Check aliasing of a and b */
    for (i = 0; i < 10000; i++)
    {
        nmod_poly_t a, b;
        mp_limb_t n = n_randtest_not_zero();
        char * str;

        nmod_poly_init(a, n);
        nmod_poly_init(b, n);
        nmod_poly_randtest(a, n_randint(100));

        str = nmod_poly_to_string(a);
        r1 = nmod_poly_from_string(b, str);
        
        result = (r1 && nmod_poly_equal(a, b));
        if (!result)
        {
            printf("FAIL:\n");
            printf("r1 = %d, n = %lu\n", r1, a->mod.n);
            printf("%s\n", str);
            nmod_poly_print(a), printf("\n\n");
            nmod_poly_print(b), printf("\n\n");
            abort();
        }

        free(str);
        nmod_poly_clear(a);
        nmod_poly_clear(b);
    }

    printf("PASS\n");
    return 0;
}
