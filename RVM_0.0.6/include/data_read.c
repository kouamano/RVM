/* data_read.c */

/*************************************************/
/* Copyright (c) 2003-2005 AMANO Kou             */
/* University of Tsukuba                         */
/* University of Liblary And Information Science */
/* National Institute of Agrobilogical Sciences  */
/* kamano@affrc.go.jp                            */
/*************************************************/

#ifndef IDSIZE
#define IDSIZE 1025
#endif

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
}

int read_ID_ftable_from_stream(int num, int dim, FILE *stream, float **table, char **IDs){
	int i;
	int j;
	float ftmp;
	char ctmp[IDSIZE];
	for(i=0;i<num;i++){
		fscanf(stream,"%s",ctmp);
		strcpy(IDs[i],ctmp);
		for(j=1;j<dim+1;j++){
			fscanf(stream,"%f",&ftmp);
			table[i][j-1] = ftmp;
		}
	}
	return(0);
}

int read_ftable_from_stdin(int num, int dim, float **table){
	int i;
	int j;
	float ftmp;
	for(i=0;i<num;i++){
		for(j=0;j<dim;j++){
			scanf("%f",&ftmp);
			table[i][j] = ftmp;
		}
	}
	return(0);
}

int read_ID_ftable_from_stdin(int num, int dim, float **table, char **IDs){
	int i;
	int j;
	float ftmp;
	char ctmp[IDSIZE];
	for(i=0;i<num;i++){
		scanf("%s",ctmp);
		strcpy(IDs[i],ctmp);
		for(j=1;j<dim+1;j++){
			scanf("%f",&ftmp);
			table[i][j-1] = ftmp;
		}
	}
	return(0);
}

int read_ilist_from_stream(int num, FILE *stream, int *list){
	int i;
	int itmp;
	for(i=0;i<num;i++){
		fscanf(stream,"%d",&itmp);
		list[i] = itmp;
	}
	return(0);
}

int read_ilist_from_stdin(int num, int *list){
	int i;
	int itmp;
	for(i=0;i<num;i++){
		scanf("%d",&itmp);
		list[i] = itmp;
	}
	return(0);
}

