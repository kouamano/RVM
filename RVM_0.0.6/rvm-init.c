/************************************************/
/*          RVM - Region Vector Machine         */
/* Copyright (c) 2005 AMANO Kou                 */
/* National Institute of Agrobiological Scences */
/* School of Libarary and Information Science   */
/* University of Tsukuba                        */
/*                           kamano@affrc.go.jp */
/************************************************/

/* rvm-init.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "define.h"
#define RVM_INIT
#include "files.h"

struct option_init {
	int status;
	char input_file_name[MAX_LEN_FILE_NAME];
	int input_file_format;
	int column_train;
	int row_train;
	char output_file_name[MAX_LEN_FILE_NAME];
	int output_file_format;
	int row_cluster;
	char pattern[MAX_LEN_STR];
};

void print_option_init(struct option_init opt){
	printf("status             :%d:\n",opt.status);
	printf("input_file         :%s:\n",opt.input_file_name);
	printf("input_file_format  :%d:\n",opt.input_file_format);
	printf("column_train       :%d:\n",opt.column_train);
	printf("row_train          :%d:\n",opt.row_train);
	printf("output_file        :%s:\n",opt.output_file_name);
	printf("output_file_format :%d:\n",opt.output_file_format);
	printf("row_cluster        :%d:\n",opt.row_cluster);
	printf("pattern            :%s:\n",opt.pattern);
};

void help_init(int level) {
	printf("USAGE:\n");
	printf("  rvm-init if=<input file (training file)> of=<output file (cluster file)> [if_form=<format>[,<column size>,<row size>]] [of_form=<format>] {Diagonal=<number of initial cluster nodes>|Grid=<numbers of fraction (comma separated)>|Automatic}\n");
	printf("FILE FORMAT:\n");
	printf("  1 - with matrix size (column row).\n");
	printf("  2 - with ID.\n");
};

void build_status_init(void){
	printf("STATUS:\n");
	printf("  mane: rvm-init .\n");
	printf("  source: rvm-init.c .\n");
	printf("  build: prototype, finished .\n");
	printf("  final update: 2005.11.08 .\n");
};

int get_option_init(int start, int end, char **arg, struct option_init *opt){
	int i = 0;
	int r = 0;
	int s = 0;
	r = end - start;
	while(r > 0){
		for(i=start;i<end;i++){
			if(strcmp(arg[i],"--check") == 0){
				if((s&1) == 0){
					s = s + 1;
				}
				r--;
			}else if(strcmp(arg[i],"--help") == 0){
				if((s&2) == 0){
					s = s + 2;
				}
				r--;
			}else if(strcmp(arg[i],"-h") == 0){
				if((s&2) == 0){
					s = s + 2;
				}
				r--;
			}else if(strncmp(arg[i],"if=",3) == 0){
				sscanf(arg[i],"if=%s",opt->input_file_name);
				if((s&4) == 0){
					s = s + 4;
				}
				r--;
			}else if(strncmp(arg[i],"of=",3) == 0){
				sscanf(arg[i],"of=%s",opt->output_file_name);
				if((s&8) == 0){
					s = s + 8;
				}
				r--;
			}else if(strncmp(arg[i],"if_form=",8) == 0){
				sscanf(arg[i],"if_form=%d,%d,%d",&opt->input_file_format,&opt->column_train,&opt->row_train);
				if((s&16) == 0){
					s = s + 16;
				}
				r--;
			}else if(strncmp(arg[i],"of_form=",8) == 0){
				sscanf(arg[i],"of_form=%d",&opt->output_file_format);
				if((s&32) == 0){
					s = s + 32;
				}
				r--;
			}else if(strncmp(arg[i],"Grid=",5) == 0){
				sscanf(arg[i],"Grid=%s",opt->pattern);
				if((s&64) == 0){
					s = s + 64;
				}
				r--;
			}else if(strncmp(arg[i],"G=",2) == 0){
				sscanf(arg[i],"G=%s",opt->pattern);
				if((s&64) == 0){
					s = s + 64;
				}
				r--;
			}else if(strncmp(arg[i],"Diagonal=",5) == 0){
				sscanf(arg[i],"Diagonal=%d",&opt->row_cluster);
				if((s&128) == 0){
					s = s + 128;
				}
				r--;
			}else if(strncmp(arg[i],"D=",2) == 0){
				sscanf(arg[i],"D=%d",&opt->row_cluster);
				if((s&128) == 0){
					s = s + 128;
				}
				r--;
			}else if(strncmp(arg[i],"Automatic",10) == 0){
				if((s&256) == 0){
					s = s + 256;
				}
				r--;
			}else if(strncmp(arg[i],"Auto",5) == 0){
				if((s&256) == 0){
					s = s + 256;
				}
				r--;
			}else if(strncmp(arg[i],"--build-status",14) == 0){
				if((s&2048) == 0){
					s = s + 2048;
				}
				r--;
			}else if(strncmp(arg[i],"-s",2) == 0){
				if((s&2048) == 0){
					s = s + 2048;
				}
				r--;
			}else{

				printf("unknown option: %s.\n",arg[i]);
				exit(0);
			}
		}
	}
	return(s);
};

#include "rvm.c"

int main(int argc, char **argv){
	int i;
	int j;
	struct option_init opt;
	opt.input_file_name[0] = 0;
	opt.input_file_format = 3;	/* 1: with size, 2: with ID */
	opt.output_file_name[0] = 0;
	opt.output_file_format = 3;
	opt.column_train = 0;
	opt.row_train = 0;
	opt.row_cluster = 0;
	int opt_status = 0;
	FILE *IN;
	FILE *OUT;
	float **matrix_train = NULL;
	int column_train = 0;
	int row_train = 0;
	struct status_train *stat_train = NULL;
	float **matrix_cluster = NULL;
	int column_cluster = 0;
	int row_cluster = 0;
	struct status_cluster *stat_cluster = NULL;
	int tensor_rank = 1;
	int *dimensions = NULL;
	char str_dimensions[MAX_LEN_STR];
	int num_grid_points = 1;
	int **grid_points = NULL;
	float **min_max_pair = NULL;
	float **min_max_matrix = NULL;
	float **tensor_vars = NULL;
	float **out_matrix = NULL;
	struct integer_count *prop_count = NULL;
	int num_property = 0;
	/* float tmp; */
	float *tmp_vec;
	/* float **tmp_matrix; */
	if(argc < 2){
		printf(head);	printf(bar);
		printf(head);	printf(title);
		printf(head);	printf(version);
		printf(head);	printf(author);
		printf(head);	printf(bar);
		exit(0);
	}
	opt_status = get_option_init(1,argc,argv,&opt);
	opt.status = opt_status;
	if((opt_status&2) == 2){
		help_init(0);
		exit(0);
	}else if((opt_status&2048) == 2048){
		build_status_init();
		exit(0);
	}
	/* (* read data and generate output */
	if((opt_status&4) == 4){
		if((IN = fopen(opt.input_file_name,"r")) == NULL){
			perror(opt.input_file_name);
			exit(1);
		}
		/* (* read format alignment */
		if((opt.input_file_format&1) == 1){
			fscanf(IN,"%d",&opt.column_train);
			fscanf(IN,"%d",&opt.row_train);
		}
		if((opt.column_train * opt.row_train) <= 0){
			printf("check matrix size\n");
			exit(0);
		}
		/* *) */
		/* (* initiarize for training data */
		column_train = opt.column_train;
		row_train = opt.row_train;
		matrix_train = f_alloc_mat(row_train,column_train);
		stat_train = alloc_status_train(row_train,MAX_LEN_STR);
		/* *) */
		/* (* for cluster data */
		column_cluster = column_train;
		if(opt.row_cluster > 0){
			row_cluster = opt.row_cluster;
			matrix_cluster = f_alloc_mat(row_cluster * RATIO_SIZE_EXPAND,column_cluster);
			stat_cluster = alloc_status_cluster(row_cluster * RATIO_SIZE_EXPAND,row_cluster,1);
		}
		/* *) */
		/* (* read training data */
		if((opt.input_file_format&2) == 2){
			read_train_ID_property_ftable_from_stream(row_train,column_train,IN,matrix_train,stat_train);
		}else{
			read_train_property_ftable_from_stream(row_train,column_train,IN,matrix_train,stat_train);
		}
		/* *) */
		fclose(IN);
		/* (* initialize */
		if((opt_status&64) == 64){	/* Grid */
			tensor_rank = column_cluster;
			sscanf(opt.pattern,"%s",str_dimensions);
			dimensions = get_tensor_dim_rank(tensor_rank,str_dimensions);
			grid_points = tensor_position_matrix(tensor_rank,&num_grid_points,dimensions);
			row_cluster = num_grid_points;
			min_max_pair = f_alloc_mat(2,column_train);	/* min value and max value */
			min_max_matrix = f_alloc_mat(row_cluster,column_cluster);
			float_min_matrix(column_train,row_train,matrix_train,min_max_pair[0],0);
			float_max_matrix(column_train,row_train,matrix_train,min_max_pair[1],0);
			stat_cluster = alloc_status_cluster(row_cluster,column_cluster,1);
			out_matrix = f_alloc_mat(row_cluster,tensor_rank);
			if((tensor_vars = malloc(sizeof(float*) * tensor_rank)) == NULL){
				printf("failed: malloc().\n");
				exit(0);
			}
			for(i=0;i<tensor_rank;i++){
				tensor_vars[i] = min_to_max_list(dimensions[i],min_max_pair[0][i],min_max_pair[1][i]);
			}
			/* (* write to output */
			for(i=0;i<row_cluster;i++){
				for(j=0;j<column_cluster;j++){
					out_matrix[i][j] = tensor_vars[j][grid_points[i][j]];
				}
			}
			/* *) */
		}else if((opt.status&128) == 128){	/* Diagonal */
			min_max_pair = f_alloc_mat(2,column_train);	/* min value and max value */
			min_max_matrix = f_alloc_mat(row_cluster,column_cluster);
			float_min_matrix(column_train,row_train,matrix_train,min_max_pair[0],0);
			float_max_matrix(column_train,row_train,matrix_train,min_max_pair[1],0);
			for(j=0;j<column_train;j++){
				tmp_vec = min_to_max_list(row_cluster,min_max_pair[0][j],min_max_pair[1][j]);
				for(i=0;i<row_cluster;i++){
					min_max_matrix[i][j] = tmp_vec[i];
				}
			}
			out_matrix = min_max_matrix;
		}else if((opt.status&256) == 256){	/* Auto */
			prop_count = alloc_integer_count(row_train);
			num_property = prop_counter(row_train,stat_train,prop_count);
			row_cluster = num_property;
			out_matrix = f_calloc_mat(row_cluster,column_cluster);
			stat_cluster = alloc_status_cluster(row_cluster,column_cluster,1);
			for(i=0;i<row_cluster;i++){
				stat_cluster[i].num_property = 1;
				stat_cluster[i].property_this_cluster = prop_count[i].v;
				stat_cluster[i].num_total_sample = prop_count[i].count;
				stat_cluster[i].freq_property = i_alloc_mat(stat_cluster->num_property,1);
				fprintf(stderr,"remark: member freq_property allocated.\n");
				stat_cluster[i].num_positive_sample = prop_count[i].count;
				stat_cluster[i].SN_positive_sample = calloc(sizeof(int),prop_count[i].count);
				fprintf(stderr,"remark: member SN_positive_sample allocated.\n");
				register_SN_positive_sample(&stat_cluster[i],row_train,stat_train);
				register_centroid_positive_sample(&stat_cluster[i],row_train,column_train,matrix_train);
				for(j=0;j<column_cluster;j++){
					out_matrix[i][j] = stat_cluster[i].centroid_positive_sample[j];
				}
			}
		}
		if(((opt.status&64) != 64)&&((opt.status&128) != 128)&&((opt.status&256) != 256)){
			fprintf(stderr,"warning: no initialize pattern, incomplete output file.\n");
		}
		/* *) */
	}
	/* *) */
	/* (* check */
	if((opt_status&1) == 1){
		print_option_init(opt);
		exit(0);
	}
	/* *) */
	/* (* file output */
	if((opt_status&8) == 8){
		OUT = fopen(opt.output_file_name,"w");
		if((opt.output_file_format&1) == 1){	/* with size */
			fprintf(OUT,"%d %d\n",column_cluster,row_cluster);
		}
		if((opt.output_file_format&2) == 2){	/* with ID */
			for(i=0;i<row_cluster;i++){
				fprintf(OUT,"%d %d",i,stat_cluster[i].property_this_cluster);
				for(j=0;j<column_cluster;j++){
					fprintf(OUT," %f",out_matrix[i][j]);
				}
				fprintf(OUT,"\n");
			}
		}else{
			for(i=0;i<row_cluster;i++){
				fprintf(OUT,"%d",stat_cluster[i].property_this_cluster);
				for(j=0;j<column_cluster;j++){
					fprintf(OUT," %f",out_matrix[i][j]);
				}
				fprintf(OUT,"\n");
			}
		}
		fclose(OUT);
	}else{
		fprintf(stderr,"warning: no output file.\n");
	}
	/* *) */
	return(0);
}
