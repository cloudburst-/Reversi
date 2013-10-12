# include "board.h"
using namespace std;


void GameEngine::setSpace(Tile t, int row, int column){
	board[row][column].setTile(t);
}

Tile opposite(Tile color){
	Tile tile;
	if (color == WHITE){
		tile = BLACK;		
	}
	else if (color == BLACK){
		tile = WHITE;
	}
	else{
		tile = EMPTY;
	}
	return tile;
}
void GameEngine::drawBoard(){
	for(int i = 0; i<8; ++i){
		for(int j = 0; j < 8; ++j){
			cout << board[i][j].getTile() << " ";
		}
		cout << endl;
	}
}

bool GameEngine::checkDirection(int row, int column, int xdirec, int ydirec, Tile enemycolor){
	Space z = Space(enemycolor, 0, 0);
	z = board[row][column];
	if(z.getTile()!=EMPTY){
		//cout << "Invalid Move, spot not empty" << endl;
		return false;
	}
	int x = column + xdirec;
	int y = row + ydirec; 
	if(x > 1 && x <=8 && y > 1 && y <=8){
	z = board[y-2][x-2];
	}
	else{ 
		//cout << row << " row does not exist and/or " << column << " column does not exist" << endl;
		return false;
	}
	if(z.getTile() != enemycolor){
		return false;
	}
	while(z.getTile() == enemycolor && x > 1 && x <=8 && y > 1 && y <=8){
		x += xdirec;
		y += ydirec;
		z = board[y-2][x-2];
		//cout << "x is " << x << " and y is " << y << endl;
	}
	if(z.getTile() == EMPTY || x <0 || x > 8 || y < 0 || y > 8){
		return false;
	}
	return true;
}

bool GameEngine::checkIfValid(Space s, Tile player){
	Tile enemy = opposite(player);
	if(enemy == EMPTY){
		cout << "Entered nonexisting player type, Bad entry" << endl;
		return false;
	}
	
	int r = s.getRow()+1;
	int c = s.getColumn()+1;
	bool test;
	if(checkDirection(r, c, 0, -1, enemy)){
	//	cout << "Good Move Up" << endl;
		return true;
	}
	else if(checkDirection(r, c, 0, 1, enemy)){
	//	cout << "Good Move Down" << endl;
		return true;
	}
	else if(checkDirection(r, c, -1, 0, enemy)){
	//	cout << "Good Move Left" << endl;
		return true;
	}	
	else if(checkDirection(r, c, 1, 0, enemy)){
		//cout << "Good Move Right" << endl;
		return true;
	}
	else if(checkDirection(r, c, 1, 1, enemy)){
		//cout << "Good Move Down Right" << endl;
		return true;
	}
	else if(checkDirection(r, c, 1, -1, enemy)){
	//	cout << "Good Move Up Right" << endl;
		return true;
	}
	else if(checkDirection(r, c, -1, 1, enemy)){
	//	cout << "Good Move Down Left" << endl;
		return true;
	}
	else if(checkDirection(r, c, -1, -1, enemy)){
	//	cout << "Good Move Down Right" << endl;
		return true;
	}
	else{
		//cout << "Bad Move" << endl;
		return false;
	}
	//cout << "Row is " << r << endl;
	//cout << "Column is " << c << endl;
	
	
}

vector <Space> GameEngine::showPossibleMoves(Tile player){
	vector <Space> result;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j].getTile() == EMPTY){
				Space s = Space(player, i+1, j+1);
				cout << s.getRow() << s.getColumn() << endl;
				if(checkIfValid(s, player)){
					result.push_back(s);
				}
			}
		}
	}
	for(int k = 0; k < result.size(); k++){
		cout << result[k].getRow() << result[k].getColumn() << endl;
	}
	return result;
}

int main(){
	Tile tile = WHITE;
	//Tile test = opposite(tile);
	GameEngine g = GameEngine();
	//cout << "Test is " << test << endl;
	/*Space s = Space(tile, 3, 5);
	Space s2 = Space(tile, 4, 5);
	Space s3 = Space(tile, 5, 5);
	Space s4 = Space(tile, 2, 5);
	Space s5 = Space(tile, 5, 4);
	Space s6 = Space(tile, 5, 3);
	Space s7 = Space(tile, 5, 2);
	Space s8 = Space(tile, 4, 2);
	Space s9 = Space(tile, 3, 2);
	Space s10 = Space(tile, 2, 2);
	Space s11 = Space(tile, 2, 3);
	Space s12 = Space(tile, 2, 4);*/
	//Space shouldFail = Space(tile, 8, 8);
	//g.setSpace(WHITE, 3,5);
	/*g.setSpace(WHITE, 3, 2);
	g.setSpace(BLACK, 3, 1);*/
	/*
	cout << "Results of s = " << s.getTile() << ", row " << s.getRow() << ", column "<< s.getColumn() << ": ";
	bool x = g.checkIfValid(s, tile);
	cout << "Results of s2 = "<< s2.getTile() << ", row " << s2.getRow() << ", column "<< s2.getColumn() << ": ";
	bool y = g.checkIfValid(s2, tile);
	cout << "Results of s3 = "<< s3.getTile() << ", row " << s3.getRow() << ", column "<< s3.getColumn() << ": ";
	bool z = g.checkIfValid(s3, tile);
	cout << "Results of s4 = "<< s4.getTile() << ", row " << s4.getRow() << ", column "<< s4.getColumn() << ": ";
	bool w = g.checkIfValid(s4, tile);
	cout << "Results of s5 = "<< s5.getTile() << ", row " << s5.getRow() << ", column "<< s5.getColumn() << ": ";
	bool v = g.checkIfValid(s5, tile);
	cout << "Results of s6 = "<< s6.getTile() << ", row " << s6.getRow() << ", column "<< s6.getColumn() << ": ";
	bool u = g.checkIfValid(s6, tile);
	cout << "Results of s7 = "<< s7.getTile() << ", row " << s7.getRow() << ", column "<< s7.getColumn() << ": ";
	bool t = g.checkIfValid(s7, tile);
	cout << "Results of s8 = "<< s8.getTile() << ", row " << s8.getRow() << ", column "<< s8.getColumn() << ": ";
	bool k = g.checkIfValid(s8, tile);
	cout << "Results of s9 = "<< s9.getTile() << ", row " << s9.getRow() << ", column "<< s9.getColumn() << ": ";
	bool r = g.checkIfValid(s9, tile);
	cout << "Results of s10 = "<< s10.getTile() << ", row " << s10.getRow() << ", column "<< s10.getColumn() << ": ";
	bool q = g.checkIfValid(s10, tile);
	cout << "Results of s11 = "<< s11.getTile() << ", row " << s11.getRow() << ", column "<< s11.getColumn() << ": ";
	bool p = g.checkIfValid(s11, tile);
	cout << "Results of s12 = "<< s12.getTile() << ", row " << s12.getRow() << ", column "<< s12.getColumn() << ": ";
	bool m = g.checkIfValid(s12, tile);
	*/
	//cout << "Results of shouldfail = ";	
	//bool n = g.checkIfValid(shouldFail, tile);
	/*if(x){
		cout << "Good Move" << endl;
	}
	else{
		cout << "Bad Move" << endl;
	}*/
	g.showPossibleMoves(WHITE);
	g.drawBoard(); 
	return 0;
	
}