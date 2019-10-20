#include "../../onitamaClasses.h"
#include "../../onitamaCards.h"
#include <fstream>
#include <iostream>

void incrementCardOwner(BoardState::CardOwner card) {
	switch (card) {
	case 0:
		card = BoardState::friendly;
		break;
	case 1:
		card = BoardState::neutral;
		break;
	case 2:
		card = BoardState::neutral;
		break;
	case 3:
		card = BoardState::neutral;
		break;
	}
}

void incrementBoard(BoardState board) {
	PawnPosition end(5, 5);
	do {
		for (int i = 0; i < 5; i++) { //iterate with enemy pawns
			if (board.friendlyPawn[i] != end) {
				++board.friendlyPawn[i]; //iterate this pawn
				break;
			}
			else {
				if (i < 4) {
					//iterate next pawn
					++board.friendlyPawn[i + 1];
				}
				else {
					for (int k = 0; k < 5; k++) { //iterate with enemy pawns
						if (board.enemyPawn[k] != end) {
							++board.enemyPawn[k]; //iterate this pawn
							break;
						}
						else {
							if (k < 4) {
								//iterate next pawn
								++board.enemyPawn[i + 1];
							}
							else {
								for (int m = 0; m < 5; m++) {
									if (board.card[m] != BoardState::enemy) {
										incrementCardOwner(board.card[m]);
										break;
									}
									else {
										if (m < 4) {
											incrementCardOwner(board.card[m + 1]);
										}
										for (int n = m; n >= 0; n--) {
											incrementCardOwner(board.card[n]);
										}
									}
								}
							}
							for (int l = k; l >= 0; l--) {
								++board.enemyPawn[l];
							}
						}
					}
				}
				for (int j = i; j >= 0; j--) {
					++board.friendlyPawn[j];
				}
			}
		}
	} while (!board.checkValid()); // iterate until board config is valid
}

int main() {
	BoardState board(false);
	BoardState initalBoard(false);
	std::ofstream dataFile;
	dataFile.open("trainingData.csv");

	do {
		std::cout << "|";
		incrementBoard(board);

	} while(board != initalBoard);

	dataFile.close();
	return 0;
}