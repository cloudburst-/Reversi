# include "board.h"
using namespace std;

GameEngine::~GameEngine() {
    
}

string GameEngine::displayBoard(){
    //set top row of column
    char boardarray[200] = {';',' ', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' ', '\n'};

    
    
    int n = 19; //there are 20 characters per row (including '\n')
    
    //print tiles row by row
    for (int i = 0; i < board.size(); i++){
        ++n;
        boardarray[n] =';';
        //store number
        ++n;
        switch (i) {
            case 0:
                boardarray[n] = '1';
                break;
            case 1:
                boardarray[n] = '2';
                break;
            case 2:
                boardarray[n] = '3';
                break;
            case 3:
                boardarray[n] = '4';
                break;
            case 4:
                boardarray[n] = '5';
                break;
            case 5:
                boardarray[n] = '6';
                break;
            case 6:
                boardarray[n] = '7';
                break;
            case 7:
                boardarray[n] = '8';
                break;
                
            default:
                break;
        }
        
        //store first '|'
        ++n;
        boardarray[n] = '|';
        
        //store player
        //go through each column in current row
        for (int j = 0; j < board[i].size(); ++j){
            ++n;
            if (board[i][j].getTile() == WHITE) boardarray[n] = 'O';
            else if (board[i][j].getTile() == BLACK) boardarray[n] = '@';
            else boardarray[n] = '_';
            
            ++n;
            boardarray[n] = '|';
        }
        
        //finish row with newline
        ++n;
        boardarray[n] = '\n';
        
    }
    
    
    //last row of chars
    ++n;
    boardarray[n] = ';';

    ++n;
    boardarray[n] = ' ';
    
    ++n;
    boardarray[n] = ' ';
    
    for (int i = 0; i < 8; ++i){
        ++n;
        boardarray[n] = i+65;
        
        ++n;
        boardarray[n] = ' ';
        
    }
    
    ++n;
    boardarray[n] = '\n';
    
    return string(boardarray);
    
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

//flip tiles and update the board
void GameEngine::makeMove(int row, int col, Tile player){
    //check if valid move
    cout << "ROW:" << row << endl;
    cout << "COL:" << col << endl;
    if (!checkIfValid(Space(player,row+1,col+1), player)){
        return; //do nothing.
    }
    
    //make copy of current board in case of undo
    undo = board;

    int x = row;
    int y = col;

    board[x][y].setTile(player);
    directions.clear();
    int xdir =1, ydir = 1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            directions.push_back(4);
        }
    }
    xdir = 1;
    ydir = 0;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            directions.push_back(0);
        }
    }
    xdir = 1;
    ydir = -1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            directions.push_back(6);
        }
    }
    xdir = 0;
    ydir = 1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            directions.push_back(2);
        }
    }
    xdir = 0;
    ydir = -1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            directions.push_back(3);
        }
    }
    xdir = -1;
    ydir = 1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            directions.push_back(5);
        }
    }
    xdir = -1;
    ydir = 0;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            directions.push_back(1);
        }
    }
    xdir = -1;
    ydir = -1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            directions.push_back(7);
        }
    }
    cout << directions.size() << endl;
    for (int i = 0; i < directions.size(); ++i) {
        goThroughSpaces(directions[i], x, y);
        while (isOnBoard(x,y) && board[x][y].getTile() != player && board[x][y].getTile() != EMPTY) {
            board[x][y].setTile(player);
            goThroughSpaces(directions[i],x,y);
        }
        x=row;
        y=col;
    }
    /*
    int xstart = s.getRow();
    int ystart = s.getColumn();
    
    int x = s.getRow();
    int y = s.getColumn();
    
    //traverse each direction  from the desired move
    for (int i = 0; i < directions.size(); i++) {
        //move once in direction
        int currentdirection = directions[i];
        goThroughSpaces(currentdirection, x, y);
        //keep going until you hit the other piece.
        while (isOnBoard(x, y) && board[x][y].getTile() != player){
            //push space onto stack as player tile
            board[x][y].setTile(opposite(player));
            cout << "setting " << x << y << " to " << player;
            //keep going through space in same direction
            goThroughSpaces(currentdirection, x, y);
        }
        //after going through each space in one direction, go back to start
        x = xstart;
        y = ystart;
    }
    
    board[s.getRow()+1][s.getColumn()-1].setTile(player); //place move*/
}

//go through each space in a specified direction
void GameEngine::goThroughSpaces(int i, int &x, int &y){
    switch (i) {
            //check right
        case 0:
            ++x;
            break;
            
            //check left
        case 1:
            --x;
            break;
            
            //check down
        case 2:
            ++y;
            break;
            
            //check up
        case 3:
            --y;
            break;
            
            //check diagonal right down
        case 4:
            ++x;
            ++y;
            break;
            
            //check diagonal left down
        case 5:
            --x;
            ++y;
            break;
            
            //check diagonal right up
        case 6:
            ++x;
            --y;
            break;
            
            //check diagonal left up
        case 7:
            --x;
            --y;
            break;
            
        default:
            break;
    }
}

bool GameEngine::checkIfValid(Space s, Tile player){
    int x = s.getRow();
    int y = s.getColumn();

    int xdir =1, ydir = 1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            return true;
        }
    }
    xdir = 1;
    ydir = 0;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            return true;
        }
    }
    xdir = 1;
    ydir = -1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            return true;
        }
    }
    xdir = 0;
    ydir = 1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            return true;
        }
    }
    xdir = 0;
    ydir = -1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            return true;
        }
    }
    xdir = -1;
    ydir = 1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            return true;
        }
    }
    xdir = -1;
    ydir = 0;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            return true;
        }
    }
    xdir = -1;
    ydir = -1;
    if (isOnBoard(x+xdir,y+ydir) && board[x+xdir][y+ydir].getTile() == opposite(player)) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() != player && board[x+xdir+i][y+ydir+j].getTile() != EMPTY) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == player) {
            return true;
        }
    }
    return false;
}

bool GameEngine::isOnBoard(int row, int column){
    if ( row < 0 || row > 7 || column < 0 || column > 7) return false;
    else return true;
}

void GameEngine::undoMove(){
    
    board = undo;
    
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

void GameEngine::resetGame() {
    board.clear();
    for(int i = 1; i <= 8; ++i){
        vector<Space> columns;
        board.push_back(columns);
        for(int j = 1; j <= 8; ++j){
            if((i == 4 && j == 5) || (i == 5 && j ==4)){
                Space s = Space(WHITE, i, j);
                board[i-1].push_back(s);
            }else if(((i == 4 && j == 4) || (i == 5 && j == 5))){
                Space s = Space(BLACK, i, j);
                board[i-1].push_back(s);
            }else {
                Space s = Space(EMPTY, i, j);
                board[i-1].push_back(s);
            }
        }
    }
}

bool GameEngine::checkDirection(int x, int y, int xdir, int ydir, Tile enemycolor){
    if (board[x+xdir][y+ydir].getTile() == enemycolor) {
        cout << x+xdir << y+ydir << "has the opposite" << endl;
        int i = xdir;
        int j = ydir;
        while (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == enemycolor) {
            i+=xdir;
            j+=ydir;
        }
        if (isOnBoard(x+xdir+i,y+ydir+j) && board[x+xdir+i][y+ydir+j].getTile() == opposite(enemycolor)) {
            return true;
        }
    }
    return false;
}

void GameEngine::setSpace(Tile t, int row, int column){
    board[row][column].setTile(t);
}

bool GameEngine::gameOver() {
    for (int i = 0; i < board.size(); ++i){
        for (int j = 0; i < board[j].size(); ++j){
            if (board[i][j].getTile() == EMPTY) return false;
            else continue;
        }
    }
    return true;
}

//int main(){
   // Tile tile = WHITE;
    //Tile test = opposite(tile);
   // GameEngine g = GameEngine();
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
   // g.showPossibleMoves(WHITE);
   // g.drawBoard(); 
   // return 0;
    
//}