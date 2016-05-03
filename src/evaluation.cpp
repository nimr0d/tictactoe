#include "evaluation.h"

i64 eval(i64 *arr) {
	i64 count = 0;

	for (Square i = 0; i < 3; ++i) {
		i64 c = 0;
		i64 h1 = 0, h2 = 0;

		for (Square j = 0; j < 3; ++j) {

			i64 pt = arr[3 * i + j];

			if (pt > 0) {
				++c;
				h1 = pt;
			} else if (pt < 0) {
				--c;
				h2 = pt;
			}

			count += pt;
		}
		if (c > 0) {
			count += h2;
		} else if (c < 0) {
			count += h1;
		}
	}

	for (Square j = 0; j < 3; ++j) {
		i64 c = 0;
		i64 h1 = 0, h2 = 0;

		for (Square i = 0; i < 3; ++i) {

			i64 pt = arr[3 * i + j];

			if (pt > 0) {
				++c;
				h1 = pt;
			} else if (pt < 0) {
				--c;
				h2 = pt;
			}

			count += pt;
		}
		if (c > 0) {
			count += h2;
		} else if (c < 0) {
			count += h1;
		}
	}


	{
		i64 c = 0;
		i64 h1 = 0, h2 = 0;

		for (Square d = 0; d < 3; ++d) {

			i64 pt = arr[4 * d];

			if (pt > 0) {
				++c;
				h1 = pt;
			} else if (pt < 0) {
				--c;
				h2 = pt;
			}

			count += pt;
		}
		if (c > 0) {
			count += h2;
		} else if (c < 0) {
			count += h1;
		}
	}

	{
		i64 c = 0;
		i64 h1 = 0, h2 = 0;

		for (Square d = 0; d < 3; ++d) {

			i64 pt = arr[2 * d + 2];

			if (pt > 0) {
				++c;
				h1 = pt;
			} else if (pt < 0) {
				--c;
				h2 = pt;
			}

			count += pt;
		}
		if (c > 0) {
			count += h2;
		} else if (c < 0) {
			count += h1;
		}
	}

	loop: 

	return count;
}