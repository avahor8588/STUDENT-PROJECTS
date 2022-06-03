"""
File:    the_internet.py
Author:  aamil vahora
Date:    December/2/2021
Section: 42
E-mail:  aamilv1@umbc.edu
Description:
  the code creates the internet
"""
# the functions below are the helper functions
def reverse_list(my_list):
    """
    :param my_list: a list that is passed in
    return : the list in reverse order
    """
    # this function is used to reverse the ping list
    if len(my_list)  == 1:
        return(my_list)
    return reverse_list(my_list[1:])  + my_list[:1] 

def ip_verify(the_dict,ip_adress):
    """
    :param the_dict: the dict that is passed in
    :param ip_address: the ip_asdress
    :return : the ip_adress
    """
    for i in the_dict:
        if ip_adress in the_dict[i]["ip_address"]:
            return False
    return True

def ip_to_server(the_dict, start_split):
    """
    :param the_dict: the dict that is passed in
    :param start_split: the input that is put in
    :return : the ip_adress
    :return : the server name
    """
    # this function converts an ip adress
    for k in the_dict:
        if start_split[1] in the_dict[k]["ip_address"]:
            return k
    return start_split[1]


def recursive_ping(a_list):
    """
    :param a_list: a list of numbers
    :return : a number with the number in the list added together
    """
    if len(a_list) == 1:
        return a_list[0]
    return a_list[0] + recursive_ping((a_list[1:]))

###########################################################################


def create_server(my_split, the_dict):
    """
    :param my_split: the user input
    :param the_dict: the dictiionary that is passed in
    return : none
    """
    server_name  = my_split[1]
    ip_address = my_split[2]

    check_split = ip_address.split(".")
    for i in check_split:
        valid_number = False
        if 0 < int(i) < 255:
            valid_number = True
    if server_name not in the_dict and valid_number == True:
        # the dictionary below might be final dictionary depending on how you use it
        the_dict[server_name] = {"ip_address": ip_address}
        the_dict[server_name]["connection"] = {}
        print(f"Sucsess:a server with the name {server_name} was created at ip {ip_address} ")

    else:
        print("one of the server names doesnt exist")


def create_connection(split,her_dict):
    """
    :param split: the user input
    :param her_dict: the dictiionary that is passed in
    return : none
    """
    server_name_one  = split[1]
    server_name_two = split[2]
    ping = int(split[3])
# if server_name_one and server_name_two in her_dict:
    if server_name_one in her_dict and server_name_two in her_dict:
        her_dict[server_name_one]["connection"][server_name_two] = ping
        her_dict[server_name_two]["connection"][server_name_one] = ping
        print(f"Success: A server with name {server_name_one} is now connected to {server_name_two} ")

    else:
        print("one of the server names doesnt exist")


def set_server(thier_split, thier_dict): 
    """
    :param thier_split: the user input
    :param thier_dict: the dictiionary that is passed in
    return starting server
    """
    starting_serever = thier_split[1]
    if starting_serever in thier_dict:
        return starting_serever


def display_server(my_dict):
    """
    :param my_dict: dictionary thats passed in
    return : none
    """
    for i in my_dict:
        if not my_dict[i]["connection"]:
            print(i+"\t"+my_dict[i]["ip_address"])
        else:
            print(i+"\t"+my_dict[i]["ip_address"])
            for j  in my_dict[i]["connection"]:
                j  = str(j)
                # theline under is the two digit ping or whatever
                time  = (my_dict[i]["connection"][j])
                print("\t" + j+"     "+ my_dict[j]["ip_address"] +"     "+ str(time))


def trace_route(trace_dict, starting_place, destination, visited, ping_list):
    """
    :param trace_dict: dictionary thats passed in
    :param starting place: where you start
    :param destination: where you want the path finding to end
    :param visited: an empty list
    :param ping_list: a list that adds the pings to it
    return function (recursive)
    return starting place
    """
    visited.append(starting_place)
    if starting_place == destination:
        return  [starting_place]
        
    else:
        path  = []
        for i in trace_dict[starting_place]["connection"]:
            if i not in visited:
                neighbor = i 
                ping_var = trace_dict[starting_place]["connection"][i]
                var  = trace_route(trace_dict, neighbor,destination, visited, ping_list)
# the cluster of code under here is what returns the path if a path exists

                if var :
                    path = []
                    path.append(starting_place)
                    for i in var:
                        path.append(i)
# the ping_list is where all the pings are taken and then called in main loop
                    ping_list.append(ping_var)
                    return path

        return []


def run_internet():
    start  = " "
    # my_dict will essentialy hold everything in it 
    my_dict = {}
    while start != "quit":
        start  = input(">>> ")
        start_split  = start.split(" ")

        if start_split[0] == "create-server":
            my_answer  = ip_verify(my_dict,start_split[2])
            if my_answer == True:
                create_server(start_split, my_dict)
            else:
                print("one of the server names doesnt exist")

        if start_split[0] == "create-connection":
            create_connection(start_split, my_dict)

        if start_split[0] == "set-server":
            ip_to_server(my_dict, start_split)
            position  = set_server(start_split, my_dict)
            if position:
                print(f"Server {position} selected.")
            else:
                print("one of the server names doesnt exist")

        if start_split[0] == "traceroute" or start_split[0] == "tracert"  :
            ping_list  = []
            # ping_list is the list wehere all the pings are appended to form trace_route function
            destination = ip_to_server(my_dict,start_split)
            trace_list  =  trace_route(my_dict, position, destination, [], ping_list)
            if trace_list  == []:
                print(f"Unable to resolve target system name {start_split[1]}")

            elif trace_list:
                ping_list.append(0)
                ping_list  = reverse_list(ping_list)
                print(f"Tracing route to {destination}  [{start_split[1]}] ")

                for k in range(len(trace_list)):
                    print(str(k)+"\t"+str(ping_list[k]) + 
                    "\t"+my_dict[trace_list[k]]["ip_address"]+"\t"+ trace_list[k])
                print("Trace Complete")

        if start_split[0] == "ping":
            
            end = ip_to_server(my_dict, start_split)
            final_ping = []

            var  = trace_route(my_dict, position, end, [], final_ping)
            if var and start_split[1] != position:

                my_ping = recursive_ping(final_ping)

                ip = my_dict[position]["ip_address"]
                print(f"Reply from {ip} time = {my_ping} ms")
            
            elif start_split[1] == position:
                new_ip = my_dict[position]["ip_address"]
                print(f"Reply from {new_ip} time = 0 ms")

            else:
                print(f"no reply from {start_split[1]}")

        if start  == "display-servers":
            display_server(my_dict)

        if start == "ip-config":
            print(position +"\t"+ my_dict[position]["ip_address"])

if __name__ == '__main__':
    run_internet()