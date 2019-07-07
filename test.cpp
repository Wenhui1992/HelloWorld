
#include "matrix.h"
#include <iostream>

void Print(const matrix& mat)
{
    UINT m=mat.GetRowCount();
    UINT n=mat.GetColCount();
    MATDATA fData=0;
    MATRET mRet=RET_OK;
    printf("matrix: nRow=%d\t nCol=%d\n",m,n);
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            mRet=mat.GetElement(i,j,fData);
            printf("\t%f",fData);
        }
        printf("\n");
    }
}

void PrintE(const MATRET& ret)
{
    switch (ret)
    {
    case RET_OK:
        printf("function return RET_OK\n");
        break;
    case RET_NOT_COL_MATCH:
        printf("function return RET_NOT_COL_MATCH\n");
        break;
    case RET_NOT_ROW_MATCH:
        printf("function return RET_NOT_ROW_MATCH\n");
        break;
    case RET_INDEX_NOT_IN_COL:
        printf("function return RET_INDEX_NOT_IN_COL\n");
        break;
    case RET_INDEX_NOT_IN_ROW:
        printf("functon return RET_INDEX_NOT_IN_ROW\n");
        break;
    case  RET_PARAM_POINT_NULL:
        printf("functon return RET_PARAM_POINT_NULL\n");
        break;
    case RET_PARAM_POINT_NOT_NULL:
        printf("functon return RET_PARAM_POINT_NOT_NULL\n");
        break;
    case RET_NOT_ENOUGH_MEMERY:
        printf("functon return RET_NOT_ENOUGH_MEMERY\n");
        break;
    default:
        break;
    }
}

int main()
{
   int m=2,n=3;
    matrix mat1(m,n);
    PrintE(mat1.SetElement(1,2,1.2));
    MATDATA* row=new MATDATA(n);
    row[0]=2.0;row[1]=3.0;row[2]=2.3;
    PrintE(mat1.SetRowData(0,row,n));
    MATDATA* col=new MATDATA(m);
    col[0]=5.0;col[1]=6.0;
    PrintE(mat1.SetColData(2,col,m));
    printf("\n*****************mat1*****************\n");
    Print(mat1);

    printf("\n*****************mat2*****************\n");
    matrix* mat2=NULL;
    matrix::GetUnitMatrix(3,&mat2);
	Print(*mat2);
	row[0]=2.0;
	mat1.AppendRow(row,n);
	printf("\n*****************mat1.AppendRow*****************\n");
	Print(mat1);
	
	matrix*pmat3=NULL;
	matrix::CombineMatrixH(mat1,*mat2,&pmat3);
	if(NULL==pmat3)
		printf("\n*****************mat3,null*****************\n");
	else
	{
		printf("\n*****************mat3*****************\n");
		Print(*pmat3);
	}
	matrix*pmat4=NULL;
	matrix::CombineMatrixV(mat1,*mat2,&pmat4);
	if(NULL==pmat3)
		printf("\n*****************mat4,null*****************\n");
	else
	{
		printf("\n*****************mat4*****************\n");
		Print(*pmat4);
	}
	//delete mat2;
	delete[] row;
	delete[] col;
	
    return 0;
}
