/* ********************************************************************
FILE                   :  prime_range_by_Array.c

PROGRAM DESCRIPTION    : calculate and display range of prime numbers by creating database in array.

AUTHOR                :  K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            :    

NOTE                  :  Compiled and tested in Turbo C++
                      1: Valid prime numbers ranges are from 1 to 10000. 
					  2: Maximum prime numbers that can be calculated is 2000. 
					  3: Maximum input of number of characters is 10 is input data. 
					  4: Non nummeric input data for valid input numberic data is validated. 
                                    
CHANGE LOGS           : 

*****************************************************************************/


#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

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

unsigned long arr_prime[MAX_PRIME_COUNT];
unsigned int prime_max_count;
void Init_prime_arr();
unsigned int validate_input(char prime_input[]);
int calc_prime(unsigned  int min_prime, unsigned  int max_prime); 
int disp_prime(unsigned int min_prime, unsigned int max_prime );
unsigned char min_prime_valid_index, max_prime_valid_index, prime_num_flag; 

void Init_prime_arr()
{
	prime_num_flag = 0; 
	prime_max_count = 0;
	min_prime_valid_index = 0; 
	max_prime_valid_index = 1;
	arr_prime[prime_max_count] = 2;
	arr_prime[++prime_max_count] = 3;
}
unsigned int validate_input( char prime_input[])
{
	char compare_string[MAX_STR], str_prime[MAX_STR];
	unsigned int sz, sz1, str_len;             
	int int_prime_input ;
	str_len = strlen(prime_input);
	int i = 0;
	
	if( prime_input[0] == '+'  && str_len ==1 )
	{
		printf("\n ERROR[05]: Invalid prime input due to only '+': %s ",prime_input);	
		printf("\n INFO[08]: Valid input number range[2, %d]", MAX_NUM);	
		return 0;		
	}
	else if(prime_input[0] == '+' && !(prime_input[1] >= '0' && prime_input[1] <= '9' ) )
	{
		printf("\n ERROR[06]: Invalid prime input:[%s] begins with + but next character is a not a integer",prime_input) ;	
		printf("\n INFO[08]: Valid input number range[2, %d]", MAX_NUM);
		return 0;
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
    	return 0;
	}
    int_prime_input = atoi (str_prime);
	itoa(int_prime_input,compare_string, 10 );
     /* compare with converted string wth given data to check given data is an integer */
    if(strcmp(compare_string,str_prime) == 0)
    {	
        if(int_prime_input<=0 || int_prime_input> MAX_NUM)
        {
           	printf("\n ERROR[02]: Number [%d] may be is <= 0 or > max limit [%d]", int_prime_input, MAX_NUM);   
			printf("\n INFO[08]: Valid input number range[2, %d]", MAX_NUM); 
            return 0;			
    	}
		return( (unsigned int )int_prime_input); 
	} 
	else 
	{
	      printf("\n ERROR[04]: Begins with number but has non integer characters.\n Given number : %s",prime_input);
		  printf("\n INFO[08]: Valid input number range[2, %d]", MAX_NUM);  		   
	}    
   	return 0;
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
     
 	return 0;
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
		 ++prime_max_count;
		 arr_prime[prime_max_count] = num;		 	
	  }  
	} 	
	return 0; 
 }
int main()
{
	unsigned int min_prime, max_prime;
	char to_continue[MAX_STR], str_prime_input[MAX_STR], to_iterate ;
	do
	{
		Init_prime_arr();
		printf("\nDisplay a range of prime numbers \n");
	    printf("\n Enter min prime number : ");
	    gets(str_prime_input);
	
	  min_prime = validate_input(str_prime_input);
	  if(min_prime)
	  {
		  strcpy(str_prime_input,"");
	      printf("\n Enter max prime number : ");
	      gets(str_prime_input);
		  max_prime = validate_input(str_prime_input);
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
	  to_iterate = 'n';
	  printf("\n\n Do you want to continue ? ");
	  printf("\n Press key 'y' or 'Y' to continue, any other key(s) to exit application. \n Continue ? - ");
	  gets(to_continue);
      if(!strcmp(to_continue, "y") || !strcmp(to_continue, "Y"))
       	to_iterate = 'y';	  
    } while(to_iterate == 'y');
    return 0;	
}
