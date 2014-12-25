/* alloc.c */

/*************************************************/
/* Copyright (c) 2003-2005 AMANO Kou             */
/* University of Tsukuba                         */
/* University of Liblary And Information Science */
/* National Institute of Agrobilogical Sciences  */
/* kamano@affrc.go.jp                            */
/*************************************************/

char **c_alloc_mat(int num, int dim){
	char **c;
	int i;
	if((c = malloc((size_t)sizeof(char *)*(num+1))) == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	if((c[0] = malloc((size_t)sizeof(char)*(num*dim+dim))) == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	for(i=1;i<num;i++){
		c[i] = c[i-1]+dim;
	}
	return(c);
}

float **f_alloc_mat(int num, int dim){
	float **m;
	int i;
	if((m = malloc((size_t)sizeof(float*)*(num+1))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	if((m[0] = malloc((size_t)sizeof(float)*(num*dim+dim))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	for(i=1;i<num;i++){
		m[i] = m[i-1]+dim;
	}
	return(m);
}

float *f_alloc_vec(int num){
	float *v;
	if((v = malloc((size_t)sizeof(float)*(num+1))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	return(v);
}

int **i_alloc_mat(int num, int dim){
	int **m;
	int i;
	if((m = malloc((size_t)sizeof(int*)*(num+1))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	if((m[0] = malloc((size_t)sizeof(int)*(num*dim+dim))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	for(i=1;i<num;i++){
		m[i] = m[i-1]+dim;
	}
	return(m);
}

int *i_alloc_vec(int num){
	int *v;
	if((v = malloc((size_t)sizeof(int)*(num+1))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	return(v);
}

float **f_calloc_mat(int num, int dim){
	float **m;
	int i;
	if((m = calloc((size_t)sizeof(float*),(num+1))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	if((m[0] = calloc((size_t)sizeof(float),(num*dim+dim))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	for(i=1;i<num;i++){
		m[i] = m[i-1]+dim;
	}
	return(m);
}

float *f_calloc_vec(int num){
	float *v;
	if((v = calloc((size_t)sizeof(float),(num+1))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	return(v);
}

int **i_calloc_mat(int num, int dim){
	int **m;
	int i;
	if((m = calloc((size_t)sizeof(int*),(num+1))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	if((m[0] = calloc((size_t)sizeof(int),(num*dim+dim))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	for(i=1;i<num;i++){
		m[i] = m[i-1]+dim;
	}
	return(m);
}

int *i_calloc_vec(int num){
	int *v;
	if((v = calloc((size_t)sizeof(int),(num+1))) == NULL){
		printf("failed : malloc(), exit.\n");
		exit(1);
	}
	return(v);
}

float **f_calloc_triangle(int dim){
	float **ff;
	int i;
	dim = dim + 1;
	if((ff = calloc((size_t)sizeof(float *),dim)) == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(1);
	}
	for(i=0;i<dim;i++){
		if((ff[i] = calloc((size_t)sizeof(float),i+1)) == NULL){
			printf("failed : malloc() -- exit.\n");
			exit(1);
		}
	}
	return(ff);
}
