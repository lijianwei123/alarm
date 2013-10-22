#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


//多个字符连接
void mult_strcat(char *buffer, char *format,...)
{
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);
}

char *ini_file = "alarm.ini";
char *log_file = "alarm.inc";
char url[200];

int get_http_header(char *url)
{	
	char *command = calloc(sizeof(url) + 50, 1);

	char data[200];
	char code[10];
	char protocol[10];
	memset(data, 0, 200);
	memset(code, 0, 10);
	memset(protocol, 0, 10);

	FILE *fp;

	mult_strcat(command, "%s %s ", "curl --head --silent", url);

	fp = popen(command, "r");

	fgets(data, 200, fp);

	pclose(fp);

	sscanf(data, "%s %s ", protocol, code);

	free(command);

	return atoi(code);
}

int main()
{


	FILE *fp = fopen(ini_file, "r");

	FILE *log_fp = fopen(log_file, "w");
	
	while(!feof(fp)) 
	{
		memset(url, 0, sizeof(url));
		fgets(url, sizeof(url), fp);
		//去除换行
		if(url[strlen(url)-1] == '\n') {
			url[strlen(url)-1] = '\0';
		}

		//检测网站
		if(url != NULL)
			fprintf(log_fp, "%s %d\n", url, get_http_header(url));
	}


	fclose(fp);
	fclose(log_fp);
	
	return 0;
}
