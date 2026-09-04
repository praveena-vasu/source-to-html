#include "html.h"

void write_html_header(FILE *fp)
{

 fprintf(fp,"<html>\n");
 fprintf(fp,"<head>\n");
 fprintf(fp,"<title>Source to HTML</title>\n");
 fprintf(fp, "<style>\n");
 fprintf(fp, ".keyword { color: blue; }\n");
 fprintf(fp, ".identifier { color: black; }\n");
  fprintf(fp, ".operator { color: red; }\n");
fprintf(fp, ".number { color: green; }\n");
fprintf(fp, ".character { color: darkgreen; }\n");
fprintf(fp, ".comment { color: gray; }\n");
fprintf(fp, ".string { color: brown; }\n");
fprintf(fp, ".special { color: purple; }\n");
fprintf(fp, ".preprocessor { color: orange; }\n");
fprintf(fp, "</style>\n");
fprintf(fp,"</head>\n");
fprintf(fp,"<body>\n");
fprintf(fp,"<pre>\n");
}
void write_html_footer(FILE *fp)
{
    fprintf(fp,"</pre>\n");
    fprintf(fp,"</body>\n");
    fprintf(fp,"</html>\n");
}
void html_escape(FILE *output, char ch)
{
    if(ch == '<')
    {
        fprintf(output, "&lt;");
    }
    else if(ch == '>')
    {
        fprintf(output, "&gt;");
    }
    else if(ch == '&')
    {
        fprintf(output, "&amp;");
    }
    else
    {
        fputc(ch, output);
    }
}