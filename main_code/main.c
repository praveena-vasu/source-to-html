#include "html.h"
#include<stdio.h>
#include "lexer.h"
int main()
{
  FILE *input =fopen ("lexer.c","r");
  FILE *output = fopen("output.html","w");
  if(input == NULL)
  {
    printf("Unable to open the FILE\n");
    return 1;
  }
if(output == NULL)
  {
    printf("Unable to generate the  html FILE\n");
    return 1;
  }
  write_html_header(output);
  
      lexical_analyzer(input,output);
   
        write_html_footer(output);
        fclose(input);
        fclose(output);
      return 0;
}
