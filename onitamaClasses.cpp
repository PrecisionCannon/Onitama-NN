#include "onitamaClasses.h"

PawnPosition::PawnPosition(int r, int c) {
	setPosition(r, c);
}

void PawnPosition::setPosition(int r, int c) {
	row = r;
	col = c;
	return;
}

PawnPosition PawnPosition::operator +(PawnPosition added) {
	PawnPosition sum(row + added.row, col + added.col);
	return sum;
}