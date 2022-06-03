"""
File:    lost_and_found_starter.py
Author:  Aamil Vahora
Date:    November 12th 2021
Section: 42
E-mail:  aamilv1@umbc.edu
Description:
  the user can move througha grid an play games with doors and keys.
"""
import json

USE = 'e'
EMPTY = ''
FLOOR = '_'
EXIT = 'x'
DOOR = 'd'
SECRET = 's'
WALL = '*'
ITEMS = 'i'
STARTING_LOCATION = 'start'
SYMBOL = "symbol"

def display_grid(the_grid,pos):
    """
    :param the_grid: the map file that is passed in
    :param pos: the position  for example [0,0]
    return : none
    """
    for i in range(len(the_grid)):
        if len(str(i)) == 1:
            print(str(i)+" ",end= " ")
        else:
            print(str(i),end= " ")
        for j in range(len(the_grid[i])):
            if i == pos[0] and j == pos[1]:
                print( '\u1330', end= " ") 
            elif the_grid[i][j]["items"]:
                print(ITEMS, end = " ")
            elif the_grid[i][j][SYMBOL] == SECRET:
                print(WALL, end = " ")
            else: 
                print(the_grid[i][j][SYMBOL], end= " ")          
        print()

def detect(her_map):
    #this function detects if there is a starting position and if there is one then it starts there
    """
    :param game_map: the map_file that is passed into the function (the file with all the dictionaries)
    return: the starting position or [0,0]
    """
    for x in range(len(her_map)):
        for y in range(len(her_map[x])):
            if STARTING_LOCATION in her_map[x][y]:
                return [x,y]
    return [0,0]

def load_map(map_file_name):
    with open(map_file_name) as map_file:
        the_map = json.loads(map_file.read())
    return the_map
       
def movements(i,start, my_grid):
    """
    :param i: whatever the user input is
    :param start:  this needs to be the length of the total map, otherwise you may not be able to place things correctly.
    :param my_grid: the actual grid that is passed in (the list of dictionaries that was given earlier)
    return : x (the position)
    """
    x = start
    commands_list = [DOOR, SECRET, WALL]
    if i == "d" and x[1] + 1 < len(my_grid): # d is to the right
        if my_grid[x[0]][x[1] + 1][SYMBOL] not in commands_list:
            x[1] += 1
    elif i == "a" and x[1] > 0: # a is to the left
        if my_grid[x[0]][x[1]-1][SYMBOL] not in commands_list:
            x[1] -= 1
    elif i == "s" and x[0] + 1 < len(my_grid): # s is down
        if my_grid[x[0]+1][x[1]][SYMBOL] not in commands_list:
            x[0] += 1
    elif i == "w" and x[0] > 0 < len(my_grid): # w is up
        if my_grid[x[0]-1][x[1]][SYMBOL] not in commands_list:
            x[0] -= 1   
    return x

def open_doors(his_map,his_pos,my_var,inventory_list,converts):
    """
    :param his_map:  the dictionary file that is passed on
    :param his_pos:  the position of the player
    :param my_var:  what you want to convert, for example door to floor, door would be my_var
    :param inventory_list: the list that will store everything that the user pickups
    :param converts: what you want the symbol to convert top, for example door to floor, floor would be converts
    return: None
    """
    requiremnts = False
    #this function checkws everything around the position of the avatar and converts whatever it is to whaterver you want it
    # the function also looks over if there is requiremnt in the door
    location_list = [[0,1], [1,0], [1,1], [-1,0], [0,-1], [-1,-1], [-1,1], [1,-1]]
    for i in location_list:
        if (his_pos[0]+i[0]) <len(his_map) and (his_pos[1]+i[1]) <len(his_map) :
            if "requires" in his_map[his_pos[0]+i[0]][his_pos[1]+i[1]]:
                requires_list = his_map[his_pos[0]+i[0]][his_pos[1]+i[1]]["requires"]
                for j in requires_list:
                    for k in inventory_list:
                        if k == j:
                            requiremnts = True # the boolean flag evaulates to true if the required and items the player has matches
                            if his_map[his_pos[0]+i[0]][his_pos[1]+i[1]][SYMBOL] == my_var:
                                his_map[his_pos[0]+i[0]][his_pos[1]+i[1]][SYMBOL] = converts
                if requiremnts == False and my_var== DOOR:
                    if len(requires_list) <=1:
                        print("you still require:",(" ").join(requires_list))
                    else:
                        print("you still require:",(", ").join(requires_list))
            elif his_map[his_pos[0]+i[0]][his_pos[1]+i[1]][SYMBOL]  == my_var:
                his_map[his_pos[0]+i[0]][his_pos[1]+i[1]][SYMBOL] = converts  
                if my_var == SECRET:
                    print("you found a secret!")

def play_game(game_map):
    # this function has all the play game functionalities
    """
    :param game_map: the file that is passed in
    return: None
    """
    inventory = []
    display_grid(game_map, detect(game_map)) # calling this function displays the grid
    print(f"your inventory is: {(' ').join(inventory)}")
    question = input("Enter Move (wasd) (e to activate doors or secrets), hit q to exit game: ")
    if question == "q":
        print("you died")
        return
    else:
        my_pos = movements(question,detect(game_map), game_map)
        print(f"your inventory is: {(' ').join(inventory)}")
        display_grid(game_map, my_pos)
        while game_map[my_pos[0]][my_pos[1]]["symbol"] != EXIT and question !="q": # the game ends when the player hits the "X" or hits q
            question = input("Enter Move (wasd) (e to activate doors or secrets), hit q to exit game: ")
            my_pos = movements(question,my_pos, game_map)
            if game_map[my_pos[0]][my_pos[1]]["symbol"] == EXIT:
                print("you win! :)")
                return
            elif question == "q":
                print("you die :(")
                return
            for i in game_map[my_pos[0]][my_pos[1]]["items"]: # this loop adds to the inventory and removes the item from the dictionary
                inventory.append(i)
                game_map[my_pos[0]][my_pos[1]]["items"].remove(i)
            if question == USE:
                open_doors(game_map,my_pos,DOOR, inventory, FLOOR)
                open_doors(game_map,my_pos,SECRET,inventory, DOOR)
            display_grid(game_map, my_pos)
            print(f"your inventory is: {(', ').join(inventory)}")

if __name__ == '__main__':
    map_file_name = input('What map do you want to load? ')
    the_game_map = load_map(map_file_name)
    if the_game_map:
        play_game(the_game_map) 