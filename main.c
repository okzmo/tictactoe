#include <math.h>
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

  if (is_grid_full(grid)) {
    return 'T';
  }

  return ' ';
}

float minimax(char grid[][3], int depth, int isMaximizing, char computer,
              char user) {
  char winner = check_win(grid);
  if (winner != ' ') {
    float score = 0;
    if (winner == computer) {
      score = 10 - depth;
    } else if (winner == user) {
      score = depth - 10;
    } else {
      score = 0;
    }
    return score;
  }

  if (isMaximizing) {
    float bestScore = -INFINITY;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (grid[i][j] == ' ') {
          grid[i][j] = computer;
          float score = minimax(grid, depth + 1, 0, computer, user);
          grid[i][j] = ' ';
          if (score > bestScore) {
            bestScore = score;
          }
        }
      }
    }
    return bestScore;
  } else {
    float bestScore = INFINITY;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (grid[i][j] == ' ') {
          grid[i][j] = user;
          float score = minimax(grid, depth + 1, 1, computer, user);
          grid[i][j] = ' ';
          if (score < bestScore) {
            bestScore = score;
          }
        }
      }
    }
    return bestScore;
  }
}

/* Generate random move and place the sign of the computer on the grid */
int computer_play(char (*grid)[3], char computer, char user) {
  float bestScore = -INFINITY;
  int bestMove[2] = {0, 0};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (grid[i][j] == ' ') {
        grid[i][j] = computer;
        float score = minimax(grid, 0, 0, computer, user);
        print_grid(grid);
        printf("%f\n", score);
        grid[i][j] = ' ';
        if (score > bestScore) {
          bestScore = score;
          bestMove[0] = i;
          bestMove[1] = j;
        }
      }
    }
  }

  grid[bestMove[0]][bestMove[1]] = computer;
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
    computer_play(grid, computer, user);
    print_grid(grid);
    winner = check_win(grid);
  }

  if (winner == 'T') {
    printf("It's a tie!\n");
  } else {
    printf("Player %c is the winner!\n", winner);
  }
}

int main() {
  start_game();

  return 0;
}
