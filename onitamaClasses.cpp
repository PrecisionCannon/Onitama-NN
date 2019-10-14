#include "onitamaClasses.h"
#include <stdlib.h>
#include <time.h>

PawnPosition::PawnPosition() {
	setPosition(1, 0); //represents a pawn removed from the game
}

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

bool PawnPosition::operator ==(PawnPosition other) {
	return (row == other.row && col == other.col);
}

bool PawnPosition::operator !=(PawnPosition other) {
	return (row != other.row || col != other.col);
}

PawnPosition PawnPosition::operator ++() {
	if (row >= onitamaBoardLength) {
		if (col >= onitamaBoardLength) {
			setPosition(1, 0); //(1, 0) is the "dead" position, and will iterate to the first valid position
		}
		row = 1;
		col++;
	}
	else {
		row++;
	}

	return PawnPosition(row, col);
}

BoardState::BoardState(int arrangePieces) {
	if (arrangePieces) {
		srand(time(0));

		for (int i = 0; i < 5; i++) {
			friendlyPawn[i].setPosition(1, i + 1);
			enemyPawn[i].setPosition(5, i + 1);

			do {
				card[i] = static_cast<CardOwner> ((rand() % enemy) + 1);
			} while (checkCardsValid());
		}
	}
}

BoardState::BoardState(CardOwner* newCards) {
	for (int i = 0; i < 5; i++) {
		friendlyPawn[i].setPosition(1, i + 1);
		enemyPawn[i].setPosition(5, i + 1);
		card[i] = newCards[i];
	}
}

bool BoardState::operator ==(BoardState other) {
	for (int i = 0; i < 5; i++) {
		if (friendlyPawn[i] != other.friendlyPawn[i] || enemyPawn[i] != other.enemyPawn[i] || card[i] != other.card[i]) {
			return false;
		}
	}

	return true;
}

bool BoardState::operator !=(BoardState other) {
	return !(*this == other);
}

bool BoardState::checkValid() {
	return (checkPiecesValid() && checkCardsValid());
}

bool BoardState::checkPiecesValid() {
	PawnPosition dead(1, 0);
	PawnPosition friendlyGate(1, 3);
	PawnPosition enemyGate(5, 3);
	int master = 2;

	if (friendlyPawn[master] == dead || enemyPawn[master] == dead) {
		return false;
	}
	if (friendlyPawn[master] == enemyGate || enemyPawn[master] == friendlyGate) {
		return false;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			if (friendlyPawn[i] == friendlyPawn[j] || friendlyPawn[i] == enemyPawn[j]) {
				if (!(friendlyPawn[i] == dead)) {
					return false;
				}
			}
			if (enemyPawn[i] == enemyPawn[j] && !(enemyPawn[i] == dead)) {
				return false;
			}
		}
	}
}

bool BoardState::checkCardsValid() {
	int numOfType[3] = { 0, 0, 0 }; //first is number of friendly cards, second is number of neutral, third is number of enemy
	for (int i = 0; i < 5; i++) {
		numOfType[card[i] - 1]++;
	}

	if (numOfType[0] > 2 || numOfType[1] > 1 || numOfType[2] > 2) {
		return false;
	}
	return true;
}