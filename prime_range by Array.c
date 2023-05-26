/* ********************************************************************
FILE                   :  prime_range_by_Array.c

PROGRAM DESCRIPTION    : calculate and display range of prime numbers by creating database in array.

AUTHOR                :  K.M. Arun Kumar alias Arunkumar Murugeswaran

KNOWN BUGS            :

NOTE                  :
                      1: Valid prime numbers ranges are from 1 to 10000.
					  2: Maximum prime numbers that can be calculated is 2000.


CHANGE LOGS           :

*****************************************************************************/


#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"
#include <ctype.h>

#define MAX_NUM          (10000UL)
#define MAX_PRIME_COUNT    (2000UL)
#define DEBUG                (00)
#define MAX_STR            (10)

#define PRIME_NUM_MIN_2_OR_3_BIT_POS   (6)
#define PRIME_NUM_MAX_2_OR_3_BIT_POS   (7)

/* Bit Operation macros */
     /* Set bit pos  in byte data   */
#define Set_Bit_in_Data(data_ptr , bit_pos)                          ((*data_ptr) |=   (1 << (bit_pos)))
      /* Clear bit pos in byte data */
#define Clear_Bit_in_Data(data_ptr ,bit_pos)                         ((*data_ptr) &= (~(1 << (bit_pos))))
    /* flip bit pos in byte data  */
#define Toggle_Bit_in_Data(data_ptr , bit_pos)                       ((*data_ptr) ^=   (1 << (bit_pos)))
    /* Test if bit pos in byte data  is set   */
#define Test_Bit_Is_Set_in_Data(data_ptr ,bit_pos)                   (((*data_ptr) & (1 << (bit_pos))) &&  (1 << bit_pos))
   /* Test if bit pos in byte data is clear */
#define Test_Bit_Is_Clear_in_Data(data_ptr ,bit_pos)                 (!(Test_Bit_Is_Set_in_Data(data_ptr ,bit_pos)))

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int64_t;

#define NULL_DATA_PTR                            ((void *)0)
#define NULL_CHAR                               ('\0')

typedef enum { SUCCESS, FAILURE } system_status_t;

unsigned long arr_prime[MAX_PRIME_COUNT];
unsigned int prime_max_count;
void Init_prime_arr();
unsigned int validate_input(void *const prime_int_ptr, char prime_input[]);
int calc_prime(unsigned  int min_prime, unsigned  int max_prime);
int disp_prime(unsigned int min_prime, unsigned int max_prime );
unsigned char min_prime_valid_index, max_prime_valid_index, prime_num_flag;

uint16_t Get_Input_Str(char *const input_str_ptr, const unsigned int input_str_max_chars);

void Init_prime_arr()
{
	prime_num_flag = 0;
	prime_max_count = 0;
	min_prime_valid_index = 0;
	max_prime_valid_index = 1;
	arr_prime[prime_max_count] = 2;
	arr_prime[++prime_max_count] = 3;
}
unsigned int validate_input(void *const prime_int_ptr, char prime_input[])
{
	char compare_string[MAX_STR], str_prime[MAX_STR];
	unsigned int sz, sz1, str_len;
	long int int_prime_input ;
	str_len = strlen(prime_input);
	int i = 0;
	unsigned long int *temp_int_ptr;

	temp_int_ptr  = (unsigned long int  *)prime_int_ptr;
	*temp_int_ptr = 0;
	if( prime_input[0] == '+'  && str_len ==1 )
	{
		printf("\n ERROR[05]: Invalid prime input due to only '+': %s ",prime_input);
		printf("\n INFO[08]: Valid input number range[2, %d]", MAX_NUM);
		return FAILURE;
	}
	else if(prime_input[0] == '+' && !(prime_input[1] >= '0' && prime_input[1] <= '9' ) )
	{
		printf("\n ERROR[06]: Invalid prime input:[%s] begins with + but next character is a not a integer",prime_input) ;
		printf("\n INFO[08]: Valid input number range[2, %d]", MAX_NUM);
		return FAILURE;
	}
	else if(prime_input[0] >= '0' && prime_input[0] <= '9' )
	{
		strcpy(str_prime, prime_input);
	}
	else if(prime_input[0] == '+')
	{
		/* copy characters in prime_input from position 1 to end of string length */
		for (i = 1; i < strlen(prime_input); ++i)
		{
			str_prime[ i - 1 ] = prime_input[ i ];
		}
		str_prime[ i - 1] = '\0';
	}
    else
    {
        printf("\n ERROR[03]: Starting letter is not a number. \n Given number : %s",prime_input);
    	printf("\n INFO[08]: Valid input number range[2, %d]", MAX_NUM);
    	return FAILURE;
	}
    int_prime_input = atol (str_prime);
	ltoa(int_prime_input,compare_string, 10 );
     /* compare with converted string wth given data to check given data is an integer */
    if(!strcmp(compare_string,str_prime))
    {
        if(int_prime_input<=0 || int_prime_input> MAX_NUM)
        {
           	printf("\n ERROR[02]: Number [%d] may be is <= 0 or > max limit [%d]", int_prime_input, MAX_NUM);
			printf("\n INFO[08]: Valid input number range[2, %d]", MAX_NUM);
            return FAILURE;
    	}
		*temp_int_ptr = int_prime_input;
		return SUCCESS;
	}
	else
	{
	      printf("\n ERROR[04]: Begins with number but has non integer characters.\n Given number : %s",prime_input);
		  printf("\n INFO[08]: Valid input number range[2, %d]", MAX_NUM);
          return FAILURE;
	}
   	return SUCCESS;
}
 int disp_prime(unsigned int min_prime, unsigned int max_prime )
 {
 	size_t prime_count = 0, min_prime_count, count = 0;

    printf("\n Displaying prime numbers in [%u,%u] \n ",min_prime, max_prime);
	for(min_prime_count = 0; min_prime_count < prime_max_count; ++min_prime_count )
	{
		if(arr_prime[min_prime_count] < min_prime && arr_prime[min_prime_count + 1] >= min_prime)
			break;
	}
	if((Test_Bit_Is_Clear_in_Data(&prime_num_flag, PRIME_NUM_MIN_2_OR_3_BIT_POS)))
	{
	    min_prime_valid_index = (min_prime_count + 1);
	}
	if((Test_Bit_Is_Clear_in_Data(&prime_num_flag, PRIME_NUM_MAX_2_OR_3_BIT_POS)))
	{
	    max_prime_valid_index = prime_max_count;
	}

	if(DEBUG)
	  printf("\n INFO[09]: initial prime_count: %u ",  min_prime_count + 1);
 	for(prime_count = min_prime_valid_index, count = 0; prime_count <= max_prime_valid_index; ++prime_count,++count )
	{
		if((count % 5) == 0)
			printf("\n");
 	    printf("%3u , ", arr_prime[prime_count]) ;
	}

 	return SUCCESS;
 }
 int calc_prime(unsigned int min_prime,unsigned int max_prime)
 {
 	unsigned int prime_count=0, num = 0, max_num_prime;
 	char is_prime='y';

    for(num = 5; num <= max_prime; num = num + 2 )
 	{
      is_prime='y';
      max_num_prime = (unsigned int) ceil(sqrt((double) num)) ;
      if(DEBUG)
          printf("\n INFO[02]: Number[%u] to find prime [%u]",num, max_num_prime);
       for( prime_count = 0  ;  prime_count<=prime_max_count; ++prime_count )
 	  {
 	  	if(DEBUG)
 	       printf("\n INFO[03]: prime count [%u] , number [%u]",prime_count,num) ;
 	  	 if( num % arr_prime[prime_count] == 0)
 	  	 {
 	  	 	if(DEBUG)
 	  	 	  printf("\n INFO[04]: Number[%u] is divisible by first prime[%u]", num,arr_prime[prime_count]) ;
 	  	 	is_prime='n';
 	  	 	break;
		 }
      }
      if(is_prime=='y')
	  {
	  	if(DEBUG)
		    printf("\n INFO[05]: Number[%u] is a prime number ", num);
		 if(prime_max_count < MAX_PRIME_COUNT)
		 {
		    ++prime_max_count;
		    arr_prime[prime_max_count] = num;
		 }
         else
		 {
			 printf("\n ERR: prime count exceeds max array elements: %u", MAX_PRIME_COUNT);
			 return FAILURE;
		 }
	  }
	}
	return SUCCESS;
 }
int main()
{
	long int min_prime, max_prime;
	char str_prime_input[MAX_STR], to_iterate[2] = "Y";

    printf("\nDisplay a range of prime numbers \n");
    while(to_iterate[0] == 'Y')
	{
		Init_prime_arr();

	    printf("\n Enter min prime number : ");
	    //gets(str_prime_input);
	    if((Get_Input_Str(str_prime_input, MAX_STR)) != SUCCESS)
		{
			to_iterate[0] = 'Y';
			printf("\n ERR: Invalid min prime number");
			continue;
		}
	    if((validate_input(&min_prime, str_prime_input)) != SUCCESS)
        {
            to_iterate[0] = 'Y';
			printf("\n ERR: Invalid min prime number");
			continue;
        }
	    if(min_prime)
	    {
		  strcpy(str_prime_input,"");
	      printf("\n Enter max prime number : ");
	     // gets(str_prime_input);
		  if((Get_Input_Str(str_prime_input, MAX_STR)) != SUCCESS)
		  {
			 to_iterate[0] = 'Y';
			 printf("\n ERR: Invalid max prime number");
			 continue;
		  }
		 if((validate_input(&max_prime, str_prime_input)) != SUCCESS)
         {
            to_iterate[0] = 'Y';
			printf("\n ERR: Invalid max prime number");
			continue;
         }
		  if( max_prime >= min_prime)
		  {
	           switch(min_prime)
	           {
	              case 2:
		            min_prime_valid_index = 0;
		            Set_Bit_in_Data(&prime_num_flag, PRIME_NUM_MIN_2_OR_3_BIT_POS);
		          break;
                  case 3:
                     min_prime_valid_index	= 1;
		             Set_Bit_in_Data(&prime_num_flag, PRIME_NUM_MIN_2_OR_3_BIT_POS);
		          break;
                  default:
                      Clear_Bit_in_Data(&prime_num_flag, PRIME_NUM_MIN_2_OR_3_BIT_POS);
	            }
                switch(max_prime)
	            {
	            	case 2:
		              max_prime_valid_index = 0;
		              Set_Bit_in_Data(&prime_num_flag, PRIME_NUM_MAX_2_OR_3_BIT_POS);
		            break;
                    case 3:
                       max_prime_valid_index = 1;
		               Set_Bit_in_Data(&prime_num_flag, PRIME_NUM_MAX_2_OR_3_BIT_POS);
		            break;
                    default:
                        Clear_Bit_in_Data(&prime_num_flag, PRIME_NUM_MAX_2_OR_3_BIT_POS);
	            }
	         if( max_prime > 3)
	            calc_prime(min_prime, max_prime);
	         disp_prime(min_prime, max_prime);
		  }
		  else
			 printf("\n ERROR[06]: max_prime[%u] < min_prime[%u]",max_prime, min_prime);
      }
	  printf("\n\n Do you want to continue ? ");
	  printf("\n Press key 'y' or 'Y' to continue, any other key(s) to exit application. \n Continue ? - ");
	  if((Get_Input_Str(to_iterate, 2)) != SUCCESS)
      {
		  to_iterate[0] = 'N';
	  }
      else
	  {
		  to_iterate[0] = toupper(to_iterate[0]);		  
	  }
    }
    return 0;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Get_Input_Str

DESCRIPTION    :

INPUT          :

OUTPUT         :

NOTE           :

Func ID        : 01.02

BUGS           :
-*------------------------------------------------------------*/
uint16_t Get_Input_Str(char *const input_str_ptr, const unsigned int input_str_max_chars)
{
    unsigned int input_str_num_chars = 0;
	char rcvd_char;

    if(input_str_ptr == NULL_DATA_PTR || input_str_max_chars <= 1)
	{
		return FAILURE;
	}
    memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
	while (1)
	{
		rcvd_char = (char) getchar();
		//scanf("%c", &rcvd_char);
		switch(rcvd_char)
        {
			case '\b':
              if(input_str_num_chars > 0)
			  {
			      input_str_ptr[input_str_num_chars] = NULL_CHAR;
				  --input_str_num_chars;
			  }
			break;
            case '\n':
			   if(input_str_num_chars != 0)
			   {
			      input_str_ptr[input_str_num_chars] = NULL_CHAR;
			      return SUCCESS;
			   }
            break;
            default:
     			if(input_str_num_chars + 1 < input_str_max_chars )
    		    {
		    	   input_str_ptr[input_str_num_chars] = rcvd_char;
                   ++input_str_num_chars;
	    		}
		    	else
			    {
			       printf("ERR: Input data num chars exceeds max chars : %u \n", input_str_max_chars - 1);
			       memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
				   fflush(stdin);
				   return FAILURE;
			    }
		}
	}
	return SUCCESS;
}
