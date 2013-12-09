#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Whenever the output array gets full, it is expanded by this quantity:
#define CHUNK_SIZE 10
#define FULL    0
#define PARTIAL 1

// Types for data and indexes:
typedef float data_t;
typedef u_int16_t index_t;

// Structure holding algorithm data and parameters:
typedef struct {
	data_t * data_v; // vector of data
	index_t data_s; // number of data points
	data_t sigmas; // number of sigmas defining the threshold
	index_t win_size; // moving windows size
	data_t stdev; // search_peaks() will put here the overal st.dev.
} PeakSearch;

typedef struct {
	data_t mean;
	data_t sd;
	data_t max;
	index_t max_idx;
} Statistics;

data_t mean(PeakSearch * ps, index_t const start, index_t const end) {
	data_t sum = 0.;
	index_t i, c;
	for (i = start, c = 0; i < end; i++, c++) {
		sum += ps->data_v[i];
	}
	return (sum / c);
}

void statistics(PeakSearch * ps, index_t const start, char const type,
		Statistics * stat) {
	data_t acc = 0.;
	index_t i, c, end;
	switch (type) {
	case FULL:
		end = ps->data_s;
		break;
	case PARTIAL:
		end = start + ps->win_size <= ps->data_s ?
				start + ps->win_size : ps->data_s;
		break;
	}
	stat->mean = mean(ps, start, end);
	stat->max = 0.;
	for (i = start, c = 0; i < end; i++, c++) {
		acc += pow((ps->data_v[i] - stat->mean), 2);
		if (ps->data_v[i] > stat->max) {
			stat->max = ps->data_v[i];
			stat->max_idx = i;
		}
	}
	stat->sd = sqrt(acc / (c - 1));
}

// Performs the peak search on the data and according to the parameters in ps.
// The indexes of found peaks are returned in peaks_v.
// ps.stdev will be loaded with the overall standard deviation.

index_t search_peaks(PeakSearch * ps, index_t ** peaks_v) {
	index_t count = 0;
	index_t peaks_s = CHUNK_SIZE;
	Statistics stat;
	free(*peaks_v);
	*peaks_v = (index_t*) malloc(peaks_s * sizeof(index_t));

	statistics(ps, 0, FULL, &stat);
	ps->stdev = stat.sd;

	index_t i;
	char in_cluster = 0;

	data_t max = 0.;
	for (i = 0; i < (ps->data_s - ps->win_size); i++) {
		statistics(ps, i, PARTIAL, &stat);
		if (stat.sd > ps->sigmas * ps->stdev) {
			if (stat.max > max) {
				(*peaks_v)[count] = stat.max_idx;
				max = stat.max;
			}
			in_cluster = 1;
		} else {
			if (in_cluster == 1)
				count++;
			if (count > peaks_s) {
				peaks_s += CHUNK_SIZE;
				*peaks_v = (index_t*) realloc(*peaks_v,
						peaks_s * sizeof(index_t));
			}
			max = 0.;
			in_cluster = 0;
		}
	}
	return count;
}

int main_statistics(int argc, const char * argv[]) {
	// data array:
	data_t d[] = { 1, 1, 2, 1, 2, 30, 32, 8, 2, 1, 1, 1, 2, 1, 2, 2, 1, 3, 1, 1,
			1, 1, 2, 1, 2, 33, 32, 8, 2, 1, 1, 1, 2, 1, 2, 2, 1, 3, 1, 1 };

	// PeakSearch structure:
	PeakSearch ps;
	ps.sigmas = 1.0;
	ps.win_size = 5;
	ps.data_s = sizeof(d) / sizeof(data_t);
	ps.data_v = (data_t*) malloc(ps.data_s * sizeof(data_t));
	ps.data_v = d;

	// Result array, initialized to minimum length (will expand automatically)
	index_t *peaks = (index_t*) malloc(sizeof(index_t));

	// Run the search on ps and put results in peaks
	index_t count = search_peaks(&ps, &peaks);

	// Printout:
	printf("Overall st.dev: %f. Found %d peaks\n", ps.stdev, count);
	index_t i;
	for (i = 0; i < count; i++) {
		printf("peak %d: point %d, value %f\n", i, peaks[i],
				ps.data_v[peaks[i]]);
	}

	// Cleanup:
	free(peaks);
	return 0;
}
