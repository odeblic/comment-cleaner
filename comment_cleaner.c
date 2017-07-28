#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  FILE* input = NULL;
  FILE* output = NULL;

  if(argc != 2)
  {
    puts("no source file provided");
    return EXIT_FAILURE;
  }

  printf("processing file '%s'\n", argv[1]);

  input = fopen(argv[1], "r");

  if(input == NULL)
  {
    puts("unable to open input file");
    return EXIT_FAILURE;
  }

  output = fopen("source_without_comment.c", "a");

  if(output == NULL)
  {
    puts("unable to open output file");
    fclose(input);
    return EXIT_FAILURE;
  }

  int c = 0;

  do
  {
    c = fgetc(input);

    switch(c)
    {
      // a slash may be the beginning of a comment
      case '/':
      switch(c = fgetc(input))
      {
        // a slash following the first one is the beginning of a single line comment
        case '/':
        do
        {
          c = fgetc(input);
      
          if(c == '\n')
          {
            fputc('\n', output);
            break;
          }
        }
        while(c != -1); // end of file is reached ?
        break;
        
        // a star following the first slash is the beginning of a multiline comment
        case '*':
        do
        {
          c = fgetc(input);
          
          if(c == '*')
          {
            c = fgetc(input);
            
            if(c == '/')
            {
              break;
            }
          }
        }
        while(c != -1); // end of file is reached ?
        break;
        
        default:
        fputc('/', output);
        fputc(c, output);
      }
      break;
      
      // a double quote is the begin of a string
      case '"':
      fputc('"', output);
      do
      {
        c = fgetc(input);
        
        // end of file is reached ?
        if(c != -1)
        {
          fputc(c, output);
          
          // a backslash is the beginning an escape sequence
          if(c == '\\')
          {
            c = fgetc(input);
            
            // end of file is reached ?
            if(c != -1) 
            {
              fputc(c, output);
            }
          }
        }
      }
      // a second double quote is the end of the string
      while(c != '"' && c != -1); // end of file is reached ?
      break;
      
      // end of file is reached ?
      case -1:
      break;
      
      default:
      fputc(c, output);
    }
  }
  while(c != -1);

  fclose(input);
  fclose(output);

  return EXIT_SUCCESS;
}

