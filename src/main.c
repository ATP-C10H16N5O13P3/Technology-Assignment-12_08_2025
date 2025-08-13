#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//create array size for the 3 main functions
int char_arr_size;
int int_arr_size;
int bool_arr_size;

//define function
__declspec(dllexport)int* INT(char* filename){
    //open file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }
    
    static char line_char[100][1024]; //create read buffer
    static int line[100]; //create int to change to from read buffer
    static int mid[8]; //return array
    /*
    mid[0] = average (avg) / mean
    mid[1] = decimal place of avg
    e.g. the number is 10.5
    mid[0] would be 105
    mid[1] would be 1
    ---------------------------------------------
    mid[2] = median
    mid[3] = median deciamal place
    mid[4] = mode
    mid[5] = range
    mid[6] = highest number
    mid[7] = lowest number
    */

    //start loop for reading into buffer
    for (size_t i = 0; i < 100; i++)
    {
        fgets(line_char[i], sizeof(line_char[i]), file); //read to buffer
        line_char[i][strcspn(line_char[i], "\n")] = '\0'; //remove newline from the read
        //printf("Read line: %s\n", line_char[i]);

        //stop readinf of found EOF
        if (strcmp(line_char[i], "EOF") == 0) {
            int_arr_size = i;
            break;
        }

        //change string from buffer to int
        line[i] = atoi(line_char[i]);
    }

    //check if the file is too long or empty
    if (int_arr_size == 0) {
        printf("Error: No EOF found or empty file.\n");
        fclose(file);
        return NULL;
    }
    
    //add up the integer
    int sum = 0;
    for (size_t i = 0; i < int_arr_size; i++){ sum += line[i]; }

    //find the average of the int
    //change from float to integer and decimal place
    float temp_avg = (float)sum / (float)int_arr_size;
    int avg = floor(temp_avg);
    for (mid[1] = 0; temp_avg != avg && mid[1] != 6; mid[1]++)
    {
        temp_avg *= 10;
        avg = floor(temp_avg);
    }
    mid[0] = avg; //assign the average value to mid[0] the variable that we will return

    //basic bubble sort
    //sufficient for small use
    //not optimized sorting method
    int sorting_num[100]; //create array for sorting
    memcpy(sorting_num, line, sizeof(int) * int_arr_size); //copy array to sorting array
    while (check_sort(sorting_num, int_arr_size) == 1) //check if the array is sorted
    {
        //parse over the array
        for (size_t i = 0; i < int_arr_size - 1; i++)
        {
            //check if the number before is more
            //if so then swap the number
            if (sorting_num[i] > sorting_num[i+1])
            {
                int buffer = sorting_num[i];
                sorting_num[i] = sorting_num[i+1];
                sorting_num[i+1] = buffer;
            }
        }
    }

    //finding the median
    int median;
    if (int_arr_size % 2 == 1) //if there's one middle number
    {
        median = sorting_num[int_arr_size / 2];
        mid[3] = 0;
    } else { //if there's two middle number
        float median_f = (sorting_num[int_arr_size / 2 - 1] + sorting_num[int_arr_size / 2]) / 2.0;
        int temp_median = floor(median_f);
        for (mid[3] = 0; median_f != temp_median && mid[3] != 6; mid[3]++) {
            median_f *= 10;
            temp_median = floor(median_f);
        }
        median = temp_median;
    }
    mid[2] = median;

    //finding the mode
    int mode;
    int count_of_num[100][2];

    for (size_t i = 0; i < int_arr_size; i++)
    {
        count_of_num[i][1] = 0; //fill array
    }
    
    //very inefficient way to find the mode
    //check if the number already exist in the array
    for (size_t i = 0; i < int_arr_size; i++)
    {
        bool num_exist_already = false;
        for (size_t j = 0; j < int_arr_size; j++)
        {
            if (sorting_num[i] == count_of_num[j][0])
            {
                count_of_num[j][1]++;
                num_exist_already = true;
                break;
            }
        }
        //if num doesn't exist already then create the num in the array
        if (num_exist_already == false)
        {
            for (size_t j = 0; j < int_arr_size; j++)
            {
                if (count_of_num[j][1] == 0)
                {
                    count_of_num[j][0] = sorting_num[i];
                    count_of_num[j][1] = 1;
                    break;
                }
            }  
        }
    }

    //find the number with the highest count
    int mode_count = 0;
    for (size_t i = 0; i < int_arr_size; i++)
    {
        if (count_of_num[i][1] > mode_count)
        {
            mode_count = count_of_num[i][1];
            mode = count_of_num[i][0];
        }
    }

    //check if there is multiple mode
    int num_with_mode_count = 0;
    for (size_t i = 0; i < int_arr_size; i++) {
        if (count_of_num[i][1] == mode_count) {
            num_with_mode_count++;
        }
    }

    if (num_with_mode_count > 1) {
        mode = -1; // no unique mode
    }
    mid[4] = mode; //we want to find a unique mode

    mid[6] = sorting_num[int_arr_size - 1]; //find the highest number
    mid[7] = sorting_num[0]; //find the lowest mumber
    int range = sorting_num[int_arr_size - 1] - sorting_num[0]; //find the range
    mid[5] = range;

    fclose(file); //close file
    return mid; //return the all the value we found
}

__declspec(dllexport)int check_sort(int arr[], int size){
    for (size_t i = 0; i < size-1; i++)
    {
        if (arr[i] > arr[i+1])
        {
            return 1;
        }
    }
    return 0;
}

//define function to return int array size
__declspec(dllexport)int INT_arr_size(){
    return int_arr_size;
}

//define function of str
__declspec(dllexport)char** STR(char* filename){
    //open file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    //create read buffer
    static char line[100][1024];

    for (size_t i = 0; i < 100; i++)
    {
        fgets(line[i], sizeof(line), file); //read
        line[i][strcspn(line[i], "\n")] = '\0'; //remove newline
        //printf("Read line: %s\n", line[i]);

        //if EOF then exit the loop
        if (strcmp(line[i], "EOF") == 0) {
            char_arr_size = i;
            break;
        }
    }

    //change from 2D array to pointer array
    static char* ptrs[100];
    for (int i = 0; i < 100; i++) {
        ptrs[i] = line[i];
    }

    fclose(file); //close file
    return ptrs; //return pointer array
}

//define function to return str array size
__declspec(dllexport)int STR_arr_size(){
    return char_arr_size;
}

//define function of bool
__declspec(dllexport)int* BOOL(char* filename){
    //open file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }
    
    static char line_char[100][1024]; //read buffer
    static int line[100]; //int buffer
    static bool line_bool[100]; //bool (the thing we will use
    static int midBool[7]; //return values
    /*
    midBool[0] = which has more true or false
    - 0 = false more, 1 = true more
    midBool[1] = percentage of true
    midBool[2] = decimal place of the percentage of true
    midBool[3] = count of true
    midBool[4] = percentage of false
    midBool[5] = decimal place of the percentage of false
    midBool[6] = count of false
    */

    for (size_t i = 0; i < 100; i++)
    {
        fgets(line_char[i], sizeof(line_char[i]), file); //read
        line_char[i][strcspn(line_char[i], "\n")] = '\0'; //remove newline
        //printf("Read line: %s\n", line_char[i]);

        //if EOF stop reading
        if (strcmp(line_char[i], "EOF") == 0) {
            bool_arr_size = i;
            break;
        }

        //change str to int
        line[i] = atoi(line_char[i]);
    }

    //check for empty file or too big of file
    if (bool_arr_size == 0) {
        printf("Error: No EOF found or empty file.\n");
        fclose(file);
        return NULL;
    }

    //change int to bool
    for (size_t i = 0; i < bool_arr_size; i++)
    {
        if (line[i] == 0) {
            line_bool[i] = false;
        } else if (line[i] == 1) {
            line_bool[i] = true;
        } else {
            printf("Not valid input. Need to be only 0 or 1.\n");
            exit(1);
        }
    }
    
    //count the amount of true and false
    size_t true_count = 0;
    size_t false_count = 0;
    for (size_t i = 0; i < bool_arr_size; i++)
    {
        if (line_bool[i] == true) {
            true_count++;
        } else if (line_bool[i] == false) {
            false_count++;
        } else {
            printf("Error.\n");
            exit(1);
        }
    }
    
    //compare if true or false is more
    if (true_count > false_count)
    {
        midBool[0] = 1;
    }
    else if (true_count == false_count)
    {
        midBool[0] = -1;
    }

    //calculate percentage of true and change from float to integer and decimal place
    float percentage_true = (float)true_count / (float)bool_arr_size * 100;
    int temp_true = floor(percentage_true);
    for (midBool[2] = 0; percentage_true != temp_true && midBool[2] != 6; midBool[2]++) {
        percentage_true *= 10;
        temp_true = floor(percentage_true);
    }
    midBool[1] = temp_true;
    midBool[3] = true_count;

    //calculate percentage of false and change from float to integer and decimal place
    float percentage_false = (float)false_count / (float)bool_arr_size * 100;
    int temp_false = floor(percentage_false);
    for (midBool[5] = 0; percentage_false != temp_false && midBool[5] != 6; midBool[5]++) {
        percentage_false *= 10;
        temp_false = floor(percentage_false);
    }
    midBool[4] = temp_false;
    midBool[6] = false_count;
    
    return midBool; //return all values
}