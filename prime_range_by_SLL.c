/* ********************************************************************
FILE                   :  prime_range_by_SLL.c

PROGRAM DESCRIPTION    : calculate and display range of prime numbers with fast execution and prime number are stored in Singly Linked List.

AUTHOR                :  K.M. Arun Kumar alias Arunkumar Murugeswaran

KNOWN BUGS            :

NOTE                  :
                      1: Valid prime numbers ranges are from 2 to 10000.


CHANGE LOGS           :

*****************************************************************************/


#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"
#include "conio.h"
#include <ctype.h>

#define MAX_NUM          (10000UL)
#define MAX_PRIME_COUNT   (200)
//#define TRACE_INFO                     (1)
//#define TRACE_DATA                     (2)
#define  MAX_STR            (10)
#define PRIME_NUM_INSERT_BIT_POS          (0)
#define PRIME_NUM_VALID_RANGE_BIT_POS     (1)
#define PRIME_NUM_1ST_TRANSVERSE_BIT_POS  (2)
#define NUM_IS_PRIME_NUM_BIT_POS          (3)
#define TRANSVERSE_MIN_PRIME_BIT_POS      (4)
#define PRIME_NUM_MIN_2_OR_3_BIT_POS      (5)
#define PRIME_NUM_MAX_2_OR_3_BIT_POS      (6)

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

typedef enum
{
	RESET_ALL_PRIME_META_DATAS, INSERT_INIT_SLL_PRIME_DATA, DELETE_INIT_SLL_PRIME_DATA, RESET_PRIME_NUM_FLAG
} prime_num_t;

typedef enum
{
	SUCCESS, FAILURE, ERR_DATA_OUT_OF_RANGE, ERR_INVALID_DATA, ERR_NULL_PTR, FSM_MIN_PRIME_NUM = 0, FSM_MAX_PRIME_NUM, FSM_CALC_PRIME_RANGE,
	FSM_TO_CONTINUE, FSM_EXIT
} err_status_t;

unsigned char system_fsm;
unsigned int Init_Prime_SLL(const unsigned char prime_num_sll_init_type);
unsigned char Validate_Input(void *const prime_num_ptr, char prime_input[]);
unsigned int Calc_Prime(const unsigned long min_prime, const unsigned long max_prime);
unsigned int Disp_Prime(const unsigned long min_prime, const unsigned long max_prime);
unsigned int Delete_Whole_Prime_Num_By_SLL();
unsigned int Insert_Prime_Num_SLL(const unsigned long prime_num);
unsigned long Transverse_Prime_Num_by_Index_SLL(const unsigned char req_node_index);
unsigned long Transverse_Prime_Num_by_Node_SLL(const unsigned long num);
uint16_t Get_Input_Str(char *const input_str_ptr, const unsigned int input_str_max_chars);

struct prime_number_t
{
	struct prime_number_t *prime_num_next_node_ptr;
	unsigned long prime_number;
	unsigned char node_index;
};

typedef struct
{
	struct prime_number_t *prime_num_head_node_ptr;
	struct prime_number_t *prime_num_range_head_node_ptr;
	struct prime_number_t *cur_insert_prime_num_node_ptr;
	struct prime_number_t *cur_transverse_prime_num_node_ptr;
	unsigned int num_prime_numbers;
	unsigned int prime_max_count;
	unsigned char cur_insert_node_index;
} prime_num_data_t;

static prime_num_data_t prime_num_meta_data;
static unsigned char prime_range_flag ;
static unsigned char  prime_num_cur_node_index;
char input_str[MAX_STR];
/* =========================================================
   Function name : Init_Prime_SLL
   Description   :
   Remarks       :
   Func ID       : 1
=========================================================== */
unsigned int Init_Prime_SLL(const unsigned char prime_num_sll_init_type)
{
	switch(prime_num_sll_init_type)
	{
		case RESET_ALL_PRIME_META_DATAS:
	       Delete_Whole_Prime_Num_By_SLL();
	       prime_num_meta_data.prime_num_head_node_ptr = NULL;
	       prime_num_meta_data.prime_num_range_head_node_ptr = NULL;
	       prime_num_meta_data.cur_insert_prime_num_node_ptr = NULL;
		   prime_num_meta_data.cur_transverse_prime_num_node_ptr = NULL;
	       prime_num_meta_data.num_prime_numbers = 0;
	       prime_num_meta_data.prime_max_count = 0;
		   prime_num_meta_data.cur_insert_node_index = 0;
		   prime_range_flag = 0;
		break;
		default:
           return ERR_DATA_OUT_OF_RANGE;
	}
	#ifdef TRACE_INFO
	    printf("\n INFO[1;1] : init SLL over reset - %u ", prime_num_sll_init_type);
	#endif
    return SUCCESS;
}

/* =========================================================
   Function name : Validate_Input
   Description   :
   Remarks       :
   Func ID       : 2
=========================================================== */
unsigned char Validate_Input(void *const prime_num_ptr, char prime_input[])
{
	char compare_string[MAX_STR], str_prime[MAX_STR];
	size_t sz, sz1, str_len;
	long int *prime_input_ptr, int_prime_input;
	str_len = strlen(prime_input);
	int i = 0;

	prime_input_ptr = (long int *)prime_num_ptr;
	if( prime_input[0] == '+'  && str_len == 1)
	{
		printf("\n ERROR[05]: Invalid prime input due to only '+': %s ",prime_input);
		printf("\n INFO[08]: Valid input number range[2, %u]", MAX_NUM);
		return ERR_INVALID_DATA;
	}
	if(prime_input[0] == '+' && !(prime_input[1] >= '0' && prime_input[1] <= '9' ) )
	{
		printf("\n ERROR[06]: Invalid prime input:[%s] begins with + but next character is a not a integer",prime_input) ;
		printf("\n INFO[08]: Valid input number range[2, %u]", MAX_NUM);
		return ERR_INVALID_DATA;
	}
	if(prime_input[0] >= '0' && prime_input[0] <= '9' )
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
    	printf("\n INFO[08]: Valid input number range[2, %u]", MAX_NUM);
    	return ERR_INVALID_DATA;
	}
    int_prime_input = atol (str_prime);
	ltoa(int_prime_input,compare_string, 10 );
     /* compare with converted string wth given data to check given data is an integer */
    if(strcmp(compare_string,str_prime) == 0)
    {
        if(int_prime_input<=0 || int_prime_input> MAX_NUM)
        {
           	printf("\n ERROR[02]: Number [%d] may be is <= 0 or > max limit [%d]", int_prime_input, MAX_NUM);
			printf("\n INFO[08]: Valid input number range[2, %u]", MAX_NUM);
            return ERR_DATA_OUT_OF_RANGE;
    	}
		*prime_input_ptr = int_prime_input;
		return(SUCCESS);
	}
	printf("\n ERROR[04]: Begins with number but has non integer characters.\n Given number : %s",prime_input);
	printf("\n INFO[08]: Valid input number range[2, %u]", MAX_NUM);
	return ERR_INVALID_DATA;
}

/* =========================================================
   Function name : Calc_Prime
   Description   :
   Remarks       :
   Func ID       : 3
=========================================================== */
 unsigned int Calc_Prime(const unsigned long min_prime, const unsigned long max_prime)
 {
	unsigned long prime_num;
 	unsigned int num = 0, max_num_prime;

 	for(num = 5; num <= max_prime; num = num + 2 )
 	{
		Set_Bit_in_Data(&prime_range_flag, NUM_IS_PRIME_NUM_BIT_POS);
        max_num_prime = (unsigned int) ceil(sqrt((double) num)) ;

         #ifdef TRACE_INFO
             printf("\n INFO[3:1]: Number - %u to  ", num, max_num_prime);
         #endif

	    for(prime_num_cur_node_index  = 0;  prime_num_cur_node_index < prime_num_meta_data.prime_max_count; ++prime_num_cur_node_index )
 	    {
 	        #ifdef TRACE_INFO
 	            printf("\n INFO[3:2]: prime index [%u] , number [%u]",prime_num_cur_node_index,num) ;
 	        #endif
	        prime_num = Transverse_Prime_Num_by_Index_SLL(prime_num_cur_node_index);
		    if(prime_num != 0)
		    {
 	  	        if( num % prime_num == 0)
 	  	        {
 	  	        	 #ifdef TRACE_INFO
 	  	                printf("\n INFO[3:3]: Number - %u is divisible by prime num : %u ", num, prime_num) ;
 	  	 	         #endif
 	  	 	         Clear_Bit_in_Data(&prime_range_flag, NUM_IS_PRIME_NUM_BIT_POS);
 	  	         	 break;
		        }
			}
        }
        if((Test_Bit_Is_Set_in_Data(&prime_range_flag, NUM_IS_PRIME_NUM_BIT_POS)))
	    {
	      	 #ifdef TRACE_INFO
		        printf("\n INFO[3:4]: Number - %u is a prime number ", num);
		     #endif
		    if(num >= min_prime )
		    {
		    	if((Test_Bit_Is_Clear_in_Data(&prime_range_flag, PRIME_NUM_VALID_RANGE_BIT_POS)))
			    {
		            Set_Bit_in_Data(&prime_range_flag, PRIME_NUM_VALID_RANGE_BIT_POS);
			    }
		    }
			if((Insert_Prime_Num_SLL(num)) != SUCCESS)
			{
				return FAILURE;
			}
	    }
	}
	return SUCCESS;
 }
 /* =========================================================
   Function name : Disp_Prime
   Description   :
   Remarks       :
   Func ID       : 4
=========================================================== */
 unsigned int Disp_Prime(unsigned long min_prime, unsigned long max_prime)
{
	struct prime_number_t *cur_node_ptr;
	unsigned char disp_index;

 	printf("\n Displaying prime numbers in [%u,%u] \n ",min_prime, max_prime);
	if((min_prime == 2 || min_prime == 3) && min_prime == max_prime)
	{
		printf("%5u , ",  min_prime);
		return SUCCESS;
	}
	cur_node_ptr = prime_num_meta_data.prime_num_range_head_node_ptr;
	disp_index = 0;
	while(cur_node_ptr != NULL)
	{
		if((disp_index % 5) == 0)
		{
			disp_index = 0;
			printf("\n");
		}
		++disp_index;
		printf("%5u , ", cur_node_ptr->prime_number);
		cur_node_ptr = cur_node_ptr->prime_num_next_node_ptr;
	}
	return SUCCESS;
}
/* =========================================================
   Function name : main
   Description   :
   Remarks       :
   Func ID       : 5
=========================================================== */
int main()
{
	long int min_prime, max_prime;
	char str_prime_input[MAX_STR], to_iterate[2] ;
	printf("\nDisplay a range of prime numbers \n");

	system_fsm = FSM_MIN_PRIME_NUM;
	do
	{
	    to_iterate[0] = 'Y';
		switch(system_fsm)
		{
			case FSM_MIN_PRIME_NUM:
			   	Init_Prime_SLL(RESET_ALL_PRIME_META_DATAS);
				strcpy(str_prime_input,"");
		        printf("\n Enter min prime number : ");
	            //gets(str_prime_input);
	            if((Get_Input_Str(str_prime_input, MAX_STR)) != SUCCESS)
		        {
					printf("\n ERR: Invalid min prime number");
                    break;
		        }
	            if((Validate_Input(&min_prime, str_prime_input)) != SUCCESS)
	            {
		    		printf("\n ERR: Invalid min prime number");
				}
				else
				{
					system_fsm = FSM_MAX_PRIME_NUM;
				}
			break;
            case FSM_MAX_PRIME_NUM:
	           strcpy(str_prime_input,"");
	           printf("\n Enter max prime number : ");
	          // gets(str_prime_input);
	          if((Get_Input_Str(str_prime_input, MAX_STR)) != SUCCESS)
	          {
		     	  printf("\n ERR: Invalid min prime number");
		          break;
			  }
	          if((Validate_Input(&max_prime, str_prime_input)) != SUCCESS)
	          {
	         	  printf("\n ERR: Invalid min prime number");
		      }
			  else
			  {
				  if(min_prime > max_prime)
	              {
					   printf("\n ERROR[06]: max_prime[%u] < min_prime[%u]",max_prime, min_prime);
					   system_fsm = FSM_MIN_PRIME_NUM;
			      }
				  else
				  {
					  system_fsm = FSM_CALC_PRIME_RANGE;
				  }
	          }
	        break;
			case FSM_CALC_PRIME_RANGE:
	           switch(min_prime)
		       {
				   case 2:
				      Set_Bit_in_Data(&prime_range_flag, PRIME_NUM_VALID_RANGE_BIT_POS);
				   break;
				   case 3:
				     Set_Bit_in_Data(&prime_range_flag, PRIME_NUM_VALID_RANGE_BIT_POS);
				  break;
		      }
	          if(((Insert_Prime_Num_SLL(2)) != SUCCESS))
		      {
			     Init_Prime_SLL(RESET_ALL_PRIME_META_DATAS);
		    	 return FAILURE;
		      }
	          if(((Insert_Prime_Num_SLL(3)) != SUCCESS))
	          {
			     Init_Prime_SLL(RESET_ALL_PRIME_META_DATAS);
		         return FAILURE;
		      }
	          if(max_prime > 3)
		      {
	             if(((Calc_Prime(min_prime, max_prime)) != SUCCESS))
			     {
				  	Init_Prime_SLL(RESET_ALL_PRIME_META_DATAS);
					return FAILURE;
			     }
		     }
		     Disp_Prime(min_prime, max_prime);
			 printf("\n\n Do you want to continue ? ");
	         printf("\n Press key 'y' or 'Y' to continue, any other key(s) to exit application. \n Continue ? - ");
			 system_fsm = FSM_TO_CONTINUE;
		   break;
           case FSM_TO_CONTINUE:
             if((Get_Input_Str(to_iterate, 2)) != SUCCESS)
             {
		         system_fsm = FSM_EXIT;
	         }
             else
	         {
		         to_iterate[0] = toupper(to_iterate[0]);
				 if(to_iterate[0] != 'Y')
				 {
					 system_fsm = FSM_EXIT;
				 }
				 else
				 {
				     system_fsm = FSM_MIN_PRIME_NUM;
				 }
	         }
           break;
		   case FSM_EXIT:
		       Init_Prime_SLL(RESET_ALL_PRIME_META_DATAS);
			   return SUCCESS;
		   break;   
		}
    } while(1);	
    return SUCCESS;
}
/* =========================================================
   Function name : Insert_Prime_Num_SLL
   Description   :
   Remarks       :
   Func ID       : 6
=========================================================== */
unsigned int Insert_Prime_Num_SLL(const unsigned long prime_num)
{
	struct prime_number_t *alloc_prime_num_insert_node_ptr;

	if(prime_num_meta_data.cur_insert_node_index >= MAX_PRIME_COUNT)
	{
		printf("\n ERR: count of prime numbers exceeds max prime number count : %u ", prime_num_meta_data.cur_insert_node_index);
		return FAILURE;
	}
	alloc_prime_num_insert_node_ptr = (struct prime_number_t* )calloc( 1, sizeof(prime_num_data_t) );
	if(alloc_prime_num_insert_node_ptr == NULL)
	{
		printf("\n ERR: [6:1] : Memory Alloc failure ");
		return ERR_NULL_PTR;
	}
	alloc_prime_num_insert_node_ptr->prime_num_next_node_ptr = NULL;
	alloc_prime_num_insert_node_ptr->prime_number = prime_num;
	alloc_prime_num_insert_node_ptr->node_index = prime_num_meta_data.cur_insert_node_index;
	++prime_num_meta_data.cur_insert_node_index;

	#ifdef TRACE_INFO
	    printf("\n INFO[6.2] : New node - 0X%X, prime no - %u, Index - %u", alloc_prime_num_insert_node_ptr,
		  alloc_prime_num_insert_node_ptr->prime_number, alloc_prime_num_insert_node_ptr->node_index);
	#endif
	if(prime_num_meta_data.prime_num_head_node_ptr == NULL)
	{
	   	prime_num_meta_data.prime_num_head_node_ptr = alloc_prime_num_insert_node_ptr;
        #ifdef TRACE_INFO
	           printf("\n INFO[6.3] : Head Node - 0X%X, prime no - %u, Index - %u ", prime_num_meta_data.prime_num_head_node_ptr,
            	 prime_num_meta_data.prime_num_head_node_ptr->prime_number, prime_num_meta_data.prime_num_head_node_ptr->node_index);
	    #endif
	}
	if(prime_num_meta_data.cur_insert_prime_num_node_ptr != NULL)
	{
	   prime_num_meta_data.cur_insert_prime_num_node_ptr->prime_num_next_node_ptr = alloc_prime_num_insert_node_ptr;
       #ifdef TRACE_INFO
	      printf("\n INFO[6.4] : Node - 0X%X, prime no - %u , Index - %u , Next Node - 0X%X ", prime_num_meta_data.cur_insert_prime_num_node_ptr,
    		  prime_num_meta_data.cur_insert_prime_num_node_ptr->prime_number, prime_num_meta_data.cur_insert_prime_num_node_ptr->node_index,
			  prime_num_meta_data.cur_insert_prime_num_node_ptr->prime_num_next_node_ptr);
	   #endif
	}
	prime_num_meta_data.cur_insert_prime_num_node_ptr = alloc_prime_num_insert_node_ptr;
	++prime_num_meta_data.prime_max_count;
	#ifdef TRACE_INFO
	      printf("\n INFO[6.5] : Cur Node - 0X%X, prime no - %u, Index - %u, Next Node - 0X%X", prime_num_meta_data.cur_insert_prime_num_node_ptr,
    		 prime_num_meta_data.cur_insert_prime_num_node_ptr->prime_number,  prime_num_meta_data.cur_insert_prime_num_node_ptr->node_index,
			 prime_num_meta_data.cur_insert_prime_num_node_ptr->prime_num_next_node_ptr);
	#endif
	if((Test_Bit_Is_Set_in_Data(&prime_range_flag, PRIME_NUM_VALID_RANGE_BIT_POS)))
	{
		if(prime_num_meta_data.prime_num_range_head_node_ptr == NULL)
		{
		    prime_num_meta_data.prime_num_range_head_node_ptr = alloc_prime_num_insert_node_ptr;
		}
		#ifdef TRACE_INFO
	       printf("\n INFO[6.6] : Valid Head - 0X%X, prime no - %u , Index - %u ", prime_num_meta_data.prime_num_range_head_node_ptr,
    		prime_num_meta_data.prime_num_range_head_node_ptr->prime_number, prime_num_meta_data.prime_num_range_head_node_ptr->node_index );
	    #endif
        Clear_Bit_in_Data(&prime_range_flag, PRIME_NUM_VALID_RANGE_BIT_POS);
	}
	++prime_num_meta_data.num_prime_numbers;
	return SUCCESS;
}
/* =========================================================
   Function name : Transverse_Prime_Num_by_Index_SLL
   Description   :
   Remarks       :
   Func ID       : 7
=========================================================== */
unsigned long Transverse_Prime_Num_by_Index_SLL(const unsigned char req_node_index)
{
	unsigned long prime_num = 0, count_;

   	if(req_node_index == 0)
	{
		prime_num_meta_data.cur_transverse_prime_num_node_ptr = prime_num_meta_data.prime_num_head_node_ptr;
		#ifdef TRACE_INFO
	       printf("\n INFO[7.1] : Head - 0X%X, prime no - %u, index : %u ", prime_num_meta_data.prime_num_head_node_ptr,
    		prime_num_meta_data.prime_num_head_node_ptr->prime_number, prime_num_meta_data.prime_num_head_node_ptr->node_index );
	    #endif
	}
	while(prime_num_meta_data.cur_transverse_prime_num_node_ptr != NULL )
	{
		if(req_node_index == prime_num_meta_data.cur_transverse_prime_num_node_ptr->node_index)
		{
			prime_num = prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_number;
			#ifdef TRACE_INFO
	            printf("\n INFO[7.2] : Cur Node - 0X%X, prime no - %u, Index : %u ", prime_num_meta_data.cur_transverse_prime_num_node_ptr,
    		    prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_number, prime_num_meta_data.cur_transverse_prime_num_node_ptr->node_index );
	        #endif
			prime_num_meta_data.cur_transverse_prime_num_node_ptr = prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_num_next_node_ptr;
			break;
		}
		#ifdef TRACE_INFO
	       printf("\n INFO[7.4] : Cur Node - 0X%X, prime no - %u, Index : %u, Next Node - 0X%X ", prime_num_meta_data.cur_transverse_prime_num_node_ptr,
    		  prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_number, prime_num_meta_data.cur_transverse_prime_num_node_ptr->node_index,
			  prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_num_next_node_ptr );
	    #endif
		prime_num_meta_data.cur_transverse_prime_num_node_ptr = prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_num_next_node_ptr;
	}
	return prime_num;
}
/* =========================================================
   Function name : Transverse_Prime_Num_by_Node_SLL
   Description   :
   Remarks       :
   Func ID       : 8
=========================================================== */
unsigned long  Transverse_Prime_Num_by_Node_SLL(const unsigned long num)
{
	unsigned long prime_num = 0;

	if(prime_num_meta_data.cur_transverse_prime_num_node_ptr == NULL)
	{
		 prime_num_meta_data.cur_transverse_prime_num_node_ptr = prime_num_meta_data.prime_num_head_node_ptr;
		 #ifdef TRACE_INFO
	       printf("\n INFO[8.1] : Head Node - 0X%X, prime no - %u, Index : %u, Next Node - 0X%X ", prime_num_meta_data.cur_transverse_prime_num_node_ptr,
    		  prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_number, prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_number,
			  prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_num_next_node_ptr );
	    #endif
	}
	if((Test_Bit_Is_Set_in_Data(&prime_range_flag, TRANSVERSE_MIN_PRIME_BIT_POS)))
	{
		while(prime_num_meta_data.cur_transverse_prime_num_node_ptr != NULL)
	    {
	    	if(prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_number >= num)
	     	{
		    	prime_num = prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_number;
			    prime_num_meta_data.cur_transverse_prime_num_node_ptr = prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_num_next_node_ptr;
			   	break;
			}
			prime_num_meta_data.cur_transverse_prime_num_node_ptr = prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_num_next_node_ptr;
		}
	}
    else
	{
		while(prime_num_meta_data.cur_transverse_prime_num_node_ptr != NULL)
	    {
	    	if(prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_number <= num)
	     	{
		    	prime_num = prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_number;
			    prime_num_meta_data.cur_transverse_prime_num_node_ptr = prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_num_next_node_ptr;
			   	break;
			}
			prime_num_meta_data.cur_transverse_prime_num_node_ptr = prime_num_meta_data.cur_transverse_prime_num_node_ptr->prime_num_next_node_ptr;
		}
	}
	return prime_num;
}
/* =========================================================
   Function name : Delete_Whole_Prime_Num_By_SLL
   Description   :
   Remarks       :
   Func ID       : 9
=========================================================== */
unsigned int Delete_Whole_Prime_Num_By_SLL()
{
	struct prime_number_t *free_memory_ptr;
	struct prime_number_t *cur_node_ptr = prime_num_meta_data.prime_num_head_node_ptr;

	while (cur_node_ptr != NULL)
	{
		free_memory_ptr = cur_node_ptr;
		#ifdef TRACE_INFO
	        printf("\n INFO[9:1] : Del node : 0X%X, Prime No : %u, Index : %u, Next Node : 0X%X ", cur_node_ptr,
		        cur_node_ptr->prime_number, cur_node_ptr->node_index, cur_node_ptr->prime_num_next_node_ptr);
	    #endif
		cur_node_ptr = cur_node_ptr->prime_num_next_node_ptr;
		if(free_memory_ptr != NULL)
		{
			#ifdef TRACE_INFO
	          printf("\n INFO[9:2] : Free node : 0X%X, prime num : %u, index : %u ", free_memory_ptr,
			         free_memory_ptr->prime_number, free_memory_ptr->node_index );
	        #endif
           free(free_memory_ptr);
		   --prime_num_meta_data.prime_max_count;
		}

	}
	return SUCCESS;
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
