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

class BoardState {
public:
	enum CardOwner { friendly = 1, neutral = 2, enemy = 3 };
	CardOwner card[5];
	PawnPosition friendlyPawn[5];
	PawnPosition enemyPawn[5];

	BoardState(int arrangePieces);
	BoardState(CardOwner* cardOwnerArray);
	bool operator==(BoardState other);
	bool operator!=(BoardState other);
	bool checkValid();
	bool checkPiecesValid();
	bool checkCardsValid();
};