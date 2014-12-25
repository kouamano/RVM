#define NR_END 1

int *i_alloc_list(long m){
	int *l;
	l = malloc((size_t)((m+NR_END)*sizeof(int)));
	if(l == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(1);
	}
	return(l);
}

long *l_alloc_list(long m){
	long *l;
	l = malloc((size_t)((m+NR_END)*sizeof(long)));
	if(l == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(1);
	}
	return(l);
}

float *f_alloc_list(long m){
	float *l;
	l = malloc((size_t)((m+NR_END)*sizeof(float)));
	if(l == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(1);
	}
	return(l);
}

float *f_clear_alloc_list(long m){
	float *l;
	l = calloc((size_t)(m+NR_END),(size_t)sizeof(float));
	if(l == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(1);
	}
	return(l);
}

double *d_alloc_list(long m){
	double *l;
	l = malloc((size_t)((m+NR_END)*sizeof(double)));
	if(l == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(1);
	}
	return(l);
}

int **i_alloc_matrix(long nrh, long nch){
	long i;
	long nrow = nrh+1;
	long ncol = nch+1;
	int **m;
	m = malloc((size_t)((nrow+NR_END)*sizeof(int*)));
	if(m == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m+=NR_END;
	m[0] = malloc((size_t)((nrow*ncol+NR_END)*sizeof(int)));
	if(m[0] == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m[0]+=NR_END;
	for(i=0+1;i<=nrh;i++){
		m[i] = m[i-1]+ncol;
	}
	return m;
}

char **s_alloc_list(long num, long len){
	char **s;
	int i;
	len = len + 1;
	if((s = malloc((size_t)sizeof(char *)*num)) == NULL){
		printf("failed : malloc() -- eixt.\n");
		exit(1);
	}
	for(i=0;i<len;i++){
		if((s[i] = malloc((size_t)sizeof(char)*len)) == NULL){
			printf("failed malloc() -- exit.\n");
		}
	}
	return(s);
}

char ***s_alloc_matrix(long len, long nrh, long nch){
	long i;
	long nrow = nrh+1;
	long ncol = nch+1;
	char ***s;
	s = malloc((size_t)((nrow+NR_END)*sizeof(char**)));
	if(s == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	s+=NR_END;
	s[0] = malloc((size_t)((nrow*ncol*len+NR_END)*sizeof(char)));
	if(s[0] == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	s[0]+=NR_END;
	for(i=0+1;i<=nrh;i++){
		s[i] = s[i-1]+ncol*len;
	}
	return s;
}

int **i_clear_alloc_matrix(long nrh, long nch){
	long i;
	long nrow = nrh+1;
	long ncol = nch+1;
	int **m;
	m = malloc((size_t)((nrow+NR_END)*sizeof(int*)));
	if(m == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m+=NR_END;
	m[0] = calloc((size_t)(nrow*ncol+NR_END),(size_t)sizeof(int));
	if(m[0] == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m[0]+=NR_END;
	for(i=0+1;i<=nrh;i++){
		m[i] = m[i-1]+ncol;
	}
	return m;
}

float **f_clear_alloc_matrix(long nrh, long nch){
	long i;
	long nrow = nrh+1;
	long ncol = nch+1;
	float **m;
	m = malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if(m == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m+=NR_END;
	m[0] = calloc((size_t)(nrow*ncol+NR_END),(size_t)sizeof(float));
	if(m[0] == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m[0]+=NR_END;
	for(i=0+1;i<=nrh;i++){
		m[i] = m[i-1]+ncol;
	}
	return m;
}

float **f_clear_alloc_triangle(long dim){
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

double **d_alloc_matrix(long nrh, long nch){
	long i;
	long nrow = nrh+1;
	long ncol = nch+1;
	double **m;
	m = malloc((size_t)((nrow+NR_END)*sizeof(double*)));
	if(m == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m+=NR_END;
	m[0] = malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
	if(m[0] == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m[0]+=NR_END;
	for(i=0+1;i<=nrh;i++){
		m[i] = m[i-1]+ncol;
	}
	return m;
}

float **f_alloc_matrix(long nrh, long nch){
	long i;
	long nrow = nrh+1;
	long ncol = nch+1;
	float **m;
	m = malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if(m == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m+=NR_END;
	m[0] = malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
	if(m[0] == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m[0]+=NR_END;
	for(i=0+1;i<=nrh;i++){
		m[i] = m[i-1]+ncol;
	}
	return m;
}

float **alloc_matrix(long nrl, long nrh, long ncl, long nch){
	long i;
	long nrow = nrh-nrl+1;
	long ncol = nch-ncl+1;
	float **m;
	m = malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if(m == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m+=NR_END;
	m-=nrl;
	m[nrl] = malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
	if(m[nrl] == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	m[nrl]+=NR_END;
	m[nrl]-=ncl;
	for(i=nrl+1;i<=nrh;i++){
		m[i] = m[i-1]+ncol;
	}
	return m;
}
