"""
File:    lost_and_found_starter.py
Author:  Aamil Vahora
Date:    November 12th 2021
Section: 42
E-mail:  aamilv1@umbc.edu
Description:
  the user can move througha grid an dplay games with doors and keys.
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
    for i in range(len(the_grid)):
        if len(str(i)) == 1:
            print(str(i)+" ",end= " ")
        else:
            print(str(i),end= " ")
        for j in range(len(the_grid[i])):
            pos = detect(the_grid,i,j)
            if i == pos[0] and j == pos[1]:
                print( '\u1330', end= " ") 
            elif the_grid[i][j]["items"]:
                print(ITEMS, end = " ")
            elif the_grid[i][j][SYMBOL] == SECRET:
                print(WALL, end = " ")
            else: 
                print(the_grid[i][j][SYMBOL], end= " ")          
        print()

def detect(map, i , j):
    detect_start = False
    if STARTING_LOCATION in map[i][j]:
        start = [i,j]
        detect_start = True
    if detect_start == False:
        start =[0,0]
    return start


def load_map(map_file_name):
    with open(map_file_name) as map_file:
        the_map = json.loads(map_file.read())
    return the_map
       
def movements(i,start, my_grid):
    x = start
    commands_list = [DOOR, SECRET, WALL]
    if i == "d" and x[1] + 1 < len(my_grid):
        if my_grid[x[0]][x[1] + 1][SYMBOL] not in commands_list:
            x[1] += 1
    elif i == "a" and x[1] > 0:
        if my_grid[x[0]][x[1]-1][SYMBOL] not in commands_list:
            x[1] -= 1
    elif i == "s" and x[0] + 1 < len(my_grid):
        if my_grid[x[0]+1][x[1]][SYMBOL] not in commands_list:
            x[0] += 1
    elif i == "w" and x[0] > 0 < len(my_grid):
        if my_grid[x[0]-1][x[1]][SYMBOL] not in commands_list:
            x[0] -= 1   
    return x

def open_doors(his_map,his_pos,my_var,inventory_list,converts):
    flag = False
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
                            flag = True
                            if his_map[his_pos[0]+i[0]][his_pos[1]+i[1]][SYMBOL] == my_var:
                                his_map[his_pos[0]+i[0]][his_pos[1]+i[1]][SYMBOL] = converts
                if flag == False and my_var== DOOR:
                    if len(requires_list) <=1:
                        print("you still require",(" ").join(requires_list))
                    else:
                        print("you still require",(" ").join(requires_list))
            elif his_map[his_pos[0]+i[0]][his_pos[1]+i[1]][SYMBOL]  == my_var:
                his_map[his_pos[0]+i[0]][his_pos[1]+i[1]][SYMBOL] = converts  


def play_game(game_map):
    inventory = []
    display_grid(game_map,detect(game_map))
    print(f"your inventory is: {(' ').join(inventory)}")
    question = input("Enter Move (wasd) (e to activate doors or secrets):")
    if question == "q":
        print("you died")
        return
    else:
        my_pos = movements(question,detect(game_map), game_map)
        print(f"your inventory is: {(' ').join(inventory)}")
        display_grid(game_map, my_pos)
        if len(inventory) <= 1:
                print(f"your inventory is: {(' ').join(inventory)}")
        else:
            print(f"your inventory is: {(', ').join(inventory)}")

        while game_map[my_pos[0]][my_pos[1]]["symbol"] != EXIT and question !="q":
            question = input("Enter Move (wasd) (e to activate doors or secrets):")
            my_pos = movements(question,my_pos, game_map)
            if game_map[my_pos[0]][my_pos[1]]["symbol"] == EXIT:
                print("you win! :)")
                return
            elif question == "q":
                print("you die :(")
                return
            for i in game_map[my_pos[0]][my_pos[1]]["items"]: # this loop adds to the inventory 
                inventory.append(i)
                game_map[my_pos[0]][my_pos[1]]["items"].remove(i)
            if question == USE:
                open_doors(game_map,my_pos,DOOR, inventory, FLOOR)
                open_doors(game_map,my_pos,SECRET,inventory, DOOR)
            display_grid(game_map, my_pos)
            if len(inventory) <= 1:
                print(f"your inventory is: {(' ').join(inventory)}")
            else:
                print(f"your inventory is: {(', ').join(inventory)}")

if __name__ == '__main__':
    map_file_name = input('What map do you want to load? ')
    the_game_map = load_map(map_file_name)
    if the_game_map:
        play_game(the_game_map) 


