#ifndef board_h
#define board_h

typedef struct {
	char *grid;
	int nrows;
	int ncols;
	int numElements;
} Board;

Board* update_board(Board *);

#endif
