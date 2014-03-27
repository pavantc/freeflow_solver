#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#define DPRINT printf
#else
#define DPRINT
#endif

enum {
	NORTH = 0,
	EAST,
	WEST,
	SOUTH
};

#define A 'A'
#define B 'B'
#define C 'C'
#define D 'D'
#define E 'E'
#define F 'F'
#define G 'G'
#define H 'H'
#define I 'I'
#define J 'J'
#define K 'K'
#define L 'L'
#define M 'M'
#define N 'N'
#define O 'O'
#define P 'P'

#define NUM_EP 6
#define MAX_SIZE 16

#if 1
int ref_arr[MAX_SIZE][MAX_SIZE] = {
	{0, 0, 0, C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, B, 0, 0, 0, 0, E, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, A, 0, F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, D, 0, 0, 0, B, 0, C, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, A, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, D, F, E, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
#else
int ref_arr[MAX_SIZE][MAX_SIZE] = {
	{A, B, C, D, E, F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{A, B, C, D, E, F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
#endif

int failure_count;
int solution_count;

typedef struct endpoint {
	int ep_id;
	int ep_row;
	int ep_col;
	int ep_completed;
} ep_t;

/*
 * Array that holds the completion status of endpoints
 * Array index 0 contains the src ep and index 1 contains the dest ep.
 * Index 2 contains the next src ep and 3 the next dest ep, and so on
 */
ep_t ep_arr[NUM_EP * 2] = {{0, 0, 0}, };

/* Each endpoint has one src and one dest. Hence multiplying by 2 */
#define EP_STK_SIZE (MAX_SIZE * 2)
ep_t ep_stk[EP_STK_SIZE] = {{0, 0, 0}, };
int top = -1;

/*
 * Weights rows and columns
 * Weight of a row is defined as the number of incomplete endpoints above and
 * below this row
 * Weight of a column is defined as the number of incomplete endpoints to the
 * left and right of this column
 * We maintain one array containing the weights of rows and one containing the
 * weigths of columns
 */

int row_weight[MAX_SIZE] = {0, };
int col_weight[MAX_SIZE] = {0, };

/* Function call counts */
int rw_cc = 0;
int tp_cc = 0;
int fnp_cc = 0;
void print_cc();

int
push_eps(ep_t *src, ep_t *dest)
{
	DPRINT("push_eps : top = %d\n", top);

	/* Each push is push of two objects - src and dest */
	if (top >= (EP_STK_SIZE - 1)) {
		return (1);
	}
	ep_stk[++top] = *src;
	ep_stk[++top] = *dest;
	return (0);
}

int
pop_eps(ep_t *src, ep_t *dest)
{
	DPRINT("pop_eps : top = %d\n", top);
	if (top <= 0) {
		return (1);
	}
	*dest = ep_stk[top--];
	*src = ep_stk[top--];

	DPRINT("TRACE: popped SRC %C - (%d, %d)\n",
	    dest->ep_id, src->ep_row, src->ep_col);
	DPRINT("TRACE: popped DST %C  - (%d, %d)\n",
	    dest->ep_id, dest->ep_row, dest->ep_col);
	return (0);
}


int **
alloc_n_by_n_array(int size)
{
	int **arr;
	int i;
	arr = malloc(size * sizeof(int *));
	for (i = 0; i < size; i++) {
		arr[i] = malloc(size * sizeof(int));
	}
	return (arr);
}

void
initialize_arr(int **arr, int size)
{
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			arr[i][j] = 0;
		}
	}
}

#define GET_EP_ID(ref_arr_entry) (ref_arr_entry - 'A');

void
dump_stack(int count)
{
	int i;

	DPRINT("DumpStack:\n");
	for (i = 0; i < count; i++) {
		DPRINT("%d : SRC : (%d, %d)\n", ep_stk[i*2].ep_id,
		    ep_stk[i*2].ep_row, ep_stk[i*2].ep_col);
		DPRINT("%d : DST : (%d, %d)\n", ep_stk[i*2 + 1].ep_id,
		    ep_stk[i*2 + 1].ep_row, ep_stk[i*2 + 1].ep_col);
	}
}

void
setup_puzzle(int ref_arr[][MAX_SIZE], int **arr, int size)
{
	struct endpoint src_ep[NUM_EP] = {{0, 0, 0}, };
	struct endpoint dest_ep[NUM_EP] = {{0, 0, 0}, };
	int i, j, k;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (!ref_arr[i][j]) {
				continue;
			}
			k = GET_EP_ID(ref_arr[i][j]);

			if (k >= NUM_EP || k < 0) {
				fprintf(stderr, "Invalid ref_arr entry %C\n",
				    ref_arr[i][j]);
				exit(1);
			}
			arr[i][j] = ref_arr[i][j];
			if (!src_ep[k].ep_id) {
				src_ep[k].ep_id = ref_arr[i][j];
				src_ep[k].ep_row = i;
				src_ep[k].ep_col = j;
			} else if (!dest_ep[k].ep_id) {
				dest_ep[k].ep_id = ref_arr[i][j];
				dest_ep[k].ep_row = i;
				dest_ep[k].ep_col = j;
			} else {
				fprintf(stderr, "Too many points for ref_arr "
				    "entry %C\n", ref_arr[i][j]);
				exit(1);
			}
		}
	}
	for(i = 0; i < NUM_EP; i++) {
		push_eps(&src_ep[i], &dest_ep[i]);
		ep_arr[2*i] = src_ep[i];
		ep_arr[2*i + 1] = dest_ep[i];
		ep_arr[2*i].ep_completed = 0;
		ep_arr[2*i + 1].ep_completed = 0;

		DPRINT("%d : SRC : (%d, %d)\n", src_ep[i].ep_id,
		    src_ep[i].ep_row, src_ep[i].ep_col);
		DPRINT("%d : DST : (%d, %d)\n", dest_ep[i].ep_id,
		    dest_ep[i].ep_row, dest_ep[i].ep_col);
	}
	dump_stack(NUM_EP);
}

print_arr(int **arr, int size)
{
	int i, j;

	printf("\n\n");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (arr[i][j]) {
				if (arr[i][j] & 0x00FF0000) {
					printf(" %-2C", arr[i][j] & 0x0000FFFF);
				} else {
					printf("*%-2C", arr[i][j] & 0x0000FFFF);
				}
			} else {
				printf("-- ");
			}
		}
		printf("\n");
	}
}

/* Return number of free slots in row and column of the supplied slot */
void
get_num_free_slots(int **arr, ep_t slot, int size, int *fr, int *fc)
{
	int i;
	int r, c;

	*fr = 0;
	*fc = 0;

	for (r = 0; r < size; r++) {
		if (arr[r][slot.ep_col] == 0) {
			(*fr)++;
		}
	}

	for (c = 0; c < size; c++) {
		if (arr[slot.ep_row][c] == 0) {
			(*fc)++;
		}
	}
	DPRINT("%s - fr = %d, fc = %d\n", __func__, *fr, *fc);
}

int
is_feasible_move(int **arr, ep_t slot, int size)
{
	int r = slot.ep_row;
	int c = slot.ep_col;
	int fr, fc;

	if (r >= size || r < 0 || c >= size || c < 0) {
		/* Boundary check */
		return (0);
	}
	if (arr[r][c]) {
		/* Already occupied */
		return (0);
	}

	get_num_free_slots(arr, slot, size, &fr, &fc);
	/*
	 * If number of free columns is less than the row weight, it is a bad
	 * move since we do not have enough columns/paths from the endpoints
	 * above this row to the ones below this row. Similar logic for free
	 * rows.
	 */
	if(fc < row_weight[r] || fr < col_weight[c]) {
		return (0);
	}
	return (1);
}

void
recalculate_weights(int **arr, int size)
{
	ep_t *s, *d;
	int ind, i;

	rw_cc++;

	/* Clear current values */
	memset(row_weight, 0, sizeof(row_weight));
	memset(col_weight, 0, sizeof(col_weight));

	/* Loop assumes grid is a square i.e. equal number of rows and cols */
	for (ind = 0; ind < size; ind++) {
		for (i = 0; i < NUM_EP; i++) {
			s = &ep_arr[2*i];
			d = &ep_arr[2*i + 1];
			if (((s->ep_row < ind) && (d->ep_row > ind)) &&
			    (!s->ep_completed)) {
				row_weight[ind]++;
			}
			if (((s->ep_col < ind) && (d->ep_col > ind)) &&
			    (!s->ep_completed)) {
				col_weight[ind]++;
			}
		}
	}
}

void
set_ep_completed(int ep_id, int **arr, int size)
{
	int i;
	for (i = 0; i < NUM_EP * 2; i++) {
		if (ep_arr[i].ep_id == ep_id) {
			ep_arr[i].ep_completed = 1;
			break;
		}
	}
	recalculate_weights(arr, size);
}

void
unset_ep_completed(int ep_id, int **arr, int size)
{
	int i;
	for (i = 0; i < NUM_EP * 2; i++) {
		if (ep_arr[i].ep_id == ep_id) {
			ep_arr[i].ep_completed = 0;
			break;
		}
	}
	recalculate_weights(arr, size);
}

/* Return 1 on failure in finding the destination, 0 on success */
void
try_path(int dir, ep_t *src, ep_t *dest, int **arr, int size)
{
	ep_t new_src;

	tp_cc++;
	switch(dir) {
	case NORTH:
		new_src.ep_row = src->ep_row - 1;
		new_src.ep_col = src->ep_col;
		break;
	case EAST:
		new_src.ep_row = src->ep_row;
		new_src.ep_col = src->ep_col + 1;
		break;
	case WEST:
		new_src.ep_row = src->ep_row;
		new_src.ep_col = src->ep_col - 1;
		break;
	case SOUTH:
		new_src.ep_row = src->ep_row + 1;
		new_src.ep_col = src->ep_col;
		break;
	}

	if (ep_cmp(&new_src, dest) == 0) {
		/* Found */
		ep_t next_src, next_dest;

		DPRINT("TRACE: Found destination %C(%d) at (%d, %d)\n",
		    dest->ep_id, dir, new_src.ep_row, new_src.ep_col);
		set_ep_completed(dest->ep_id, arr, size);

		/* Finished with the current ep pair. Process next set */
		if (pop_eps(&next_src, &next_dest) == 1) {
			/* No more endpoints to find routes between */
			if (arr_full(arr, size)) {
				/* Solved */
				solution_count++;
				print_arr(arr, size);
			} else {
				DPRINT("No solution in this route\n");
				failure_count++;
			}
			return;
		}

		/* Continue with the next set of endpoints */
		find_next_path(&next_src, &next_dest, arr, size);

		/* Add back path to stack */
		push_eps(&next_src, &next_dest);
		unset_ep_completed(next_dest.ep_id, arr, size);
	} else if (is_feasible_move(arr, new_src, size)) {
		DPRINT("TRACE: Old path for %C(%d)  - (%d, %d)\n",
		    dest->ep_id, dir, src->ep_row, src->ep_col);
		DPRINT("TRACE: New path for %C(%d)  - (%d, %d)\n",
		    dest->ep_id, dir, new_src.ep_row, new_src.ep_col);

		/*
		 * UI related. Set the path to the ep_id of the src/dest so
		 * that the path is highlighted with the same ID. Mask is used
		 * to differentiate the actual endpoints and the path between
		 * them. If the third byte in the ep_id is set to 0xFF, it is a
		 * path.
		 */
		arr[new_src.ep_row][new_src.ep_col] = 
		    (0x00FF0000 | dest->ep_id);
		find_next_path(&new_src, dest, arr, size);
		arr[new_src.ep_row][new_src.ep_col] = 0;
	}
}

int
arr_full(int **arr, int size)
{
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (arr[i][j] == 0) {
				return (0);
			}
		}
	}
	return (1);
}

/* If endpoints are the same, returns 0, else returns 1 */
int
ep_cmp(ep_t *src, ep_t *dest)
{
	if ((src->ep_row == dest->ep_row) &&
	    (src->ep_col == dest->ep_col)) {
		return (0);
	}
	return (1);
}

int
find_next_path(ep_t *src, ep_t *dest, int **arr, int size)
{
	fnp_cc++;

	try_path(NORTH, src, dest, arr, size);
	try_path(EAST, src, dest, arr, size);
	try_path(WEST, src, dest, arr, size);
	try_path(SOUTH, src, dest, arr, size);

	DPRINT("TRACE: Returning %C - (%d, %d)\n",
	    dest->ep_id, src->ep_row, src->ep_col);
}

solve_puzzle(int **arr, int size)
{
	ep_t src = {0}, dest = {0};
	pop_eps(&src, &dest);
	find_next_path(&src, &dest, arr, size);
}

void
print_cc()
{
	printf("rw_cc = %d\n", rw_cc);
	printf("fnp_cc = %d\n", fnp_cc);
	printf("tp_cc = %d\n", tp_cc);
}

#define SIZE 8

int
main()
{
	int size = SIZE;
	int **arr;

	if (SIZE > MAX_SIZE) {
		printf("Unsupported size %d. Max supported = %d\n", SIZE,
		    MAX_SIZE);
	}
	if (NUM_EP > SIZE) {
		printf("Number of endpoints %d greater than grid size %d\n",
 		    NUM_EP, SIZE);
	}

	arr = alloc_n_by_n_array(size);
	initialize_arr(arr, size);
	setup_puzzle(ref_arr, arr, size);

	printf("Problem:\n");
	printf("===============\n");
	print_arr(arr, size);

	printf("\nSolutions: \n");
	printf("===============\n");
	failure_count = 0;
	solution_count = 0;

	solve_puzzle(arr, size);
	printf("\nCompletions but no array full = %d\n", failure_count);
	printf("\nSolution count = %d\n", solution_count);
	print_cc();
}
