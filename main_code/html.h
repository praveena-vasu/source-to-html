#ifndef HTML_H
#define HTML_H
#include <stdio.h>

void write_html_header(FILE *fp);
void write_html_footer(FILE *fp);
void html_escape(FILE *output, char ch);
#endif