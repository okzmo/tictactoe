#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_grid(char grid[][3]) {
  printf("_____________\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("| %c ", grid[i][j]);
    }
    printf("|\n");
    printf("_____________\n");
  }
}

char check_win(char grid[][3]) {
  char winChar;
  int i;

  // check rows
  for (i = 0; i < 3; i++) {
    winChar = grid[i][0];
    if (winChar == ' ') {
      continue;
    }
    if (winChar == grid[i][1] && winChar == grid[i][2]) {
      return winChar;
    }
  }

  // check columns
  for (i = 0; i < 3; i++) {
    winChar = grid[0][i];
    if (winChar == ' ') {
      continue;
    }
    if (winChar == grid[1][i] && winChar == grid[2][i]) {
      return winChar;
    }
  }

  // check diagonals
  winChar = grid[0][0];
  if (winChar != ' ' && winChar == grid[1][1] && winChar == grid[2][2]) {
    return winChar;
  }
  winChar = grid[0][2];
  if (winChar != ' ' && winChar == grid[1][1] && winChar == grid[2][0]) {
    return winChar;
  }

  return ' ';
}

/* Generate random move and place the sign of the computer on the grid */
void computer_play(char (*grid)[3], char computer) {
  srand(time(0));
  int row = rand() % 3;
  int col = rand() % 3;

  while (grid[row][col] != ' ') {
    row = rand() % 3;
    col = rand() % 3;
  }

  grid[row][col] = computer;
}

/* Ask for the player's move and start a while loop if choose an already used
 * cell */
void player_play(char (*grid)[3], char user) {
  char choice[] = "0,0";
  printf("What's your move ? (R,C)\n");
  scanf("%s", choice);

  while (grid[choice[0] - '0' - 1][choice[2] - '0' - 1] != ' ') {
    printf("You can't play there! Choose another move.\n");
    scanf("%s", choice);
  }

  grid[choice[0] - '0' - 1][choice[2] - '0' - 1] = user;
}

int is_grid_full(char grid[][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (grid[i][j] == ' ') {
        return 0;
      }
    }
  }
  return 1;
}

void start_game() {
  char user = 'N';
  char computer = 'N';
  char winner = ' ';

  char grid[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      grid[i][j] = ' ';
    }
  }

  printf("Welcome to this tic tac toe game, who do you want to play ?\n");
  printf("Write either: O or X\n");
  scanf("%c", &user);
  if (user == 'O') {
    computer = 'X';
  } else {
    computer = 'O';
  }

  while (winner == ' ' && !is_grid_full(grid)) {
    player_play(grid, user);
    print_grid(grid);
    winner = check_win(grid);
    if (winner != ' ' || is_grid_full(grid)) {
      break;
    }

    printf("Let see what the computer will play... \n");
    computer_play(grid, computer);
    print_grid(grid);
    winner = check_win(grid);
  }

  if (winner == ' ') {
    printf("There's no winner...\n");
  } else {
    printf("Player %c is the winner!\n", winner);
  }
}

int main() {
  start_game();

  return 0;
}
