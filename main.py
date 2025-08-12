import ctypes
import os
import math
import time
#you can store data better by using a csv file instead of multiple txt file

lib = ctypes.CDLL("./c.dll")

lib.INT.argtypes = [ctypes.c_char_p]
lib.INT.restype = ctypes.POINTER(ctypes.c_int)

lib.INT_arr_size.restype = ctypes.c_int

lib.STR.argtypes = [ctypes.c_char_p]
lib.STR.restype = ctypes.POINTER(ctypes.c_char_p)

lib.STR_arr_size.restype = ctypes.c_int
#msg.decode('utf-8')

lib.BOOL.argtypes = [ctypes.c_char_p]
lib.BOOL.restype = ctypes.POINTER(ctypes.c_int)

char_arr_ptr = lib.STR(b"data/column_3_str.txt")

arr_size = lib.STR_arr_size()
arr = [char_arr_ptr[i].decode('utf-8') for i in range(arr_size)]

int_result_ptr = lib.INT(b"data/column_1_int.txt")
int_results = [int_result_ptr[i] for i in range(8)]

bool_result_ptr = lib.BOOL(b"data/column_2_bool.txt")
bool_results = [bool_result_ptr[i] for i in range(7)]

mean = int_results[0] / pow(10 ,int_results[1])
median = int_results[2] / pow(10, int_results[3])

mode = int_results[4]
if mode == -1:
    mode = str(mode)
    mode = "None"

count = lib.INT_arr_size()

equal = False
true_more = False
if bool_results[0] == 0:
    true_more = False
elif bool_results[0] == 1:
    true_more = True
elif bool_results[0] == -1:
    equal = True
else:
    print("Error.")
    exit(1)

percentage_true = bool_results[1] / pow(10, bool_results[2])
true_count = bool_results[3]
percentage_false = bool_results[4] / pow(10, bool_results[5])
false_count = bool_results[6]

print(f"Mean: {mean} ", end='')
print(type(mean))
print(f"Median: {median} ", end='')
print(type(median))
print(f"Mode: {mode} ", end='')
print(type(mode))
print(f"Range: {int_results[5]} ", end='')
print(type(int_results[5]))
print(f"Highest Number: {int_results[6]} ", end='')
print(type(int_results[7]))
print(f"Lowest Number: {int_results[7]} ", end='')
print(type(int_results[7]))
print(f"Count: {count} ", end='')
print(type(count))

print("")

print(f"True or False is more: {true_more} ", end='')
print(type(true_more))
print(f"Equal?: {equal} ", end='')
print(type(equal))
print(f"Percentage of true: {percentage_true} ", end='')
print(type(percentage_true))
print(f"True Count: {true_count} ", end='')
print(type(true_count))
print(f"Percentage of false: {percentage_false} ", end='')
print(type(percentage_false))
print(f"False Count: {false_count} ", end='')
print(type(false_count))

view_comments = input("Do you want to view the comments? [Y/N] : ")
view_comments = view_comments.lower()

while view_comments != 'y':
    if view_comments == 'n':
        break
    else:
        print("Invalid input")    
        view_comments = input("Do you want to view the comments? [Y/N] : ")
        view_comments = view_comments.lower

if view_comments == 'y':
    print(arr)
    with open("saved_comments.txt", "w") as fsaved_comments:
        for i in range(arr_size):
            os.system('cls')            
            print("Press enter to continue")
            print("Enter S to save")
            print("Enter M to view statistic")
            print(f"\033[1m{arr[i]}\033[0m")
            print(type(arr[i]))
            saved = input("")
            while saved != '':
                if saved == 'S' or saved == 's':
                    print(f"{i}: ", file=fsaved_comments, end='')
                    print(arr[i], file=fsaved_comments)
                    break
                elif saved == 'M' or saved == 'm':
                    os.system('cls')  
                    print(f"Mean: {mean} ", end='')
                    print(type(mean))
                    print(f"Median: {median} ", end='')
                    print(type(median))
                    print(f"Mode: {mode} ", end='')
                    print(type(mode))
                    print(f"Range: {int_results[5]} ", end='')
                    print(type(int_results[5]))
                    print(f"Highest Number: {int_results[6]} ", end='')
                    print(type(int_results[7]))
                    print(f"Lowest Number: {int_results[7]} ", end='')
                    print(type(int_results[7]))
                    print(f"Count: {count} ", end='')
                    print(type(count))

                    print("")

                    print(f"True or False is more: {true_more} ", end='')
                    print(type(true_more))
                    print(f"Equal?: {equal} ", end='')
                    print(type(equal))
                    print(f"Percentage of true: {percentage_true} ", end='')
                    print(type(percentage_true))
                    print(f"True Count: {true_count} ", end='')
                    print(type(true_count))
                    print(f"Percentage of false: {percentage_false} ", end='')
                    print(type(percentage_false))
                    print(f"False Count: {false_count} ", end='')
                    print(type(false_count))
                    input("Enter to continue\n")
                    
                    os.system('cls')            
                    print("Press enter to continue")
                    print("Enter S to save")
                    print("Enter M to view statistic")
                    print(f"\033[1m{arr[i]}\033[0m")
                    print(type(arr[i]))
                    saved = input("")
                else:
                    print("Invalid Input")
                    saved = input("")