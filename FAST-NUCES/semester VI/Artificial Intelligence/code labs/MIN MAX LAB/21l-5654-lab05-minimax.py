"""
Tic Tac Toe Player
"""

import copy
import math
import random


X = "X"
O = "O"
D="D"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]

def draw_board(board):
    print("-------------")
    for i in range(3):
        print("| ", end="")
        for j in range(3):
            if board[i][j] == EMPTY:
                print(" ", end="")
            else:
                print(board[i][j], end="")
            print(" | ", end="")
        print()
        print("-------------")


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    count = 0
    for i in board:
        for j in i:
            if j:
                count += 1
    if count % 2 != 0:
        return O
    return X


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    res = set()
    board_len = len(board)
    for i in range(board_len):
        for j in range(board_len):
            if board[i][j] == EMPTY:
                res.add((i, j))
    return res


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    curr_player = player(board)
    result_board = copy.deepcopy(board)
    (i, j) = action
    result_board[i][j] = curr_player
    return result_board


def get_horizontal_winner(board):
    # check horizontally
    winner_val = None
    board_len = len(board)
    for i in range(board_len):
        winner_val = board[i][0]
        for j in range(board_len):
            if board[i][j] != winner_val:
                winner_val = None
        if winner_val:
            return winner_val
    return winner_val


def get_vertical_winner(board):
    # check vertically
    winner_val = None
    board_len = len(board)
    for i in range(board_len):
        winner_val = board[0][i]
        for j in range(board_len):
            if board[j][i] != winner_val:
                winner_val = None
        if winner_val:
            return winner_val
    return winner_val


def get_diagonal_winner(board):
    # check diagonally
    winner_val = None
    board_len = len(board)
    winner_val = board[0][0]
    for i in range(board_len):
        if board[i][i] != winner_val:
            winner_val = None
    if winner_val:
        return winner_val

    winner_val = board[0][board_len - 1]
    for i in range(board_len):
        j = board_len - 1 - i
        if board[i][j] != winner_val:
            winner_val = None

    return winner_val

def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    curr_player = player(board)

    if curr_player == X:
        _, action = max_value(board)
    else:
        _, action = min_value(board)

    return action

def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    winner_val = get_horizontal_winner(board) or get_vertical_winner(board) or get_diagonal_winner(board) or None
    return winner_val


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board) != None:
        return True

    for i in board:
        for j in i:
            if j == EMPTY:
                return False
    return True

def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    winner_val = winner(board)
    if winner_val == X:
        return 1
    elif winner_val == O:
        return -1
    return 0

def max_value(board):
    if terminal(board):
        return utility(board), None

    v = float("-inf")
    best_action = None

    for action in actions(board):
        min_val, _ = min_value(result(board, action))
        if min_val > v:
            v = min_val
            best_action = action

    return v, best_action

def min_value(board):
    if terminal(board):
        return utility(board), None

    v = float("inf")
    best_action = None

    for action in actions(board):
        max_val, _ = max_value(result(board, action))
        if max_val < v:
            v = max_val
            best_action = action

    return v, best_action

def play_game():
    board = initial_state()
    draw_board(board)
    while not terminal(board):
        print("Enter the row and column number")
        row, col = map(int, input().split())
        board = result(board, (row, col))
        if not terminal(board):
            action = minimax(board)
            board = result(board, action)
            draw_board(board)
    print("Winner is ", winner(board))
if __name__ == '__main__':
    play_game()