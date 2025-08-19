import os

def info ():
    data_preset_food = list({"spagetti carbonara", "egg fried rice", "mac & cheese"})
    array_size = len(data_preset_food)
    exit = False
    while exit == False:
        input_info = input("Do you want to enter an information? \n(This will delete the prexisting data)\n[Y/N]: ")
        if input_info.lower() == 'y':
            sure_or_not = input("Are you sure?\n(As this will delete the prexisting data)\n[Y/N]: ")
            exit_2 = False
            while exit_2 == False:
                if sure_or_not.lower() == 'y':
                    #function
                    os.system('cls')
                    print("This is an prexisting preset to enter the data.")
                    print("On the range of 0-10 (no decimals),")
                    with open('data/column_1_int.txt', 'w') as file_int:
                        for i in range(array_size):
                            exit_int = False
                            while exit_int == False:
                                temp_int = int(input(f"How much do you like \033[1m{data_preset_food[i]}\033[0m?\n"))
                                if temp_int > 10:
                                    print("Invalid Input, Try again.")
                                elif temp_int < 0:
                                    print("Invalid Input, Try again.")
                                else:
                                    print(temp_int, file=file_int)
                                    exit_int = True
                        print("EOF", file=file_int)
                    os.system('cls')
                    with open('data/column_2_bool.txt', 'w') as file_bool:
                        for i in range(array_size):
                            exit_bool = False
                            while exit_bool == False:
                                temp_bool = input(f"Would you eat \033[1m{data_preset_food[i]}\033[0m on a regular basis?\n[Y/N]: ")
                                if temp_bool.lower() == 'y':
                                    print(1, file=file_bool)
                                    exit_bool = True
                                elif temp_bool.lower() == 'n':
                                    print(0, file=file_bool)
                                    exit_bool = True
                                else:
                                    print("Invalid Input, Try again.")
                        print("EOF", file=file_bool)
                    os.system('cls')
                    with open('data/column_3_str.txt', 'w') as file_str:
                        for i in range(array_size):
                            temp_str = input(f"What do you think of \033[1m{data_preset_food[i]}\033[0m? (Comments/Review): ")
                            print(temp_str, file=file_str)
                        print("EOF", file=file_str)
                    exit = True
                    os.system('cls')
                elif sure_or_not.lower() == 'n':
                    exit = True
                    exit_2 = True
                    return
                else:
                    print("Invalid Input, Try again")
        elif input_info.lower() == 'n':
            exit = True
            return
        else:
            print("Invalid Input, Try again.")