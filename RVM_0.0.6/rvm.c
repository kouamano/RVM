/*************************************************/
/*          RVM - Region Vector Machine          */
/* Copyright (c) 2005 AMANO Kou                  */
/* National Institute of Agrobiological Scences  */
/* School of Libarary and Information Science    */
/* University of Tsukuba                         */
/*                           kamano@affrc.go.jp  */
/*************************************************/

/* rvm.c */

/* version information       */
/* definitions of structure, */
/* structure operations,     */
/* tensor operations,        */
/* input/output functions.   */

static char    head[128] = {"                "};
static char     bar[128] = {"-------------------------------------\n"};
static char version[128] = {"   Version 0.0.6 @ 2005.11.08 JST    \n"};
static char   title[128] = {"    RVM -- Region Vector Machine     \n"};
static char  author[128] = {" by AMANO Kou @ NIAS / Univ. Tsukuba \n"};

struct integer_count {
	int v;
	int count;
};

struct integer_count *alloc_integer_count(int size){
	struct integer_count *p;
	if((p = calloc(sizeof(struct integer_count),size)) == NULL){
		printf("failed: calloc in alloc_integer_count().\n");
		exit(1);
	}
	return(p);
};

struct position_value {
	int position;
	float value;
};

struct position_value *alloc_position_value(int size){
	int i;
	struct position_value *p;
	if((p = malloc(sizeof(struct position_value) * size)) == NULL){
		printf("failed: calloc in alloc_position_value().\n");
		exit(1);
	}
	return(p);
};

int print_position_value(int size, struct position_value *p_v, char *format, char *caption, int conjugate){
	int i;
	if(conjugate > 0){
		printf(OFS"\n");
	}
	printf(BRKT_START);
	printf("%s%s%s",CAP_BRKT_START,caption,CAP_BRKT_END);
	printf("%s\n%s%d%s%f%s",OFS,BRKT_START,p_v[0].position,OFS,p_v[0].value,BRKT_END);
	for(i=1;i<size;i++){
		printf("%s%s%d%s%f%s",OFS,BRKT_START,p_v[i].position,OFS,p_v[i].value,BRKT_END);
	}
	printf(BRKT_END);
	return(0);
};

int print_f_mat(int size_row, int size_column, float **mat, char *format, char *caption, int conjugate){
	int i;
	int j;
	if(conjugate > 0){
		printf(OFS"\n");
	}
	printf(BRKT_START);
	printf("%s%s%s",CAP_BRKT_START,caption,CAP_BRKT_END);
	for(i=0;i<size_row;i++){
		printf(OFS);
		printf("\n");
		printf(BRKT_START);
		printf("%f",mat[i][0]);
		for(j=1;j<size_column;j++){
			printf(OFS);
			printf("%f",mat[i][j]);
		}
		printf(BRKT_END);
	}
	printf(BRKT_END);
	return(0);
};

struct status_train {
	char *ID;
	int property;
};

struct status_train *alloc_status_train(int size, int size_ID){
	int i;
	struct status_train *p;
	if((p = malloc(sizeof(struct status_train) * size)) == NULL){
		printf("failed: malloc in alloc_status_train().\n");
		exit(1);
	}
	for(i=0;i<size;i++){
		if((p[i].ID = malloc(sizeof(char) * size_ID)) == NULL){
			printf("failed: malloc in alloc_status_train().\n");
			exit(1);
		}
		p[i].ID[0] = '\0';
		p[i].property = 0;
	}
	return(p);
};

struct status_cluster {
	char *ID;
	int decided;
	int property_this_cluster;
	int num_property;
	int **freq_property;			/* num_property * 2 */
	int num_total_sample;
	int *SN_total_sample;
	int num_positive_sample;
	int *SN_positive_sample;
	int num_negative_sample;
	double *coordinate_this_cluster;	/* column */
	double *centroid_positive_sample;	/* column */
};

struct status_cluster *alloc_status_cluster(int size, int size_vector, int size_ID){
	int i;
	struct status_cluster *p;
	if((p = malloc(sizeof(struct status_cluster) * size)) == NULL){
		printf("failed: malloc in alloc_status_cluster().\n");
		exit(1);
	}
	for(i=0;i<size;i++){
		if((p[i].ID = malloc(sizeof(char) * size_ID)) == NULL){
			printf("failed: calloc in alloc_status_cluster().\n");
			exit(1);
		}
		p[i].ID[0] = '\0';
		p[i].decided = 0;
		p[i].property_this_cluster = -1;
		p[i].num_property = 0;
		p[i].freq_property = NULL;
		p[i].num_total_sample = 0;
		p[i].SN_total_sample = NULL;
		p[i].num_positive_sample = 0;
		p[i].SN_positive_sample = NULL;
		p[i].num_negative_sample = 0;
		if((p[i].coordinate_this_cluster = calloc(sizeof(double),size_vector)) == NULL){
			fprintf(stderr,"failed: calloc() in alloc_status_cluster().\n");
			exit(1);
		}
		if((p[i].centroid_positive_sample = calloc(sizeof(double),size_vector)) == NULL){
			fprintf(stderr,"failed: calloc() in alloc_status_cluster().\n");
			exit(1);
		}
	}
	fprintf(stderr,"warning: member freq_property::matrix is not allocated yet.\n");
	fprintf(stderr,"warning: member SN_total_sample::vector is not allocated yet.\n");
	fprintf(stderr,"warning: member SN_positive_sample::vector is not allocated yet.\n");
	return(p);
};

int print_status_cluster(int conjugate, int column_cluster, int row_cluster, struct status_cluster *status_cluster, int level){
	int j;
	int k;
	int l;
	if(conjugate > 0){
		printf(OFS);
	}
	printf(BRKT_START OLS);
	for(j=0;j<row_cluster;j++){
		printf(OFS BRKT_START);
		for(k=0;k<15;k++){
			if((level&1) == (int)pow(2,k)){
				printf("%d",j);
			}
			if((level&2) == (int)pow(2,k)){
				printf("\"ID:%s\"",status_cluster[j].ID);
			}
			if((level&4) == (int)pow(2,k)){
				printf("%d",status_cluster[j].decided);
			}
			if((level&8) == (int)pow(2,k)){
				printf("%d",status_cluster[j].property_this_cluster);
			}
			if((level&16) == (int)pow(2,k)){
				printf("%d",status_cluster[j].num_property);
			}
			if((level&32) == (int)pow(2,k)){
				if(status_cluster[j].freq_property == NULL){
					printf(NULL_ELEMENT);
				}else{
					printf(BRKT_START);
					for(l=0;l<status_cluster[j].num_property;l++){
						printf("%d,%d",status_cluster[j].freq_property[l][0],status_cluster[j].freq_property[l][1]);
					}
					printf(BRKT_END);
				}
			}
			if((level&64) == (int)pow(2,k)){
				printf("%d",status_cluster[j].num_total_sample);
			}
			if((level&128) == (int)pow(2,k)){
				if(status_cluster[j].SN_total_sample == NULL){
					printf(NULL_ELEMENT);
				}else{
					printf(BRKT_START);
					printf("%d",status_cluster[j].SN_total_sample[0]);
					for(l=1;l<status_cluster[j].num_total_sample;l++){
						printf(OFS "%d",status_cluster[j].SN_total_sample[l]);
					}
					printf(BRKT_END);
				}
			}
			if((level&256) == (int)pow(2,k)){
				printf("%d",status_cluster[j].num_positive_sample);
			}
			if((level&512) == (int)pow(2,k)){
				if(status_cluster[j].SN_positive_sample == NULL){
					printf(NULL_ELEMENT);
				}else{
					printf(BRKT_START);
					printf("%d",status_cluster[j].SN_positive_sample[0]);
					for(l=1;l<status_cluster[j].num_positive_sample;l++){
						printf(OFS "%d",status_cluster[j].SN_positive_sample[l]);
					}
					printf(BRKT_END);
				}
			}
			if((level&1024) == (int)pow(2,k)){
				printf("%d",status_cluster[j].num_negative_sample);
			}
			if((level&2048) == (int)pow(2,k)){
				if(status_cluster[j].coordinate_this_cluster == NULL){
					printf(NULL_ELEMENT);
				}else{
					printf(BRKT_START);
					printf("%f",status_cluster[j].coordinate_this_cluster[0]);
					for(l=1;l<column_cluster;l++){
						printf(OFS "%f",status_cluster[j].coordinate_this_cluster[l]);
					}
					printf(BRKT_END);
				}
			}
			if((level&4096) == (int)pow(2,k)){
				if(status_cluster[j].centroid_positive_sample == NULL){
					printf(NULL_ELEMENT);
				}else{
					printf(BRKT_START);
					printf("%f",status_cluster[j].centroid_positive_sample[0]);
					for(l=1;l<column_cluster;l++){
						printf(OFS "%f",status_cluster[j].centroid_positive_sample[l]);
					}
					printf(BRKT_END);
				}
			}
			printf(OFS);
		}
		printf(BRKT_END OLS);
	}
	printf(BRKT_END);
	return(0);
}

int uni_alloc_status_cluster__SN_total_sample(int size_member, int size_cluster, struct status_cluster *stat_cluster){
	int j;
	for(j=0;j<size_cluster;j++){
		if((stat_cluster[j].SN_total_sample = malloc(sizeof(int) * size_member)) == NULL){
			fprintf(stderr,"failed malloc() in uni_alloc_status_cluster_SN_total_sample\n.");
			exit(1);
		}
	}
	return(0);
}

int prop_counter(int row_train, struct status_train *stat_train, struct integer_count *i_count){
	int i;
	int j;
	int exist = 0;
	int pointer = 0;
	i_count[0].v = stat_train[0].property;
	i_count[0].count++;
	for(i=1;i<row_train;i++){
		exist = 0;
		for(j=0;j<=pointer;j++){
			if(stat_train[i].property == i_count[j].v){
				i_count[j].count++;
				exist++;
			}
		}
		if(exist == 0){
			pointer++;
			i_count[pointer].v = stat_train[i].property;
			i_count[pointer].count++;
		}
	}
	pointer++;
	return(pointer);
};

int register_SN_positive_sample(struct status_cluster *stat_cluster, int size_stat_train, struct status_train *stat_train){	/* one by one */
	int i = 0;
	int pointer = 0;
	for(i=0;i<size_stat_train;i++){
		if(stat_cluster->property_this_cluster == stat_train[i].property){
			stat_cluster->SN_positive_sample[pointer] = i;
			pointer++;
		}
	}
	return(0);
};

int register_centroid_positive_sample(struct status_cluster *stat_cluster, int row_train, int column_train, float **mat_train){	/* one by one */
	int i = 0;
	int j = 0;
	for(i=0;i<stat_cluster->num_positive_sample;i++){
		for(j=0;j<column_train;j++){
			stat_cluster->centroid_positive_sample[j] = stat_cluster->centroid_positive_sample[j] + mat_train[stat_cluster->SN_positive_sample[i]][j];
		}
	}
	for(j=0;j<column_train;j++){
		stat_cluster->centroid_positive_sample[j] = stat_cluster->centroid_positive_sample[j] / stat_cluster->num_positive_sample;
	}
	return(0);
};

int read_ftable_from_stream(int num, int dim, FILE *stream, float **table){
        int i;
        int j;
        float ftmp;
        for(i=0;i<num;i++){
                for(j=0;j<dim;j++){
                        fscanf(stream,"%f",&ftmp);
                        table[i][j] = ftmp;
                }
        }
        return(0);
};

int read_ID_ftable_from_stream(int num, int dim, FILE *stream, float **table, char **IDs){
        int i;
        int j;
        float ftmp;
        char ctmp[MAX_LEN_STR];
        for(i=0;i<num;i++){
                fscanf(stream,"%s",ctmp);
                strcpy(IDs[i],ctmp);
                for(j=1;j<dim+1;j++){
                        fscanf(stream,"%f",&ftmp);
                        table[i][j-1] = ftmp;
                }
        }
        return(0);
};

int read_train_property_ftable_from_stream(int num, int dim, FILE *stream, float **table, struct status_train *prp){
        int i;
        int j;
        float ftmp;
	int vtmp;
        for(i=0;i<num;i++){
                sprintf(prp[i].ID,"%d",i);
                fscanf(stream,"%d",&vtmp);
		prp[i].property = vtmp;
                for(j=2;j<dim+2;j++){
                        fscanf(stream,"%f",&ftmp);
                        table[i][j-2] = ftmp;
                }
        }
        return(0);
};

int read_train_ID_property_ftable_from_stream(int num, int dim, FILE *stream, float **table, struct status_train *prp){
        int i;
        int j;
        float ftmp;
        char ctmp[MAX_LEN_STR];
	int vtmp;
        for(i=0;i<num;i++){
                fscanf(stream,"%s",ctmp);
                strcpy(prp[i].ID,ctmp);
                fscanf(stream,"%d",&vtmp);
		prp[i].property = vtmp;
                for(j=2;j<dim+2;j++){
                        fscanf(stream,"%f",&ftmp);
                        table[i][j-2] = ftmp;
                }
        }
        return(0);
};

int read_cluster_property_ftable_from_stream(int num, int dim, FILE *stream, float **table, struct status_cluster *prp){
        int i;
        int j;
        float ftmp;
	int vtmp;
        for(i=0;i<num;i++){
                sprintf(prp[i].ID,"%d",i);
                fscanf(stream,"%d",&vtmp);
		prp[i].property_this_cluster = vtmp;
                for(j=2;j<dim+2;j++){
                        fscanf(stream,"%f",&ftmp);
                        table[i][j-2] = ftmp;
                }
        }
        return(0);
};

int read_cluster_ID_property_ftable_from_stream(int num, int dim, FILE *stream, float **table, struct status_cluster *prp){
        int i;
        int j;
        float ftmp;
        char ctmp[MAX_LEN_STR];
	int vtmp;
        for(i=0;i<num;i++){
                fscanf(stream,"%s",ctmp);
                strcpy(prp[i].ID,ctmp);
                fscanf(stream,"%d",&vtmp);
		prp[i].property_this_cluster = vtmp;
                for(j=2;j<dim+2;j++){
                        fscanf(stream,"%f",&ftmp);
                        table[i][j-2] = ftmp;
                }
        }
        return(0);
};

float *min_to_max_list(int fraction, float min, float max){
        int i = 0;
        int j = 0;
        int cut = 0;
        float segment_size = 1;
        float length = 1;
        float *out_list = NULL;
        cut = fraction*2;
        length = max - min;
        segment_size = length / cut;
        out_list = f_alloc_vec(fraction);
        j = 0;
        for(i=1;i<cut;i+=2){
                out_list[j] = min + segment_size * i;
                j++;
        }
        return(out_list);
};

float **get_table_distance_cluster_train(int row_cluster, int column_cluster, float **mat_cluster, int row_train, int column_train, float **mat_train){
	int i;
	int j;
	float **out;
	out = f_alloc_mat(row_cluster,row_train);
	for(i=0;i<row_cluster;i++){
		for(j=0;j<row_train;j++){
			out[i][j] = euc_dist(column_train,mat_cluster[i],mat_train[j]);
		}
	}
	return(out);
};

struct position_value *find_nearest_cluster(int row_cluster, int row_train, float **table_distance_cluster_train){
	struct position_value *p;
	int i;
	int j;
	p = alloc_position_value(row_train);
	for(j=0;j<row_train;j++){
		p[j].position = 0;
		p[j].value = table_distance_cluster_train[0][j];
	}
	for(i=0;i<row_cluster;i++){
		for(j=1;j<row_train;j++){
			if(table_distance_cluster_train[i][j] < p[j].value){
				p[j].position = i;	/* cluster No. */
				p[j].value = table_distance_cluster_train[i][j];	/* euclide distance */
			}
		}
	}
	return(p);
};

/* (* UNDER CONSTRUCTION */
int register_nearest_cluster(int column_cluster, int row_cluster, int row_train, struct position_value *p_v, struct status_cluster *stat_cluster){
	int j;
	int k;
	for(j=0;j<row_cluster;j++){
		stat_cluster[p_v[j].position].num_total_sample = 0;
	}
	for(j=0;j<row_train;j++){
		stat_cluster[p_v[j].position].SN_total_sample[stat_cluster[p_v[j].position].num_total_sample] = j;
		stat_cluster[p_v[j].position].num_total_sample++;
		/* TODO: */
	}
	return(0);
};
/* *) */

#ifdef RVM_INIT
int *get_tensor_dim_rank(const int rank, char *str){
        int i = 0;
        int j = 0;
        int k = 0;
        int *dim = NULL;
        int local_rank = 0;
        int len = 0;
        char tmp_c[MAX_LEN_STR];
        int tmp = 0;
        len = strlen(str);
        for(i=0;i<len;i++){
                if(str[i] == ','){
                        local_rank++;
                }
        }
        local_rank++;
        if(local_rank > rank){
                printf("local_rank:%d\n",local_rank);
                printf("the tensor rank exceeded dimensions of cluster.\n");
                exit(1);
        }
        if((dim = malloc(sizeof(int)*(rank))) == NULL){
                printf("malloc error.\n");
                exit(1);
        }
        j = 0;
        k = 0;
        for(i=0;i<len;i++){
                if(str[i] != ','){
                        tmp_c[j] = str[i];
                        j++;
                }else{
                        tmp_c[j] = '\0';
                        sscanf(tmp_c,"%d",&tmp);
                        dim[k] = tmp;
                        k++;
                        j = 0;
                }
        }
        tmp_c[j] = '\0';
        sscanf(tmp_c,"%d",&tmp);
        dim[k] = tmp;
        k++;
        for(i=k;i<rank;i++){
                dim[i] = 1;
        }
        return(dim);
};

int **tensor_position_matrix(int rank, int *num, int *dim){
        int i = 0;
        int j = 0;
        int *prod = NULL;
        int elm = 0;
        int tmp = 0;
        float f = 0;
        int **out_mat = NULL;
        if((prod = malloc(sizeof(int)*(rank+1))) == NULL){
                printf("malloc error.\n");
                exit(1);
        }
        elm = 1;
        for(i=0;i<rank;i++){
                elm = dim[i] * elm; } out_mat = i_alloc_mat(elm,rank);
        j = 1;
        tmp = 1;
        prod[0] = 1;
        for(i=1;i<rank;i++){
                tmp = tmp * dim[i-1];
                prod[j] = tmp;
                j++;
        }
        for(i=0;i<elm;i++){
                for(j=0;j<rank;j++){
                        f = (float)i/prod[j];
                        out_mat[i][j] = ((int)f)%dim[j];
                }
        }
        *num = elm;
        return(out_mat);
};
#endif

#ifdef RVM_TRAIN
int training_loop(struct option_train opt, struct status_cluster *stat_cluster, int *row_cluster_fixed, int column_cluster, float **matrix_cluster, struct status_train *stat_train, int row_train, int column_train, float **matrix_train){
	int i = 0;
	int j = 0;
	int k = 0;
	float **table_distance_cluster_train = NULL;
	int r = opt.loop;
	int de = 0;
	struct position_value *position_distance;
	if(opt.loop == 0){
		de = 0;
	}else if(opt.loop > 0){
		de = 1;
	}
	printf(BRKT_START);
	printf(CAP_BRKT_START"training-loop"CAP_BRKT_END);
	uni_alloc_status_cluster__SN_total_sample(MAX_MEMBER,opt.row_cluster * opt.cluster_expand,stat_cluster);
	for(r=opt.loop-1;r>=0;){
		printf("\n"OFS BRKT_START CAP_BRKT_START"loop"CAP_BRKT_END OFS"%d"BRKT_END,r);
		table_distance_cluster_train = get_table_distance_cluster_train(*row_cluster_fixed,column_cluster,matrix_cluster,row_train,column_train,matrix_train);
		/* (* test */
		print_f_mat(*row_cluster_fixed,row_train,table_distance_cluster_train,"LIST","table_distance_cluster_train",1);
		/* *) */
		position_distance = find_nearest_cluster(*row_cluster_fixed,row_train,table_distance_cluster_train);
		print_position_value(row_train,position_distance,"LIST","position_distance",1);
		/* (* UNDER CONSTRUCTION */
		register_nearest_cluster(column_cluster,*row_cluster_fixed,row_train,position_distance,stat_cluster);
		print_status_cluster(1,column_cluster,*row_cluster_fixed,stat_cluster,1+2+4+8+16+32+64+128+256+512+1024+4096);
		/* *) */

		r = r - de;
	}
	printf(BRKT_END"\n");
	return(0);
};
#endif
