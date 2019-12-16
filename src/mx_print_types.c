#include "uls.h"

static void print_name(char *name, bool folder);

void mx_basic_print(t_info *info, bool folder) {
	int j;
	int sub_r;
	int tab_len = 0;
	int num_of_lines = mx_num_of_cols(info);

	for (int i = 0; i < num_of_lines; i++) {
		j = 0;
		sub_r = 0;
		for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next, j++) {
			if ((j + num_of_lines - i) % num_of_lines == 0) {
				print_name(tmp->data, folder);
				if (sub_r + num_of_lines < info->num_of_sub) {
					tab_len = info->max_sub_len - mx_strlen(tmp->data) 
					+ mx_strlen(info->path) + 1;
					mx_print_tabs(tab_len + (8 - (info->max_sub_len % 8)));
				}
			}
			++sub_r;
		}
		mx_printchar('\n');
	}
}

void mx_print_1(t_info *info, bool folder) {
	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next) {
		print_name(tmp->data, folder);
		mx_printchar('\n');
	}
}

void mx_print_l(t_info *info, bool folder) {
	t_uni_list *t2 = info->sub_args;
	t_tabs_l *tmp3 = info->tabs_l;

	for (t_info_l *tmp = info->info_l; tmp; tmp = tmp->next, t2 = t2->next) {
		mx_printstr(tmp->access);
		mx_print_tabs(tmp3->l_nlink - mx_strlen(tmp->nlink));
		mx_printstr(tmp->nlink);
		mx_print_tabs(1);
		mx_printstr(tmp->login);
		mx_print_tabs(tmp3->l_login - mx_strlen(tmp->login) + 2);
		mx_printstr(tmp->group_owner);
		mx_print_tabs(tmp3->l_group_owner - mx_strlen(tmp->group_owner));
		mx_print_tabs(mx_strlen(tmp->sym_num) < 9 ? tmp3->l_sym_num
			- mx_strlen(tmp->sym_num) + 2 : 2);
		mx_printstr(tmp->sym_num);
		mx_print_tabs(1);
		mx_printstr(tmp->time_upd);
		mx_print_tabs(tmp3->l_time_upd - mx_strlen(tmp->time_upd) + 1);
		print_name(t2->data, folder);
		mx_printchar('\n');
	}
}

static void print_name(char *name, bool folder) {
	if (folder) {
		for (int i = mx_strlen(name) - 1; i >= 0; i--)
			if (name[i - 1] == '/' || i == 0) {
				mx_printstr(&name[i]);
				break;
			}
	}
	else
		mx_printstr(name);
}