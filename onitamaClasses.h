#include <iostream>

#define onitamaBoardLength 5

class PawnPosition {
public:
	int row; //row of pawn
	int col; //column of pawn

	PawnPosition();
	PawnPosition(int r, int c);
	void setPosition(int r, int c);
	PawnPosition operator +(PawnPosition added);
	bool operator ==(PawnPosition other);
	bool operator !=(PawnPosition other);
	PawnPosition operator ++();
};

std::ostream& operator <<(std::ostream& stream, const PawnPosition& p);

class BoardState {
public:
	enum CardOwner { undefined = 0, friendly = 1, neutral = 2, enemy = 3 };
	CardOwner card[5];
	PawnPosition friendlyPawn[5];
	PawnPosition enemyPawn[5];

	BoardState(bool arrangePieces);
	BoardState(CardOwner* cardOwnerArray);
	bool operator==(BoardState other);
	bool operator!=(BoardState other);
	bool checkValid();
	bool checkPiecesValid();
	bool checkCardsValid();
};