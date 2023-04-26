#include <iostream>
#include <array>
#include <limits>
#include <cstdlib>

class Sudoku{
public:
  Sudoku(){
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        board[i][j] = -1;
      }
    }
    createBoard();
    win_state = ongoing;
  }
  void createBoard() {
  
    std::array<int, 10> row_check;
    std::array<int, 10> column_check;
    std::array<int, 10> box_check;
    int a = 0;
    int b = 0;
    int temp = -1;
    srand((unsigned) time(NULL));

    for(int i = 0; i < 9; i++){
      row_check.fill(0);
      for(int j = 0; j < 9; j++){
        temp = 1 + rand() % 9;
        board[i][j] = temp;
        if(board[i][j] != -1) row_check[board[i][j]]++;
        if(row_check[board[i][j]] > 1) board[i][j] = -1;
      }
    }
    for(int i = 0; i < 9; i++){
      column_check.fill(0);
      for(int j = 0; j < 9; j++){
        if(board[j][i] != -1) column_check[board[j][i]]++;
        if(column_check[board[j][i]] > 1) board[i][j] = -1;
      }
    }
    for(int bruh = 0; bruh < 9; bruh++){
      box_check.fill(0);
      for(int i = b; i < b+3 && b <= 6; i++){
        for(int j = a; j < a+3 && a <= 6; j++){
          box_check[board[i][j]]++;
          if(box_check[board[i][j]] > 1) board[i][j] = -1;
        }
      }
      b += 3;
      if(b > 6){
        b = 0;
        a += 3;
      }
    }
    return;
  }

  void printBoard(){
    std::cout << "+---+---+---+---+---+---+---+---+---+" << std::endl;
    for(int i = 0; i < 9; i++){
      std::cout << "|";
      for(int j = 0; j < 9; j++){
        std::cout << " "; 
        if(board[i][j] >= 0 && board[i][j] <= 9) std::cout << board[i][j]; 
        else if (board[i][j] == -1) std::cout << " ";
        std::cout << " ";
        std::cout << "|";
      }
      std::cout << std::endl;
      std::cout << "+---+---+---+---+---+---+---+---+---+" << std::endl;
    }
  }

  void getInput(int input, int row, int column){

    board[row-1][column-1] = input;
    turn_count++;
    if(turn_count == 81) {
      if(validate()) win_state = won;
      else           win_state = lost;
    }
  }

  bool validate() {
  
    std::array<int, 10> row_check;
    std::array<int, 10> column_check;
    std::array<int, 10> box_check;
    int a = 0;
    int b = 0;

    for(int i = 0; i < 9; i++){
      row_check.fill(0);
      column_check.fill(0);
      for(int j = 0; j < 9; j++){
        if(board[i][j] == 0) return false;
        row_check[board[i][j]]++;
        column_check[board[j][i]]++;
        if(row_check[board[i][j]] > 1 || column_check[board[j][i]] > 1) return false;
      }
    }
    for(int bruh = 0; bruh < 9; bruh++){
      box_check.fill(0);
      for(int i = b; i < b+3 && b <= 6; i++){
        for(int j = a; j < a+3 && a <= 6; j++){
          box_check[board[i][j]]++;
          if(box_check[board[i][j]] > 1) return false;
        }
      }
      b += 3;
      if(b > 6){
        b = 0;
        a += 3;
      }
    }
    return true;
  }
  enum state{
    ongoing,
    won,
    lost
  };
  state win_state;
  ~Sudoku(){
    std::cout << "Class Destroyed." << std::endl;
  }

private:
  std::array<std::array<int, 9>, 9> board;
  unsigned turn_count;
};

int main(){

  Sudoku sudoku;
  srand((unsigned) time(NULL));

  while(sudoku.win_state == sudoku.ongoing){
    sudoku.printBoard();
    int num_input;
    int row_input;
    int column_input;
    std::cout << "Enter number: ";
    std::cin >> num_input;
    if(num_input >= 0 && num_input <= 9 && std::cin.good()){
      std::cout << "Enter row: ";
      std::cin >> row_input;
      if(row_input >= 0 && row_input <= 9 && std::cin.good()){
        std::cout << "Enter column: ";
        std::cin >> column_input;
        if(column_input >= 0 && column_input <= 9 && std::cin.good()){
          sudoku.getInput(num_input, row_input, column_input);      
          continue;
        }
      }
    }
    std::cout << "Invalid Input. " << std::endl;
    std::cin.clear();
    std::cin.ignore(1000,'\n');
  }

  switch (sudoku.win_state){
    case sudoku.won:
      std::cout << "You Won" << std::endl;
      break;
  
    case sudoku.lost:
      std::cout << "You Lost" << std::endl;
    default:
      break;
  }
}