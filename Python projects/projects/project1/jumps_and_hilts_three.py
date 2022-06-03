"""
    snakes and ladders
"""
import random
GRID_WIDTH = 8
GRID_HEIGHT = 3
DICE_SIDES = 6

def generate_random_map(length, the_seed=0):
    if the_seed:
        random.seed(the_seed)
    map_list = []
    for _ in range(length - 2):
        random_points = random.randint(1, 100)
        random_position = random.randint(0, length - 1)
        map_list.append(random.choices(['nop', f'add {random_points}', f'sub {random_points}', f'mul {random_points}', f'jmp {random_position}', 'hlt'], weights=[5, 2, 2, 2, 3, 1], k=1)[0])    
    return ['nop'] + map_list + ['hlt']

def make_grid(table_size):
    floating_square_root = table_size ** (1 / 2)
    int_square_root = int(floating_square_root) + (1 if floating_square_root % 1 else 0)
    table_height = int_square_root
    if int_square_root * (int_square_root - 1) >= table_size:
        table_height -= 1
    the_display_grid = [[' ' if j % GRID_WIDTH else '*' for j in range(GRID_WIDTH * int_square_root + 1)]
                        if i % GRID_HEIGHT else ['*' for j in range(GRID_WIDTH * int_square_root + 1)]
                        for i in range(table_height * GRID_HEIGHT + 1)]
    return the_display_grid

def display_grid(the_grid):
    for i in range(len(the_grid)):
        print(''.join(the_grid[i]))

def fill_grid_square(display_grid, size, index, message):
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
    return random.randint(1, DICE_SIDES)

def jump_commands(jump,my_pos):
    jump = jump.split()
    if jump[0] == "jmp":
        my_pos = int(jump[1])
    return my_pos

def math_commands(my_command, my_score):
    message = my_command
    message = message.split()
    if message[0] == "mul":
        my_score *= int(message[1])
    if message[0] == "add":
        my_score += int(message[1])
    if message[0] == "sub":
        my_score -= int(message[1])
    return my_score

def play_game(game_map):
    the_board = game_map.split()
    size =  int(the_board[0])
    seed = int(the_board[1])
    commands = generate_random_map(size,seed)#prints commands and messages
    grid = (make_grid(size)) # prints the grid
    for i in range(size):
        fill_grid_square(grid, size, (i), str(i) + "\n" +  commands[i])
    display_grid(grid) # displays grid

    pos = 0
    score = 0
    while commands[pos]!= "hlt":
        dice  = roll_dice()
        pos += dice
        if pos >= size:
            pos =(pos % size) # the line sets the pos back to 0 if the pos is out of range
        if "jmp" in commands[pos]:
            print(f"pos:{pos} score: {score}, instruction {commands[pos]} Rolled: {dice}" )
            pos = jump_commands(commands[pos], pos)
            print(f"pos:{pos} score: {score}, instruction {commands[pos]} Rolled: {dice}" )
            score = math_commands(commands[pos],score)
        else:
            score = math_commands(commands[pos],score)
            print(f"pos:{pos} score: {score}, instruction {commands[pos]} Rolled: {dice}" )
    print(f"Final Pos: {pos} Final Score: {score}, Instruction {commands[pos]} " )

if __name__ == '__main__':
    the_board = input("Board Size and Seed:")
    play_game(the_board)