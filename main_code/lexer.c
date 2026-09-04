#include "lexer.h"
#include "keyword.h"
#include "operator.h"
#include <string.h>
#include "html.h"
#include <stdio.h>

void lexical_analyzer(FILE *input, FILE *output)
{
    int ch;
    char word[100];
    int pos = 0;

    ch = fgetc(input);

    while(ch != EOF)
    {
        if(ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
        {
            fputc(ch, output);
            ch = fgetc(input);
            continue;
        }

        else if(ch == '#')
        {
            fprintf(output, "<span class=\"preprocessor\">");

            while(ch != '\n' && ch != EOF)
            {
                html_escape(output, ch);
                ch = fgetc(input);
            }

            fprintf(output, "</span>");

            if(ch == '\n')
            {
                fputc(ch, output);
                ch = fgetc(input);
            }
        }

        else if((ch >= 'a' && ch <= 'z') ||
                (ch >= 'A' && ch <= 'Z') ||
                ch == '_')
        {
            while((ch >= 'a' && ch <= 'z') ||
                  (ch >= 'A' && ch <= 'Z') ||
                  ch == '_' ||
                  (ch >= '0' && ch <= '9'))
            {
                word[pos] = ch;
                pos++;
                ch = fgetc(input);
            }

            word[pos] = '\0';

            int flag = 0;

            for(int i = 0; i < 32; i++)
            {
                if(strcmp(word, keyword[i]) == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if(flag == 1)
            {
                fprintf(output,
                        "<span class=\"keyword\">%s</span>",
                        word);
            }
            else
            {
                fprintf(output,
                        "<span class=\"identifier\">%s</span>",
                        word);
            }

            pos = 0;
        }

        else if(ch >= '0' && ch <= '9')
        {
            char num[100];
            int index = 0;
            int dot_count = 0;

            while((ch >= '0' && ch <= '9') ||
                  (ch == '.' && dot_count == 0))
            {
                if(ch == '.')
                {
                    dot_count++;
                }

                num[index] = ch;
                index++;

                ch = fgetc(input);
            }

            num[index] = '\0';

            fprintf(output,
                    "<span class=\"number\">%s</span>",
                    num);
        }

        /* CHARACTER LITERAL */
        else if(ch == '\'')
        {
            char character[5];
            int ind = 0;

            character[ind++] = ch;     /* opening ' */

            ch = fgetc(input);

            if(ch == '\\')
            {
                character[ind++] = ch;

                ch = fgetc(input);
                character[ind++] = ch;
            }
            else
            {
                character[ind++] = ch;
            }

            ch = fgetc(input);

            if(ch == '\'')
            {
                character[ind++] = ch; /* closing ' */
                character[ind] = '\0';

                fprintf(output,
                        "<span class=\"character\">");

                for(int i = 0;
                    character[i] != '\0';
                    i++)
                {
                    html_escape(output, character[i]);
                }

                fprintf(output, "</span>");

                ch = fgetc(input);
            }
            else
            {
                character[ind] = '\0';

                fprintf(output,
                        "<span class=\"invalid\">");

                for(int i = 0;
                    character[i] != '\0';
                    i++)
                {
                    html_escape(output, character[i]);
                }

                fprintf(output, "</span>");
            }
        }

        /* /, // AND /* COMMENTS */
        else if(ch == '/')
        {
            ch = fgetc(input);

            if(ch == '/')
            {
                fprintf(output,
                        "<span class=\"comment\">");

                fputc('/', output);
                fputc('/', output);

                ch = fgetc(input);

                while(ch != '\n' && ch != EOF)
                {
                    html_escape(output, ch);
                    ch = fgetc(input);
                }

                fprintf(output, "</span>");

                if(ch == '\n')
                {
                    fputc(ch, output);
                    ch = fgetc(input);
                }
            }

            else if(ch == '*')
            {
                fprintf(output,
                        "<span class=\"comment\">");

                fputc('/', output);
                fputc('*', output);

                ch = fgetc(input);

                while(ch != EOF)
                {
                    html_escape(output, ch);

                    if(ch == '*')
                    {
                        ch = fgetc(input);

                        if(ch != EOF)
                        {
                            html_escape(output, ch);
                        }

                        if(ch == '/')
                        {
                            fprintf(output,
                                    "</span>");

                            ch = fgetc(input);
                            break;
                        }
                    }
                    else
                    {
                        ch = fgetc(input);
                    }
                }
            }

            else
            {
                fprintf(output,
                        "<span class=\"operator\">/</span>");

                ungetc(ch, input);
                ch = fgetc(input);
            }
        }

        /* OPERATORS */
        else if(ch == '+' || ch == '-' ||
                ch == '*' || ch == '/' ||
                ch == '=' || ch == '%' ||
                ch == '!' || ch == '<' ||
                ch == '>' || ch == '&' ||
                ch == '|')
        {
            char op[3];
            int op_pos = 0;

            op[op_pos] = ch;
            op_pos++;

            ch = fgetc(input);

            op[op_pos] = ch;
            op_pos++;

            op[op_pos] = '\0';

            int flag = 0;

            for(int i = 0; i < 30; i++)
            {
                if(strcmp(op, operators[i]) == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if(flag == 0)
            {
                fprintf(output,
                        "<span class=\"operator\">");

                html_escape(output, op[0]);

                fprintf(output, "</span>");

                ungetc(op[1], input);
            }
            else
            {
                fprintf(output,
                        "<span class=\"operator\">");

                for(int i = 0;
                    op[i] != '\0';
                    i++)
                {
                    html_escape(output, op[i]);
                }

                fprintf(output, "</span>");

                ch = fgetc(input);
            }
        }

        /* SPECIAL CHARACTERS */
        else if(ch == '{' || ch == '}' ||
                ch == '(' || ch == ')' ||
                ch == '[' || ch == ']' ||
                ch == ';' || ch == ',')
        {
            fprintf(output,
                    "<span class=\"special\">%c</span>",
                    ch);

            ch = fgetc(input);
        }

        /* STRING */
        else if(ch == '"')
        {
            char str[100];
            int i = 0;

            ch = fgetc(input);

            while(ch != '"' && ch != EOF)
            {
                if(ch == '\\')
                {
                    str[i] = ch;
                    i++;

                    ch = fgetc(input);

                    if(ch != EOF)
                    {
                        str[i] = ch;
                        i++;
                    }
                }
                else
                {
                    str[i] = ch;
                    i++;
                }

                ch = fgetc(input);
            }

            str[i] = '\0';

            fprintf(output,
                    "<span class=\"string\">&quot;");

            for(int j = 0;
                str[j] != '\0';
                j++)
            {
                html_escape(output, str[j]);
            }

            fprintf(output,
                    "&quot;</span>");

            if(ch == '"')
            {
                ch = fgetc(input);
            }
        }

        /* INVALID */
        else
        {
            fprintf(output,
                    "<span class=\"invalid\">");

            html_escape(output, ch);

            fprintf(output, "</span>");

            ch = fgetc(input);
        }
    }
}