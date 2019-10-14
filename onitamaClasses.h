class PawnPosition {
public:
	int row; //row of pawn
	int col; //column of pawn

	PawnPosition(int r, int c);
	void setPosition(int r, int c);
	PawnPosition operator +(PawnPosition added);
};

class BoardState {
public:
	enum CardOwner { friendly = 1, neutral = 0, enemy = -1 };
	CardOwner cardOwner[5];
	PawnPosition friendlyPawn[5];
	PawnPosition enemyPawn[5];
};