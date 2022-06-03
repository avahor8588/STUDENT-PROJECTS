"""
File:    jumps_and_hlts.py
Author:  Aamil Vahora
Date:    October 28/2021
Section: 42
E-mail:  aamilv1@umbc.edu
Description:
the code generates a board game which then the user can play using an input and the game loops until
the game is over and the winner is decided. Almsot like snaked and latters.
	"""

"""
Hills Of Pain
"""

import random

GRID_WIDTH = 8
GRID_HEIGHT = 3
DICE_SIDES = 6


def generate_random_map(length, the_seed=0):
    """
        :param length - the length(size) of the map
        :param the_seed - the seed of the map
        :return: a randomly generated map based on a specific seed, and length.
    """

    if the_seed:
        random.seed(the_seed)
    map_list = []
    for _ in range(length - 2):
        random_points = random.randint(1, 100)
        random_position = random.randint(0, length - 1)
        map_list.append(random.choices(['nop', f'add {random_points}', f'sub {random_points}', f'mul {random_points}', f'jmp {random_position}', 'hlt'], weights=[5, 2, 2, 2, 3, 1], k=1)[0])

    return ['nop'] + map_list + ['hlt']


def make_grid(table_size):
    """
    :param table_size: this needs to be the length of the map
    :return: returns a display grid that you can then modify with fill_grid_square (it's a 2d-grid of characters)
    """

    floating_square_root = table_size ** (1 / 2)

    int_square_root = int(floating_square_root) + (1 if floating_square_root % 1 else 0)
    table_height = int_square_root
    if int_square_root * (int_square_root - 1) >= table_size:
        table_height -= 1

    the_display_grid = [[' ' if j % GRID_WIDTH else '*' for j in range(GRID_WIDTH * int_square_root + 1)]
                        if i % GRID_HEIGHT else ['*' for j in range(GRID_WIDTH * int_square_root + 1)]
                        for i in range(table_height * GRID_HEIGHT + 1)]
    return the_display_grid

# this function prints the grid
def display_grid(my_size,my_seed):
    messages = generate_random_map(my_size,my_seed)# this stuffs the messagas/commands into a variable which later can be put into the grid.
    grid = (make_grid(my_size))
    for i in range(my_size):
        fill_grid_square(grid, my_size, (i), str(i) + "\n" +  messages[i])
    for i in range(len(grid)):
        print(''.join(grid[i]))
    
    

def fill_grid_square(display_grid, size, index, message):
    """
    :param display_grid:  the grid that was made from make_grid
    :param size:  this needs to be the length of the total map, otherwise you may not be able to place things correctly.
    :param index: the index of the position where you want to display the message
    :param message: the message to display in the square at position index, separated by line returns.
    """
    floating_square_root = size ** (1 / 2)
    int_square_root = int(floating_square_root) + (1 if floating_square_root % 1 else 0)
    table_row = index // int_square_root
    table_col = index % int_square_root

    if table_row % 2 == 0:
        column_start = GRID_WIDTH * table_col
    else:
        column_start = GRID_WIDTH * (int_square_root - table_col - 1)

    for r, message_line in enumerate(message.split('\n')):
        for k, c in enumerate(message_line):
            display_grid[GRID_HEIGHT * table_row + 1 + r][column_start + 1 + k] = c


def roll_dice():
    """
        Call this function once per turn.

        :return: returns the dice roll
    """
    return random.randint(1, DICE_SIDES)


def jump_commands(jump,my_pos):# this function moves the position of the player to where the jump position says
    jump = jump.split()
    if jump[0] == "jmp":
        my_pos = int(jump[1])
    return my_pos


def math_commands(my_command, my_score): # this function deals with all the math commands in the game
    message = my_command
    message = message.split()
    if message[0] == "nop":
        my_score += 0
    if message[0] == "mul":
        my_score *= int(message[1])
    if message[0] == "add":
        my_score += int(message[1])
    if message[0] == "sub":
        my_score -= int(message[1])
    return my_score

# the function below has all the game play commadns and code for the game to actually run
def play_game(game_map):
    game_map = game_map.split()
    size =  int(game_map[0])
    seed = int(game_map[1])
    display_grid(size,seed)
    if size < 2:
        size = 2
    commands = generate_random_map(size,seed)
    pos = 0
    score = 0
# the loop below loops until the player reaches hlt(meaning end of game).
    while commands[pos]!= "hlt":
        dice  = roll_dice()
        pos += dice   
        if pos >= size:
            pos =(pos % size) # the line sets the pos back in the range of the board size if it falls out of it
        print(f"pos:{pos} score: {score}, instruction {commands[pos]} Rolled: {dice}" )
        if "jmp" in commands[pos]:
            pos = jump_commands(commands[pos], pos)
            print(f"pos:{pos} score: {score}, instruction {commands[pos]} Rolled: {dice}" )
            score = math_commands(commands[pos],score)
        else:
            score = math_commands(commands[pos],score)

        while "jmp" in commands[pos]:
            pos = jump_commands(commands[pos], pos)
            print(f"pos:{pos} score: {score}, instruction {commands[pos]} Rolled: {dice}" )
            score = math_commands(commands[pos],score)
    print(f"Final Pos: {pos} Final Score: {score}, Instruction {commands[pos]} " )

if __name__ == '__main__':
    keep_playing = ""
    while keep_playing != "no":
        the_board = input("Board Size and Seed: ") # the user input is fed into the play game dunction which has all the play game functonalities.
        play_game(the_board)
        keep_playing = input ("continue? ")
