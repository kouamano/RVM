/************************************************/
/*          RVM - Region Vector Machine         */
/* Copyright (c) 2005 AMANO Kou                 */
/* National Institute of Agrobiological Scences */
/* School of Libarary and Information Science   */
/* University of Tsukuba                        */
/*                           kamano@affrc.go.jp */
/************************************************/

/* rvm-train.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "define.h"
#define RVM_TRAIN
#include "files.h"

struct option_train {
	int status;
	char training_file_name[MAX_LEN_FILE_NAME];
	int training_file_format;
	int column_train;
	int row_train;
	char cluster_file_name[MAX_LEN_FILE_NAME];
	int cluster_file_format;
	int column_cluster;
	int row_cluster;
	char output_file_name[MAX_LEN_FILE_NAME];
	int output_file_format;
	float learning_rate;
	int fission_pattern;
	int fission_every_times;
	int max_cluster;
	int fusion_pattern;
	int fusion_every_times;
	int min_cluster;
	int cluster_expand;
	int loop;
};

void print_option_train(struct option_train opt){
	printf("status                :%d:\n",opt.status);
	printf("training_file         :%s:\n",opt.training_file_name);
	printf("training_file_format  :%d:\n",opt.training_file_format);
	printf("column_train          :%d:\n",opt.column_train);
	printf("row_train             :%d:\n",opt.row_train);
	printf("cluster_file          :%s:\n",opt.cluster_file_name);
	printf("cluster_file_format   :%d:\n",opt.cluster_file_format);
	printf("column_cluster        :%d:\n",opt.column_cluster);
	printf("row_cluster           :%d:\n",opt.row_cluster);
	printf("output_file           :%s:\n",opt.output_file_name);
	printf("output_file_format    :%d:\n",opt.output_file_format);
	printf("learning rate         :%f:\n",opt.learning_rate);
	printf("fission_pattern       :%d:\n",opt.fission_pattern);
	printf("fission_every_times   :%d:\n",opt.fission_every_times);
	printf("max_cluster           :%d:\n",opt.max_cluster);
	printf("fusion_pattern        :%d:\n",opt.fusion_pattern);
	printf("fusion_every_times    :%d:\n",opt.fusion_every_times);
	printf("min_cluster           :%d:\n",opt.min_cluster);
	printf("cluster_expnad        :%d:\n",opt.cluster_expand);
	printf("loop                  :%d:\n",opt.loop);
};

void help_train(int level) {
	printf("USAGE:\n");
	printf("  rvm-train tf=<training file> cf=<cluster file> of=<output file> [tf_form=<format>[,<column size>,<row size>]] [cf_form=<format>[,<column size>,<row size>]] [of_form=<format>] [loop=<loop limitation>]\n");
	printf("FILE FORMAT:\n");
	printf("  1 - with matrix size (column row).\n");
	printf("  2 - with ID.\n");
};

void build_status_train(void){
	printf("STATUS:\n");
	printf("  name: rvm-train .\n");
	printf("  source: rvm-train.c .\n");
	printf("  build: prototype, under construction AT[training_loop()]IN[rvm.c] AT[register_nearest_cluser()]IN[rvm.c] .\n");
	printf("  final update: 2005.11.08 .\n");
}

int get_option_train(int start, int end, char **arg, struct option_train *opt){
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
			}else if(strncmp(arg[i],"tf=",3) == 0){
				sscanf(arg[i],"tf=%s",opt->training_file_name);
				if((s&4) == 0){
					s = s + 4;
				}
				r--;
			}else if(strncmp(arg[i],"cf=",3) == 0){
				sscanf(arg[i],"cf=%s",opt->cluster_file_name);
				if((s&8) == 0){
					s = s + 8;
				}
				r--;
			}else if(strncmp(arg[i],"of=",3) == 0){
				sscanf(arg[i],"of=%s",opt->output_file_name);
				if((s&16) == 0){
					s = s + 16;
				}
				r--;
			}else if(strncmp(arg[i],"tf_form=",8) == 0){
				sscanf(arg[i],"tf_form=%d,%d,%d",&opt->training_file_format,&opt->column_train,&opt->row_train);
				if((s&32) == 0){
					s = s + 32;
				}
				r--;
			}else if(strncmp(arg[i],"cf_form=",8) == 0){
				sscanf(arg[i],"cf_form=%d,%d,%d",&opt->cluster_file_format,&opt->column_cluster,&opt->row_cluster);
				if((s&64) == 0){
					s = s + 64;
				}
				r--;
			}else if(strncmp(arg[i],"of_form=",8) == 0){
				sscanf(arg[i],"of_form=%d",&opt->output_file_format);
				if((s&128) == 0){
					s = s + 128;
				}
				r--;
			}else if(strncmp(arg[i],"rate=",5) == 0){
				sscanf(arg[i],"rate=%f",&opt->learning_rate);
				if((s&512) == 0){
					s = s + 512;
				}
				r--;
			}else if(strncmp(arg[i],"fission=",8) == 0){
				sscanf(arg[i],"fission=%d,%d,%d",&opt->fission_pattern,&opt->fission_every_times,&opt->max_cluster);
				if((s&1024) == 0){
					s = s + 1024;
				}
				r--;
			}else if(strncmp(arg[i],"fusion=",7) == 0){
				sscanf(arg[i],"fusion=%d,%d,%d",&opt->fusion_pattern,&opt->fusion_every_times,&opt->min_cluster);
				if((s&2048) == 0){
					s = s + 2048;
				}
				r--;
			}else if(strncmp(arg[i],"cluster_expand=",15) == 0){
				sscanf(arg[i],"cluster_expand=%d",&opt->cluster_expand);
				if((s&4096) == 0){
					s = s + 4096;
				}
				r--;
			}else if(strncmp(arg[i],"loop=",5) == 0){
				sscanf(arg[i],"loop=%d",&opt->loop);
				if((s&8192) == 0){
					s = s + 8192;
				}
				r--;
			}else if(strncmp(arg[i],"--build-status",14) == 0){
				if((s&32768) == 0){
					s = s + 32768;
				}
				r--;
			}else if(strncmp(arg[i],"-s",2) == 0){
				if((s&32768) == 0){
					s = s + 32768;
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
	struct option_train opt;
	opt.training_file_name[0] = 0;
	opt.training_file_format = 3;	/* 1: with size, 2: with ID */
	opt.cluster_file_name[0] = 0;
	opt.cluster_file_format = 3;
	opt.output_file_name[0] = 0;
	opt.output_file_format = 3;
	opt.column_train = 0;
	opt.row_train = 0;
	opt.column_cluster = 0;
	opt.row_cluster = 0;
	opt.learning_rate = 0;
	opt.fission_pattern = 0;
	opt.fission_every_times = 1;
	opt.max_cluster = MAX_CLUSTER;
	opt.fusion_pattern = 0;
	opt.fusion_every_times = 1;
	opt.cluster_expand = RATIO_SIZE_EXPAND;
	opt.min_cluster = MIN_CLUSTER;
	opt.loop = DEFAULT_LOOP;
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
	struct integer_count *prop_count = NULL;
	int num_property = 0;
	if(argc < 2){
		printf(head);	printf(bar);
		printf(head);	printf(title);
		printf(head);	printf(version);
		printf(head);	printf(author);
		printf(head);	printf(bar);
		exit(0);
	}
	opt_status = get_option_train(1,argc,argv,&opt);
	opt.status = opt_status;
	if((opt_status&2) == 2){
		help_train(0);
		exit(0);
	}else if((opt_status&32768) == 32768){
		build_status_train();
		exit(0);
	}
	if((opt_status&4) == 0){
		fprintf(stderr,"warning: incomplete argument training file not read.\n");
	}
	if((opt_status&8) == 0){
		fprintf(stderr,"warning: incomplete argument initial cluster file not read.\n");
	}
	if((opt_status&16) == 0){
		fprintf(stderr,"warning: no specific output file, result not printed.\n");
	}
	/* (* read training data */
	if((opt_status&4) == 4){
		if((IN = fopen(opt.training_file_name,"r")) == NULL){
			perror(opt.training_file_name);
			exit(1);
		}
		/* (* read format */
		if((opt.training_file_format&1) == 1){
			fscanf(IN,"%d",&opt.column_train);
			fscanf(IN,"%d",&opt.row_train);
		}
		if((opt.column_train * opt.row_train) <= 0){
			printf("check training matrix size\n");
			exit(0);
		}
		/* *) */
		/* (*for training data */
		column_train = opt.column_train;
		row_train = opt.row_train;
		matrix_train = f_alloc_mat(row_train,column_train);
		stat_train = alloc_status_train(row_train,MAX_LEN_STR);
		/* *) */
		/* (* read training data */
		if((opt.training_file_format&2) == 2){
			read_train_ID_property_ftable_from_stream(row_train,column_train,IN,matrix_train,stat_train);
		}else{
			read_train_property_ftable_from_stream(row_train,column_train,IN,matrix_train,stat_train);
		}
		/* *) */
		fclose(IN);
	}
	/* *) */
	/* (* read initial cluster data */
	if((opt_status&8) == 8){
		if((IN = fopen(opt.cluster_file_name,"r")) == NULL){
			perror(opt.cluster_file_name);
			exit(1);
		}
		/* (* read format */
		if((opt.cluster_file_format&1) == 1){
			fscanf(IN,"%d",&opt.column_cluster);
			fscanf(IN,"%d",&opt.row_cluster);
		}
		if((opt.column_cluster * opt.column_cluster) <= 0){
			printf("check cluster matrix size\n");
			exit(0);
		}
		/* *) */
		/* (* initialize for cluster data */
		column_cluster = opt.column_cluster;
		row_cluster = opt.row_cluster;
		matrix_cluster = f_alloc_mat(row_cluster * opt.cluster_expand,column_cluster);
		stat_cluster = alloc_status_cluster(row_cluster * opt.cluster_expand,MAX_LEN_STR,MAX_LEN_STR);
		/* *) */
		/* (* read cluster data */
		if((opt.cluster_file_format&2) == 2){
			read_cluster_ID_property_ftable_from_stream(row_cluster,column_cluster,IN,matrix_cluster,stat_cluster);
		}else{
			read_cluster_property_ftable_from_stream(row_cluster,column_cluster,IN,matrix_cluster,stat_cluster);
		}
		/* *) */

	}
	/* *) */
	/* (* check */
	if((opt_status&1) == 1){
		print_option_train(opt);
		exit(0);
	}
	/* *) */

	/* *( training */
	/* UNDER CONSTRUCTION */
	training_loop(opt,stat_cluster,&row_cluster,column_cluster,matrix_cluster,stat_train,row_train,column_train,matrix_train);

	/* (* test */
	//printf("row_cluster :%d:\n",row_cluster);
	/* *) */
	/* *) */

	/* (* file output */
	if((opt_status&16) == 16){
		OUT = fopen(opt.output_file_name,"w");
		if((opt.output_file_format&1) == 1){	/* with size */
			fprintf(OUT,"%d %d\n",column_cluster,row_cluster);
		}
		if((opt.output_file_format&2) == 2){	/* with ID */
			for(i=0;i<row_cluster;i++){
				fprintf(OUT,"%d %d",i,stat_cluster[i].property_this_cluster);
				for(j=0;j<column_cluster;j++){
					fprintf(OUT," %f",matrix_cluster[i][j]);
				}
				fprintf(OUT,"\n");
			}
		}else{
			for(i=0;i<row_cluster;i++){
				fprintf(OUT,"%d",-1);
				for(j=0;j<column_cluster;j++){
					fprintf(OUT," %f",matrix_cluster[i][j]);
				}
				fprintf(OUT,"\n");
			}
		}
		fclose(OUT);
	}
	/* *) */
	return(0);
}
