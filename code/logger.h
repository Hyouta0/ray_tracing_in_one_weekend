#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
// TODO: add log level
// TODO: add line no. and file name
// TODO: format string like this "[ERROR]: This is my error\n"

/*
 * This are colors which are printed in terminal
 * \033[1;<color>m  : start of colored text
 * \033[1;0m  : reset color back to normal
    Black  : 30
    Red    : 31
    Green  : 32
    Yellow : 33
    Blue   : 34
    Magenta: 35
    Cyan   : 36
    White  : 37
    Reset  : 0
 */

#define log(color,fmt,...)\
	do{\
		fprintf(stderr,"\033[1;%dm" fmt "\033[0m",color,##__VA_ARGS__);\
		fflush(stderr);\
	}while(0)

#define log_del(fmt,...) log(0,fmt,##__VA_ARGS__)
#define log_dev(fmt,...) log(32,fmt,##__VA_ARGS__)
#define log_err(fmt,...) log(31,fmt,##__VA_ARGS__)


#define GREEN_START  "\033[1;32m" 
#define COLOR_END    "\033[0m"

#define log_vec3(X) \
	log_del("variable : '%s"#X"%s' values: %s{%f, %f, %f}%s\n",\
			GREEN_START,COLOR_END,GREEN_START,(X).x,(X).y,(X).z,COLOR_END)
#endif
