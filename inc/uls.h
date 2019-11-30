#ifndef ULS_H
#define ULS_H

#define INVALID_USAGE "usage: uls [-l] [file ...]"

#include "libmx/inc/libmx.h"

// Uls

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <wchar.h>
#include <pwd.h>
#include <grp.h>

typedef struct s_uni_list {
	char *data;
	struct s_uni_list *next;
} t_uni_list;

typedef struct s_info {
	int argc;
	char **argv;

	bool flags_exist;
	bool args_exist;

	int *where_what; // 0 - не валідна, 1 - флажок, 2 - агрумент

	char *all_our_flags; // список всіх наших флагів, які нам прийшли
	
	struct s_uni_list *sub_args; // назви файлів, які є в аргументі
	struct s_uni_list *access; // доступ до файлів
} t_info;

// mx_check_errors
char *mx_up_to_one(char *str);
bool mx_check_flags(t_info *info, int i);
bool mx_check_argv(t_info *info, int i);

// mx_start
void mx_start(t_info *info);

// mx_del_all
void mx_del_info(t_info **info);

// print_errors
void mx_invalid_usage();
void mx_arg_not_exist(char *arg);

// mx_work_with_args
void mx_work_with_args(t_info *info);
void mx_sort_args(t_info *info);

// mx_work_with_flags
void mx_work_with_flags(t_info *info);
void mx_l_flag(t_info *info);
void mx_take_flags(t_info *info);

// mx_window.c
int mx_num_of_cols(t_info *info);

// mx_list
t_uni_list *mx_create_uni_list(char *data);
void mx_push_uni_list_back(t_uni_list **list, void *data);
void mx_pop_uni_list_front(t_uni_list **head);

#endif